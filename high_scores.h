#ifndef FONCTIONS_H_
#define FONCTIONS_H_

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Taille maximale du nom
#define MAX_NAME 50

// Nom du fichier de meilleurs scores
#define SAVE_SCORES "high_scores.txt"

// Structure qui prend les données d'une partie
typedef struct {
  char name[MAX_NAME];
  int score;
  int rows;
  int cols;
  double timer;
} Player;

void storeHighScores(const char *name,int scores,int rows,int cols,double timer);
void printHighScores();

#endif