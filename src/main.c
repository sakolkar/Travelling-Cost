#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"
#include "Lab2IO.h"
#include <semaphore.h>

// Global Variables
int thread_count_;
int **dp_;
int city_count_;

sem_t ***sem_array;

// Function Signatures
void* thread_subcal(void *);

int main(int argc, char* argv[]) {
    long thread_i;
    pthread_t* thread_handles;
    double start, end;

    if (argc != 2) {
        fprintf(stderr, "Please indicate the number of threads!\n");
        exit(EXIT_FAILURE);
    }
    thread_count_ = strtol(argv[1], NULL, 10);

    thread_handles = malloc(thread_count_ * sizeof *thread_handles);

    Lab2_loadinput(&dp_, &city_count_);

    int i, j, k;
    sem_array = malloc(city_count_ * sizeof *sem_array);

    for (i = 0; i < city_count_; ++i) {
        sem_array[i] = malloc(city_count_ * sizeof *sem_array[i]);
        for (j = 0; j < city_count_; ++j) {
            sem_array[i][j] = malloc(city_count_ * sizeof *sem_array[i][j]);
            for (k = 0; k < city_count_; ++k) {
                sem_init(&sem_array[i][j][k],
                         0, // shared == 0; shared between threads
                         0);// init_value is set to zero
            } 
        }
    }


    for (i = 0; i < city_count_; ++i) {
        for (j = 0; j < city_count_; ++j) {
            sem_post(&sem_array[i][j][0]);
        }
    }

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
            for (j = 0; j < city_count_; ++j) {

                //printf("[%i] waiting on %d, %d, %d.\n", myrank, i, k, k);
                sem_wait(&sem_array[i][k][k]);
                sem_post(&sem_array[i][k][k]);

                //printf("[%i] waiting on %d, %d, %d.\n", myrank, k, j, k);
                sem_wait(&sem_array[k][j][k]);
                sem_post(&sem_array[k][j][k]);

                //printf("[%i] done waiting.\n", myrank);
                if ((temp = dp_[i][k]+dp_[k][j]) < dp_[i][j]) {
                    dp_[i][j] = temp;
                }

                sem_post(&sem_array[i][j][k+1]);
            }
        }
    }

    return NULL;
}
