#include<sys/types.h>  #include<unistd.h>  #include<stdio.h>  int main()  {  pid_t pid;  int cnt = 0;  pid = fork(); 
 if(pid<0)  printf("error in fork!\n");  else if(pid == 0)  
{  cnt++;  printf("cnt=%d\n",cnt);  printf("I am the child process,ID is %d\n",getpid());  }  else  {  cnt++;  printf("cnt=%d\n",cnt);  printf("I am the parent process,ID is %d\n",getpid());  }  return 0;  }  

fork��ִ�н����
cnt=1  
I am the child process,ID is 4711  
cnt=1  
I am the parent process,ID is 4710 

vfork��ִ�н����
cnt=1  
I am the child process,ID is 4711  
cnt=2  
I am the parent process,ID is 4710  


fork�����Ǹ����˸����̵���Դ���¿���һ����ַ�������ǶԸ��Ե�cnt���в���
vfork�����Ǻ͸����̹����ַ�ռ䣬���Զ�ͬһ��cnt���в���


#include<sys/types.h>  #include<unistd.h>  #include<stdio.h>  int main()  {  pid_t pid;  int cnt = 0;  pid = vfork();  if(pid<0)  printf("error in fork!\n");  else if(pid == 0)  {  cnt++;   printf("cnt=%d\n",cnt);  printf("I am the child process,ID is %d\n",getpid());   _exit(0);  }  else  {  cnt++;   printf("cnt=%d\n",cnt);  printf("I am the parent process,ID is %d\n",getpid());  }  return 0;  }  

 ���н��
Child process 6427, data 10
Child process 6427, data 20
Parent process 6426, data 10
�� 1��Child process 6427, data 10����Ϊ�ӽ��̴���ʱtask_struct��mmֱ�ӿ�����parent��mm��
��2��Child process 6427, data 20����Ϊ�ӽ��̽����ˡ�дʱ�������������Լ���dataa��
��3��Parent process 6426, data 10���10����Ϊ�ӽ��̵�data�͸����̵�data����ͬһ�ݡ�



�ں�ֻΪ�����ɵ��ӽ��̴�������ռ�ṹ�������������ڸ����̵����⾿���ṹ��
���ǲ�Ϊ��Щ�η��������ڴ棬���ǹ������̵�����ռ䣬�����ӽ������и�����Ӧ�ε���Ϊ����ʱ��
��Ϊ�ӽ�����Ӧ�Ķη�������ռ䡣






