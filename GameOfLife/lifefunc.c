// Alex Schumann
// CSE 20311.01
// Homework 6
// playlife.c
// The main function for the game of life which will simulate a cellular automaton.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "lifefunc.h"

// Initialize a global variable for the board size
//extern const int boardSize = 40;

// Check the number of user inputs
int getMode(int numArgs) {
    switch (numArgs) {
        // A value of one will represent Interactive mode
        // A value of two will represent Batch mode
        case 1:
        case 2:
            return numArgs;
        // Display an error if too many arguments are passed
        default:
            printf("Error: Too Many Arguments");
            return 0;
    }
}

// Populate the board with empty spaces
void setEmpty(char boardToEmpty[][boardSize]) {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            boardToEmpty[i][j] = ' ';
        }
    }
}

// Display the contents of the board
void dispBoard(char userBoard[][boardSize]) {
    // Print the top border
    // We add 2 to the board size to account for a 1 character wall on either side of the board
    for (int i = 0; i < boardSize + 2; i++) {
        printf("-");
    }
    printf("\n");
    // Print body of board
    for (int i = 0; i < boardSize; i++) {
        printf("|");
        for (int j = 0; j < boardSize; j++) {
            printf("%c", userBoard[i][j]);
        }
        printf("|\n");
    }
    // Print base of border
    for (int i = 0; i < boardSize + 2; i++) {
        printf("-");
    }
    printf("\n");

}

// Take user input
char getInput() {
    char input;
    printf("COMMAND: ");
    scanf("%c", &input);
    return input;
}

// Take input from file
void getFileInput(FILE *userFile, char userBoard[][boardSize]) {
    char input;
    int row, col;
    while (!feof(userFile)) {
        fscanf(userFile, "%c", &input);
        switch (input) {
            // Add a cell
            case 'a':
                fscanf(userFile, "%d%d", &row, &col);
                printf(" %d %d\n", row, col);
                editCell(input, row, col, userBoard);
                break;
            // Play continuously
            case 'p':
                play(userBoard);
                break;
        }
    }
}

// Run commands based on user input
int runInput(char userInput, char userBoard[][boardSize]) {
    int row, col;
    switch (userInput) {
        // Add a cell
        case 'a':
            scanf("%d%d", &row, &col);
            editCell(userInput, row, col, userBoard);
            break;
        // Remove a cell
        case 'r':
            scanf("%d%d", &row, &col);
            editCell(userInput, row, col, userBoard);
            break;
        // Advance the game state one screen
        case 'n':
            next(userBoard);
            break;
        // Play continuously
        case 'p':
            play(userBoard);
            break;
        case 'q':
            printf("Thank you for playing! Good bye.\n");
            return 0;
        default:
            system("clear");
            printf("Unkown Command\n");
    }
    // Intercept the newline character from entering the user input
    getchar();
    return 1;
}

// Add or remove a cell at the user specified location
void editCell(char type, int row, int col, char userBoard[][boardSize]) {
    system("clear");
    if (row < 1 || row > boardSize || col < 1 || col > boardSize) {
        printf("Invalid Point!\n");
    } else {
        switch (type) {
        // We will subtract 1 so that the user can reference the first cel as 1,1 rather than 0,0
            case 'a':
                userBoard[row-1][col-1] = 'X';
                break;
            case 'r':
                userBoard[row-1][col-1] = ' ';
        }
    }
}

void next(char userBoard[][boardSize]) {
    char tempBoard[boardSize][boardSize];
    int count;
    setEmpty(tempBoard);
    for (int row = 0; row < boardSize; row++) {
        for (int col = 0; col < boardSize; col++) {
            count = countNeighbors(row, col, userBoard);
            //tempBoard[row][col] = count + '0';
            // If a cell has three neighbors, it is alive
            // If a cell has two neighbors, it does not change it's state, live or dead
            // Otherwise, the cell is dead
            if (count == 3) {
                tempBoard[row][col] = 'X';
            } else if (count == 2) {
                tempBoard[row][col] = userBoard[row][col];
            } else {
                tempBoard[row][col] = ' ';
            }
        }
    }
    // Copy the temporary array into the main array
    for (int row = 0; row < boardSize; row++) {
        for (int col = 0; col < boardSize; col++) {
            userBoard[row][col] = tempBoard[row][col];
        }
    }
}

int countNeighbors(int iRow, int iCol, char filledBoard[][boardSize]) {
    int numNeighbors = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            // Only include spaces within the 40 by 40 board, ensure the loop does not check beyond the bounds
            if ((iRow+i >= 0) && (iRow+i < boardSize) && (iCol+j >= 0) && (iCol+j < boardSize)) {
                if (filledBoard[iRow+i][iCol+j] == 'X') {
                    // Do not include i = 0 and j = 0, only consider surrounding cells
                    if (!(i == 0 && j == 0)) {
                        numNeighbors++;
                    }
                }
            }
        }
    }
    return numNeighbors;
}

void play(char userBoard[][boardSize]) {
    while(1) {
        next(userBoard);
        system("clear");
        dispBoard(userBoard);
        usleep(250000);
    }
}
