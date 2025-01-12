#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 20

void prepare_key(char key[], char newKey[], char ptext[]);
void vernam_cipher(char ptext[], char ctext[], char key[]);
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

    // Input key
    printf("Enter a key: ");
    fgets(key, MAX, stdin);
    remove_space(key, key);

    // Remove the newline character from the input if present
    ptext[strcspn(ptext, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';

    // Check key length
    if (strlen(ptext) >= strlen(key)) {
        prepare_key(key, key, ptext);
    } else {
        printf("Length of key is greater than length of plaintext.\n");
        return 1;
    }

    // Encrypt using Vernam Cipher
    vernam_cipher(ptext, ctext, key);

    // Output ciphertext
    printf("The Ciphertext is: %s\n", ctext);

    return 0;
}

// Expands the key to match the length of the plaintext
void prepare_key(char key[], char newKey[], char ptext[]) {
    int lenKey = strlen(key), lenPtext = strlen(ptext), j = 0;

    for (int i = 0; j < lenPtext; i++) {
        if (i == lenKey)  
            i = 0;
        newKey[j++] = key[i];
    }
    newKey[j] = '\0';  
}

void vernam_cipher(char ptext[], char ctext[], char key[]) {
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

