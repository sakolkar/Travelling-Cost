/*
Test the result stored in the "data_output" by a serial version of calculation

-----
Compiling:
    "Lab2IO.c" should be included, like
    > gcc serialtester.c Lab2IO.c -o serialtester
*/

#include <stdio.h>
#include <stdlib.h>
#include "Lab2IO.h"

int main (int argc, char* argv[]) {
    int i, j, k, city_count, temp;
    int **dp;
    FILE* fp;
    double Time;

    /*Load the input data and calculate the result*/
    Lab2_loadinput(&dp, &city_count);
    for (k = 0; k < city_count; ++k)
        for (i = 0; i < city_count; ++i)
            for (j = 0; j < city_count; ++j)
                if ((temp = dp[i][k]+dp[k][j]) < dp[i][j])
                    dp[i][j] = temp;
    /*Load the result and compare*/
    if ((fp = fopen("data_output", "r")) == NULL) {   
        printf("Fail to open the result data!\n");
        return 1;
    }
    fscanf(fp, "%d\n\n", &temp);
    if (temp != city_count){   
        fclose(fp);
        printf("Input data size does not match the result size!\n");
        return -2;
    }

    /*Compare the result with the reference*/
    fscanf(fp, "%lf\n\n", &Time);
    for (i = 0; i < city_count; ++i) {
        for (j = 0; j < city_count; ++j){
            fscanf(fp, "%d\t", &temp);
            if (temp != dp[i][j]){
                fclose(fp);
                DestroyMat(dp, city_count);
                printf("The result is wrong.\n");
                return -1;
            }
        }
        fscanf(fp, "\n");
    }
    fclose(fp);
    DestroyMat(dp, city_count);
    printf("Congratulations! The result is correct!\n");
    return 0;
}
