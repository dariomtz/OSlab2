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

void shutdownHandler(int sig){
	if (sig != SIGUSR1) return;
    printf("I was sent to die %d\n", getpid());
	kill(getppid(), SIGUSR1);
	//exit(0);
}

int main(){
    file = fopen("./passwd.txt", "r");
    char *argv[] = {NULL};

    signal(SIGUSR1, shutdownHandler);

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
                        execvp("./sh", argv);
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