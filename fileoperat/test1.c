#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

int main() {

	int fd;
	char *buf = "asddfgg";

	printf("X:%x", buf[7]);
	char *buff = "1";
	fd = open("test1", O_RDWR);
	if (fd == -1) {
		/* code */
		perror("open failed!\n");
	}
	printf("open\n");

	if(write(fd, buf, 4) == -1) {
		perror("read error!");
	}

	close(fd);

	fd = open("test1", O_RDWR|O_TRUNC);
	if (fd == -1) {
		/* code */
		perror("open failed!\n");
	}
	printf("open\n");

	if(write(fd, buff, 1) == -1) {
		perror("read error!");
	}
	
	


}
