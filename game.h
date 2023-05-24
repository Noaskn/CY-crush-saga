#ifndef FONCTIONS_H_
#define FONCTIONS_H_

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Taille maximale de la grille
#define MAX_SIZE 10

// Taille maximale du nom
#define MAX_NAME 50

// Define pour les couleurs
#define RESET_COLOR "\033[0m"
#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"
#define YELLOW_COLOR "\033[33m"
#define BLUE_COLOR "\033[34m"
#define MAGENTA_COLOR "\033[35m"
#define CYAN_COLOR "\033[36m"

int convertCols(char letter);
int validSwap(char grid[MAX_SIZE][MAX_SIZE],int rows1, int ccols1,int rows2,int ccols2);
void symbolsSwap(char grid[MAX_SIZE][MAX_SIZE],int *rows1,int *ccols1,int *rows2,int *ccols2);
int searchAlignment(char grid[MAX_SIZE][MAX_SIZE],int rows,int cols,int firstrows,int firstcols);
void copyGrid(char source[MAX_SIZE][MAX_SIZE],char destination[MAX_SIZE][MAX_SIZE],int rows,int cols);
void removeSymbols(char grid[MAX_SIZE][MAX_SIZE],int rows,int cols,int *score);
void gravity(char grid[MAX_SIZE][MAX_SIZE],int rows,int cols);
void replace(char grid[MAX_SIZE][MAX_SIZE],int rows,int cols,int num_symbols);
void turn_play(char grid[MAX_SIZE][MAX_SIZE],int *rows1,int *rows2,char *cols1,char *cols2,int rows,int cols,int num_symbols,int *score);
int move(char grid[MAX_SIZE][MAX_SIZE],int rows,int cols);

#endif