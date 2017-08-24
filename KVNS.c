#include "KVNS.h"

//  Inicializa o Valor de K
KVNS initializeKVNS(KVNS k, int kMax, int movMax) {
    k.k = 0;
    k.movement = 0;
    k.kMax = kMax;
    k.movMax = movMax;

    return k;
}

//  Atualiza o Valor de K para o proximo
KVNS nextK(KVNS k) {
    k.k++;
    k.movement++;
    if (k.k > k.kMax && k.movement < k.movMax)
        k.k = 0;
    if (k.movement > k.movMax && k.k < k.kMax)
        k.movement = 0;

    return k;
}

//  Verifica se k atingiu o kMax (maximo)
int checkK(KVNS k) {
    if (k.k < k.kMax && k.movement < k.kMax)
        return 1;
    return 0;
}