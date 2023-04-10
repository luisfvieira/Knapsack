#include "knapsack.h"

//  Initialize Knapsack struct
Knapsack initializeKnapsack(int itensNum, int capacity, int ** conflicts) {
    Knapsack knapsack;

    knapsack.itensNum = itensNum;
    knapsack.weight = 0;
    knapsack.profit = 0;
    knapsack.capacity = capacity;
    //  Inicializa as posicoes de memoria
    knapsack.itens = (int*) calloc(itensNum, sizeof(int));
    knapsack.conflicts = (int **) calloc(itensNum, sizeof(int*));
    for (int i = 0; i < itensNum; i++)
        knapsack.conflicts[i] = (int *) calloc(itensNum, sizeof(int));
    //  Preenche com as restricoes
    for (int i = 0; i < itensNum; i++)
        for (int j = 0; j < itensNum; j++)
            knapsack.conflicts[i][j] = conflicts[i][j];

    return knapsack;
}

//  Copies an Knapsack
Knapsack copyKnapsack(Knapsack knapsack) {
    Knapsack copy;

    copy = knapsack;
    copy.itens = (int*) calloc(copy.itensNum, sizeof(int));
    for (int i = 0; i < knapsack.itensNum; i++)
        copy.itens[i] = knapsack.itens[i];
    for (int i = 0; i < knapsack.itensNum; i++)
        for (int j = 0; j < knapsack.itensNum; j++)
            copy.conflicts[i][j] = knapsack.conflicts[i][j];

    return copy;
}

//  Conflict verification
int conflictCheck(Knapsack knapsack, Item item) {
    if (knapsack.itens[item.itemId] == 1 || knapsack.capacity < knapsack.weight + item.weight)
        return 0;
    else
        for (int i = 0; i < knapsack.itensNum; i++) {
            if (knapsack.itens[i] == 1 && (knapsack.conflicts[item.itemId][i] == 1 ||
                knapsack.conflicts[i][item.itemId] == 1))
                return 0;
        }
    return 1;
}

//  Add item, increasing weight and profit
int addItem(Knapsack* knapsack, Item item) {
    if (conflictCheck(*knapsack, item) == 1) {
        knapsack->weight += item.weight;
        knapsack->profit += item.profit;
        knapsack->itens[item.itemId] = 1;

        return 1;
    }
    return 0;
}

//  Remove item, decreasing weight and profit
int removeItem(Knapsack* knapsack, Item item) {
    if (knapsack->itens[item.itemId] == 1) {
        knapsack->weight -= item.weight;
        knapsack->profit -= item.profit;
        knapsack->itens[item.itemId] = 0;

        return 1;
    }
    return 0;
}

//  Troca um Item da Mochila, por Outro
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
