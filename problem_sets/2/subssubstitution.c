// Dependency libraries -

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// prototypes.

int check_key_func(char* str); 

char* get_user_input();

char* translated_text_function(char* user_input, char* key);
// The main logic -

int main(int argc, char *argv[]) {
    // argc - argument count, the number of command-line arguments
    // argv - argument vector, an array of character pointers listing all the arguments

    // If the number of sysargs -
    // is not exactly 2 (including the program name) -
    // then exit the program.
    if (argc != 2){
      return 1;
    }

    // now verify that the second sys arg has exactly 26 chars -
    if (strlen(argv[1]) != 26){
      printf("Usage: ./substitution key\n");
      return 1;
    }

    // Now verify the propriety of the user supplied input -
    // i.e. it has all the values from A..Z with each char -
    // present exactly once.
    int key_validity = check_key_func(argv[1]);

    if (key_validity != 0){
      // print test
      printf("The key has 26 chars but is crooked!\n");
      return 1;
    }

    // At this point in time we have verified the key -
    // for length and content. Now we can get the input -
    // from the user.
    
    //  to just print this here -
    // and not pollute the function logic.
    printf("Plaintext:"); 

    // Get the user's input.
    
    char* user_input = get_user_input();

    // Call the translation function.
     
    char* encrypted_text = translated_text_function(user_input, argv[1]);

    printf("ciphertext: %s\n",encrypted_text);

  
    free(encrypted_text);
          
    return 0;    
}

// Function:- `get_user_input`
// This is the general function for getting -
// the user's input.

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

// Function:- `check_key_func`
// Goal:- Check if the user supplied key is proper i.e. -
// has all the values from A..Z with each char present exactly once.
// Return type:- An int.
// Returns 0 if the key is right -
// else returns 1.

int check_key_func(char* str) {
    int letter_count[26] = {0};  // Array to keep track of each letter's occurrence
    int value_count = 0;

    while (*str) {
        char current_letter = toupper(*str);

        // Check if it's a valid uppercase letter
        if (current_letter < 'A' || current_letter > 'Z') {
            printf("Error: Key must only contain alphabetic characters.\n");
            return 1;
        }

        // Increment the count for this letter
        int index = current_letter - 'A';
        letter_count[index]++;

        // Check for repeated letters
        if (letter_count[index] > 1) {
            printf("Error: Key contains repeated letters.\n");
            return 1;
        }

        value_count += (unsigned int) current_letter;
        str++;
    }

    // Check if all letters are present
    for (int i = 0; i < 26; i++) {
        if (letter_count[i] == 0) {
            printf("Error: Key must contain all letters from A to Z.\n");
            return 1;
        }
    }

    // The sum check is redundant now, but kept for consistency with original code
    if (value_count == 2015) {
        return 0;  // Valid key
    } else {
        printf("Usage: ./substitution key\n");
        return 1;  // Invalid key
    }
}
// Function:- `translated_text_func`
// Goal:- Return the converted cipher text.
// Takes:-
// 1. User supplied plaintext
// 2. The verified encryption key
// Returns:- The encrypted text.
char* translated_text_function(char* user_input, char* key) {
    
    // Allocate memory for the final string
    char* final_string = (char*)malloc((strlen(user_input) + 1) * sizeof(char));
    if (final_string == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    int i = 0;
    while (*user_input) {
        
        // Make case-insensitive
        char current = *user_input;        
        if (current >= 65 && current <= 90) {
            int position = (unsigned int)current - 65;
            final_string[i] = toupper(key[position]);
        } else if (current >= 97 && current <= 122){

          int position = (unsigned int)current - 97;

          final_string[i] = tolower(key[position]);

        }else {
            final_string[i] = *user_input;
        }

        user_input++;
        i++;
    }

    //final_string[i] = '\0'; // Null-terminate the final string
    
    return final_string;
}
