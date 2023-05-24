#include "game.h"
#include "grid.h"
#include "high_scores.h"
#include "save.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Fonction principale
int main() {
  int rows, cols, num_symbols, rows1, rows2;
  char cols1, cols2;
  char grid[MAX_SIZE][MAX_SIZE];
  int score = 0;
  int play;
  int save;
  int rules;
  int main_menu;
  char name[MAX_NAME];
  clock_t start_time, end_time, start_time2, end_time2;
  double time_used, time_used2;

  // Initialise la graine pour la génération aléatoire
  srand(time(NULL));

  // Affichage du menu principal
  printf("\033[0;31mBienvenue sur le jeu CY-crush saga\033[0m\n\n");

  // Demande à l'utilisateur s'il souhaite avoir les règles du jeu
  printf("Voulez-vous une explication des règles du jeu ?\n1-Oui\n2-Non\n");
  scanf("%d",&rules);

  // Vérifie si ce qui est saisi est différent de 1 et 2
  while(rules != 1 && rules != 2){
    printf("Erreur, veuillez resaisir votre réponse\n");

    // Vide l'entrée
    while(getchar() != '\n');

    // Repose la question
    printf("Voulez vous une explication des règles du jeu ?\n1-Oui\n2-Non\n");
    scanf("%d",&rules);
  }

  // Règles du jeu
  if(rules == 1){
    printf("\nLe but du jeu est simple, il faut faire le plus grand score possible.\n\n");
  
    printf("\033[0;31mExplication des règles :\033[0m\n\n");
    printf("En début de partie, vous pouvez choisir la taille de votre grille ainsi que le nombre de symboles différents.\nLors de chaque tour, vous pouvez échanger un symbole uniquement avec une case voisine afin d'aligner 3 symboles au minimum à la verticale, à l'horizontale ou en diagonale.\nUne gravité sera alors appliquée vers le haut et les cases vides seront automatiquement remplacées par d’autres symboles.\nLe jeu s’arrête lorsqu’il n’y a plus de déplacement possible.\nVous pouvez décider à tout moment d’arrêter votre partie et/ou de la sauvegarder.\nUne seule sauvegarde est possible, vous pouvez reprendre la partie sauvegardée en début de jeu.\nA la fin de chaque partie, la liste des 10 meilleurs joueurs sera affichée.\n\n");
  
    printf("\033[0;31mExplication du score :\033[0m\n\n");
    printf("* * * horizontal ou vertical = \033[0;34m30 points\033[0m\n\n");
    printf("*\n * = \033[0;34m35 points\033[0m\n  *\n\n");
    printf("* * * * horizontal ou vertical = \033[0;34m40 points\033[0m\n\n");
    printf("*\n * = \033[0;34m45 points\033[0m\n  *\n   *\n\n");
    printf("* * * * * horizontal ou vertical = \033[0;34m50 points\033[0m\n\n");
    printf("*\n *\n  * = \033[0;34m55 points\033[0m\n   *\n    *\n\n");
    printf("* * *\n  *   dans tous les sens = \033[0;34m60 points\033[0m\n  *\n\n");
    printf("*\n*     dans tous les sens = \033[0;34m60 points\033[0m\n* * *\n\n");
    printf("*\n*     dans tous les sens = \033[0;34m70 points\033[0m\n* * *\n*\n\n");
    printf("*\n*\n* * * dans tous les sens = \033[0;34m80 points\033[0m \n*\n*\n\n");
  }
  
  printf("\n\033[0;31mDébut du jeu :\033[0m\n\n");

  // Demande le nom du joueur
  printf("Quel est votre nom ?\n");
  scanf("%s",name);

  // Demande à l'utilisateur s'il souhaite commencer une nouvelle partie ou continuer celle qui est sauvegardée
  printf("Voulez-vous :\n1-Commencer une nouvelle partie\n2-Continuer l'ancienne partie déjà sauvegarder\n");
  scanf("%d",&main_menu);

  // Vérifie si ce qui est saisi est différent de 1 et 2
  while(main_menu != 1 && main_menu != 2){
    printf("Erreur, veuillez resaisir votre réponse\n");

    // Vide l'entrée
    while(getchar() != '\n');

    // Repose la question
    printf("Voulez-vous :\n1-Commencer une nouvelle partie\n2-Continuer l'ancienne partie déjà sauvegardée\n");
    scanf("%d",&main_menu);
  }

  // Commence une nouvelle partie
  if(main_menu == 1){

    // Demande les paramètres de jeu à l'utilisateur (nombre de lignes, nombre de colonnes, nombre de symboles)
    enter_parameters(&rows,&cols,&num_symbols);

    // Crée la grille et l'affiche
    create_grid(rows,cols,num_symbols,grid);
    print_grid(rows,cols,grid);

    // Premier tour + début du timer
    start_time = time(NULL);
    turn_play(grid,&rows1,&rows2,&cols1,&cols2,rows,cols,num_symbols,&score);

    // Verifie s'il y a des déplacements possibles
    while(move(grid, rows, cols) == 0){
      printf("Des déplacements sont encore possibles\n");

      // Demande à l'utilisateur s'il veut continuer la partie
      printf("Voulez-vous continuer votre partie ?\n1-Oui\n2-Non\n");
      scanf("%d",&play);

      // Vérifie si ce qui est saisi est différent de 1 et 2
      while(play != 1 && play != 2){
        printf("Erreur, veuillez resaisir votre réponse\n");

        // Vide l'entrée
        while(getchar() != '\n');

        // Repose la question
        printf("Voulez-vous continuer votre partie ?\n1-Oui\n2-Non\n");
        scanf("%d",&play);
      }

      // Si oui, on joue
      if(play == 1){
        turn_play(grid,&rows1,&rows2,&cols1,&cols2,rows,cols,num_symbols,&score);
      }

      // Si non, on demande à l'utilisateur s'il veut sauvegarder la partie
      else if(play == 2){
        printf("Voulez-vous sauvegarder votre partie ?\n1-Oui\n2-Non\n");
        scanf("%d",&save);

        // Vérifie si ce qui est saisi est différent de 1 et 2
        while(save != 1 && save != 2){
          printf("Erreur, veuillez resaisir votre réponse\n");

          // Vide l'entrée
          while(getchar() != '\n');

          // Repose la question
          printf("Voulez-vous sauvegarder votre partie ?\n1-Oui\n2-Non\n");
          scanf("%d",&save);
        }

        // Si oui, on sauvegarde et on sort du jeu
        if(save == 1){

          // Affiche le temps de jeu
          end_time = time(NULL);
          time_used = difftime(end_time,start_time);
          printf("Votre temps passé à jouer sur cet essai est %.2f secondes\n",time_used);

          // Sauvegarde
          save_game(grid,score,rows,cols,num_symbols,time_used);

          // Sortie du jeu
          exit(1);
        }

        // Si non, on sort du jeu
        else if(save == 2){

          // Affiche le temps de jeu
          end_time = time(NULL);
          time_used = difftime(end_time,start_time);
          printf("Votre temps passé à jouer est %.2f secondes\n",time_used);

          // Sauvegarde le score + affiche les 10 meilleurs scores
          storeHighScores(name,score,rows,cols,time_used);
          printHighScores();

          // Sortie du jeu
          exit(2);
        }
      }
    }

    // Fin de la partie s'il n'y a plus de déplacement possible
    printf("Plus de déplacement possible\n");
    printf("Fin de la partie\n");

    // Affiche le temps de jeu
    end_time = time(NULL);
    time_used = difftime(end_time,start_time);
    printf("Votre temps passé à jouer est %.2f secondes\n",time_used);

    // Sauvegarde le score + affiche les 10 meilleurs scores
    storeHighScores(name,score,rows,cols,time_used);
    printHighScores();

    // Sortie du jeu
    exit(3);
  }

  // Continue la partie sauvegardée
  else if(main_menu == 2){
    
    // Si une partie est stockée, on la charge
    if(load_game(grid,&score,&rows,&cols,&num_symbols,&time_used) == 1){

      // Affiche le score sauvegardé
      printf("Score : %d\n",score);

      // Affiche la grille sauvegardée
      print_grid(rows,cols,grid);

      // Affiche le temps sauvegardé
      printf("Vous avez déjà joué pendant %.2f secondes sur cette partie\n",time_used);
      
      // Premier tour + début du timer
      start_time2 = time(NULL);
      turn_play(grid,&rows1,&rows2,&cols1,&cols2,rows,cols,num_symbols,&score);

      // Verifie s'il y a des déplacements possibles
      while(move(grid, rows, cols) == 0){
        printf("Des déplacements sont encore possibles\n");

        // Demande à l'utilisateur s'il veut continuer la partie
        printf("Voulez-vous continuer votre partie ?\n1-Oui\n2-Non\n");
        scanf("%d",&play);

        // Vérifie si ce qui est saisi est différent de 1 et 2
        while(play != 1 && play != 2){
          printf("Erreur, veuillez resaisir votre réponse\n");

          // Vide l'entrée
          while(getchar() != '\n');

          // Repose la question
          printf("Voulez-vous continuer votre partie ?\n1-Oui\n2-Non\n");
          scanf("%d",&play);
        }

        // Si oui, on joue
        if(play == 1){
          turn_play(grid,&rows1,&rows2,&cols1,&cols2,rows,cols,num_symbols,&score);
        }

        // Si non, on demande à l'utilisateur s'il veut sauvegarder la partie
        else if(play == 2){
          printf("Voulez-vous sauvegarder votre partie ?\n1-Oui\n2-Non\n");
          scanf("%d",&save);

          // Vérifie si ce qui est saisi est différent de 1 et 2
          while (save != 1 && save != 2) {
            printf("Erreur, veuillez resaisir votre réponse\n");

            // Vide l'entrée
            while(getchar() != '\n');

            // Repose la question
            printf("Voulez-vous sauvegarder votre partie ?\n1-Oui\n2-Non\n");
            scanf("%d",&save);
          }

          // Si oui, on sauvegarde et on sort du jeu
          if(save == 1){

            // Affiche le temps de jeu
            end_time2 = time(NULL);
            time_used2 = difftime(end_time2,start_time2);
            time_used = time_used2 + time_used;
            printf("Votre temps passé à jouer sur cette partie est désormais %.2f secondes\n",time_used);

            // Sauvegarde
            save_game(grid,score,rows,cols,num_symbols,time_used);

            // Sortie du jeu
            exit(4);
          }

          // Si non, on sort du jeu
          else if(save == 2){

            // Affiche le temps de jeu
            end_time2 = time(NULL);
            time_used2 = difftime(end_time2,start_time2);
            time_used = time_used2 + time_used;
            printf("Votre temps passé à jouer sur cette partie est désormais %.2f secondes\n",time_used);

            // Sauvegarde le score + affiche les 10 meilleurs scores
            storeHighScores(name,score,rows,cols,time_used);
            printHighScores();

            // Sortie du jeu
            exit(5);
          }
        }
      }
      
      // Fin de la partie s'il n'y a plus de déplacement possible
      printf("Plus de déplacement possible\n");
      printf("Fin de la partie\n");

      // Affiche le temps de jeu
      end_time2 = time(NULL);
      time_used2 = difftime(end_time2,start_time2);
      time_used = time_used2 + time_used;
      printf("Votre temps passé à jouer est %.2f secondes\n",time_used);

      // Sauvegarde le score + affiche les 10 meilleurs scores
      storeHighScores(name,score,rows,cols,time_used);
      printHighScores();

      // Sortie du jeu
      exit(6);
    }
      
    // S'il n'y a pas de partie sauvegardée
    else if(load_game(grid,&score,&rows,&cols,&num_symbols,&time_used) == 0){

      // Sortie du jeu
      exit(7);
    }
  }
  return 0;
}