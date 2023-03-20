#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define N 100000
long int A[N][N];
long int B[N][N];
long int C[N][N];
long int D[N][N];
void *runner(void *param) {
	long int row = (long int) param;
	for (long int col = 0; col < N; col++) {
		for (long int k = 0; k < N; k++) {
			C[row][col] += A[row][k] * B[k][col];
		}
	}
	pthread_exit(0);
}
void printMatrix(long int arr[][N], char c) {
	printf("Matrix %c :\n", c);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%ld ", arr[i][j]);
		}
		printf("\n");
	}
	printf("----------\n");
}

int main() {
    
	for (long int i = 0; i < N; i++) { 
		for (long int j = 0; j < N; j++) {
			A[i][j] = rand() % 10;
			B[i][j] = rand() % 10;
		}
	}
	printMatrix(A, 'A');
	printMatrix(B, 'B');
    clock_t start1,end1;
    start1 = clock();
	pthread_t threads[N];

	for (long int i = 0; i < N; i++) {
		pthread_create(&threads[i], NULL, runner, (void *) i);
        // create threads with thread id, runner subroutine ,i as parameter
	}

	for (long int i = 0; i < N; i++) {
		pthread_join(threads[i], NULL);
        // used to wait for termination of thread
	}

	printMatrix(C, 'C');
    end1 = clock();
    double time_taken = ((double)(end1-start1))/CLOCKS_PER_SEC; // in seconds
 
    printf("program of mat_mul using threads took %f seconds to execute \n", time_taken);

    clock_t start2,end2;
    start2 = clock();
    for(long int i =0 ; i < N; i++) {
        for(long int j = 0; j < N; j++) {
            for(long int k = 0; k < N; k++ ){
                D[i][k] += A[i][k]*B[k][j];
            }
        }
    }
    printMatrix(D, 'D');
    end2 = clock();
    double time_taken2 = ((double)end2-start2)/CLOCKS_PER_SEC; // in seconds
    printf("program of mat_mul without using threads took %f seconds to execute \n", time_taken2);
	return 0;
}
