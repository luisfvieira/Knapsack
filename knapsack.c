C#include "knapsack.h"

//  Inicializa a  Mochila
Knapsack initializeKnapsack(int itensNum, int capacity) {
    Knapsack knapsack;

    knapsack.itensNum = itensNum;
    knapsack.weight = 0;
    knapsack.profit = 0;
    knapsack.capacity = capacity;
    knapsack.itens = (int*) calloc(itensNum, sizeof(int));
    knapsack.conflicts = (int **) calloc(itensNum, sizeof(int));
    for (int i = 0; i < itensNum; i++)
        knapsack.conflicts

    return knapsack;
}

//  Copia Uma Mochila
Knapsack copyKnapsack(Knapsack knapsack) {
    Knapsack copy;

    copy = knapsack;
    copy.itens = (int*) calloc(copy.itensNum, sizeof(int));
    for (int i = 0; i < knapsack.itensNum; i++)
        copy.itens[i] = knapsack.itens[i];
    return copy;
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
    if (conflictCheck(*knapsack, item) == 1) {
        knapsack->weight += item.weight;
        knapsack->profit += item.profit;
        knapsack->itens[item.itemId] = 1;

        return 1;
    }
    return 0;
}

int removeItem(Knapsack* knapsack, Item item) {
    if (knapsack->itens[item.itemId] == 1) {
        knapsack->weight -= item.weight;
        knapsack->profit -= item.profit;
        knapsack->itens[item.itemId] = 0;

        return 1;
    }
    return 0;
}

int exchangeItem(Knapsack* knapsack, Item item1, Item item2) {
    Knapsack knapsackAux = copyKnapsack(*knapsack);
    int removeAnswer, addAnswer;

    removeAnswer = removeItem(&knapsackAux, item1);
    addAnswer = addItem(&knapsackAux, item2);

    if (removeAnswer == 1 && addAnswer == 1) {
        *knapsack = copyKnapsack(knapsackAux);
        return 1;
    }
    return 0;
}
