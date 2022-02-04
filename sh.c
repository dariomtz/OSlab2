#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

char buffer[80];
char cmd[80];
char c;

int main(){
	pid_t p;
    int i;
	char* argv[] = { NULL, NULL };
	while(1) {
		printf(">");
        scanf(" %[^\n]",buffer);
        // contar espacios
        // revisar si la ultima palabra es &
        // restar un espacio
        // hacer un maloc con ese int
        sscanf(buffer, " %s", cmd);

        if(strcmp(cmd,"exit") == 0)
            break;
        
        if(strcmp(cmd,"shutdown") == 0){
            kill(getppid(), SIGUSR1);
        }

        i = 0;
        while(buffer[i] != '\0' && buffer[i] != '&')
            i++;
        
		p = fork();
		argv[0] = cmd;
		if(!p)
			if(execvp(cmd, argv) == -1){
                printf("Command not found: %s\n", cmd);
                exit(0);
            }

        if(buffer[i] != '&')
		    wait(NULL);
        
	}

    return 0;
}