#ifndef _KNAPSACK_H
#define _KNAPSACK_H

typedef struct {
    int * itens;
    int weight;
    int capacity;
    int profit;
} Knapsack;

void InitializeKnapsack();

#endif
