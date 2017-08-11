#include <stdlib.h>

#include "knapsack.h"
#include "item.h"

#ifndef _KNAPSACK_H
#define _KNAPSACK_H

typedef struct {
    int * itens;
    int weight;
    int capacity;
    int profit;
} Knapsack;

void InitializeKnapsack(Knapsack, int, int);
int addItem(Knapsack, Item);
int removeItem(Knapsack, Item);

#endif
