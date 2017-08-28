#include <stdio.h>

#include "knapsack.h"

Knapsack BestImprovement(Knapsack knapsack, Item* itens) {
    Knapsack nextKnapsack, currentKnapsack;
    int deleteFlag = 0;

    nextKnapsack = copyKnapsack(knapsack);
    currentKnapsack = copyKnapsack(knapsack);
    for (int i = 0; i < knapsack.itensNum; i++) {
        if (addItem(&nextKnapsack, itens[i]) == 1) {
            if (nextKnapsack.profit > currentKnapsack.profit) {
                currentKnapsack = copyKnapsack(nextKnapsack);
                break;
            }
        }
        else {
            for (int j = i + 1; j < knapsack.itensNum; j++)
                if (exchangeItem(&nextKnapsack, itens[i], itens[j]) == 1) {
                    deleteFlag = 1;
                    if (nextKnapsack.profit > currentKnapsack.profit) {
                        currentKnapsack = copyKnapsack(nextKnapsack);
                        break;
                    }
                }
        }
        if (deleteFlag == 0 && knapsack.itens[i] == 1) {
            removeItem(&nextKnapsack, itens[i]);
        }
    }
    return currentKnapsack;
}
