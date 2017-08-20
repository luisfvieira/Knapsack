// #include "knapsack.h"
//
// Knapsack Shake(Knapsack knapsack, int k) {
//
// }
//
// Knapsack BVNS(Knapsack knapsack, int kMax, int tMax) {
//     int t = 0, k;
//     Knapsack kShake, kBest;
//
//     kShake = initializeKnapsack(knapsack.itensNum, knapsack.capacity);
//     kBest = initializeKnapsack(knapsack.itensNum, knapsack.capacity);
//
//     while (t < tMax) {
//         k = 1;
//         kShake = Shake(knapsack, k);
//         // kBest = BestImprovement();
//         k = NeighborhoodChange(knapsack, kBest, k);
//     }
// }
