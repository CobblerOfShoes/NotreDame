// Alex Schumann
// CSE 20311.01
// Homework 6
// playlife.c
// The main function for the game of life which will simulate a cellular automaton.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "lifefunc.h"
//#define boardSize = 40;

// Initialize a global variable for the board size
const int boardSize = 40;

int main(int argc, char* argv[]) {
    // Display rules of the game
    //dispRules();

    // Get the game mode from user arguments
    int mode = getMode(argc);

    // Create the game board and populate it with dead cells (' ')
    char board[boardSize][boardSize];
    setEmpty(board);

    // Create a variable to store user input
    char command;

    // Clear the screen
    system("clear");

    if (mode == 1) {
        // Begin gameplay loop
        int playing = 1;
        while(playing) {
            // Display the current state of the board
            dispBoard(board);

            // Get user input
            command = getInput();
            playing = runInput(command, board);
        }
    } else if (mode == 2) {
        FILE *fp;
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            printf("Error: File Does Not Exist!\n");
        } else {
            getFileInput(fp, board);
        }
    }
    return 0;
}
