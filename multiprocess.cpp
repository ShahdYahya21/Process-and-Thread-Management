#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>  // Include the header for gettimeofday

#define ARRAY_SIZE 100
#define NUM_CHILDREN 8

int main() {
    struct timeval start_t, end_t;  // Use struct timeval for time measurements
    int idMatrix[100][100];
    int idxBirthYearMatrix[100][100];
    int multiplicationMatrix[100][100];
    int id = 1210249;
    int ID[10]; // 1D array to contain id numbers
    int size1 = 0; // size of 1D id array

    // fill the id numbers into 1D array
    while (id > 0) {
        ID[size1] = id % 10;
        size1++;
        id /= 10;
    }

    // reverse the array because it was filled reversed
    for (int i = 0; i < size1 / 2; i++) {
        int temp = ID[i];
        ID[i] = ID[size1 - 1 - i];
        ID[size1 - 1 - i] = temp;
    }

    long long idMulBirth = 1210249l * 2003l;
    int idXbirthYear[20]; // 1D array to contain (id * birth year) numbers
    int size2 = 0; // size of 1D id * BirthYear array

    // fill the id multiplied with the birth year into 1D array
    while (idMulBirth > 0) {
        idXbirthYear[size2] = idMulBirth % 10;
        idMulBirth /= 10;
        size2++;
    }

    // reverse the array because it was filled reversed
    for (int i = 0; i < size2 / 2; i++) {
        int temp = idXbirthYear[i];
        idXbirthYear[i] = idXbirthYear[size2 - 1 - i];
        idXbirthYear[size2 - 1 - i] = temp;
    }

    // fill the id matrix and id * birth year matrix
    int k = 0, l = 0;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            if (k == size1)
                k = 0;
            if (l == size2)
                l = 0;
            idMatrix[i][j] = ID[k];
            idxBirthYearMatrix[i][j] = idXbirthYear[l];
            l++;
            k++;
        }
    }
    int rows_per_child = ARRAY_SIZE / NUM_CHILDREN + 1; // Rows assigned to each child(I added 1 to avoid missing any row when the number of children is negative)
    int pipe_fds[NUM_CHILDREN][2]; //create a pipe for each child
    gettimeofday(&start_t, NULL);  // Get the start time

    for (int i = 0; i < NUM_CHILDREN; i++) {
        if (pipe(pipe_fds[i]) == -1) {
            perror("Pipe creation failed");
            return 1;
        }
    }

    pid_t pids[NUM_CHILDREN]; // create pid for each child

    for (int i = 0; i < NUM_CHILDREN; i++) {
        pids[i] = fork(); // creating a child
        if (pids[i] < 0) {
            printf("Fork failed");
        }
        else if (pids[i] == 0) {
            // Child process
            close(pipe_fds[i][0]);

            // To store the child result
            int ans_child[rows_per_child][ARRAY_SIZE];

            // Initialize the array elements to zero
            for (int i = 0; i < rows_per_child; i++) {
                for (int j = 0; j < ARRAY_SIZE; j++) {
                    ans_child[i][j] = 0;
                }
            }
            // calculate the start and end of the rows assigned to the child
            int start_row = i * rows_per_child;
            int end_row = (i == NUM_CHILDREN - 1) ? ARRAY_SIZE : (i + 1) * rows_per_child;

            // evaluate the child multiplication
            for (int x = start_row; x < end_row; x++) {
                for (int j = 0; j < ARRAY_SIZE; j++) {
                    ans_child[x - start_row][j] = 0;
                    for (k = 0; k < ARRAY_SIZE; k++) {
                        ans_child[x - start_row][j] += (idMatrix[x][k] * idxBirthYearMatrix[k][j]);
                    }
                }
            }

            // Write the result to the pipe
            write(pipe_fds[i][1], ans_child, sizeof(ans_child));

            close(pipe_fds[i][1]);
            exit(0); // Exit the child process
        }
    }

    for (int i = 0; i < NUM_CHILDREN; i++) {
        close(pipe_fds[i][1]);
        waitpid(pids[i], NULL, 0); // wait for child process
        int temp_result[rows_per_child][ARRAY_SIZE]; // To store the child array
        read(pipe_fds[i][0], temp_result, sizeof(temp_result));
        close(pipe_fds[i][0]);
        int start_row = i * rows_per_child;
        int end_row = (i == NUM_CHILDREN - 1) ? ARRAY_SIZE : (i + 1) * rows_per_child;

        // add the partial array to the final array
        for (int x = start_row; x < end_row; x++) {
            for (int j = 0; j < ARRAY_SIZE; j++) {
                multiplicationMatrix[x][j] += temp_result[x - start_row][j];
            }
        }
    }

    gettimeofday(&end_t, NULL);  // Get the end time
    double elapsed_time = (end_t.tv_sec - start_t.tv_sec) + (end_t.tv_usec - start_t.tv_usec) / 1000000.0;
    int x = NUM_CHILDREN;
    printf("\nThe time of the multiprocess approach is %f  (%d children) ", elapsed_time,x);

    // Print the final result matrix
    printf("\n\nResult Matrix:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        for (int j = 0; j < ARRAY_SIZE; j++) {
            printf("%d ", multiplicationMatrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}



