#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* user_input_func();

int char_value(char current_char);

int main(void){

  printf("Player 1: ");
  char* player_1_input = user_input_func();

  printf("Player 2: ");
  char* player_2_input = user_input_func();

  // placeholders for scores
  int player_1_score = 0;

  int player_2_score = 0;
  
  // Get the actual scores
  
  for(int i = 0; i < strlen(player_1_input);i++){
    printf("The i is :- %i, the char is %c and the returned value is %i\n",i,player_1_input[i],char_value(player_1_input[i]));
    player_1_score += char_value(player_1_input[i]);
  }


  for(int i = 0; i < strlen(player_2_input);i++){
    player_2_score += char_value(player_2_input[i]);
  }

  //printf("player 1:- %i and player 2 :- %i", player_1_score, player_2_score);

  if (player_2_score > player_1_score){
    printf("Player 2 wins!\n");
  } else if (player_1_score > player_2_score){
    printf("Player 1 wins!\n");
  } else{
    printf("Tie!\n");
  }
  
  free(player_1_input);

  free(player_2_input);
}

char* user_input_func() {

    char* user_input = malloc(50 * sizeof(char));
    fgets(user_input, 50, stdin);
    user_input[strcspn(user_input, "\n")] = 0;
    return user_input;
}

int char_value(char current_char){

  // if we up all the the chars then -
  // that saves us the trouble of having -
  // check for both.

  char upped = toupper(current_char);

  if (upped <= 'A' & upped >= 'Z'){
    return 0;
  }
  
  if((upped == 'A' ) || (upped == 'E' ) || (upped == 'I' ) || (upped == 'L' ) || (upped == 'N' ) || (upped == 'O' ) || (upped == 'R' ) || (upped == 'S' ) || (upped == 'T' ) || (upped == 'U')){
    return 1;
  } else if((upped == 'D' ) || (upped == 'G')){
    return 2;
  } else if((upped == 'B' ) || (upped == 'C' ) || (upped == 'M' ) || (upped == 'P')){
    return 3;
  } else if ((upped == 'F' ) || (upped == 'H' ) || (upped == 'V' ) || (upped == 'W' ) || (upped == 'Y')){
    return 4;
  } else if(upped == 'K'){
    return 5;
  } else if((upped == 'J' ) || (upped == 'X')) {
    return 8;
  } else if((upped == 'Q' ) || (upped == 'Z')){
    return 10;
  } else {
    return 0;
  }
}
