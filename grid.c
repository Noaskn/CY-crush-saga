#include "grid.h"

// Affiche un symbole avec une couleur donnée
void print_colored_symbol(char symbol,char* color){
    printf("%s%c%s ",color,symbol,RESET_COLOR);
    printf(RESET_COLOR);
}

// Imprime des symboles colorés
void color_symbols(char symbol){
  switch (symbol) {
    case '*':
      print_colored_symbol('*',RED_COLOR);
      break;
    case '#':
      print_colored_symbol('#',GREEN_COLOR);
      break;
    case '$':
      print_colored_symbol('$',YELLOW_COLOR);
      break;
    case '@':
      print_colored_symbol('@',BLUE_COLOR);
      break;
    case '&':
      print_colored_symbol('&',MAGENTA_COLOR);
      break;
    case '+':
      print_colored_symbol('+',CYAN_COLOR);
      break;
    default:
      break;
  }
}

// L'utilisateur saisit les paramètres
void enter_parameters(int *rows,int *cols,int *num_symbols){

  // Demande à l'utilisateur de saisir le nombre de lignes
  printf("Entrez le nombre de lignes de la grille (entre 4 et 10) : ");
  scanf("%d",rows);

  // Vérifie si ce qui est saisi est supéreur à 10 et inférieur à 4
  while(*rows < 4 || *rows > 10){
    printf("Erreur, veuillez resaisir votre réponse\n");

    // Vide l'entrée
    while(getchar() != '\n');

    // Repose la question
    printf("Entrez le nombre de lignes de la grille (entre 4 et 10) : ");
    scanf("%d",rows);
  }

  // Demande à l'utilisateur de saisir le nombre de colonnes
  printf("Entrez le nombre de colonnes de la grille (entre 4 et 10) : ");
  scanf("%d",cols);

  // Vérifie si ce qui est saisi est supéreur à 10 et inférieur à 4
  while(*cols < 4 || *cols > 10){
    printf("Erreur, veuillez resaisir votre réponse\n");

    // Vide l'entrée
    while(getchar() != '\n');

    // Repose la question
    printf("Entrez le nombre de colonnes de la grille (entre 4 et 10) : ");
    scanf("%d",cols);
  }
  
  // Demande à l'utilisateur de saisir le nombre de symboles différents
  printf("Entrez le nombre de symboles différents (entre 4 et 6) : ");
  scanf("%d",num_symbols);

  // Vérifie si ce qui est saisi est supéreur à 6 et inférieur à 4
  while(*num_symbols < 4 || *num_symbols > 6){
    printf("Erreur, veuillez resaisir votre réponse\n");

    // Vide l'entrée
    while(getchar() != '\n');

    // Repose la question
    printf("Entrez le nombre de symboles différents (entre 4 et 6) : ");
    scanf("%d",num_symbols);
  }
}

// Création de la grille
void create_grid(int rows,int cols,int num_symbols,char grid[MAX_SIZE][MAX_SIZE]){
  int i,j,k;
  char symbols[6] = {'*', '#', '$', '@', '&', '+'};

  // Initialise la grille avec des symboles aléatoires
  for(i = 0 ; i < rows ; i++){
    for(j = 0 ; j < cols ; j++){
      grid[i][j] = symbols[rand() % num_symbols];
    }
  }

  // Verification des cases adjacentes et en diagonale
  for(i=0 ; i<rows ; i++){
    for(j=0 ; j<cols ; j++){
      while((grid[i][j] == grid[i+1][j] && grid[i][j] == grid[i+2][j]) || (grid[i][j] == grid[i-1][j] && grid[i][j] == grid[i-2][j]) || (grid[i][j] == grid[i][j+1] && grid[i][j] == grid[i][j+2]) || (grid[i][j] == grid[i][j-1] && grid[i][j] == grid[i][j-2]) || (grid[i][j] == grid[i+1][j+1] && grid[i][j] == grid[i+2][j+2]) || (grid[i][j] == grid[i-1][j-1] && grid[i][j] == grid[i-2][j-2]) || (grid[i][j] == grid[i-1][j-1] && grid[i][j] == grid[i+1][j+1]) || (grid[i][j] == grid[i-1][j+1] && grid[i][j] == grid[i+1][j-1])){
        grid[i][j] = symbols[rand() % num_symbols];
      }
    }
  }
}

// Affichage de la grille
void print_grid(int rows,int cols,char grid[MAX_SIZE][MAX_SIZE]){
  int i,j;
  printf("    ");
  for (j = 1 ; j <= cols ; j++){
    printf("%c ",'A'+j-1); // Première ligne de A à cols
  }
  printf("\n");
  for(i = 0 ; i < rows ; i++){
    printf(" %-2d ",i+1); // Première colonne de 1 à rows
    for(j = 0 ; j < cols ; j++){
      color_symbols(grid[i][j]); // Affichage des symboles
    }
    printf("\n");
  }
}