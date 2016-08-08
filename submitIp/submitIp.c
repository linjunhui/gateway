#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 4096
int get_mac(char* mac)

{
    struct ifreq tmp;
    int sock_mac;
    char mac_addr[30];
    sock_mac = socket(AF_INET, SOCK_STREAM, 0);
    if( sock_mac == -1){
        perror("create socket fail\n");
        return -1;
    }
    memset(&tmp,0,sizeof(tmp));
    strncpy(tmp.ifr_name,"eth0",sizeof(tmp.ifr_name)-1 );
    if( (ioctl( sock_mac, SIOCGIFHWADDR, &tmp)) < 0 ){
        printf("mac ioctl error\n");
        return -1;
    }
    sprintf(mac_addr, "%02x%02x%02x%02x%02x%02x",
            (unsigned char)tmp.ifr_hwaddr.sa_data[0],
            (unsigned char)tmp.ifr_hwaddr.sa_data[1],
            (unsigned char)tmp.ifr_hwaddr.sa_data[2],
            (unsigned char)tmp.ifr_hwaddr.sa_data[3],
            (unsigned char)tmp.ifr_hwaddr.sa_data[4],
            (unsigned char)tmp.ifr_hwaddr.sa_data[5]
            );
    printf("local mac:%s\n", mac_addr);
    close(sock_mac);
    memcpy(mac,mac_addr,strlen(mac_addr));
    return 0;
}

int main() {

	int sockfd, connfd;
	struct sockaddr_in addr;
	struct sockaddr_in peeraddr;
	int UID = 6655;
	char buf[500];

	char mac[105];
	get_mac(mac);



	sockfd = socket(AF_INET, SOCK_STREAM, 0);


	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("119.29.34.51");
	addr.sin_port = htons(6666);

	connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	//printf("%s\n", mac);
	sprintf(buf, "G%s", mac);
	send(sockfd, buf, strlen(buf), 0);
	printf("%s, %s\n",buf, mac);
	close(sockfd);
	return 0;

}

