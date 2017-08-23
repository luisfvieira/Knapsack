#include "knapsack.h"

Knapsack BestImprovement(Knapsack knapsack, Item* itens) {
    Knapsack nextKnapsack, currentKnapsack;

    nextKnapsack = copyKnapsack(knapsack);
    currentKnapsack = copyKnapsack(knapsack);
    for (int i = 0; i < knapsack.itensNum; i++) {
        if (addItem(&nextKnapsack, itens[i]) == 1) {
            if (nextKnapsack.profit > currentKnapsack.profit)
                currentKnapsack = copyKnapsack(nextKnapsack);

        }
        else {
            for (int j = 0; j < knapsack.itensNum; j++)
                if (exchangeItem(&nextKnapsack, itens[i], itens[j]) == 1) {
                    if (nextKnapsack.profit > currentKnapsack.profit)
                        currentKnapsack = copyKnapsack(nextKnapsack);
                }
        }
    }
    return currentKnapsack;
}
