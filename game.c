#include "game.h"

// Convertit les colonnes en chiffre
int convertCols(char letter){
  return tolower(letter) - 'a' + 1;
}

// Vérifie si un échange est valide
int validSwap(char grid[MAX_SIZE][MAX_SIZE],int rows1,int ccols1,int rows2,int ccols2){

  // Echange valide
  if((rows1 - 1) == (rows2 - 1) && abs(ccols1 - ccols2) == 1){
    return 1;
  }

  // Echange valide
  else if((ccols1 - 1) == (ccols2 - 1) && abs(rows1 - rows2) == 1){
    return 1;
  }

  // Echange invalide
  return 0;
}

// Echange deux symboles
void symbolsSwap(char grid[MAX_SIZE][MAX_SIZE],int *rows1,int *ccols1,int *rows2,int *ccols2){
  char temp = grid[*rows1 - 1][*ccols1 - 1];
  grid[*rows1 - 1][*ccols1 - 1] = grid[*rows2 - 1][*ccols2 - 1];
  grid[*rows2 - 1][*ccols2 - 1] = temp;
}

// Recherche des symboles identiques en horizontal, vertical ou diagonal
int searchAlignment(char grid[MAX_SIZE][MAX_SIZE],int rows,int cols,int firstrows,int firstcols){
  int i = 1;
  char symbols = grid[firstrows][firstcols];
  int alignmentFound = 0;
  int numAlign = 1;

  // Recherche à droite
  while(firstcols + i < cols && grid[firstrows][firstcols + i] == symbols){
    numAlign++;
    i++;
  }

  // Réinitialise i à 1
  i = 1;

  // Recherche à gauche
  while(firstcols - i >= 0 && grid[firstrows][firstcols - i] == symbols){
    numAlign++;
    i++;
  }

  // Si 3 symoles sont alignés en ligne
  if(numAlign >= 3){
    alignmentFound = 1;
  }

  // Réinitialise numAlign et i à 1
  numAlign = 1;
  i = 1;

  // Recherche en bas
  while(firstrows + i < rows && grid[firstrows + i][firstcols] == symbols){
    numAlign++;
    i++;
  }
  
  // Réinitialise i à 1
  i = 1;

  // Recherche en haut
  while(firstrows - i >= 0 && grid[firstrows - i][firstcols] == symbols){
    numAlign++;
    i++;
  }

  // Si 3 symboles sont alignés en colonne
  if(numAlign >= 3){
    alignmentFound = 1;
  }

  // Réinitialise numAlign et i à 1
  numAlign = 1;
  i = 1;

  // Recherche en diagonale bas-droite
  while(firstrows + i < rows && firstcols + i < cols && grid[firstrows + i][firstcols + i] == symbols){
    numAlign++;
    i++;
  }

  // Réinitialise i à 1
  i = 1;

  // Recherche en diagonale haut-gauche
  while(firstrows - i >= 0 && firstcols - i >= 0 && grid[firstrows - i][firstcols - i] == symbols){
    numAlign++;
    i++;
  }

  // Si 3 symboles sont alignés en diagonal vers la bas-droite/haut-gauche
  if(numAlign >= 3){
    alignmentFound = 1;
  }

  // Réinitialise numAlign et i à 1
  numAlign = 1;
  i = 1;

  // Recherche en diagonale haut-droite
  while(firstrows - i >= 0 && firstcols + i < cols && grid[firstrows - i][firstcols + i] == symbols){
    numAlign++;
    i++;
  }

  // Réinitialise i à 1
  i = 1;

  // Recherche en diagonale bas-gauche
  while(firstrows + i < rows && firstcols - i >= 0 && grid[firstrows + i][firstcols - i] == symbols){
    numAlign++;
    i++;
  }

  // Si 3 symboles sont alignés en diagonal vers la bas-gauche/haut-droite
  if(numAlign >= 3){
    alignmentFound = 1;
  }

  // Retourne le nombre d'alignements trouvés
  return alignmentFound;
}

// Sauvegarde de la grille
void copyGrid(char source[MAX_SIZE][MAX_SIZE],char destination[MAX_SIZE][MAX_SIZE],int rows,int cols){
  for(int i = 0 ; i < rows ; i++){
    for(int j = 0 ; j < cols ; j++){
      destination[i][j] = source[i][j];
    }
  }
}

// Supprime les symboles alignés + Compte les points
void removeSymbols(char grid[MAX_SIZE][MAX_SIZE],int rows,int cols,int *score){
  int i, j, k, l;

  // Verifie les lignes verticales et horizontales qui forment un L
  for(i = 0 ; i < rows ; i++){
    for(j = 0 ; j < cols ; j++){

      // Bas-droite
      if(grid[i][j] != ' ' && grid[i][j] == grid[i + 1][j] && grid[i][j] == grid[i + 2][j] && grid[i][j] == grid[i][j + 1] && grid[i][j] == grid[i][j + 2]){
        if(grid[i][j] == grid[i - 1][j]){
          if(grid[i][j] == grid[i - 2][j]){

            // Supprime
            grid[i][j] = ' ';
            grid[i + 1][j] = ' ';
            grid[i + 2][j] = ' ';
            grid[i][j + 1] = ' ';
            grid[i][j + 2] = ' ';
            grid[i - 1][j] = ' ';
            grid[i - 2][j] = ' ';

            // Compte les points
            *score += 80;
          }
          else{

            // Supprime
            grid[i][j] = ' ';
            grid[i + 1][j] = ' ';
            grid[i + 2][j] = ' ';
            grid[i][j + 1] = ' ';
            grid[i][j + 2] = ' ';
            grid[i - 1][j] = ' ';

            // Compte les points
            *score += 70;
          }
        }
        if(grid[i][j] == grid[i][j - 1]){
          if(grid[i][j] == grid[i][j - 2]){

            // Supprime
            grid[i][j] = ' ';
            grid[i + 1][j] = ' ';
            grid[i + 2][j] = ' ';
            grid[i][j + 1] = ' ';
            grid[i][j + 2] = ' ';
            grid[i][j - 1] = ' ';
            grid[i][j - 2] = ' ';

            // Compte les points
            *score += 80;
          }
          else{

            // Supprime
            grid[i][j] = ' ';
            grid[i + 1][j] = ' ';
            grid[i + 2][j] = ' ';
            grid[i][j + 1] = ' ';
            grid[i][j + 2] = ' ';
            grid[i][j - 1] = ' ';

            // Compte les points
            *score += 70;
          }
        }
        else{

          // Supprime
          grid[i][j] = ' ';
          grid[i + 1][j] = ' ';
          grid[i + 2][j] = ' ';
          grid[i][j + 1] = ' ';
          grid[i][j + 2] = ' ';

          // Compte les points
          *score += 60;
        }
      }

      // Haut-droite
      if(grid[i][j] != ' ' && grid[i][j] == grid[i + 1][j] && grid[i][j] == grid[i + 2][j] && grid[i][j] == grid[i + 2][j + 1] && grid[i][j] == grid[i + 2][j + 2]){
        if(grid[i][j] == grid[i + 3][j]){
          if(grid[i][j] == grid[i + 4][j]){

            // Supprime
            grid[i][j] = ' ';
            grid[i + 1][j] = ' ';
            grid[i + 2][j] = ' ';
            grid[i + 2][j + 1] = ' ';
            grid[i + 2][j + 2] = ' ';
            grid[i + 3][j] = ' ';
            grid[i + 4][j] = ' ';

            // Compte les points
            *score += 80;
          }
          else{

            // Supprime
            grid[i][j] = ' ';
            grid[i + 1][j] = ' ';
            grid[i + 2][j] = ' ';
            grid[i + 2][j + 1] = ' ';
            grid[i + 2][j + 2] = ' ';
            grid[i + 3][j] = ' ';

            // Compte les points
            *score += 70;
          }
        }
        if(grid[i][j] == grid[i + 2][j - 1]){
          if(grid[i][j] == grid[i + 2][j - 2]){

            // Supprime
            grid[i][j] = ' ';
            grid[i + 1][j] = ' ';
            grid[i + 2][j] = ' ';
            grid[i + 2][j + 1] = ' ';
            grid[i + 2][j + 2] = ' ';
            grid[i + 2][j - 1] = ' ';
            grid[i + 2][j - 2] = ' ';

            // Compte les points
            *score += 80;
          }
          else{

            // Supprime
            grid[i][j] = ' ';
            grid[i + 1][j] = ' ';
            grid[i + 2][j] = ' ';
            grid[i + 2][j + 1] = ' ';
            grid[i + 2][j + 2] = ' ';
            grid[i + 2][j - 1] = ' ';

            // Compte les points
            *score += 70;
          }
        }
        else{

          // Supprime
          grid[i][j] = ' ';
          grid[i + 1][j] = ' ';
          grid[i + 2][j] = ' ';
          grid[i + 2][j + 1] = ' ';
          grid[i + 2][j + 2] = ' ';

          // Compte les points
          *score += 60;
        }
      }

      // Haut-gauche
      if(grid[i][j] != ' ' && grid[i][j] == grid[i + 1][j] && grid[i][j] == grid[i + 2][j] && grid[i][j] == grid[i + 2][j - 1] && grid[i][j] == grid[i + 2][j - 2]){
        if(grid[i][j] == grid[i + 3][j]){
          if(grid[i][j] == grid[i + 4][j]){

            // Supprime
            grid[i][j] = ' ';
            grid[i + 1][j] = ' ';
            grid[i + 2][j] = ' ';
            grid[i + 2][j - 1] = ' ';
            grid[i + 2][j - 2] = ' ';
            grid[i + 3][j] = ' ';
            grid[i + 4][j] = ' ';

            // Compte les points
            *score += 80;
          }
          else{

            // Supprime
            grid[i][j] = ' ';
            grid[i + 1][j] = ' ';
            grid[i + 2][j] = ' ';
            grid[i + 2][j - 1] = ' ';
            grid[i + 2][j - 2] = ' ';
            grid[i + 3][j] = ' ';

            // Compte les points
            *score += 70;
          }
        }
        if(grid[i][j] == grid[i + 2][j + 1]){
          if(grid[i][j] == grid[i + 2][j + 2]){

            // Supprime
            grid[i][j] = ' ';
            grid[i + 1][j] = ' ';
            grid[i + 2][j] = ' ';
            grid[i + 2][j - 1] = ' ';
            grid[i + 2][j - 2] = ' ';
            grid[i + 2][j + 1] = ' ';
            grid[i + 2][j + 2] = ' ';

            // Compte les points
            *score += 80;
          }
          else{

            // Supprime
            grid[i][j] = ' ';
            grid[i + 1][j] = ' ';
            grid[i + 2][j] = ' ';
            grid[i + 2][j - 1] = ' ';
            grid[i + 2][j - 2] = ' ';
            grid[i + 2][j + 1] = ' ';

            // Compte les points
            *score += 70;
          }
        }
        else{

          // Supprime
          grid[i][j] = ' ';
          grid[i + 1][j] = ' ';
          grid[i + 2][j] = ' ';
          grid[i + 2][j - 1] = ' ';
          grid[i + 2][j - 2] = ' ';

          // Compte les points
          *score += 60;
        }
      }

      // Bas-gauche
      if(grid[i][j] != ' ' && grid[i][j] == grid[i][j + 1] && grid[i][j] == grid[i][j + 2] && grid[i][j] == grid[i][j + 2] && grid[i + 1][j + 2] == grid[i + 2][j + 2]){
        if(grid[i][j] == grid[i][j + 3]){
          if(grid[i][j] == grid[i][j + 4]){

            // Supprime
            grid[i][j] = ' ';
            grid[i][j + 1] = ' ';
            grid[i][j + 2] = ' ';
            grid[i + 1][j + 2] = ' ';
            grid[i + 2][j + 2] = ' ';
            grid[i][j + 3] = ' ';
            grid[i][j + 4] = ' ';

            // Compte les points
            *score += 80;
          }
          else{

            // Supprime
            grid[i][j] = ' ';
            grid[i][j + 1] = ' ';
            grid[i][j + 2] = ' ';
            grid[i + 1][j + 2] = ' ';
            grid[i + 2][j + 2] = ' ';
            grid[i][j + 3] = ' ';

            // Compte les points
            *score += 70;
          }
        }
        if(grid[i][j] == grid[i - 1][j + 2]){
          if(grid[i][j] == grid[i - 2][j + 2]){

            // Supprime
            grid[i][j] = ' ';
            grid[i][j + 1] = ' ';
            grid[i][j + 2] = ' ';
            grid[i + 1][j + 2] = ' ';
            grid[i + 2][j + 2] = ' ';
            grid[i - 1][j + 2] = ' ';
            grid[i - 2][j + 2] = ' ';

            // Compte les points
            *score += 80;
          }
          else{

            // Supprime
            grid[i][j] = ' ';
            grid[i][j + 1] = ' ';
            grid[i][j + 2] = ' ';
            grid[i + 1][j + 2] = ' ';
            grid[i + 2][j + 2] = ' ';
            grid[i - 1][j + 2] = ' ';

            // Compte les points
            *score += 70;
          }
        }
        else {

          // Supprime
          grid[i][j] = ' ';
          grid[i][j + 1] = ' ';
          grid[i][j + 2] = ' ';
          grid[i + 1][j + 2] = ' ';
          grid[i + 2][j + 2] = ' ';

          // Compte les points
          *score += 60;
        }
      }
    }
  }

  // Verifie les T
  for(i = 0 ; i < rows; i++){
    for(j = 0 ; j < cols ; j++){

      // Vers le haut
      if(grid[i][j] != ' ' && grid[i][j] == grid[i + 1][j] && grid[i][j] == grid[i + 2][j] && grid[i][j] == grid[i + 2][j + 1] && grid[i][j] == grid[i + 2][j - 1]){

        // Supprime
        grid[i][j] = ' ';
        grid[i + 1][j] = ' ';
        grid[i + 2][j] = ' ';
        grid[i + 2][j + 1] = ' ';
        grid[i + 2][j - 1] = ' ';

        // Compte les points
        *score += 50;
      }

      // Vers le bas
      if(grid[i][j] != ' ' && grid[i][j] == grid[i][j + 1] && grid[i][j] == grid[i][j + 2] && grid[i][j] == grid[i + 1][j + 1] && grid[i][j] == grid[i + 2][j + 1]){

        // Supprime
        grid[i][j] = ' ';
        grid[i][j + 1] = ' ';
        grid[i][j + 2] = ' ';
        grid[i + 1][j + 1] = ' ';
        grid[i + 2][j + 1] = ' ';

        // Compte les points
        *score += 50;
      }

      // Vers la droite
      if(grid[i][j] != ' ' && grid[i][j] == grid[i + 1][j] && grid[i][j] == grid[i + 2][j] && grid[i][j] == grid[i + 1][j + 1] && grid[i][j] == grid[i + 1][j + 2]){

        // Supprime
        grid[i][j] = ' ';
        grid[i + 1][j] = ' ';
        grid[i + 2][j] = ' ';
        grid[i + 1][j + 1] = ' ';
        grid[i + 1][j + 2] = ' ';

        // Compte les points
        *score += 50;
      }

      // Vers la gauche
      if(grid[i][j] != ' ' && grid[i][j] == grid[i + 1][j] && grid[i][j] == grid[i + 2][j] && grid[i][j] == grid[i + 1][j - 1] && grid[i][j] == grid[i + 1][j - 2]){

        // Supprime
        grid[i][j] = ' ';
        grid[i + 1][j] = ' ';
        grid[i + 2][j] = ' ';
        grid[i + 1][j - 1] = ' ';
        grid[i + 1][j - 2] = ' ';

        // Compte les points
        *score += 50;
      }
    }
  }

  // Verifie les lignes horizontales
  for(i = 0 ; i < rows ; i++){
    for(j = 0 ; j < cols - 2 ; j++){
      if(grid[i][j] != ' ' && grid[i][j] == grid[i][j + 1] && grid[i][j] == grid[i][j + 2]){
        if(grid[i][j] == grid[i][j + 3]){
          if(grid[i][j] == grid[i][j + 4]){

            // Supprime
            grid[i][j] = ' ';
            grid[i][j + 1] = ' ';
            grid[i][j + 2] = ' ';
            grid[i][j + 3] = ' ';
            grid[i][j + 4] = ' ';
            
            // Compte les points
            *score += 50;
          }
          else{

            // Supprime
            grid[i][j] = ' ';
            grid[i][j + 1] = ' ';
            grid[i][j + 2] = ' ';
            grid[i][j + 3] = ' ';

            // Compte les points
            *score += 40;
          }
        }
        else{

          // Supprime
          grid[i][j] = ' ';
          grid[i][j + 1] = ' ';
          grid[i][j + 2] = ' ';

          // Compte les points
          *score += 30;
        }
      }
    }
  }

  // Vérifie les lignes verticales
  for(j = 0 ; j < cols ; j++){
    for(i = 0 ; i < rows - 2 ; i++){
      if(grid[i][j] != ' ' && grid[i][j] == grid[i + 1][j] && grid[i][j] == grid[i + 2][j]){
        if(grid[i][j] == grid[i + 3][j]){
          if(grid[i][j] == grid[i + 4][j]){

            //Supprime
            grid[i][j] = ' ';
            grid[i + 1][j] = ' ';
            grid[i + 2][j] = ' ';
            grid[i + 3][j] = ' ';
            grid[i + 4][j] = ' ';

            // Compte les points
            *score += 50;
          }
          else{

            // Supprime
            grid[i][j] = ' ';
            grid[i + 1][j] = ' ';
            grid[i + 2][j] = ' ';
            grid[i + 3][j] = ' ';

            // Compte les points
            *score += 40;
          }
        }
        else{

          // Supprime
          grid[i][j] = ' ';
          grid[i + 1][j] = ' ';
          grid[i + 2][j] = ' ';

          // Compte les points
          *score += 30;
        }
      }
    }
  }

  // Vérifie les diagonales descendantes
  for(i = 0 ; i < rows - 2 ; i++){
    for(j = 0 ; j < cols - 2 ; j++){
      if(grid[i][j] != ' ' && grid[i][j] == grid[i + 1][j + 1] && grid[i][j] == grid[i + 2][j + 2]){
        if(grid[i][j] == grid[i + 3][j + 3]){
          if(grid[i][j] == grid[i + 4][j + 4]){

            // Supprime
            grid[i][j] = ' ';
            grid[i + 1][j + 1] = ' ';
            grid[i + 2][j + 2] = ' ';
            grid[i + 3][j + 3] = ' ';
            grid[i + 4][j + 4] = ' ';

            // Compte les points
            *score += 55;
          }
          else {

            // Supprime
            grid[i][j] = ' ';
            grid[i + 1][j + 1] = ' ';
            grid[i + 2][j + 2] = ' ';
            grid[i + 3][j + 3] = ' ';

            // Compte les points
            *score += 45;
          }
        }
        else {

          // Supprime
          grid[i][j] = ' ';
          grid[i + 1][j + 1] = ' ';
          grid[i + 2][j + 2] = ' ';

          // Compte les points
          *score += 35;
        }
      }
    }
  }

  // Vérifie les diagonales ascendantes
  for(i = rows - 1 ; i >= 2 ; i--){
    for(j = 0 ; j < cols - 2 ; j++){
      if(grid[i][j] != ' ' && grid[i][j] == grid[i - 1][j + 1] && grid[i][j] == grid[i - 2][j + 2]){
        if(grid[i][j] == grid[i - 3][j + 3]){
          if(grid[i][j] == grid[i - 4][j + 4]){

            // Supprime
            grid[0][j] = ' ';
            grid[1][j + 1] = ' ';
            grid[2][j + 2] = ' ';
            grid[3][j + 3] = ' ';
            grid[4][j + 4] = ' ';

            // Compte les points
            *score += 55;
          }
          else{

            // Supprime
            grid[0][j] = ' ';
            grid[1][j + 1] = ' ';
            grid[2][j + 2] = ' ';
            grid[3][j + 3] = ' ';

            // Compte les points
            *score += 45;
          }
        }
        else{

          // Supprime
          grid[0][j] = ' ';
          grid[1][j + 1] = ' ';
          grid[2][j + 2] = ' ';

          // Compte les points
          *score += 35;
        }
      }
    }
  }
}

// Applique la gravité vers le haut
void gravity(char grid[MAX_SIZE][MAX_SIZE],int rows,int cols) {
  int i,j;
  int empty_rows = 0;
  char temp;
  for(j = 0 ; j < cols ; j++){
    empty_rows = 0;
    for(i = 0 ; i < rows ; i++){
      if(grid[i][j] == ' '){
        empty_rows ++;
      }
      else if(empty_rows > 0){
        temp = grid[i][j];
        grid[i][j] = ' ';
        grid[i - empty_rows][j] = temp;
      }
    }
  }
}

// Remplace les endroits vides par des symboles aléatoires
void replace(char grid[MAX_SIZE][MAX_SIZE],int rows,int cols,int num_symbols){
  char symbols[6] = {'*', '#', '$', '@', '&', '+'};
  for(int j = 0 ; j < cols ; j++){
    for(int i = 0 ; i < rows ; i++){
      if(grid[i][j] == ' '){
        grid[i][j] = symbols[rand() % num_symbols];
      }
    }
  }
}

// 1 tour de jeu
void turn_play(char grid[MAX_SIZE][MAX_SIZE],int *rows1,int *rows2,char *cols1,char *cols2,int rows,int cols,int num_symbols,int *score){
  int ccols1, ccols2;
  char previousGrid[MAX_SIZE][MAX_SIZE]; // Grille précédente
  int previousRows1,previousRows2; // Lignes précédentes
  int previousCols1,previousCols2; // Colonnes précédentes

  // Sauvegarde de la grille et les positions des pièces à échanger
  copyGrid(grid,previousGrid,rows,cols);
  previousRows1 = *rows1;
  previousCols1 = convertCols(*cols1);
  previousRows2 = *rows2;
  previousCols2 = convertCols(*cols2);

  // Demande à l'utilisateur les pièces à échanger
  printf("Quelle est la première pièce à échanger (ex : A1) : \n");
  scanf(" %c%d",cols1,rows1);
  ccols1 = convertCols(*cols1); // Convertit la colonne en chiffre
  printf("Quelle est la seconde pièce à échanger (ex : A2) : \n");
  scanf(" %c%d",cols2,rows2);
  ccols2 = convertCols(*cols2); // Convertit la colonne en chiffre

  // Si l'échange est valide
  if(validSwap(grid,*rows1,ccols1,*rows2,ccols2)){

    // Echanche les symboles
    symbolsSwap(grid,rows1,&ccols1,rows2,&ccols2);

    // Vérification de l'alignement
    if(searchAlignment(grid,rows,cols,*rows1 - 1,ccols1 - 1) || searchAlignment(grid,rows,cols,*rows2 - 1,ccols2 - 1)){
      printf("Alignement trouvé\n");

      // Suppression
      removeSymbols(grid,rows,cols,score);

      // Gravité
      gravity(grid,rows,cols);

      // Remplacement
      replace(grid,rows,cols,num_symbols);

      // Lors du remplacement, si les nouveaux symboles forment des alignements, ils doivent être supprimés
      for(int i = 0 ; i < rows ; i++){
        for(int j = 0 ; j < cols ; j++){

          // Tant qu'il y a un alignement
          while(searchAlignment(grid,rows,cols,i,j)){

            // Suppresion
            removeSymbols(grid, rows, cols, score);

            // Gravité
            gravity(grid, rows, cols);

            // Remplacement
            replace(grid, rows, cols, num_symbols);

            // Réinitialise i et j à 0
            i=0;
            j=0;
          }
        }
      }

      // Affichage de la grille
      print_grid(rows, cols, grid);
    }

    // S'il n'y a plus d'alignement
    else{
      printf("Aucun alignement trouvé\n");
      
      // Restauration de la grille précédente
      copyGrid(previousGrid, grid, rows, cols);
      *rows1 = previousRows1;
      *rows2 = previousRows2;
      *cols1 = previousCols1;
      *cols2 = previousCols2;
    }
  }

  // Si l'échange est invalide
  else{
    printf("L'échange n'est pas valide\n");
  }

  // Affichage du score à la fin de chaque tour
  printf("Votre score est : %d points\n",*score);
}

// Verifie s'il y a des déplacements possibles
int move(char grid[MAX_SIZE][MAX_SIZE],int rows,int cols){
  int i,j,k,l;
  int temp;

  // Parcours de toutes les cases de la grille
  for(i = 0 ; i < rows ; i++){
    for(j = 0 ; j < cols ; j++){

      // Echange de la case avec chacune de ses 4 cases voisines
      for(k = -1 ; k <= 1 ; k++){
        for(l = -1 ; l <= 1 ; l++){

          // Vérifie si la case voisine existe et est différente de la case courante
          if((k == 0 || l == 0) && (k != l) && i + k >= 0 && i + k < rows && j + l >= 0 && j + l < cols && grid[i][j] != grid[i + k][j + l]){

            // Echange temporaire des valeurs
            temp = grid[i][j];
            grid[i][j] = grid[i + k][j + l];
            grid[i + k][j + l] = temp;

            // Vérifie s'il y a une ligne de 3 symboles identiques
            if(searchAlignment(grid,rows,cols,i,j) || searchAlignment(grid,rows,cols,i + k,j + l)){

              // Echange de nouveau pour revenir à l'état initial de la grille
              grid[i + k][j + l] = grid[i][j];
              grid[i][j] = temp;
              return 0; // Il y a encore des déplacements possibles
            }

            // Echange de nouveau pour revenir à l'état initial de la grille
            grid[i + k][j + l] = grid[i][j];
            grid[i][j] = temp;
          }
        }
      }
    }
  }
  return 1; // Il n'y a plus de déplacements possibles
}