#include <stdlib.h>

#include "item.h"

#ifndef _KNAPSACK_H
#define _KNAPSACK_H

typedef struct {
    int* itens;
    int ** conflicts;
    int itensNum;
    int weight;
    int capacity;
    int profit;
} Knapsack;

Knapsack initializeKnapsack(int, int, int**);
Knapsack copyKnapsack(Knapsack);
int conflictCheck(Knapsack, Item);
int addItem(Knapsack*, Item);
int removeItem(Knapsack*, Item);
int exchangeItem(Knapsack*, Item, Item);

#endif
