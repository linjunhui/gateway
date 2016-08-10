#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include "dealmsg.h"
#include "linklist.h"
#define FIFO "~/fifo/devmsg"

int main() {
	int sockfd, connfd, len, rc, reuse0;
	struct sockaddr_in addr;
	struct sockaddr_in peeraddr;
	pid_t pid;

	Attr atr1;
	char *sw = "开关";
	memcpy(atr1.attrName, sw, 11);
	atr1.dataType = 0x01;
	atr1.data = 0x01;
	atr1.times = 1;



	
	

	//创建链表
	PdevicelistNode deviceLinklist = create_list();
	//创建ndev节点
	PdevicelistNode ndev1 = (PdevicelistNode)malloc(sizeof(devicelistNode));
	ndev1->msgtype = 0x0004;
	ndev1->deviceIP = 0xc0a80390;
	char *name = "格力空调";
	char *id = "123456";
	memcpy(ndev1->deviceID, id, 9);
	memset(ndev1->name, 0, 21);
	memcpy(ndev1->name, name, 21);

	ndev1->attrs[0] = atr1;
	ndev1->pNext = NULL;
	
	list_add(deviceLinklist, ndev1); 

	printf("devicelistNode size: %d\n", sizeof(devicelistNode));
	PdevicelistNode ndev2 = (PdevicelistNode)malloc(sizeof(devicelistNode));
	ndev2->msgtype = 0x0004;
	ndev2->deviceIP = 0xc0a80390;
	char *name2 = "medea空调";
	memset(ndev2->name, 0, 21);
	memcpy(ndev2->name, name2, 21);

	ndev2->attrs[0] = atr1;
	ndev2->pNext = NULL;
	
	list_add(deviceLinklist, ndev2); 

	PdevicelistNode ndev3 = (PdevicelistNode)malloc(sizeof(devicelistNode));
	ndev3->msgtype = 0x0004;
	ndev3->deviceIP = 0xc0a80390;
	char *name3 = "Gree空调";
	memset(ndev3->name, 0, 21);
	memcpy(ndev3->name, name3, 21);

	ndev3->attrs[0] = atr1;
	ndev3->pNext = NULL;
	
	list_add(deviceLinklist, ndev3); 





	sockfd = socket(AF_INET, SOCK_STREAM, 0);
		printf("%s\n", strerror(errno));

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr =  INADDR_ANY; //inet_addr("10.104.7.92");
	addr.sin_port = htons(6547);

	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse0, sizeof(reuse0));
	rc = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	printf("bind:%d\n", rc);
	listen(sockfd, 1000);
 	
 	while(1) {
 		int len = sizeof(peeraddr);
		if ((connfd = accept(sockfd, (struct sockaddr*)&peeraddr, &len)) == -1) {
				printf("error\n");
				printf("%s\n", strerror(errno));
				close(connfd);
		} else if((pid = vfork()) == 0 ) {
			int tmpfd = connfd,i;
			char buf[200];
			int buflen;
			printf("%s\n", inet_ntoa(peeraddr.sin_addr));
			printf("child process : %ld  tmpfd:%d\n", (long)getpid(), tmpfd);
			buflen = recv(tmpfd, buf, 200, 0);
			buf[buflen] = '\0';
			printf("data length:%d, %s\n", buflen, buf);

			
			//如果返回0x0002, 给  APP回复
			dealmsg(buf, buflen+1, tmpfd, deviceLinklist);
			
			//组数据单元(msgtype, ip, content, connfd);,
			//short msgtype = 0x0002;
			//assemPdu(msgtype, NULL, NULL, tmpfd);
		
			



			 
			// for(i = 0; i < buflen; i++)
			// 	printf("buf[%d]:%x\n", i, buf[i]);
			//  close(connfd);
		}
		
		

 	}


}
