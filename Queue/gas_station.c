#include <stdio.h>

int canCompleteCircuit(int* gas, int* cost, int n) {
    int totalGas = 0;  
    int totalCost = 0;
    int currentGas = 0; 
    int startIndex = 0; 

    
    for (int i = 0; i < n; i++) {
        totalGas += gas[i];
        totalCost += cost[i];
        currentGas += gas[i] - cost[i];
    
        if (currentGas < 0) {
            startIndex = i + 1;
            currentGas = 0; 
        }
    }

    
    if (totalGas < totalCost) {
        return -1;
    }

    
    return startIndex;
}

int main() {
    int n;
    printf("Enter the number of gas stations: ");
    scanf("%d", &n);

    int gas[n];
    int cost[n];

    printf("Enter the amount of gas at each station:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &gas[i]);
    }

    printf("Enter the cost to travel to the next station from each station:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &cost[i]);
    }

    int startStation = canCompleteCircuit(gas, cost, n);
    if (startStation == -1) {
        printf("It's not possible to complete the circuit.\n");
    } else {
        printf("The starting station to complete the circuit is: %d\n", startStation);
    }

    return 0;
}
