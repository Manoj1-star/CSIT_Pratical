#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 2
#define MAX 100

void convertStringtoArrOfint(char text[], int a[]);
void convertArrOfinttoString(int a[], char text[]);
void remove_space(char original_text[], char text_without_space[]);
void convertTo2DArray(int input[], int output[][SIZE]);
void convertTo1DArray(int input[][SIZE], int output[]);
void hill_cipher(int ptext[][SIZE], int ctext[][SIZE], int key[SIZE][SIZE]);
int gcd(int a, int b);

int main() {
    char ptext[MAX], ctext[MAX]; 
    int key[SIZE][SIZE], a[MAX], b[SIZE][SIZE];

    // Input plaintext
    printf("Enter a plaintext: ");
    fgets(ptext, MAX, stdin);
    ptext[strcspn(ptext, "\n")] = '\0'; // Remove newline character

    // Add padding 'X' if length is odd
    if (strlen(ptext) % 2 != 0) {
        ptext[strlen(ptext)] = 'X';
        ptext[strlen(ptext) + 1] = '\0'; // Null-terminate the string after adding 'X'
    }

    printf("Enter the elements of a 2x2 matrix (key):\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("Enter value for key[%d][%d]: ", i, j);
            scanf("%d", &key[i][j]);
        }
    }

    // Check if the key matrix is invertible by calculating the determinant (mod 26)
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;
    if (det == 0 || gcd(det, 26) != 1) {
        printf("The key matrix is not invertible. Try a different matrix.\n");
        return 1;
    }

    // Remove spaces from plaintext
    remove_space(ptext, ptext);

    // Convert plaintext to array of integers
    convertStringtoArrOfint(ptext, a);

    // Convert 1D array to 2D array
    convertTo2DArray(a, b);

    // Apply Hill Cipher
    hill_cipher(b, b, key);

    // Convert 2D array back to 1D array
    convertTo1DArray(b, a);

    // Convert array back to string (ciphertext)
    convertArrOfinttoString(a, ctext);  

    // Output ciphertext
    printf("Ciphertext is: %s\n", ctext);
}

// Convert plaintext string to integer array (A=0, B=1, ..., Z=25)
void convertStringtoArrOfint(char text[], int a[]) {
    int i = 0;
    while (text[i] != '\0') { 
        a[i] = toupper(text[i]) - 'A';  
        i++;
    }
}

// Convert integer array back to string (0=A, 1=B, ..., 25=Z)
void convertArrOfinttoString(int a[], char text[]) {
    int i = 0;
    while (a[i] >= 0 && a[i] <= 25) {  
        text[i] = (char)(a[i] + 'A');   
        i++;
    }
    text[i] = '\0';  // Null-terminate the string
}

// Remove spaces from the original text
void remove_space(char original_text[], char text_without_space[]) {
    int j = 0;
    for (int i = 0; original_text[i] != '\0'; i++) {
        if (original_text[i] != ' ') {
            text_without_space[j++] = original_text[i];
        }
    }
    text_without_space[j] = '\0';
}

// Convert 1D integer array to 2D array for Hill cipher encryption
void convertTo2DArray(int input[], int output[][SIZE]) {
    int index = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            output[i][j] = input[index++];
        }
    }
}

// Convert 2D integer array back to 1D array after Hill cipher encryption
void convertTo1DArray(int input[][SIZE], int output[]) {
    int index = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            output[index++] = input[i][j];
        }
    }
}

// Hill cipher encryption (matrix multiplication)
void hill_cipher(int ptext[][SIZE], int ctext[][SIZE], int key[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            ctext[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                ctext[i][j] += (key[i][k] * ptext[k][j]) % 26;
            }
            ctext[i][j] = ctext[i][j] % 26;
        }
    }
}

// GCD Function
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

