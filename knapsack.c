#include "item.h"

//  Inicializa a  Mochila
Knapsack initializeKnapsack(Knapsack knapsack, int itensNum, int capacity) {
    knapsack.weight = 0;
    knapsack.profit = 0;
    knapsack.capacity = capacity;
    knapsack.itens = (int*) malloc(sizeof(int) * itensNum);
    for (int i = 0; i < itensNum; i++)
        knapsack.itens[i] = 0;
}

int addItem(Knapsack knapsack, Item item) {
    if (knapsack.itens[itemId] != 1 && knapsack.capacity >= item.weight)
        knapsack.weight += item.weight;
        knapsack.profit += item.profit;
        knapsack.capacity -= item.weight;
        knapsack.itens[item.itemId] = 1;

        return 1;
    }
    else
        return 0;
}

int removeItem(Knapsack knapsack, Item item) {
    if (knapsack.itens[itemId] == 1)
        knapsack.weight -= item.weight;
        knapsack.profit -= item.profit;
        knapsack.capacity += item.weight;
        knapsack.itens[item.itemId] = 0;

        return 1;
    }
    else
        return 0;
}
