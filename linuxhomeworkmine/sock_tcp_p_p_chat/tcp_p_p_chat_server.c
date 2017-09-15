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
    struct sockaddr_in my_addr, their_addr; //ipv4����ͨ��sockaddr�ṹ��
    unsigned int myport, lisnum;
    char buf[MAXBUF + 1];

    if (argv[2])
		myport = atoi(argv[2]);//���������ַ�ת��Ϊ�������ڶ˿�
    else
		myport = 5678;//Ĭ�϶˿�

    if (argv[3])
		lisnum = atoi(argv[3]);//�������д�С
	else
		lisnum = 5;//Ĭ��

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
    {
		perror("socket");
		exit(EXIT_FAILURE);
    }
//����socket(ͨ��Э�����ͣ�socket����(�������Ӻ�������)��ָ������Э��)��ip/tcp�������ļ�������������bind��һ������
    
    bzero(&my_addr, sizeof(my_addr));//����
    my_addr.sin_family = AF_INET;//Э������ ip
    my_addr.sin_port = htons(myport);//�ֽ�ת��Ϊ����˳��
    if (argv[1])
		my_addr.sin_addr.s_addr = inet_addr(argv[1]);//�ַ���ת��Ϊ32Ϊ������ip��ַ
    else
		my_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr))== -1) 
    {
		perror("bind");
		exit(EXIT_FAILURE);
    }//bind(�󶨱���ip��Ϣ���ļ���������sockaddrָ�룬(���ֵ�ַ���Ͳ�ͬ����)��ַ����)

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
} //�������Կͻ��˵���������their_addr��ʶ�󶨵���Ϣ�������µ��ļ�����������ʶ������.ԭ������������������
    else
        printf("server: got connection from %s, port %d, socket %d\n",inet_ntoa(their_addr.sin_addr),ntohs(their_addr.sin_port), new_fd);
 	  //��ӡ������ϢתΪ���ʮ���ƺ�short net to host
	if(-1==(pid=fork()))	//�����ӽ��̷�������
	{
		perror("fork");exit(EXIT_FAILURE);
	}
	else if( pid == 0)
	{
		while (1) 
		{
			bzero(buf, MAXBUF + 1);//������
			printf("input the message to send:");
			fgets(buf, MAXBUF, stdin);//��stdin�������ݷ��뻺����
			if (!strncasecmp(buf, "quit", 4)) 
			{
				printf("i will close the connect!\n");
				break;
			}//�������������quit��ر�����
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



