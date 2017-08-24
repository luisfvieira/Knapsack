#ifndef _KVNS_H
#define _KVNS_H

typedef struct {
    int k;
    int movement;
    int kMax;
    int movMax;
} KVNS;

KVNS initializeKVNS(KVNS k, int kMax, int movMax);
KVNS nextK(KVNS k);
int checkK(KVNS k);

#endif
