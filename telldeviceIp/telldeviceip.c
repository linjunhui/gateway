#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>


struct in_addr localInterface;
struct sockaddr_in groupSock;
int sd;
char databuf[1024] = "Multicast test message lol!\n";
int datalen = sizeof(databuf);


int main (int argc, char *argv[ ])
{
     sd = socket(AF_INET, SOCK_DGRAM, 0);
     if(sd < 0) {
          perror("Opening datagram socket error");
          exit(1);
     } else
          printf("Opening the datagram socket...OK.\n");


     memset((char *) &groupSock, 0, sizeof(groupSock));
     groupSock.sin_family = AF_INET;
     groupSock.sin_addr.s_addr = inet_addr("227.0.0.25");
     groupSock.sin_port = htons(49500);


     localInterface.s_addr = inet_addr("192.168.1.101");
     if(setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface)) < 0) {
        perror("Setting local interface error");
        exit(1);
     } else
        printf("Setting the local interface...OK\n");


     if(sendto(sd, databuf, datalen, 0, (struct sockaddr*)&groupSock, sizeof(groupSock)) < 0) {
        perror("Sending datagram message error");}
     else
        printf("Sending datagram message...OK\n");


     return 0;
}
