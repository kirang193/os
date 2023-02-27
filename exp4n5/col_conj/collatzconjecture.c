#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
int main(int argc, char *argv[])
{
	 // suppose ./a.out 10 -> argc = 2, argv = ['./a.out', '10']
    	// to cast char string to number, we use atoi()
	int n = atoi(argv[1]);
	pid_t pid;
	pid = fork();
    	if (pid == 0){
        	// inside child process
		printf("Child play!!\n");
		printf("%d\n",n);
		while (n != 1){
			if (n%2)
                		n = 3 * (n) + 1;
			else
				n = n/2;
			printf("%d\n",n);
		}
		printf("Child has finished!!.\n");
	}else{
		// inside parent process
        	printf("Parent waits!!\n");
        	wait();
        	printf("Parent has finished.\n");
	}
	return 0;
}
