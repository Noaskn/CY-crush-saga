#ifndef FONCTIONS_H_
#define FONCTIONS_H_

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Taille maximale de la grille
#define MAX_SIZE 10

// Define pour les couleurs
#define RESET_COLOR "\033[0m"
#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"
#define YELLOW_COLOR "\033[33m"
#define BLUE_COLOR "\033[34m"
#define MAGENTA_COLOR "\033[35m"
#define CYAN_COLOR "\033[36m"

void print_colored_symbol(char symbol,char *color);
void color_symbols(char symbol);
void enter_parameters(int *rows,int *cols,int *num_symbols);
void create_grid(int rows,int cols,int num_symbols,char grid[MAX_SIZE][MAX_SIZE]);
void print_grid(int rows,int cols,char grid[MAX_SIZE][MAX_SIZE]);

#endif