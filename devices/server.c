#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "devicelink.h"

//声明一个device_link指向 设备链表
pdevice_link device_link;

void thread1(int connfd) {
	char buf[300];
	int buflen;
	short msgtype;

	//返回接收到的数据长度
	buflen = recv(connfd, buf, 300, 0);
	printf("buf0 = %d\n", buf[0]);
	printf("buf1 = %d\n", buf[1]);

	memcpy(&msgtype, buf, 2);
	printf("buflen = %d\n", buflen);
	printf("msgtype = %d\n", msgtype);

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


	} else if (msgtype == 0x0003) {
		//处理来自APP的消息 
		printf("收到来APP请求设备列表的消息\n");
		//send(connfd, "我是网关, 收到请求\n", 200, 0);
		traverse_to_app(device_link, connfd);
		//======遍历链表回复给APP========
	}


	printf("有设备接入，连接id: connfd = %d\n", connfd);
	traverse_list(device_link);
}

void list_thread(pdevice_link device_link) {
	while(1) {
		traverse_list_off(device_link);
		sleep(60);
	}

}


void adver_gateip(void) {
	//创建一个发送的socket
	int sockfd;
	struct sockaddr_in addr, c_addr;
	socklen_t addr_len, c_addr_len;
	char buf[50] = {'c','\0', '\r', '\n'};
	int len, err;
	const int on = 1;

	//创建UDP socket
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	printf("创建UDP socket结果%s \n", strerror(errno));

	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(7575);	
	addr_len=sizeof(addr);

	//客户端地址
	memset(&c_addr,0,sizeof(c_addr));
	c_addr.sin_family = AF_INET;
	c_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST); 
	c_addr.sin_port = htons(7576);	
	c_addr_len=sizeof(c_addr);

	setsockopt(sockfd,SOL_SOCKET, SO_BROADCAST,&on,sizeof(on));

	//绑定socket 和 地址
	err = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	printf("UDP绑定结果%s\n", strerror(err));


	while(1) {
	//阻塞在这里接受消息
	len = recvfrom(sockfd, buf, 50, 0, (struct sockaddr*)&addr, &addr_len);
	printf("UDP接收%s \n", strerror(errno));
	printf("收到消息:%s\n", buf);

	//发送消息
	len = sendto(sockfd, "buf", 50, 0, (struct sockaddr*)&c_addr, c_addr_len);
	printf("UDP发送%s \n", strerror(errno));
	printf("len = %d\n", len);
	printf("发送消息\n");
	}




}
int main(int argc, char const *argv[])
{
	//创建socket
	//声明socket
	int sockfd, connfd;

	//错误描述
	int err, reuse0;
	//声明本服务端地址结构体
	struct sockaddr_in server_addr;
	//声明对端的地址结构体
	struct sockaddr_in peer_addr;

//============pthread相关的定义=====
	int thread1_id;
//=================================																							
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
//==============设备链表相关==============
	device_link = create_list();
	//开一个线程没隔一分钟将所有设备 设置为离线
	err = pthread_create(&thread1_id, NULL, (void *)list_thread, device_link);
		printf("链表创建线程结果%s\n", strerror(err));

//========新新建线程处理设备广播消息告知设备 网关ip
err = pthread_create(&thread1_id, NULL, (void *)adver_gateip, NULL);
//==============新建线程处理连接==========
	int i = 10;
	//多个线程使用同一个线程id变量，无影响，这只是系统创建线程时返回给用户的一个id,改变其值对线程无影响
	//将链接的connfd 传给子线程
	while(1) {
		//等待客户端连接, 没有连接就阻塞在这里
		int len = sizeof(peer_addr);
		connfd = accept(sockfd, (struct sockaddr *)&peer_addr, &len);
		printf("connfd = %d\n", connfd);   

		err = pthread_create(&thread1_id, NULL, (void *)thread1, connfd);
		printf("创建线程结果%s\n", strerror(err)); 

	}
	


	return 0;
}
