#include "item.h"

//  Inicializa a  Mochila
Knapsack initializeKnapsack(int itensNum, int capacity) {
    Knapsack knapsack;
    knapsack.weight = 0;
    knapsack.profit = 0;
    knapsack.capacity = capacity;
    knapsack.itens = (int*) calloc(itensNum, sizeof(int));

    return knapsack;
}

//  Verifica por Conflitos na Mochila
int conflictCheck(Knapsack knapsack, Item item) {
    if (knapsack.itens[item.itemId] != 1 && knapsack.capacity >= item.weight)
        for (int i = 0; i < item.conflictNum; i++)
            if (knapsack.itens[item.conflitantItems[i]] == 1)
                return 0;
    return 1;
}


int addItem(Knapsack* knapsack, Item item) {
    if (conflictCheck(knapsack, item) == 1)
        knapsack->weight += item.weight;
        knapsack->profit += item.profit;
        knapsack->capacity -= item.weight;
        knapsack->itens[item.itemId] = 1;

        return 1;
    }
    else
        return 0;
}

int removeItem(Knapsack* knapsack, Item item) {
    if (knapsack->itens[itemId] == 1)
        knapsack->weight -= item.weight;
        knapsack->profit -= item.profit;
        knapsack->capacity += item.weight;
        knapsack->itens[item.itemId] = 0;

        return 1;
    }
    else
        return 0;
}
