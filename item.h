#ifndef _ITEM_H_
#define _ITEM_H_H

typedef struct {
    int profit;
    int weight;
    int conflictNum;
    int *conflitantItems;
} Item;

#endif
