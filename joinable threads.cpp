#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>  // Include the header for gettimeofday

#define NumberOfThreads 16
int multiplicationMatrix[100][100] = {0}; // Result matrix
int idMatrix[100][100];
int idxBirthYearMatrix[100][100];

// struct task to add to the thread pool
typedef struct Task {
    int start, end;
} Task;


// Thread function to process tasks
void *startThread(void *task) {
    struct Task *myTask = (struct Task*)task;

    // Process the task
    for (int x = myTask->start; x < myTask->end; x++) {
        for (int j = 0; j < 100; j++) {
            for (int k = 0; k < 100; k++) {
                multiplicationMatrix[x][j] += (idMatrix[x][k] * idxBirthYearMatrix[k][j]);
            }
        }
    }

    pthread_exit(NULL);

}


int main(int argc, char* argv[]) {
    struct timeval start_t, end_t;  // Use struct timeval for time measurements
    int id = 1210249;
    int ID[10]; // 1D array to contain id numbers
    int size1 = 0; //size of 1D id array

    // fill the id numbers into 1D array
    while(id > 0){
        ID[size1] = id % 10;
        size1++;
        id /= 10;
    }

    // reverse the array because it was filled reversed
    for(int i = 0; i < size1 / 2; i++){
        int temp = ID[i];
        ID[i] = ID[size1 - 1 - i];
        ID[size1 - 1 - i] = temp;
    }

    long long idMulBirth = 1210249l * 2003l;
    int idXbirthYear[20];// 1D array to contain (id * birth year) numbers
    int size2 = 0; // size of 1D id * BirthYear array

    // fill the id multiplied with the birth year into 1D array
    while(idMulBirth > 0){
        idXbirthYear[size2] = idMulBirth % 10;
        idMulBirth /= 10;
        size2++;
    }
    // reverse the array because it was filled reversed
    for(int i = 0; i < size2 / 2; i++){
        int temp = idXbirthYear[i];
        idXbirthYear[i] = idXbirthYear[size2 - 1 - i];
        idXbirthYear[size2 - 1 - i] = temp;
    }

    // fill the id matrix and id * birth year matrix
    int k = 0,l =0;
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 100; j++){
            if(k == size1) k = 0; // when the id ends start over
            if(l == size2) l = 0; // when the id * birth year number ends start over
            idMatrix[i][j] = ID[k];
            idxBirthYearMatrix[i][j] = idXbirthYear[l];
            l++;
            k++;
        }
    }

    int splitIndex = 100 / NumberOfThreads;
    pthread_t th[NumberOfThreads];

    gettimeofday(&start_t, NULL);  // Get the start time

    for (int i = 0; i < NumberOfThreads; i++) {
        int start = i * splitIndex;
        int end = (i == NumberOfThreads - 1) ? 100 : (i + 1) * splitIndex;
        struct Task *t = (struct Task *)malloc(sizeof(struct Task));
        t->start = start;
        t->end = end;
        // Create threads to process tasks
        if (pthread_create(&th[i], NULL, startThread, (void *)t) != 0) {
            printf("Failed to create the thread");
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < NumberOfThreads; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            printf("Failed to join the thread");
        }
    }

    gettimeofday(&end_t, NULL);  // Get the end time

    // Calculate the elapsed time in seconds
    double elapsed_time = (end_t.tv_sec - start_t.tv_sec) + (end_t.tv_usec - start_t.tv_usec) / 1000000.0;
    printf("\nThe time of the multithreading approach is %f seconds", elapsed_time);

    // print the result matrix
    printf("\n\nThe final matrix : \n");
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            printf("%d ", multiplicationMatrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
