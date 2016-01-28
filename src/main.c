#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"
#include "Lab2IO.h"

// Global Variables
int thread_count_;
int **dp_;
int city_count_;

// Function Signatures
void* thread_subcal(void *);

int main(int argc, char* argv[]) {
	long thread_i;
	pthread_t* thread_handles;
	double start, end;

	if (argc != 2) {
		printf("Please indicate the number of threads!\n");
	}
	thread_count_ = strtol(argv[1], NULL, 10);

	Lab2_loadinput(&dp_, &city_count_);
	thread_handles = malloc(thread_count_ * sizeof *thread_handles);

	GET_TIME(start);
	for (thread_i = 0; thread_i < thread_count_; ++thread_i)
		pthread_create( &thread_handles[thread_i], 
				NULL, 
				thread_subcal, 
				(void*)thread_i);
	for (thread_i = 0; thread_i < thread_count_; ++thread_i)
		pthread_join(thread_handles[thread_i], NULL);
	GET_TIME(end);

	Lab2_saveoutput(dp_, city_count_, end-start);

	return EXIT_SUCCESS;
}

void* thread_subcal(void* rank) {
	long myrank = (long) rank;
	int i, j, k, temp;
	
	for (k = 0; k < city_count_; ++k){
		for (i = myrank * city_count_ / thread_count_; i < (myrank + 1) * city_count_ / thread_count_; ++i) {
			for (j = 0; j < city_count_; ++j)
				if ((temp = dp_[i][k]+dp_[k][j]) < dp_[i][j])
					dp_[i][j] = temp;
		}
	}
}
