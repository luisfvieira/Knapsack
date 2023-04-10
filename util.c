#include <stdlib.h>
#include <time.h>

/**
    There is a time limit. This function verifies if it was reached
*/
int checktime(double timeLimit, clock_t initialTime) {
    clock_t finalTime = clock();
    double dTime = ((finalTime - initialTime) * 1000.0) / CLOCKS_PER_SEC;

    if (dTime < timeLimit)
        return 1;
    return 0;
}
