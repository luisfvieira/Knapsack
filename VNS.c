#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "knapsack.h"
#include "KVNS.h"

//  Numero de Movimentos
#define MOVMAX 5

double returnTime(clock_t);
int checktime(double, clock_t);
Knapsack BestImprovement(Knapsack, Item*);

//  Encontra o melhor beneficio para inserir na Mochila
int findBestBenefit(Knapsack knapsack, Item* itens) {
    int bestBenefit = 0, bestItem, complSize = knapsack.itensNum - knapsack.qtdItens;

    int* complement = itemComplement(knapsack);
    for (int i = 0; i < complSize; i++) {
        int benefit = itens[complement[i]].profit / itens[complement[i]].weight;
        if (bestBenefit < benefit) {
            bestBenefit = benefit;
            bestItem = i;
        }
    }
    return bestItem;
}

//  Encontra o pior Beneficio na Mochila
int findWorstBenefit(Knapsack knapsack, Item* itens) {
    double worstBenefit = 9999999.99;
    int worstItem;
    int* itensK = itensKnapsack(knapsack);

    for (int i = 0; i < knapsack.qtdItens; i++) {
        double benefit = itens[itensK[i]].profit / itens[itensK[i]].weight;
        if (worstBenefit > benefit) {
            worstBenefit = benefit;
            worstItem = i;
        }
    }
    return worstItem;
}

Knapsack Shake(Knapsack knapsack, Item *itens, KVNS k) {
    Knapsack kShake = initializeKnapsack(knapsack.itensNum, knapsack.capacity,
        knapsack.conflicts);
    int bestItem, worstBenefit, rand1;
    int* complement;

    srand(time(NULL));
    kShake = copyKnapsack(knapsack);
    switch (k.movement) {
        case 0:             //  Adicionar Melhor do Complemento
            complement = itemComplement(knapsack);
            bestItem = findBestBenefit(knapsack, itens);
            addItem(&kShake, itens[complement[bestItem]]);
            break;
        case 1:             //  Trocar o mais conflitante
            removeMoreConflitant(&kShake, itens);
            break;
        case 2:             //  Adicionar Cegamente
            if (addItem(&kShake, itens[k.k]) == 0) {
                rand1 = rand() % knapsack.itensNum;
                addItem(&kShake, itens[rand1]);
            }
            break;
        case 3:             //  Trocar o pior pelo Melhor
            worstBenefit = findWorstBenefit(knapsack, itens);
            complement = itemComplement(knapsack);
            bestItem = findBestBenefit(knapsack, itens);
            if (worstBenefit != -1)
                exchangeItem(&kShake, itens[worstBenefit], itens[complement[bestItem]]);
            break;
        case 4:             //  Trocar o pior cegamente
            worstBenefit = findWorstBenefit(knapsack, itens);
            if (worstBenefit != 9999999) {
                if (exchangeItem(&kShake, itens[worstBenefit], itens[k.k]) == 0) {
                    rand1 = rand() % knapsack.itensNum;
                    exchangeItem(&kShake, itens[worstBenefit], itens[rand1]);
                }
            }
            break;
    }

    return kShake;
}

KVNS NeighborhoodChange(Knapsack *current, Knapsack kBest, KVNS k, clock_t initialTime) {
    if (kBest.profit > current->profit) {
        printf("%ds solution improved to: %d by heuristic\n",
            (int) returnTime(initialTime), kBest.profit - current->profit);
        *current = copyKnapsack(kBest);
        k = initializeKVNS(k, k.kMax, k.movMax);
    }
    else
        k = nextK(k);
    return k;
}

/**
    TODO elaborar metodo para estimar o kMax para instancias
**/
Knapsack BVNS(Knapsack knapsack, Item *itens, int kMax, double tMax) {
    Knapsack kShake, kBest, currentKnapsack;
    KVNS k;
    clock_t initialTime = clock();

    //  kMax = knapsack.itensNum;
    kShake = initializeKnapsack(knapsack.itensNum, knapsack.capacity, knapsack.conflicts);
    kBest = initializeKnapsack(knapsack.itensNum, knapsack.capacity, knapsack.conflicts);
    currentKnapsack = initializeKnapsack(knapsack.itensNum, knapsack.capacity, knapsack.conflicts);
    currentKnapsack = copyKnapsack(knapsack);
    while (checktime(tMax, initialTime)) {
        k = initializeKVNS(k, kMax, MOVMAX);
        while (checkK(k) == 1 && checktime(tMax, initialTime)) {
            kShake = Shake(currentKnapsack, itens, k);
            kBest = BestImprovement(kShake, itens);
            k = NeighborhoodChange(&currentKnapsack, kBest, k, initialTime);
        }
    }

    return currentKnapsack;
}
