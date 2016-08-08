#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>

#define MAX 4096
char *ip = NULL;
char *rip = NULL;
int count = 0;

int callback(void *d, int cols, char **col_values, char **col_names) {
	
	int i;
	
	for(i = 0;i<cols;i++) {
		printf("col_values=%s, col_names=%s", col_values[i], col_names[i]);
		
	}
	count = cols;	
	printf("cols=%d\n", cols);
	
	return 0;

}

int callbackq(void *d, int cols, char **col_values, char **col_names) {
	
	int i;
	
	for(i = 0;i<cols;i++) {
		printf("in querying col_values=%s, col_names=%s ", col_values[i], col_names[i]);
		
	}
	rip = col_values[0];
	count = cols;	
	printf("cols=%d\n", cols);
	
	return 0;

}
int main() {

//socket 相关
	int sockfd, connfd;
	struct sockaddr_in addr;
	struct sockaddr_in peeraddr;
	int len, buflen;
	char buf[MAX];
	char type;
	char mac[20];
//数据库相关
	char sql[50];
	sqlite3 *db = NULL;
	int rc;
	char *errmesg;
	
//创建数据库
	rc = sqlite3_open("data.db", &db);
//创建表
	sqlite3_exec(db, "create table mytable(mac varchar(50) primary key, ip varchar(50))", NULL, NULL, &errmesg);
//创建socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
//设置地址的ip 端口等
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("10.104.7.92");
	addr.sin_port = htons(6666);
//绑定socket和地址
	bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
//开始监听，设置监听队列数
	listen(sockfd, 1000);

	while(1) {//66
		
		len = sizeof(peeraddr);
		//阻塞线程等待连接
		if ((connfd = accept(sockfd, (struct sockaddr*)&peeraddr, &len)) == -1) {//1
			printf("err1:\n");
			continue;
		}//1
//连接成功，打印client的ip和端口
		printf("%s, %d\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));
		//char*inet_ntoa(struct in_addr in); 
		//将client的ip存
		ip = inet_ntoa(peeraddr.sin_addr);
		printf("ip: %s", ip);
//开始接收数据
		buflen = recv(connfd, buf, MAX, 0);
		//buf 的第一个表示类型 后四个表示id
		buf[buflen] = '\0';
		//拿到id
		strncpy(mac, buf+1, 17);
		mac[17] = '\0';
		printf("mac=:%s\n", mac);
		//如果消息来自网关
		if(buf[0] == 'G') {//22
			rc = sqlite3_close(db);
  			rc = sqlite3_open("data.db", &db);

			printf("buf=%s, mac=%s\n",buf, mac);
			
			
			//2. 插入数据
			//sqlite3_exec(db, "insert into mytable(uid, ip) values(5566, '22.33.44.66');", NULL, NULL, &errmesg);
			//查询数据  
			sprintf (sql, "select *from mytable where mac='%s'", mac);
    rc = sqlite3_exec( db, sql, callback, NULL, &errmesg);
	printf("1rc:%d SQLITE_OK=%d   errmesg=%s    count=%d\n", rc, SQLITE_OK, errmesg, count);
    if(count == 0) {//33  
    	
    	//拼接sql插入命令
    	sprintf (sql, "insert into mytable(mac, ip) values('%s', '%s')", mac, ip);
    	//如果数据不存在就创建
			sqlite3_exec(db, sql, NULL, NULL, &errmesg);
			printf("errmesg=%s\n", errmesg);
			sqlite3_close(db);
			//33
    } else {//44
    		sprintf(sql, "update mytable set ip='%s' where mac='%s'", ip, mac);
    		printf("ip=%s   mac=%s    \n", ip, mac);
    	//如果数据存在就更新
    	sqlite3_exec(db, sql, NULL, NULL, &errmesg);
    	
    	}//44
    	//如果消息来自moblie
    	//22
  	}	else if (buf[0] == 'M') {//55
  		rc = sqlite3_close(db);
  		rc = sqlite3_open("data.db", &db);
  		
  		sprintf (sql, "select ip from mytable where mac='%s'", mac);
    	//4.查询数据	
		 	rc = sqlite3_exec( db, sql, callbackq, NULL, &errmesg );
		 	printf("quering ;;;rc:%d SQLITE_OK=%d   errmesg=%s    count=%d rip=%s\n", rc, SQLITE_OK, errmesg, count, rip);
		 	//回调函数设置了ip
		 	sprintf (buf, "%s\n", rip);
		 	if(count == 0)
		 		sprintf (buf, "%s no record!\n", mac);
		 	send(connfd, buf, strlen(buf), 0);
		 	printf("send OK\n");
    }
		printf("%s, %s\n",buf, mac);
	}
	return 0;
}

