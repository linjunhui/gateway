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
	struct sockaddr_in addr;

	char buf[300];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(6547);
	
	connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));

	short msgtype = 0x0002;

	pdevice dc = (pdevice)malloc(sizeof(device));
	memcpy(dc->device_id, "123457", 7);
	memcpy(dc->name, "美的空调", 13);

	memcpy(dc->attrs[0].attr_name, "开关", 7);
	dc->attrs[0].property = 0x07;


	memcpy(buf, &msgtype, 2);
	memcpy(buf+2, dc, 274);
printf("property %d\n", buf[65]);
printf("属性名 %s\n", buf+52);

	send(sockfd, buf, 276, 0);

	close(sockfd);
	return 0;
}