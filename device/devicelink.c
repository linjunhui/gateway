
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "linklist.h"
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

#define FIFO "/tmp/fifodevmsg"

//使用多线程了将
int count = 0, i;
int ppid;//管道的id
int fd;
pid_t pid;

PdevicelistNode deviceLinklist;

//定义一个数组来在遍历时存储所有节点的地址
PdevicelistNode devices[100];

/*线程一*/  
//在线程中处理管道
void thread_1(void)  
{  
	char flag[1]={0};
	char buf[1000];
	
	printf("This is a pthread_1.\n"); 
	
	fd = open(FIFO, O_RDWR);
	if (fd == -1) {
		/* code */
		printf("open failed!\n");
	}
	printf("open\n");

	if(write(fd, flag, 1) == -1) {
		perror("read error!");
	}

	
	
	
	
	//
	while(1) {

		fd = open(FIFO, O_RDWR);
		if (fd == -1) {
			/* code */
			printf("open failed!\n");
		}
	
		if(read(fd, flag, 1) == -1) {
			perror("read error!");
		}
		
		char type = flag[1];
		
		//type 0:将链表写入到管道，  1：将管道的内容读出加入到链表
		if(0 == type) {
			int count = traverse_list(deviceLinklist, devices, 100 );
			buf[0] = 3;
			buf[1] = 0;
			memcpy(buf+2, devices[0], sizeof(count * 188 + 2));

			if(write(fd, flag, 1) == -1) 
				perror("read error!");


			close(fd);
		}
		
		
	}
	
	
	
	
	

	close(fd);
 
	printf("This is a pthread_1 end\n"); 
}

int main() {
	//int pthread_create(pthread_t *tidp,const pthread_attr_t *attr,(void*)(*start_rtn)(void*),void *arg);
	
	
	pthread_t id_1,id_2;  
    int i,ret;  
	/*创建线程一*/  
    ret=pthread_create(&id_1,NULL,(void  *) thread_1,NULL); 
	
	if(ret!=0)   {  
        printf("Create pthread error!\n");  
    } 
	
	deviceLinklist = create_list();

	if((ppid = mkfifo(FIFO, 0777)) == -1) {
		perror("create pipe failed");
		return 1;
	} else 
		printf("create pipe success\n");
	
		
	PdevicelistNode device1 = (PdevicelistNode)malloc(sizeof(devicelistNode));
	//memset(device1, 0, sizeof(devicelistNode));
	device1-> msgtype = 0x0004;
	device1-> deviceIP = inet_addr("192.168.1.119");
	device1-> deviceID = 123456;
	char *name = "aircond";
	memcpy(device1-> name, name, 8);
	device1-> locked = 0;
	device1-> gateID = 0;

	printf("size:%d\n", sizeof(devicelistNode));

	
	list_add(deviceLinklist, device1); 

		
	count = traverse_list(deviceLinklist, devices, 100 );
	printf("count:%d\n", count);
	
	for (i = 0; i < count; ++i)
		printf("%x\n", devices[i]->msgtype);

	
	/*等待线程结束*/  
    pthread_join(id_1,NULL); 		
}