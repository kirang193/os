#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

long long fib[100];

// thread function
void *thread_function(void *var) {
	int n = atoi(var);
	fib[0] = 0;
	fib[1] = 1;
	for (int i = 2; i < n; i++) {
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	pthread_exit(0);
}

int main(int argc, char *argv[]) {

    // suppose ./a.out 10 -> argc = 2, argv = ['./a.out', '10']
    // to cast char string to number, we use atoi()
	pthread_t tid;

	if (argc!=2 || atoi(argv[1]) <= 0) {
		printf("pass single +ve number as cmd arg\n");
		return 0;
	}
	// create the thread.
	pthread_create(&tid, NULL, thread_function, argv[1]);

	// parent thread will wait for the child thread to exit.
	pthread_join(tid, NULL);

	// parent thread will output the fib sequence computed by the child thread i.e (thread_function).
	printf("First %d Fibonacci numbers : ",atoi(argv[1]));
	for (int i = 0; i < atoi(argv[1]); i++) {
		printf("%lld ", fib[i]);
	}
	printf("\n");

	return 0;
}
