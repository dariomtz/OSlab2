#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define MAXCHILDS 6

void shutdownHandler(int sig){
	if (sig != SIGUSR1) return;
	kill(0, SIGKILL);
}

int main(){
	char pidStr[10];
	sprintf(pidStr, "%d", getpid());

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

	// Only child processes get here
	char *argv[] = {"xterm","-e","./getty", pidStr, NULL};
	char *cmd = "xterm";
	execvp(cmd,argv);

	// Return statement unreachable
	return 0;
}