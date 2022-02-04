#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

char  cmd[80];

void main(){
	pid_t p;
	char* argv[2] = {NULL,NULL};
	printf(">");
	while(scanf("%s",cmd),strcmp(cmd,"exit") && strcmp(cmd,"shutdown")){
		p = fork();
		argv[0] = cmd;
		if(!p){
			execvp(cmd, argv);
		}
		wait(NULL);
		printf(">");
	}

}