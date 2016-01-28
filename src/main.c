#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <timer.h>
#include <Lab2IO.h>

// Global Variables
int thread_count_;
int **dp_;
int city_count_;

// Function Signatures


int main(int argc, char* argv[]) {
	long thread_i;
	pthread_t* thread_handles;
	double start, end;

	if (argc != 2) {
		printf("Please indicate the number of threads!\n");
	}
	thread_count_ = strtol(argc[1], NULL, 10);

	Lab2_loadinput(&dp_, &city_count_);

	thread_handles = malloc(thread_count_ * sizeof *thread_handles);

	GET_TIME(start);
	for (thread_i = 0; thread_i < thread_count_; ++thread_i)
		pthread_create( &thread_handle_pt[thread_i], 
				NULL, 
				thread_subcal, 
				(void*)thread_i);
	for (thread_i = 0; thread_i < thread_count_; ++thread_i)
		pthread_join(thread_handle_pt[thread_i], NULL);
	GET_TIME(end);

	return EXIT_SUCCESS;
}
