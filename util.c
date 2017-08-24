#include <stdlib.h>
#include <time.h>


/**
    Retorna o valor do tempo
*/
double returnTime(clock_t initialTime) {
    clock_t actual = clock();
    return ((actual - initialTime) / CLOCKS_PER_SEC);
}

/**
    Verifica se o tempo limite foi atingido.
*/
int checktime(double timeLimit, clock_t initialTime) {
    double dTime = returnTime(initialTime);

    if (dTime < timeLimit)
        return 1;
    return 0;
}
