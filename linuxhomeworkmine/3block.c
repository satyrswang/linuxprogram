#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
main()
{
pid_t pc,pr;
pc=fork();
if(pc<0) 
printf("error ocurred!\n");
else if(pc==0){ 
printf("This is child process with pid of %d\n",getpid());
sleep(10); 
}
else{ 
printf("Now in parent process, pid = %d\n", getpid()); 
printf("I am waiting child process to exit.\n"); 
pr = wait(NULL);  
if ( pr > 0 )  
printf("I catched a child process with pid of %d\n", pr); 
} 
exit(0);
}

