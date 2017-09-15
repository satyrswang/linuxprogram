#include<sys/types.h>  #include<unistd.h>  #include<stdio.h>  int main()  {  pid_t pid;  int cnt = 0;  pid = fork(); 
 if(pid<0)  printf("error in fork!\n");  else if(pid == 0)  
{  cnt++;  printf("cnt=%d\n",cnt);  printf("I am the child process,ID is %d\n",getpid());  }  else  {  cnt++;  printf("cnt=%d\n",cnt);  printf("I am the parent process,ID is %d\n",getpid());  }  return 0;  }  

fork的执行结果：
cnt=1  
I am the child process,ID is 4711  
cnt=1  
I am the parent process,ID is 4710 

vfork的执行结果：
cnt=1  
I am the child process,ID is 4711  
cnt=2  
I am the parent process,ID is 4710  


fork（）是复制了父进程的资源，新开了一个地址，所以是对各自的cnt进行操作
vfork（）是和父进程共享地址空间，所以对同一个cnt进行操作


#include<sys/types.h>  #include<unistd.h>  #include<stdio.h>  int main()  {  pid_t pid;  int cnt = 0;  pid = vfork();  if(pid<0)  printf("error in fork!\n");  else if(pid == 0)  {  cnt++;   printf("cnt=%d\n",cnt);  printf("I am the child process,ID is %d\n",getpid());   _exit(0);  }  else  {  cnt++;   printf("cnt=%d\n",cnt);  printf("I am the parent process,ID is %d\n",getpid());  }  return 0;  }  

 运行结果
Child process 6427, data 10
Child process 6427, data 20
Parent process 6426, data 10
第 1个Child process 6427, data 10是因为子进程创建时task_struct的mm直接拷贝自parent的mm；
第2个Child process 6427, data 20是因为子进程进行了“写时拷贝”，有了自己的dataa；
第3个Parent process 6426, data 10输出10是因为子进程的data和父进程的data不是同一份。



内核只为新生成的子进程创建虚拟空间结构，它们来复制于父进程的虚拟究竟结构，
但是不为这些段分配物理内存，它们共享父进程的物理空间，当父子进程中有更改相应段的行为发生时，
再为子进程相应的段分配物理空间。






