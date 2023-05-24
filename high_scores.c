#include "high_scores.h"

// Stocke les scores
void storeHighScores(const char* name,int scores,int rows,int cols,double timer){
  
  // Ouvre le fichier en mode écriture
  FILE* file = fopen(SAVE_SCORES,"a");
  if(file == NULL){
    printf("Erreur lors de l'ouverture du fichier.\n");
    return;
  }

  // Ecrit les caractéristiques de la partie
  fprintf(file,"%s %d %dx%d %.2f\n",name,scores,rows,cols,timer);

  // Ferme le fichier
  fclose(file);
}

// Afficher les scores dans l'ordre
void printHighScores(){

  // Ouvre le fichier en mode lecture
  FILE* file = fopen(SAVE_SCORES,"r");
  if(file == NULL){
    printf("Erreur lors de l'ouverture du fichier.\n");
    return;
  }

  // Tableau de joueurs
  Player players[100];
  int count = 0;

  // Lecture des données dans un tableau de joueurs
  while(fscanf(file,"%s %d %dx%d %lf",players[count].name,&players[count].score,&players[count].rows,&players[count].cols,&players[count].timer) == 5){
    count++;
  }

  // Ferme le fichier
  fclose(file);

  // Tri des joueurs dans l'ordre décroissant en fonction de leur score
  for(int i = 1 ; i < count ; i++){
    Player player = players[i];
    int j = i-1;
    while(j >= 0 && players[j].score < player.score){
      players[j + 1] = players[j];
      j--;
    }
    players[j + 1] = player;
  }

  // Affichage des meilleurs scores triés
  printf("Meilleurs scores :\n");
  int maxScores = (count < 10) ? count : 10; // Vérifie si le nombre de scores est inférieur à 10
  for(int i = 0 ; i < maxScores ; i++){
    printf("%d: %s - Score: %d points - Taille grille: %dx%d - Temps de jeu: %.2lf secondes\n",i+1,players[i].name, players[i].score,players[i].rows,players[i].cols,players[i].timer);
  }
}