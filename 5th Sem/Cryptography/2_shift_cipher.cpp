// Program to implement Shift Cipher
/* Shift cipher is same as Caesar cipher, the only difference is it allows negative keys.
General formula is:
    C = ((P + K) mod 26 + 26) mod 26
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h> // Include for atoi()
#define MAX 100

// Function to perform Shift Cipher encryption
void shift_cipher(char ptext[], char ctext[], int key);

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
    if (isdigit(key_input[0]) || (key_input[0] == '-' && isdigit(key_input[1]))) {
        key = atoi(key_input); // Convert numeric key (including negatives) to integer
    } else if (isalpha(key_input[0]) && strlen(key_input) == 1) {
        key = toupper(key_input[0]) - 'A'; // Convert letter key to numeric position (0–25)
    } else {
        printf("Invalid key. Please enter a number or a single letter.\n");
        return 1; // Exit the program with error
    }

    // Encrypt the plaintext
    shift_cipher(ptext, ctext, key);

    // Display the resulting ciphertext
    printf("Ciphertext is: %s\n", ctext);

    return 0;
}

// Function to apply Shift Cipher logic
void shift_cipher(char ptext[], char ctext[], int key) {
    for (int i = 0; ptext[i] != '\0'; i++) {
        if (isalpha(ptext[i])) { // Process only alphabetic characters
            char base = islower(ptext[i]) ? 'a' : 'A'; // Determine base ('a' or 'A')
            ctext[i] = ((ptext[i] - base + key) % 26 + 26) % 26 + base; 
            // Add 26 before % to handle negative shifts
        } else {
            ctext[i] = ptext[i]; // Preserve non-alphabetic characters
        }
    }
    ctext[strlen(ptext)] = '\0'; // Null-terminate the ciphertext string
}

