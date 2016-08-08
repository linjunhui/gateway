#include "dealmsg.h"
#include <arpa/inet.h>
#include <string.h>
#include <malloc.h>

void dealmsg(char msg[], int length, int connfd, PdevicelistNode deviceLinklist) {
	short msgtype ;
	struct in_addr ip;

	msgtype = msg[1] | ((short)msg[0] << 8);
	ip.s_addr = ((int)(msg[5] & 0xFF) << 24) | ((int)(msg[4] & 0xFF) << 16) | ((int)(msg[3] & 0xFF) << 8) | (msg[2]& 0xFF) ;
	char *nip = inet_ntoa(ip);

	// printf("%x\n", ((int)(msg[2] & 0xFF)));
	// printf("%x\n", ((int)(msg[3] & 0xFF)));

	printf("msgtype :%x    ip:%s\n", msgtype, nip);

	
	//根据不同的消息类型来处理数据
	if(0x0001 == msgtype) {
		//调用发送函数
		short type = 0x0002;
		printf("send-0x0002\n");
		assemPdu(type, NULL, NULL, connfd);
		printf("send 0x0002\n");
		close(connfd);

	} else if(0x0002 == msgtype){//网关应该不会收到这个类型的数据，这是网关发给APP的

	} else if(0x0003 == msgtype) {
		printf("msgtype:0x0003,dealing\n");
		PdevicelistNode ndev = (PdevicelistNode)malloc(sizeof(devicelistNode));
		ndev->msgtype = 0x0004;
		ndev->deviceIP = 0xc0a80390;
		char *name = "格力空调";
		memset(ndev->name, 0, 21);
		memcpy(ndev->name, name, 21);
		
		//向APP发送设备信息
		sendDevicePdu(ndev, connfd, deviceLinklist);
	}



}

void sendDevicePdu(PdevicelistNode ndev, int connfd, PdevicelistNode deviceLinklist) {
	int i , count = 0;
	//定义一个数组来在遍历时存储所有节点的地址
	PdevicelistNode devices[100];

	count = traverse_list(deviceLinklist, devices, 100 );
	printf("count %d\n", count);

	for (i = 0; i < count; ++i) {
		//unsigned char buf[500];
		// memcpy(buf, &devices[i]->msgtype,2);
		// memcpy(buf+2, &devices[i]->deviceIP, 4);
		// memcpy(buf+6, &devices[i]->name, 21);
		// memcpy(buf+27, &ndev->deviceID, 9);
		// memcpy(buf+36, &ndev->locked, 1);
		// memcpy(buf+37, &ndev->gateID, 13);

		unsigned char buf[500];
		memset(buf, 0,410);
		memcpy(buf, devices[i],410);
		send(connfd, buf, 410, 0);
		
		//printf("buf[2]%s   %p\n", &devices[i]->name, devices[i]);
		//send(connfd, buf, 410, 0);
		
	}
		
	char buf[500];
	memset(buf, 0,410);
	// send(connfd, buf, 414, 0);
	send(connfd, buf, 410, 0);
	close(connfd);

}

void assemPdu(short msgtype, int ip, char *content, int connfd) {
	char *pdu;
	int length;
	if(content == NULL) {
		length = 6 + 1;
		pdu = (char *)malloc(length * sizeof(char));
		memcpy(pdu,&msgtype,2);
		memcpy(pdu+2, &ip, 4);

		pdu[length-1] = '\n';


	} else {
		int contentlen = strlen(content);
		length = 6 + contentlen + 1;
		pdu = (char *)malloc(length * sizeof(char));
		memcpy(pdu,&msgtype,2);
		memcpy(pdu+2, &ip, 4);
		memcpy(pdu+6,content,contentlen);
		pdu[length-1] = '\n';
	
	}

	printf("assembled pdu\n");
	printf("pdu[0]:%d\n", pdu[0]);
	printf("pdu[1]:%d\n", pdu[1]);
	send(connfd, pdu, length, 0);
	send(connfd, NULL, length, 0);
	close(connfd);
	
}
