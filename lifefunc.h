// Alex Schumann
// CSE 20311.01
// Homework 6
// playlife.c
// The main function for the game of life which will simulate a cellular automaton.

// Initialize a global variable for the board size
//#define boardSize 40

#ifndef LIFEFUNC_H
#define LIFEFUNC_H

extern const int boardSize;

// Function parameters
void dispRules();
int getMode(int);
void setEmpty(char[][boardSize]);
void dispBoard(char[][boardSize]);
char getInput();
void getFileInput(FILE *, char[][boardSize]);
int runInput(char, char[][boardSize]);
void editCell(char, int, int, char[][boardSize]);
void next(char[][boardSize]);
int countNeighbors(int, int, char[][boardSize]);
void play(char[][boardSize]);

#endif
