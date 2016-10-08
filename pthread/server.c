#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

void thread1(int a) {
	sleep(3);
	printf("thread1: i = %d\n", a);
}

int main(int argc, char const *argv[])
{
	//创建socket
	//声明socket
	int sockfd, connfd;

	//错误描述
	int err;
	//声明本服务端地址结构体
	struct sockaddr_in server_addr;
	//声明对端的地址结构体
	struct sockaddr_in peer_addr;

//============pthread相关的定义=====
	int thread1_id;
//=================================																							
	//创建socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("创建socket结果%s sockfd = %d\n", strerror(sockfd), connfd);
	//设置服务端的地址结构体，设置地址的ip 端口等
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(6666);

	//绑定本机的socket 和 地址
	err = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	//开始监听, 设置监听队列中的最大等待个数
	err = listen(sockfd, 1000);
	printf("绑定结果%s\n", strerror(err));
	//等待客户端连接
	int len = sizeof(peer_addr);
	connfd = accept(sockfd, (struct sockaddr *)&peer_addr, &len);
	printf("accept结果%s\n", strerror(connfd));  
	printf("connfd = %d\n", connfd);   

//==============新建线程处理连接==========
	int i = 10;
	//多个线程使用同一个线程id变量，无影响，这只是系统创建线程时返回给用户的一个id,改变其值对线程无影响
	err = pthread_create(&thread1_id, NULL, (void *)thread1, i);
	printf("线程id = %d\n", thread1_id);
	err = pthread_create(&thread1_id, NULL, (void *)thread1, 11);
	printf("线程id = %d\n", thread1_id);
	err = pthread_create(&thread1_id, NULL, (void *)thread1, 12);
	printf("线程id = %d\n", thread1_id);


	sleep(10);

		return 0;
}
