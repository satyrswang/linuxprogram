#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#define SIG_USER 1

void SigUserProc()

{

     int status;

     wait(&status); 

}
main()
{
pid_t pc,pr;
int status;

signal(SIG_USER, SigUserProc);
pc=fork();
if(pc<0) 
printf("error ocurred!\n");
else if(pc==0){ 
printf("This is child process with pid of %d\n",getpid());


kill(getpid(), SIG_USER);
printf("after kill\n");
sleep(10);
return; 
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
