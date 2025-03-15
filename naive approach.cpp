#include <stdio.h>
#include <sys/time.h>  // Include the header for gettimeofday
int main() {
    struct timeval start_t, end_t;  // Use struct timeval for time measurements
    int idMatrix[100][100];
    int idxBirthYearMatrix[100][100];
    int multiplicationMatrix[100][100];
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
    gettimeofday(&start_t, NULL);  // Get the start time

    // multiplication process
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            multiplicationMatrix[i][j] = 0;
            for(int k = 0; k < 100; k++){
                multiplicationMatrix[i][j] += (idMatrix[i][k] * idxBirthYearMatrix[k][j]);

            }
        }
    }
    gettimeofday(&end_t, NULL);  // Get the end time
    double elapsed_time = (end_t.tv_sec - start_t.tv_sec) + (end_t.tv_usec - start_t.tv_usec) / 1000000.0;
    printf("\nThe time of the naive approach is %f ",elapsed_time);

    // print the result matrix
    printf("\n\nThe final matrix : \n");
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            printf("%d ", multiplicationMatrix[i][j]);
        }
    }



    return 0;
}




