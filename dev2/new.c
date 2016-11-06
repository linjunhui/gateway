#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "devicelink.h"
#include <arpa/inet.h>

pdevice_link device_link;
int bsockfd;
struct sockaddr_in	c_addr;
socklen_t	c_addr_len;


void list_thread(pdevice_link device_link) {
	while(1) {
		traverse_list_off(device_link);
		sleep(60);
	}

}

void recvAPPmsg(int connfd) {
	char buf[300];
	int buflen, len;
	short msgtype;

	//返回接收到的数据长度
	buflen = recv(connfd, buf, 300, 0);
	printf("buf0 = %d\n", buf[0]);
	printf("buf1 = %d\n", buf[1]);

	memcpy(&msgtype, buf, 2);
	printf("buflen = %d\n", buflen);
	printf("msgtype = %d\n", msgtype);

	if (msgtype == 0x0003) {
		//处理来自APP的消息 
		printf("收到来APP请求设备列表的消息\n");
		//send(connfd, "我是网关, 收到请求\n", 200, 0);
		traverse_to_app(device_link, connfd);
		//======遍历链表回复给APP========

		close(connfd);
	} else if(msgtype == 0x0005) {
		//网关好像不用做什么处理直接转发到设备就行
		printf("收到了APP对设备的控制消息\n");
		printf("APP控制消息分割线==========================\n");

		printf("参数的值data = %d\n", buf[69]);
		printf("值得倍数times = %d\n", buf[73]);

		//关闭原连接
		close(connfd);

		//通过广播发送控制到设备					
		len = sendto(bsockfd, buf, 300, 0, (struct sockaddr*)&c_addr, c_addr_len);
		printf("客服端地址%s\n", inet_ntoa(c_addr.sin_addr));
		printf("UDP发送%s 端口：%d\n", strerror(errno), ntohs(c_addr.sin_port));
		printf("len = %d\n", len);
		printf("发送消息*************************************************\n");
		
	}


	printf("有设备接入，连接id: connfd = %d\n", connfd);
	traverse_list(device_link);	
}

//创建UDP，接收设备的消息
void recvDevicemsg(void ) {
	short msgtype;
	char buf[300] ;
	int len, err;
	const int on = 1;
	memset(buf, 0, 300);
	
	while(1) {
		//阻塞在这里接受消息
		len = recvfrom(bsockfd, buf, 300, 0, NULL, NULL);
		memcpy(&msgtype, buf, 2);
		int ip ;	
		memcpy(&ip, buf+2, 4);
		
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
		//printf("id = %s\n", buf);
		int i;
		
		printf("UDP接收%s \n", strerror(errno));
		printf("收到消息:%s\n", buf); 
		//收到消息:smartlinkfind
		
			//msgtype = 0x0002;
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

		pnode->online = 'y';
		printf("pnode->online:%c\n", pnode->online);
		remove_from_list(device_link, pnode->device_id);

		list_add(device_link, pnode);
	}

	}

}



int main(int argc, char const *argv[])
{	
	int thread_id, err, len, reuse0;
	int sockfd, connfd;
	
	device_link = create_list();
	
	//开一个线程每隔一分钟将所有设备 设置为离线
	err = pthread_create(&thread_id, NULL, (void *)list_thread, device_link);
	printf("链表创建线程结果%s\n", strerror(err));

	//创建广播socket 自身端口48899 用来接收设备广播
	//目标端口7575 给设备发送控制消息
//==========广播socket==============
//***************************************************************************//
	struct sockaddr_in addr;//自身和客户端地址
	socklen_t addr_len;

	//创建UDP socket
	bsockfd = socket(AF_INET,SOCK_DGRAM,0);
	printf("创建UDP socket结果%s \n", strerror(errno));

	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(49999);	
	addr_len=sizeof(addr);

	//客户端地址
	memset(&c_addr,0,sizeof(c_addr));
	c_addr.sin_family = AF_INET;
	c_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST); 
	c_addr.sin_port = htons(48999);	
	c_addr_len=sizeof(c_addr);


	setsockopt(bsockfd,SOL_SOCKET, SO_BROADCAST,&reuse0,sizeof(reuse0));

	//绑定socket 和 地址
	err = bind(bsockfd, (struct sockaddr *)&addr, sizeof(addr));
	printf("UDP绑定结果%s\n", strerror(err));
	err = pthread_create(&thread_id, NULL, (void *)recvDevicemsg, NULL);
//***************************************************************************//
	//===============接收APP消息的socket==============
	//声明本服务端地址结构体
	struct sockaddr_in server_addr;
	//声明对端的地址结构体
	struct sockaddr_in peer_addr;
		//创建socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("创建socket结果%s sockfd = %d\n", strerror(errno), connfd);
	//设置服务端的地址结构体，设置地址的ip 端口等
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET; 
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(6547);

	//设置端口的复用
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse0, sizeof(reuse0));
	//绑定本机的socket 和 地址
	err = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	//开始监听, 设置监听队列中的最大等待个数
	err = listen(sockfd, 1000);
	printf("绑定结果%s\n", strerror(err));
	
	//多个线程使用同一个线程id变量，无影响，这只是系统创建线程时返回给用户的一个id,改变其值对线程无影响
	//将链接的connfd 传给子线程
	while(1) {
		//等待客户端连接, 没有连接就阻塞在这里
		int len = sizeof(peer_addr);
		connfd = accept(sockfd, (struct sockaddr *)&peer_addr, &len);
		printf("connfd = %d\n", connfd);   

		err = pthread_create(&thread_id, NULL, (void *)recvAPPmsg, connfd);
		printf("创建线程结果%s\n", strerror(err)); 

	}
	
}