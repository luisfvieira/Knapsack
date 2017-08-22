#include <stdio.h>
#include "knapsack.h"

void printKnapsack2(Knapsack knapsack) {
    printf("Knapsack\nCapacity: %d\nProfit: %d\nWeight: %d\n", knapsack.capacity,
        knapsack.profit, knapsack.weight);
    printf("ItensNum: %d\n", knapsack.itensNum);
    for (int i = 0; i < knapsack.itensNum; i++) {
        printf("%d ", knapsack.itens[i]);
    }
    printf("\n");
}

Knapsack BestImprovement(Knapsack knapsack, Item* itens) {
    Knapsack nextKnapsack, currentKnapsack;
    int delete;

    nextKnapsack = copyKnapsack(knapsack);
    currentKnapsack = copyKnapsack(knapsack);
    for (int i = 0; i < knapsack.itensNum; i++) {
        delete = 1;
        if (addItem(&nextKnapsack, itens[i]) == 1) {
            if (nextKnapsack.profit > currentKnapsack.profit)
                currentKnapsack = copyKnapsack(nextKnapsack);
            delete = 0;

        }
        else {
            for (int j = 0; j < knapsack.itensNum; j++)
                if (exchangeItem(&nextKnapsack, itens[i], itens[j]) == 1) {
                    if (nextKnapsack.profit > currentKnapsack.profit)
                        currentKnapsack = copyKnapsack(nextKnapsack);
                    delete = 0;
                }
        }
        // if (delete == 1)
        //     if (removeItem(&nextKnapsack, itens[i]) == 0)
        //         printf("Warning! Item wasn't removed!\n");
    }
    return currentKnapsack;
}
