#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "knapsack.h"

int checktime(double, clock_t);
Knapsack BestImprovement(Knapsack, Item*);

Knapsack Shake(Knapsack knapsack, Item *itens, int k) {
    srand(time(NULL));

    Knapsack kShake = initializeKnapsack(knapsack.itensNum, knapsack.capacity,
        knapsack.conflicts);
    int i, random, compSize = knapsack.itensNum - itens[k].conflictNum;
    if (compSize > 0) {
        random = rand() % compSize;
        i = 0;
        int conflictCompl[compSize];

        for (int j = 0; j < knapsack.itensNum; j++)
            if (knapsack.conflicts[k][j] == 0) {
                conflictCompl[i] = j;
                i++;
            }
        int randValue = conflictCompl[random];
        addItem(&kShake, itens[randValue]);
    }
    return kShake;
}

int NeighborhoodChange(Knapsack *current, Knapsack kBest, int k) {
    if (kBest.profit > current->profit) {
        *current = copyKnapsack(kBest);
        k = 1;
    }
    else
        k++;
    return k;
}
/**
    TODO create a method for kMax estimation
**/
Knapsack BVNS(Knapsack knapsack, Item *itens, int kMax, double tMax) {
    Knapsack kShake, kBest, currentKnapsack;
    int k;
    clock_t initialTime = clock();

    //  kMax = knapsack.itensNum;
    kShake = initializeKnapsack(knapsack.itensNum, knapsack.capacity, knapsack.conflicts);
    kBest = initializeKnapsack(knapsack.itensNum, knapsack.capacity, knapsack.conflicts);
    currentKnapsack = initializeKnapsack(knapsack.itensNum, knapsack.capacity, knapsack.conflicts);
    while (checktime(tMax, initialTime)) {
        k = 0;
        while (k < kMax) {
            kShake = Shake(knapsack, itens, k);
            kBest = BestImprovement(kShake, itens);
            k = NeighborhoodChange(&currentKnapsack, kBest, k);
        }
    }

    return currentKnapsack;
}
