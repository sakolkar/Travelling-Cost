/*
Reference solution with barrier.

The matrix is partitioned by rows.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"
#include "Lab2IO.h"

int thread_count_;
int **dp_;  //pointer to the distance array
int city_count_;

pthread_barrier_t barr_;

void* thread_subcal (void* rank);

int main (int argc, char* argv[])
{
    long thread_i;
    pthread_t* thread_handle_pt;
    double start, end;
    
    if (argc < 2) {
        printf("Please indicate the number of threads!\n");
        return 1;
    }
    thread_count_ = strtol(argv[1], NULL, 10);
    
    Lab2_loadinput(&dp_, &city_count_);

    thread_handle_pt=malloc(thread_count_*sizeof(pthread_t));

    pthread_barrier_init(&barr_, NULL, thread_count_);

    GET_TIME(start);
    for (thread_i = 0; thread_i < thread_count_; ++thread_i)
        pthread_create(&thread_handle_pt[thread_i], NULL, thread_subcal, (void*)thread_i);
    for (thread_i = 0; thread_i < thread_count_; ++thread_i)
        pthread_join(thread_handle_pt[thread_i], NULL);
    GET_TIME(end);

    printf("The elapsed time is %lfs.\n", end-start);

    pthread_barrier_destroy(&barr_);
    free(thread_handle_pt);
    Lab2_saveoutput(dp_, city_count_, end-start);

    DestroyMat(dp_, city_count_);
    return 0;
}

void* thread_subcal(void* rank){
    long myrank = (long)rank;
    int i, j, k, temp;
    
    for (k = 0; k < city_count_; ++k){
        pthread_barrier_wait(&barr_);
        for (i = myrank * city_count_ / thread_count_; i < (myrank + 1) * city_count_ / thread_count_; ++i)
            for (j = 0; j < city_count_; ++j)
                if ((temp = dp_[i][k]+dp_[k][j]) < dp_[i][j])
                    dp_[i][j] = temp;
    }
    return 0;
}

