#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Data {
    int numbers[12];
} Data;

int DiceRoll();
int Choose();
int Check(Data data);

int main() {
    Data data = {.numbers = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
    char dice, dice2;
    int roll1, roll2, roll;
    
    while (!(Check(data))) {
        printf("\n");
        for (int i = 0; i < 12; i++) {
            if (data.numbers[i] == 0) {
                printf("\033[31m"); // Red color for picked numbers
            } else {
                printf("\033[32m"); // Green color for unpicked numbers
            }
            printf("%d ", i + 1);
        }
        printf("\033[0m\n"); // Reset
        
        char input[10];
        // First roll
        do {
            printf("Press R to roll dice again: ");
            fgets(input, sizeof(input), stdin);
            sscanf(input, "%c", &dice);
        } while (dice != 'R');
        roll1 = DiceRoll();
        
        // Second roll
        do {
            printf("Press R to roll dice again: ");
            fgets(input, sizeof(input), stdin);
            sscanf(input, "%c", &dice2);
        } while (dice2 != 'R');
        roll2 = DiceRoll();
        
        roll = roll1 + roll2;
        printf("Roll Ts: %i", roll);
        int choose = Choose();
        int choose2 = Choose();
        int total = choose + choose2;
        
        if (roll == total) {
            if (data.numbers[choose - 1] == 1) {
                if (data.numbers[choose2 - 1] == 1) {
                    data.numbers[choose - 1] = 0;
                    data.numbers[choose2 - 1] = 0;
                } else if (choose2 == 0) {
                    data.numbers[choose - 1] = 0;
                }
            } else {
                printf("YOU FAILED.\n");
                return 0;
            }
        } else {
            printf("YOU FAILED.\n");
            return 0;
        }
    }
    
    printf("\nYOU WON!\n");
    return 0;
}

int DiceRoll() {
    int dice;
    srand(time(NULL));

    for (int i = 0; i < 12; i++) {
        dice = (rand() % 6) + 1; 
        printf("\r%d", dice);
        fflush(stdout); 
        usleep(45000); 
    }
    printf("\n");

    return dice;           
}

int Choose() {
    int one;
    printf("\nPick number: ");
    scanf("%i", &one); // First Pick
    
    while (getchar() != '\n'); 
    
    return one;
}

int Check(Data data) {
    for (int i = 0; i < 12; i++) {
        if (data.numbers[i] != 0) {
            return 0; // Not all numbers are selected
        }
    }
    return 1; // All numbers are selected
}
