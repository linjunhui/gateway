#include "linklist.h"

void dealmsg(char msg[], int length, int connfd, PdevicelistNode deviceLinklist);
void assemPdu(short msgtype, int ip, char *content, int connfd);
void sendDevicePdu(PdevicelistNode ndev, int connfd, PdevicelistNode deviceLinklist);
