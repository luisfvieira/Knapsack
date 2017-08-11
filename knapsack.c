//  Inicializa a  Mochila
Knapsack initializeKnapsack(Knapsack knapsack, int itensNum, int capacity) {
    knapsack.weight = 0;
    knapsack.profit = 0;
    knapsack.capacity = capacity;
    knapsack.itens = (Item*) malloc(sizeof(Item) * itensNum);
}
