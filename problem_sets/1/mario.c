#include <stdio.h>

int get_number();

void mario(int height);

int main(void){

  int number = get_number();
  mario(number);
}

int get_number(){

  int number;

  printf("Please enter a number:- ");

  scanf("%d", &number);

  if(number <= 0 || number > 8){
    number = get_number();
  }

  return number;
}

void mario(int height) {

  // This function will only be if the input is right
  // So we do not need to worry
  for(int i=height;i >= 1;i = i -1){
    for(int j = 1;j <= height;j++){
      if (j >= i){
        printf("#");
      } else if (j < height){
        printf(" ");
      }
    }
    printf("  ");
    for(int k = height; k >= 1; k = k -1){
      if (k >= i){
        printf("#");
      }
    }
    printf("\n");
  }
}
