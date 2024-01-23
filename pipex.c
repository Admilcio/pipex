#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int id = fork();
    int n;
    if(id == 0) {
        n = 1;
    }else{
        n = 6;
    }
    if(id != 0)
        wait(NULL);    int i;
    printf("Process %d: ", id);
    for(i = n; i < n + 5; i++)
    {
        printf("%d ", i);
        //fflush(stdout);
    }
    if(id != 0)
        printf("\n");
    return 0;
}