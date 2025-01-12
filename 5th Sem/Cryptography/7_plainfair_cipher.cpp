#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Function Declarations
int isPresent(char *array, char ch);
void preprocessInput(char *input, char *processed);
void buildMatrix(char matrix[5][5], char *processed);
void printMatrix(char matrix[5][5]);
void formatInput(char *input, char *formatted);
void encryptPlayfair(char *input, char matrix[5][5], char *encrypted);
void findPosition(char ch, char matrix[5][5], int *row, int *col);

int main() {
    char key[100], formattedInput[50], encrypted[50];  // Variables for key, formatted input, and encrypted text
    char matrix[5][5] = {{'\0'}};  // 5x5 matrix initialized to null
    char processed[26] = "";       // Processed array to hold unique characters (max 25)

    // Step 1: Get the key for Playfair Cipher
    printf("Enter a key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';  // Remove trailing newline

    // Step 2: Preprocess the key (remove duplicates, replace 'J' with 'I')
    preprocessInput(key, processed);

    // Step 3: Build the Playfair Cipher matrix using the processed key
    buildMatrix(matrix, processed);

    // Step 4: Print the matrix
    printf("\nKey (5x5) Matrix Formation:\n");
    printMatrix(matrix);

    // Step 5: Get the plaintext to encrypt
    char input[100];  // Plaintext input
    printf("\nEnter a Plaintext: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';  // Remove trailing newline

    // Step 6: Format the input (ensuring pairs of letters and handling 'J')
    formatInput(input, formattedInput);

    // Step 7: Encrypt the formatted input using the Playfair Cipher
    encryptPlayfair(formattedInput, matrix, encrypted);

    // Step 8: Print the ciphertext
    printf("\nCiphertext is: %s\n", encrypted);

    return 0;
}

// Function Definitions

// Check if a character is already in the array (matrix or processed input)
int isPresent(char *array, char ch) {
    for (int i = 0; array[i] != '\0'; i++) {
        if (array[i] == ch) {
            return 1;  // Character already exists
        }
    }
    return 0;  // Character does not exist
}

// Preprocess the key input: remove duplicates, convert to uppercase, replace 'J' with 'I'
void preprocessInput(char *input, char *processed) {
    int index = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        char ch = toupper(input[i]);  // Convert to uppercase

        if (ch == 'J') {
            ch = 'I';  // Replace 'J' with 'I'
        }

        if (isalpha(ch) && !isPresent(processed, ch)) {
            processed[index++] = ch;  // Add unique characters
        }
    }
    processed[index] = '\0';  // Null-terminate the processed string
}

// Build the Playfair Cipher matrix: 5x5, excluding 'J'
void buildMatrix(char matrix[5][5], char *processed) {
    char alphabet[] = "ABCDEFGHIKLMNOPQRSTUVWXYZ";  // Alphabet without 'J'
    int index = 0;

    // Step 1: Fill matrix with characters from the processed key
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (processed[index] != '\0') {
                matrix[i][j] = processed[index++];  // Insert character from key
            } else {
                break;
            }
        }
    }

    // Step 2: Fill the remaining matrix spaces with unused characters from the alphabet
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == '\0') {
                for (int k = 0; k < 25; k++) {
                    if (!isPresent(processed, alphabet[k])) {
                        matrix[i][j] = alphabet[k];  // Add unused characters
                        processed[index++] = alphabet[k];  // Mark character as used
                        processed[index] = '\0';  // Null-terminate processed string
                        break;
                    }
                }
            }
        }
    }
}

// Print the Playfair matrix (for debugging purposes)
void printMatrix(char matrix[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Format the input to ensure it has pairs of letters, inserting 'X' if the same letter is repeated
void formatInput(char *input, char *formatted) {
    int index = 0;
    int len = strlen(input);

    for (int i = 0; i < len; i++) {
        char ch = toupper(input[i]);

        if (ch == 'J') ch = 'I';  // Replace 'J' with 'I'

        if (isalpha(ch)) {
            if (i < len - 1 && toupper(input[i]) == toupper(input[i + 1])) {
                formatted[index++] = ch;
                formatted[index++] = 'X';  // Insert 'X' between same letters
                i++;  // Skip the next letter
            } else {
                formatted[index++] = ch;
            }
        }
    }

    // If the length is odd, append 'X' at the end
    if (index % 2 != 0) {
        formatted[index++] = 'X';
    }
    formatted[index] = '\0';  // Null-terminate the formatted string
}

// Encrypt the input using Playfair Cipher
void encryptPlayfair(char *input, char matrix[5][5], char *encrypted) {
    int index = 0;
    int len = strlen(input);

    for (int i = 0; i < len; i += 2) {
        int row1, col1, row2, col2;

        // Find the position of the first letter
        findPosition(input[i], matrix, &row1, &col1);
        // Find the position of the second letter
        findPosition(input[i + 1], matrix, &row2, &col2);

        // If both letters are in the same row
        if (row1 == row2) {
            encrypted[index++] = matrix[row1][(col1 + 1) % 5];
            encrypted[index++] = matrix[row2][(col2 + 1) % 5];
        }
        // If both letters are in the same column
        else if (col1 == col2) {
            encrypted[index++] = matrix[(row1 + 1) % 5][col1];
            encrypted[index++] = matrix[(row2 + 1) % 5][col2];
        }
        // If letters are in different rows and columns
        else {
            encrypted[index++] = matrix[row1][col2];
            encrypted[index++] = matrix[row2][col1];
        }
    }

    encrypted[index] = '\0';  // Null-terminate the encrypted string
}

// Find the position of a character in the matrix
void findPosition(char ch, char matrix[5][5], int *row, int *col) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

