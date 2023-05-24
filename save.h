#ifndef FONCTIONS_H_
#define FONCTIONS_H_

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Nom du fichier de sauvegarder
#define SAVE_FILE "save.txt"

// Taille maximale de la grille
#define MAX_SIZE 10

void save_game(char grid[MAX_SIZE][MAX_SIZE],int score,int rows,int cols,int numSymbols,double timer);
int load_game(char grid[MAX_SIZE][MAX_SIZE],int *score,int *rows,int *cols,int *numSymbols,double *timer);

#endif