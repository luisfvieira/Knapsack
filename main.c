#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "knapsack.h"
Knapsack BVNS(Knapsack, Item *, int, double);
Knapsack BestImprovement(Knapsack, Item*);
void printKnapsack(Knapsack);
void printItens(Item*, int);

int main(int argc, char const *argv[]) {
    //  Some argument is necessary to specify the file and time limit
    if (argc < 3) {
        printf("Error\nShould provide a file as argument and a time limit.\n");
        exit(1);
    }

    FILE *instFile;
    Item *itens;
    Knapsack knapsack;
    int itensNum, capacity;
    int **conflicts;
    double timeLimit = atoll(argv[2]) * 1000.0;


    if ((instFile = fopen(argv[1], "rt")) == NULL) {
        printf("Error\nFile doesn't open properly.\n");
        exit(1);
    }

    fscanf(instFile, "%d", &itensNum);
    fscanf(instFile, "%d", &capacity);
    printf("itens: %d\ncapacity: %d\n", itensNum, capacity);
    itens = (Item *) malloc(sizeof(Item) * itensNum);
    conflicts = (int **) calloc(itensNum, sizeof(int*));
    for (int i = 0; i < itensNum; i++)
        conflicts[i] = (int *) calloc(itensNum, sizeof(int));
    for (int i = 0; i < itensNum; i++)
        itens[i].itemId = i;
    for (int i = 0; i < itensNum; i++)
        fscanf(instFile, "%d", &itens[i].profit);
    for (int i = 0; i < itensNum; i++)
        fscanf(instFile, "%d", &itens[i].weight);
    for (int i = 0; i < itensNum; i++) {
        fscanf(instFile, "%d", &itens[i].conflictNum);
        itens[i].conflitantItems = (int *) malloc(sizeof(int) * itens[i].conflictNum);
        for (int j = 0; j < itens[i].conflictNum; j++) {
            int aux;
            fscanf(instFile, "%d", &aux);
            itens[i].conflitantItems[j] = aux;
            conflicts[i][aux] = 1;
        }
    }
    knapsack = initializeKnapsack(itensNum, capacity, conflicts);
    printItens(itens, itensNum);
    printKnapsack(knapsack);
    knapsack = BVNS(knapsack, itens, knapsack.itensNum, timeLimit);
    printKnapsack(knapsack);

    //  Free Allocated Memory
    for (int i = 0; i < itensNum; i++) {
        free(conflicts[i]);
        free(itens[i].conflitantItems);
    }
    free(conflicts);
    free(itens);

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

void printItens(Item* itens, int itensNum) {
    //  Print Itens
    printf("#\tprofit\tweight\tconflict\n");
    for (int i = 0; i < itensNum; i++) {
        printf("#%d\t%d\t%d\t%d\t", i, itens[i].profit, itens[i].weight,
            itens[i].conflictNum);

        for (int j = 0; j < itens[i].conflictNum; j++)
            printf("%d ", itens[i].conflitantItems[j]);
        printf("\n");
    }
}
