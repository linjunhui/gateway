#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>

void recv_device_info(void){
	short msgtype;
	char buf[300] ;
	int len, err;
	const int on = 1;
	memset(buf, 0, 300);

	while(1) {
		len = recvfrom(bsockfd, buf, 127, 0, (struct sockaddr *)&c_addr, &c_addr_len);
		printf("收到来自IP：%s  端口：%d 的消息\n 内容：%s\n", inet_ntoa(c_addr.sin_addr), ntohs(c_addr.sin_port), buf);
		
		//取得msgtype
		memcpy(&msgtype, buf, 2);
		
				char name[22];
		memcpy(&name, buf+6, 22);
		name[21] = '\0';
		
		char id[13];
		memcpy(&id, buf+28, 13);
		id[12] = '\0';
		printf("msgtype = %d\n", msgtype);
		printf("ip = %d\n", ip);
		printf("name = %s\n", name);
		printf("id = %s\n", id);
		
		//如果msgtype == 0x0002 将消息当作设备消息处理
		if (msgtype == 0x0002) {
			//申请空间创建节点 将设备信息存入到链表中 乘以2 倍以后free不会出错
			pdevice_node pnode =(pdevice_node)malloc(sizeof(device_node)*2);
			pnode->pNext = NULL;
			//memcpy(pnode->device_id, "123456", 7);
			memcpy(pnode, buf+2, 284);

			//通过id查找链表中的此设备, 删除此设备，重新加入新的节点信息
			printf("%s\n", pnode->device_id);
			printf("%s\n", pnode->name);
			int data;
			memcpy(&data, buf+66, 4);
			printf("参数的值data = %d\n", data);
			printf("参数的值buf[66] = %d\n", buf[66]);
			pnode->online = 'y';
			printf("pnode->online:%c\n", pnode->online);
			remove_from_list(device_link, pnode->device_id);

			list_add(device_link, pnode);
		}
	}	
}

int main() {
	struct sockaddr_in addr;//自身和客户端地址
	socklen_t addr_len;

	char buf[128];
	int bsockfd;
	int len, err, reuse0 = 1;
	struct sockaddr_in	c_addr;
	socklen_t	c_addr_len;

	//创建UDP socket
	bsockfd = socket(AF_INET,SOCK_DGRAM,0);
	printf("创建UDP socket结果%s \n", strerror(errno));

	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(8999);	
	addr_len=sizeof(addr);
	
	setsockopt(bsockfd,SOL_SOCKET, SO_BROADCAST,&reuse0,sizeof(reuse0));

	//绑定socket 和 地址
	err = bind(bsockfd, (struct sockaddr *)&addr, sizeof(addr));
	
	memset(&c_addr,0,sizeof(c_addr));
	c_addr.sin_family = AF_INET;
	c_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST); 
	c_addr.sin_port = htons(9999);	
	c_addr_len=sizeof(c_addr);
	c_addr_len=sizeof(c_addr);
	
	memcpy(buf, "dfdaf", 6);
	len = sendto(bsockfd, buf, 127, 0, (struct sockaddr *)&c_addr, c_addr_len);
	sleep(4);

}
