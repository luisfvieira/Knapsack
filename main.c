#include <stdio.h>
#include <stdlib.h>

#include "item.h"
#include "knapsack.h"
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
    //  Print Itens
    for (int i = 0; i < itensNum; i++) {
        printf("%d: %d\t%d\t%d\t", i, itens[i].profit, itens[i].weight,
            itens[i].conflictNum);

        for (int j = 0; j < itens[i].conflictNum; j++)
            printf("%d\t", itens[i].conflitantItems[j]);
        printf("\n");
    }

    for (int i = 0; i < itensNum; i++)
        free(itens[i].conflitantItems);
    free(itens);

    return 0;
}
