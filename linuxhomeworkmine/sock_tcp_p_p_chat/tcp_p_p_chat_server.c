#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAXBUF 1024

int main(int argc, char *argv[])
{
    int pid;	
    int sockfd, new_fd;
    socklen_t len;// typedef socklen_t int
    struct sockaddr_in my_addr, their_addr; //ipv4网络通信sockaddr结构体
    unsigned int myport, lisnum;
    char buf[MAXBUF + 1];

    if (argv[2])
		myport = atoi(argv[2]);//将命令行字符转换为整数用于端口
    else
		myport = 5678;//默认端口

    if (argv[3])
		lisnum = atoi(argv[3]);//监听队列大小
	else
		lisnum = 5;//默认

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
    {
		perror("socket");
		exit(EXIT_FAILURE);
    }
//创建socket(通信协议类型，socket类型(面向连接和无连接)，指定具体协议)，ip/tcp，返回文件描述符，用于bind第一个参数
    
    bzero(&my_addr, sizeof(my_addr));//置零
    my_addr.sin_family = AF_INET;//协议类型 ip
    my_addr.sin_port = htons(myport);//字节转换为网络顺序
    if (argv[1])
		my_addr.sin_addr.s_addr = inet_addr(argv[1]);//字符串转化为32为的网络ip地址
    else
		my_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr))== -1) 
    {
		perror("bind");
		exit(EXIT_FAILURE);
    }//bind(绑定本地ip信息的文件描述符，sockaddr指针，(多种地址类型不同长度)地址长度)

    if (listen(sockfd,lisnum ) == -1) 
    {
		perror("listen");
		exit(EXIT_FAILURE);
    }
    printf("wait for connect\n");	
    len = sizeof(struct sockaddr);
    if ((new_fd =accept(sockfd, (struct sockaddr *) &their_addr,&len)) == -1) 
    {
        perror("accept");
        exit(EXIT_FAILURE);
} //接收来自客户端的连接请求，their_addr标识绑定的信息，返回新的文件描述符来标识该连接.原来的描述符继续监听
    else
        printf("server: got connection from %s, port %d, socket %d\n",inet_ntoa(their_addr.sin_addr),ntohs(their_addr.sin_port), new_fd);
 	  //打印连接信息转为点分十进制和short net to host
	if(-1==(pid=fork()))	//创建子进程发送数据
	{
		perror("fork");exit(EXIT_FAILURE);
	}
	else if( pid == 0)
	{
		while (1) 
		{
			bzero(buf, MAXBUF + 1);//缓冲区
			printf("input the message to send:");
			fgets(buf, MAXBUF, stdin);//将stdin流中数据放入缓冲区
			if (!strncasecmp(buf, "quit", 4)) 
			{
				printf("i will close the connect!\n");
				break;
			}//如果传来数据是quit则关闭连接
			len = send(new_fd, buf, strlen(buf) - 1, 0);
	  		if (len < 0)
			 {
				printf("message'%s' send failure!errno code is %d,errno message is '%s'\n",
				buf, errno, strerror(errno));
				break;
			}
		}
	}
	else 
	{	
		while(1)
		{
			bzero(buf, MAXBUF + 1);
			len = recv(new_fd, buf, MAXBUF, 0);
			if (len > 0)
				printf("message recv successful :'%s',%dByte recv\n",buf, len);
			else if (len < 0)
			{
				printf("recv failure!errno code is %d,errno message is '%s'\n",
				errno, strerror(errno));
				break;
			}
			else
			{
				printf("the other one close the connection\n");
				break;
			}
		}
	}
	close(new_fd);
	close(sockfd);
    	return 0;
}



