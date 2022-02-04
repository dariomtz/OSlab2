#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

char username[50];
char password[50];
char buffer[50];
FILE *file;
int f;
int initPid;

void shutdownHandler(int sig){
	if (sig != SIGUSR1) return;
    if(initPid != 0)
	    kill(initPid, SIGUSR1);
    else 
        exit(0);
}

int main(int argc, char *argv[]){
    char *sh = "./sh";
    char *arguments[] = {sh, NULL};

    if(argc == 2){
        // initPid was supplied
        initPid = atoi(argv[1]);
    }
    
    signal(SIGUSR1, shutdownHandler);

    file = fopen("./passwd.txt", "r");
    while(1){
        printf("usernamme: ");
        scanf(" %[^\n]", username); 
        printf("password: ");
        scanf(" %[^\n]", password);
        
        //read until ':' char
        while(fscanf(file, " %[^:]", buffer) != EOF){
            if (strcmp(username, buffer)==0){
                // skip ':' char
                fscanf(file, " %c", buffer);
                fscanf(file, " %[^\n]", buffer);

                if(strcmp(password, buffer)==0){
                    f = fork();
                    if (!f)
                        execvp(sh, arguments);
                    wait(NULL);
                }
            }else // skip rest of line
                fscanf(file, " %[^\n]", buffer);
        }
        rewind(file);
    }
    fclose(file);
    
    return 0;
}