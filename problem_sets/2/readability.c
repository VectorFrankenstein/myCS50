#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// The structs that will be used


// I want this to hold the number of characters and words -
// that the supplied text will have.

struct  the_counts {
    int characters;
    int words;
    int sentences;
};

// Functions prototype.

char* get_user_input();

struct the_counts count_user_inputs(char* current_input);

int count_sentence_delimiters(char* user_input_param_count_sentence_delimiters);

int count_non_whitespace(char* str);

void coleman_liau_func(int n_letters, int n_words, int n_sentences);

// Main logic

int main(void){

  printf("Text:");
  
  char* current_input = get_user_input();

  struct the_counts user_input_counts = count_user_inputs(current_input);

  // At this point in the script -
  // we have the count of sentences, words and letter -
  // now we can implement the Coleman-Liau formula.

  coleman_liau_func(
    user_input_counts.characters,
    user_input_counts.words,
    user_input_counts.sentences  
  );
}

// functions used in the script

// Function to get user input. -
// The dynamically adjusts the size of the allocation -
// to fit the user input.

char* get_user_input() {
    char *input;
    size_t size = 64;
    size_t used = 0;
    int c;

    input = (char *)malloc(size * sizeof(char));
    if (input == NULL) {
        return NULL; // Memory allocation failed
    }

    while ((c = getchar()) != '\n' && c != EOF) {
        if (used + 1 >= size) {
            size *= 2;
            char *temp = (char *)realloc(input, size * sizeof(char));
            if (temp == NULL) {
                free(input);
                return NULL; // Memory allocation failed
            }
            input = temp;
        }
        input[used++] = c;
    }

    input[used] = '\0'; // Null-terminate the string

    return input;
}

// Function to count non-whitespace -
// chars.

int count_letters(char *str) {
    int count = 0;
    while (*str) {
        if (isalpha((unsigned char)*str)) {
            count++;
        }
        str++;
    }
    return count;
}

int count_words(char *str) {
    int in_word = 0;
    int count = 0;
    while (*str) {
        if (isspace((unsigned char)*str)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            count++;
        }
        str++;
    }
    return count;
}

int count_sentences(char *str) {
    int count = 0;
    while (*str) {
        if (*str == '.' || *str == '!' || *str == '?') {
            count++;
        }
        str++;
    }
    return count;
}

struct the_counts count_user_inputs(char* user_input) {
    struct the_counts counts;
    counts.characters = count_letters(user_input);
    counts.words = count_words(user_input);
    counts.sentences = count_sentences(user_input);
    return counts;
}

void coleman_liau_func(int n_letters, int n_words, int n_sentences) {
    float L = (float)n_letters / n_words * 100;
    float S = (float)n_sentences / n_words * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = (int)(index + 0.5);  // Round to nearest integer

    if (grade < 1) {
        printf("Before Grade 1\n");
    } else if (grade >= 16) {
        printf("Grade 16+\n");
    } else {
        printf("Grade %d\n", grade);
    }
}