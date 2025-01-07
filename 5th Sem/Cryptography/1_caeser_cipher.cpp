// WAP to implement a Caesar Cipher
/* 
   Formula: 
       C = (P + K) mod 26
   Where:
       P = Plaintext (each letter of the input text)
       C = Ciphertext (each encrypted letter)
       K = Key (number of positions to shift)

   Steps to convert this formula into programming logic:
   1. Convert each letter to its numeric position:
       i. For uppercase letters: position = char - 'A'
       ii. For lowercase letters: position = char - 'a'

   2. Apply the Caesar Cipher formula:
       C(Number) = (P(Number) + K) mod 26

   3. Convert the numeric position back to a letter:
       i. For uppercase letters: char = position + 'A'
       ii. For lowercase letters: char = position + 'a'

   4. Preserve non-alphabetic characters (e.g., spaces, numbers, punctuation).

   5. Handle key input:
       - If the key is a number, use it directly.
       - If the key is a letter, convert it to its numeric position:
           Key (K) = toupper(key) - 'A'

   Note: This program accepts a key as either a single digit (0-9) or a letter (A-Z).
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX 100

// Function to perform Caesar Cipher encryption
void caesar_cipher(char ptext[], char ctext[], int key);

int main() {
    char ptext[MAX], ctext[MAX], key_input[MAX];
    int key;

    // Read plaintext from the user
    printf("Enter a plaintext: ");
    gets(ptext);

    // Read the key (either a number or a single letter)
    printf("Enter a key (number or single letter): ");
    scanf("%s", key_input);

    // Validate and process the key
    if (isdigit(key_input[0]) && strlen(key_input) == 1) {
        key = key_input[0] - '0'; // Convert numeric key to integer
    } else if (isalpha(key_input[0]) && strlen(key_input) == 1) {
        key = toupper(key_input[0]) - 'A'; // Convert letter key to numeric position (0–25)
    } else {
        printf("Invalid key. Please enter a number or a single letter.\n");
        return 1; // Exit the program with error
    }

    // Encrypt the plaintext
    caesar_cipher(ptext, ctext, key);

    // Display the resulting ciphertext
    printf("Ciphertext is: %s\n", ctext);

    return 0;
}

// Function to apply Caesar Cipher logic
void caesar_cipher(char ptext[], char ctext[], int key) {
    for (int i = 0; ptext[i] != '\0'; i++) {
        if (isalpha(ptext[i])) { // Process only alphabetic characters
            char base = islower(ptext[i]) ? 'a' : 'A'; // Determine base ('a' or 'A')
            ctext[i] = ((ptext[i] - base + key) % 26) + base; // Apply cipher formula
        } else {
            ctext[i] = ptext[i]; // Preserve non-alphabetic characters
        }
    }
    ctext[strlen(ptext)] = '\0'; // Null-terminate the ciphertext string
}

