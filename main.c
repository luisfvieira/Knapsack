#include <stdio.h>

#include "knapsack.h"

Knapsack BestImprovement(Knapsack, Item*);
void printKnapsack(Knapsack);
void printItens(Item*, int);

int main(int argc, char const *argv[])
{
    //  Some argument is necessary to specify the file and time limit
    if (argc < 3) {
        printf("Error\nShould provide a file as argument and a time limit.\n");
        exit(1);
    }

    FILE *instFile;
    Item *itens;
    Knapsack knapsack;
    int itensNum, capacity;
    // double timeLimit = atoll(argv[2]) * 1000.0;

    if ((instFile = fopen(argv[1], "rt")) == NULL) {
        printf("Error\nFile doesn't open properly.\n");
        exit(1);
    }

    fscanf(instFile, "%d", &itensNum);
    fscanf(instFile, "%d", &capacity);
    printf("itens: %d\ncapacity: %d\n", itensNum, capacity);
    itens = (Item *) malloc(sizeof(Item) * itensNum);
    knapsack = initializeKnapsack(itensNum, capacity);
    printKnapsack(knapsack);
    for (int i = 0; i < itensNum; i++)
        itens[i].itemId = i;
    for (int i = 0; i < itensNum; i++)
        fscanf(instFile, "%d", &itens[i].profit);
    for (int i = 0; i < itensNum; i++)
        fscanf(instFile, "%d", &itens[i].weight);
    for (int i = 0; i < itensNum; i++) {
        fscanf(instFile, "%d", &itens[i].conflictNum);
        itens[i].conflitantItems = (int *) malloc(sizeof(int) * itens[i].conflictNum);
        for (int j = 0; j < itens[i].conflictNum; j++)
            fscanf(instFile, "%d", &itens[i].conflitantItems[j]);
    }
    printItens(itens, itensNum);
    knapsack = BestImprovement(knapsack, itens);
    printKnapsack(knapsack);
    knapsack = BestImprovement(knapsack, itens);
    printKnapsack(knapsack);
    //  Free Allocated Memory
    for (int i = 0; i < itensNum; i++)
        free(itens[i].conflitantItems);
    free(itens);

    return 0;
}

void printKnapsack(Knapsack knapsack) {
    printf("Knapsack\nCapacity: %d\nProfit: %d\nWeight: %d\n", knapsack.capacity,
        knapsack.profit, knapsack.weight);
    printf("ItensNum: %d\n", knapsack.itensNum);
    for (int i = 0; i < knapsack.itensNum; i++) {
        printf("%d ", knapsack.itens[i]);
    }
    printf("\n");
}

void printItens(Item* itens, int itensNum) {
    //  Print Itens
    printf("#\tprofit\tweight\tconflict\n");
    for (int i = 0; i < itensNum; i++) {
        printf("%d\t%d\t%d\t%d\t", i, itens[i].profit, itens[i].weight,
            itens[i].conflictNum);

        for (int j = 0; j < itens[i].conflictNum; j++)
            printf("%d\t", itens[i].conflitantItems[j]);
        printf("\n");
    }
}
