#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MSG(args...)    printf(args)


//函数声明
static int gpio_export(int pin);
static int gpio_unexport(int pin);
static int gpio_direction(int pin, int dir);
static int gpio_write(int pin, int value);
static int gpio_read(int pin);

 
static int gpio_export(int pin) 
{ 

    char buffer[64]; 
    int len; 
    int fd; 

    fd = open("/sys/class/gpio/export", O_WRONLY); 

    if (fd < 0) { 
        MSG("Failed to open export for writing!\n"); 
        return(-1); 
    } 

    len = snprintf(buffer, sizeof(buffer), "%d", pin); 
    if (write(fd, buffer, len) < 0) { 
        MSG("Failed to export gpio!"); 
        return -1; 
    } 
    close(fd); 

 return 0; 

} 

 


static int gpio_unexport(int pin) 

{ 

    char buffer[64]; 
    int len; 
    int fd; 

    fd = open("/sys/class/gpio/unexport", O_WRONLY); 

    if (fd < 0) { 
        MSG("Failed to open unexport for writing!\n"); 
        return -1; 

    } 

    len = snprintf(buffer, sizeof(buffer), "%d", pin); 
    if (write(fd, buffer, len) < 0) { 
        MSG("Failed to unexport gpio!"); 
       // return -1; 

    } 
    close(fd); 

    return 0; 

}

//dir: 0-->IN, 1-->OUT
static int gpio_direction(int pin, int dir) 
{ 

    static const char dir_str[] = "in\0out"; 
    char path[64]; 
    int fd; 
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/direction", pin); 
    fd = open(path, O_WRONLY); 
   if (fd < 0) { 
        MSG("Failed to open gpio direction for writing!\n"); 
        return -1; 

    } 

    if (write(fd, &dir_str[dir == 0 ? 0 : 3], dir == 0 ? 2 : 3) < 0) { 
        MSG("Failed to set direction!\n"); 
        return -1; 
    } 
    close(fd); 

    return 0; 

} 

 


//value: 0-->LOW, 1-->HIGH

static int gpio_write(int pin, int value) 

{ 

    static const char values_str[] = "01"; 
    char path[64]; 
    int fd; 

    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin); 

    fd = open(path, O_WRONLY); 
    if (fd < 0) { 
        MSG("Failed to open gpio value for writing!\n"); 
        return -1; 

    } 

    if (write(fd, &values_str[value == 0 ? 0 : 1], 1) < 0) { 
        MSG("Failed to write value!\n"); 
        return -1; 

    } 
   close(fd); 

    return 0; 

}

 


static int gpio_read(int pin) 
{ 
    char path[64]; 
    char value_str[3]; 
    int fd; 

    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin); 
    fd = open(path, O_RDONLY); 
    if (fd < 0) { 
        MSG("Failed to open gpio value for reading!\n"); 
        return -1; 
    } 

    if (read(fd, value_str, 3) < 0) { 
      MSG("Failed to read value!\n"); 
      return -1; 

    } 

    close(fd); 
    return (atoi(value_str));

} 

 


// none表示引脚为输入，不是中断引脚
// rising表示引脚为中断输入，上升沿触发
// falling表示引脚为中断输入，下降沿触发
// both表示引脚为中断输入，边沿触发
// 0-->none, 1-->rising, 2-->falling, 3-->both
static int gpio_edge(int pin, int edge)
{
    const char dir_str[] = "none\0rising\0falling\0both";
    char ptr;
    char path[64]; 
    int fd;
    switch(edge){
        case 0:
        ptr = 0;
        break;
        case 1:
        ptr = 5;
        break;
        case 2:
        ptr = 12;
        break;
        case 3:
        ptr = 20;
        break;
        default:
        ptr = 0;
    }

    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/edge", pin); 
    fd = open(path, O_WRONLY); 
    if (fd < 0) { 
        MSG("Failed to open gpio edge for writing!\n"); 
        return -1; 

    } 
    if (write(fd, &dir_str[ptr], strlen(&dir_str[ptr])) < 0) { 
        MSG("Failed to set edge!\n"); 
        return -1; 
    } 
    close(fd); 
    return 0; 
}

int main()
{

	//SOCKET
	int sockfd, connfd, rc, reuse0;
	struct sockaddr_in addr;
	struct sockaddr_in peeraddr;
	char buf[50];
	int len;
	char ssid[50];
	char pass[50];
	char nmcli[64] = "nmcli dev wifi connect ";
	char *password = " password ";

    gpio_unexport(197);
    gpio_unexport(198);
    gpio_unexport(199);
    //led
    gpio_export(198);
    gpio_direction(198, 1);
    gpio_export(199);
    gpio_direction(199, 1);

    //key
    gpio_export(197);
    gpio_direction(197, 0);

    gpio_write(199, 1);
    gpio_write(198, 1);

    while(1) {
         while(gpio_read(197) == 0) {

        }
        gpio_write(199, 0);
        system("./auto_wifi.sh");

        sleep(3);
    //Create TCP Socket
        printf("start tcp\n");
        rc = sockfd = socket(AF_INET, SOCK_STREAM, 0);
printf("create socket:%d\n", rc);
    //set Ip, port
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr("192.168.2.1");
        addr.sin_port = htons(45566);
printf("create addr\n");

setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse0, sizeof(reuse0));
    //bind address
        rc = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
printf("bind:%d\n", rc);
printf("3\n");
    //start listen
        rc = listen(sockfd, 1000);
printf("listen:%d\n", rc);
printf("4\n");
    //accept 
        if ((connfd = accept(sockfd, (struct sockaddr*)&peeraddr, &len)) == -1) {
            printf("err1:\n");
        }
        printf("connected\n");

        len=recv(connfd, buf, 50, 0);
        buf[len] = '\0';
        printf("%s\n", buf);
        close(sockfd);

        char i = 0;
        while(buf[i] != ':')
            i++;
        memset(ssid,0,50);
        memset(pass,0,50);
        memcpy(ssid,buf,i);
        memcpy(pass,buf+i+1,strlen(buf)-(i+1));
        printf("%s:%s\n", ssid, pass);
    //connet router
        strcat(nmcli, ssid);
        strcat(nmcli, password);
        strcat(nmcli, pass);
        printf(":%s\n", nmcli);
        system("./ap-stop.sh");
        sleep(5);
        system(nmcli);
	gpio_write(199, 1);
        printf("end \n");
    }

   
//get ip address ,turn off led
    
    return 0;
}
