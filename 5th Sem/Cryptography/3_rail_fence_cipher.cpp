#include <stdio.h>
#include <string.h>
#define MAX 20

void remove_space(char original_text[], char text_without_space[]);
void rail_fence_cipher(char ptext[], char ctext[], int depth);

int main() {
    char ptext[MAX], ctext[MAX]; 
    int depth;

    printf("Enter a plaintext: ");
    gets(ptext);

    printf("Enter a depth (or key): ");
    scanf("%d", &depth);

    remove_space(ptext, ptext);
    rail_fence_cipher(ptext, ctext, depth);

    printf("Ciphertext is: %s\n", ctext);
}

void remove_space(char original_text[], char text_without_space[]) {
    int j = 0;
    for (int i = 0; original_text[i] != '\0'; i++) {
        if (original_text[i] != ' ') {
            text_without_space[j++] = original_text[i];
        }
    }
    text_without_space[j] = '\0';
}

void rail_fence_cipher(char ptext[], char ctext[], int depth) {
    int len = strlen(ptext);
    char rail[depth][len];

    // Initialize rail matrix with '*'
    for (int i = 0; i < depth; i++) {
        for (int j = 0; j < len; j++) {
            rail[i][j] = '*';
        }
    }

    int row = 0, dir_down = 0;

    // Fill rail matrix with plaintext in zigzag
    for (int i = 0; i < len; i++) {
        rail[row][i] = ptext[i];

        if (row == 0 || row == depth - 1)
            dir_down = !dir_down;

        row += dir_down ? 1 : -1;
    }

    // Read rail matrix to construct ciphertext
    int index = 0;
    for (int i = 0; i < depth; i++) {
        for (int j = 0; j < len; j++) {
            if (rail[i][j] != '*') {
                ctext[index++] = rail[i][j];
            }
        }
    }
    ctext[index] = '\0';
}

