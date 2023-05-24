#include "save.h"

// Sauvegarde la partie
void save_game(char grid[MAX_SIZE][MAX_SIZE],int score,int rows,int cols,int numSymbols,double timer){

  // Ouvre le fichier en mode écriture
  FILE *file = fopen(SAVE_FILE, "w");
  if (file == NULL) {
    printf("Erreur lors de l'ouverture du fichier de sauvegarde\n");
    return;
  }

  // Écrit la grille, le score et le temps dans le fichier
  fprintf(file,"%d %d %d %d %.2f\n",rows,cols,numSymbols,score,timer);
  for(int i = 0 ; i < rows ; i++){
    for(int j = 0 ; j < cols ; j++){
      fprintf(file,"%c",grid[i][j]);
    }
    fprintf(file,"\n");
  }

  // Ferme le fichier
  fclose(file);
  printf("Partie sauvegardée avec succès\n");
}

// Charge la partie
int load_game(char grid[MAX_SIZE][MAX_SIZE],int *score,int *rows,int *cols,int *numSymbols,double *timer){

  // Ouvre le fichier en mode lecture
  FILE *file = fopen(SAVE_FILE, "r");
  if (file == NULL) {
    printf("Aucune partie sauvegardée\n");
    return 0;
  }

// Lit la grille et le score depuis le fichier
  fscanf(file,"%d %d %d %d %lf\n",rows,cols,numSymbols,score,timer);
  for(int i = 0 ; i <= *rows ; i++){
    for(int j = 0 ; j <= *cols ; j++){
      fscanf(file,"%c",&grid[i][j]);
    }
  }

  // Ferme le fichier
  fclose(file);
  printf("Partie chargée avec succès\n");
  return 1;
}