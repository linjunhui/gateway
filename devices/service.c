/*
		 开始

		 创建设备链表


		 创建socket


		 等待设备接入


		 设备接入创建新线程

*/


#include <stdio.h>


//创建线程处理消息
void dealmesg(int fd) {
	short msgtype;

	//客户端请在 发送完消息后主动关闭socket
	buflen = recv(fd, buf, size, 0);
	//将消息拆成两半 msgtype 和 消息内容 content
	memcpy(msgtype, buf, 2);
	memcpy(content, buf, csize);

	if(msgtype == 0x0002) {
		deal_device_msg(content);
	} else if(msgtype == 0x0004) {
		deal_app_msg(content);
	}



}
