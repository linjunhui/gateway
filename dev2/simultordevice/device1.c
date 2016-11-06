#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#pragma pack(1)
struct attr_data {
	//属性名 占11字节
	char attr_name[13];
	//属性 性质 （读，写，可读可写） 占1个字节
	char property;
	//属性值 4个字节
	int data;
	//属性值的倍数 占4个字节
	int times;
};

#pragma pack(1)
typedef struct device_link
{
	//设备id 占4个字节
	unsigned int device_ip;

	//设备名字 占 22 个字节
	char name[22];

	//设备ID 占 9个字节
	char device_id[9];

	//是否绑定了 网关 1个字节
	char locked;

	//设备是否在线, 在设备中只是为了对齐使用
	char online;

	//绑定的网关ID 13 
	char gate_id[13];

	//定义 设备的 10个参数参数

	struct attr_data attrs[10];

	struct device_link * pNext;
} device, *pdevice;


int main(int argc, char const *argv[])
{	
	int sockfd;
	int udpsockfd;
	struct sockaddr_in addr, c_addr, d_addr;
	int on = 1, len, c_addr_len, addr_len, err;

	char buf[300];
//========================UDP广播=============================
	//创建UDP socket
	udpsockfd = socket(AF_INET,SOCK_DGRAM,0);
	printf("创建UDP socket结果%s \n", strerror(errno));
	//本设备UDP端口
	memset(&d_addr,0,sizeof(d_addr));
	d_addr.sin_family = AF_INET;
	d_addr.sin_addr.s_addr = INADDR_ANY;
	d_addr.sin_port = htons(7576);	
	addr_len=sizeof(d_addr);

	//客户端地址
	memset(&c_addr,0,sizeof(c_addr));
	c_addr.sin_family = AF_INET;
	c_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST); 
	c_addr.sin_port = htons(7575);	
	c_addr_len=sizeof(c_addr);

	setsockopt(udpsockfd,SOL_SOCKET, SO_BROADCAST,&on,sizeof(on));

	//绑定socket 和 地址
	err = bind(udpsockfd, (struct sockaddr *)&d_addr, sizeof(d_addr));
	printf("UDP绑定结果%s\n", strerror(err));

		//发送消息
	len = sendto(udpsockfd, "buf", 50, 0, (struct sockaddr*)&c_addr, c_addr_len);
	printf("UDP发送%s \n", strerror(errno));
	printf("len = %d\n", len);
	printf("发送消息\n");

	//阻塞在这里接受消息
	len = recvfrom(udpsockfd, buf, 50, 0, (struct sockaddr*)&c_addr, &c_addr_len);
	printf("UDP接收%s \n", strerror(errno));
	//printf("收到消息:%s\n", buf);
	printf("网关的ip = %s\n", inet_ntoa(c_addr.sin_addr));


//====创建socket连接网关=======================
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	// memset(&addr, 0, sizeof(addr));
	// addr.sin_family = AF_INET;
	// addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	// addr.sin_port = htons(6547);

	//设备在接收广播消息时，已经获得了网管ip，现在改变端口port
	c_addr.sin_port = htons(6547);
	
	connect(sockfd, (struct sockaddr *)&c_addr, sizeof(c_addr));

	short msgtype = 0x0002;

	pdevice dc = (pdevice)malloc(sizeof(device));
	memcpy(dc->device_id, "123456", 7);
	memcpy(dc->name, "格力空调", 13);

	memcpy(dc->attrs[0].attr_name, "开关", 7);
	dc->attrs[0].property = 0x07;


	memcpy(buf, &msgtype, 2);
	memcpy(buf+2, dc, 274);

	printf("property %d\n", buf[65]);
	printf("属性名 %s\n", buf+52);

	send(sockfd, buf, 276, 0);

	close(sockfd);

	//继续使用之前创建的UDP的socket接收网关的控制消息
	while(1) {
			//阻塞在这里接受消息
		len = recvfrom(udpsockfd, buf, 300, 0, (struct sockaddr*)&c_addr, &c_addr_len);
		printf("UDP接收%s \n", strerror(errno));
		printf("收到控制消息长度%d\n", len);
		printf("收到控制消息data = %d, times = %d\n", buf[69], buf[73]);
		printf("网关的ip = %s\n", inet_ntoa(c_addr.sin_addr));

	//====创建socket连接网关=======================
		// sockfd = socket(AF_INET, SOCK_STREAM, 0);	
		// printf("创建socket结果%s\n", strerror(errno));		

		// connect(sockfd, (struct sockaddr *)&c_addr, sizeof(c_addr));
		// printf("连接结果%s\n", strerror(errno));
		// short msgtype = 0x0002;
		// memcpy(buf, &msgtype, 2);

		// printf("property %d\n", buf[65]);
		// printf("属性名 %s\n", buf+52);

		// send(sockfd, buf, 276, 0);
		// close(sockfd);
	}

	return 0;
}