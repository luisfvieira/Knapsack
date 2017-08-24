#include <stdio.h>
#include <stdlib.h>

#include "knapsack.h"

//  Inicializa a  Mochila
Knapsack initializeKnapsack(int itensNum, int capacity, int ** conflicts) {
    Knapsack knapsack;

    knapsack.itensNum = itensNum;
    knapsack.qtdItens = 0;
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

//  Copia Uma Mochila
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

//  Retorna vetor de elementos que estao na Mochila
int* itensKnapsack(Knapsack knapsack) {
    int* itens = (int*) malloc(knapsack.qtdItens * sizeof(int));
    int j = 0;

    for (int i = 0; i < knapsack.qtdItens && j < knapsack.qtdItens; i++)
        if (knapsack.itens[i] == 1) {
            itens[j] = i;
            j++;
        }

    return itens;
}

//  Retorna vetor de elementos que nao estao na Mochila
int* itemComplement(Knapsack knapsack) {
    int complSize = knapsack.itensNum - knapsack.qtdItens;
    int* complement = (int*) malloc(complSize * sizeof(int));
    int j = 0;

    for (int i = 0; i < knapsack.itensNum && j < complSize ; i++)
        if (knapsack.itens[i] == 0) {
            complement[j] = i;
            j++;
        }

    return complement;
}

//  Verifica por Conflitos na Mochila
int conflictCheck(Knapsack knapsack, Item item) {
    if (knapsack.itens[item.itemId] == 1 || knapsack.capacity < knapsack.weight + item.weight)
        return 0;
    else {
        for (int i = 0; i < knapsack.itensNum && i != item.itemId; i++) {
            if (knapsack.itens[i] == 1) {
                if (knapsack.conflicts[item.itemId][i] == 1 || knapsack.conflicts[i][item.itemId] == 1)
                    return 0;
            }
        }
    }
    return 1;
}

//  Adiciona um Item a Mochila
int addItem(Knapsack* knapsack, Item item) {
    if (conflictCheck(*knapsack, item) == 1) {
        knapsack->weight += item.weight;
        knapsack->profit += item.profit;
        knapsack->itens[item.itemId] = 1;
        knapsack->qtdItens++;

        return 1;
    }
    return 0;
}

//  Remove um Item da Mochila
int removeItem(Knapsack* knapsack, Item item) {
    if (knapsack->itens[item.itemId] == 1) {
        knapsack->weight -= item.weight;
        knapsack->profit -= item.profit;
        knapsack->itens[item.itemId] = 0;
        knapsack->qtdItens--;

        return 1;
    }
    return 0;
}

//  Remove o mais conflitante
int removeMoreConflitant(Knapsack* knapsack, Item* itens) {
    int *conflictSum = calloc(knapsack->itensNum, sizeof(int));
    int moreConfSum = 0, conflitantId;

    for (int i = 0; i < knapsack->itensNum; i++)
        for (int j = 0; i < knapsack->itensNum; j++)
            conflictSum[i] += knapsack->conflicts[i][j];
    for (int i = 0; i < knapsack->itensNum; i++)
        if (moreConfSum < conflictSum[i]) {
            moreConfSum = conflictSum[i];
            conflitantId = i;
        }
    return removeItem(knapsack, itens[conflitantId]);
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

void printKnapsack(Knapsack knapsack) {
    printf("Knapsack\nCapacity: %d\nProfit: %d\nWeight: %d\n", knapsack.capacity,
        knapsack.profit, knapsack.weight);
    printf("ItensNum: %d\n", knapsack.itensNum);
    for (int i = 0; i < knapsack.itensNum; i++)
        printf("%d ", i % 10);
    printf("\n");
    for (int i = 0; i < knapsack.itensNum; i++) {
        printf("%d ", knapsack.itens[i]);
    }
    printf("\nGraph\n");
    for (int i = 0; i < knapsack.itensNum; i++) {
        for (int j = 0; j < knapsack.itensNum; j++)
            printf("%d ", knapsack.conflicts[i][j]);
        printf("\n");
    }
}
