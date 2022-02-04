#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define MAXCHILDS 6

void shutdownHandler(int sig){
	if (sig != SIGUSR1) return;
	printf("I was sent to die %d\n", getpid());
	kill(0, SIGKILL);
}

void main(){

	signal(SIGUSR1, shutdownHandler);
	pid_t p;
	for(int i = 0; i< MAXCHILDS; i++){
		p = fork();
		if(!p)break;
	}
	while(p){
		wait(NULL);
		p = fork();
	}
	char *argv[] = {"xterm","-e","./getty",NULL};
	char *cmd = "xterm";
	if(!p){
		if(execvp(cmd,argv) == -1){
			printf("Hubo un error, soy %d\n",getpid());
		}
	}
}