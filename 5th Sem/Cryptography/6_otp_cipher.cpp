#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20

void prepare_key(char key[], char ptext[]);
void otp_cipher(char ptext[], char ctext[], char key[]);
void remove_space(char original_text[], char text_without_space[]);

int main() {
    printf("Note: This program is Case-Insensitive.\n");
    printf("i.e., It doesn't differentiate between UPPERCASE and lowercase in the key and plaintext.\n");
    printf("Both 'A' and 'a' are treated the same.\n\n");

    char ctext[MAX], ptext[MAX], key[MAX];

    // Input plaintext
    printf("Enter a plaintext: ");
    fgets(ptext, MAX, stdin);
    remove_space(ptext, ptext);

    // Generate a random key using the prepare_key function
    prepare_key(key, ptext);

    // Encrypt using OTP Cipher
    otp_cipher(ptext, ctext, key);

    // Output the random key and the ciphertext
    printf("Generated Random Key: %s\n", key);
    printf("The Ciphertext is: %s\n", ctext);

    return 0;
}

// Function to generate the key automatically based on the plaintext
void prepare_key(char key[], char ptext[]) {
    int lenPtext = strlen(ptext);

    srand(time(0));  // Seed the random number generator

    // Generate a random key with uppercase letters
    for (int i = 0; i < lenPtext; i++) {
        key[i] = 'A' + (rand() % 26);  // Random letter between 'A' and 'Z'
    }
    key[lenPtext] = '\0';  // Null-terminate the key
}

void otp_cipher(char ptext[], char ctext[], char key[]) {
    int cnum, lenPtext = strlen(ptext);
    for (int i = 0; i < lenPtext; i++) {
        // Convert both plaintext and key to uppercase before XOR
        char plainChar = toupper(ptext[i]);
        char keyChar = toupper(key[i]);

        // XOR operation and map back to uppercase letter
        cnum = (plainChar - 'A') ^ (keyChar - 'A');
        
        // Ensure the result is a valid letter in the A-Z range (using modulo 26)
        ctext[i] = (cnum % 26) + 'A';
    }
    ctext[lenPtext] = '\0';  // Null-terminate ciphertext
}

// Remove spaces from text
void remove_space(char original_text[], char text_without_space[]) {
    int j = 0;
    for (int i = 0; original_text[i] != '\0'; i++) {
        if (original_text[i] != ' ' && original_text[i] != '\n') {
            text_without_space[j++] = original_text[i];
        }
    }
    text_without_space[j] = '\0';
}

