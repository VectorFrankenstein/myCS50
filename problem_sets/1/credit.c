#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

long get_credit_card_number();

void luhn_algorithm(long credit_card_number);

int get_long_length(long num);

char* long_to_string(char buffer[],long num);

int main(void){

  long credit_card_number = get_credit_card_number();

  luhn_algorithm(credit_card_number);
}

// A function to prompt the user to get and return the
// a credit card number
long get_credit_card_number(){

  long credit_card_number;

  printf("Please supply the credit card number:- ");

  scanf("%ld",&credit_card_number);

  int length_long = get_long_length(credit_card_number);

  if (length_long < 13){
    printf("INVALID\n");
    exit(0);
  }
  return credit_card_number;
}

// A function that implement's luhn's algorithm
// to check if the number if valid or not
void luhn_algorithm(long credit_card_number){

  int x = get_long_length(credit_card_number);

  // Make a buffer of the right size

  char long_as_string[x];

  char * long_as_char = long_to_string(long_as_string,credit_card_number);

  char card_type[12];

  // What type of a card is it?
  if ((x == 15) & (strncmp(long_as_char, "34", 2) == 0 || strncmp(long_as_char, "37", 2) == 0)) {
      strcpy(card_type, "AMEX");
  } else if (long_as_char[0] == '5' && long_as_char[1] >= '1' && long_as_char[1] <= '5') {
      strcpy(card_type, "MASTERCARD");
  } else if ((long_as_char[0] == '4') & (x == 13 || x == 16)) {
      strcpy(card_type, "VISA");
  } else {
      strcpy(card_type, "INVALID");
  }

  int odd_sum = 0;

  int even_sum = 0;

  for(int k = x - 2; k >= 0; k = k - 2){

    char current_char = long_as_char[k];

    int current_val = (current_char - '0') * 2;
    // Check if the current_val is a single digit or double digit value
    // if double digit
    // use modulo to get the second digit
    // use divide by 10 and int to get the first
    if(current_val >= 10){
      int second_digit = current_val % 10;

      int first_digit = current_val / 10;

      even_sum += second_digit;

      even_sum += first_digit;
    } else {
      even_sum += current_val;
    }
  }
  // For the numbers in the even position
  // These numbers do not need to be multiplied


  for(int j = x - 1; j >= 0; j = j - 2){

    char current_char = long_as_char[j];

    int current_val = (current_char - '0');

    odd_sum += current_val;
  }

  int final_sum = even_sum + odd_sum;

  if(final_sum % 10 == 0){
    printf("%s\n", card_type);
  } else {
    printf("INVALID\n");
  }

}

// Generally useful functions
int get_long_length(long num) {
    if (num == 0) return 1;

    int length = 0;
    long abs_num = num < 0 ? -num : num;

    while (abs_num > 0) {
        length++;
        abs_num /= 10;
    }

    return length;
}


// Convert a long to a string
char* long_to_string(char buffer[], long num){

  sprintf(buffer, "%ld", num);

  return buffer;
}
