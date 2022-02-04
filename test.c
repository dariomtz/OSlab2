#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int i = 10;
    while(i--){
        printf("Test test %d\n", getpid());
        sleep(1);
    }
    return 0;
}