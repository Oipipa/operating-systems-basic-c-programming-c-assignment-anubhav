#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

// Function to check if a string is a positive integer
int is_positive_integer(char *str) {
    if (str == NULL || *str == '\0') return 0;
    char *p = str;
    while (*p) {
        if (!isdigit(*p)) return 0;
        p++;
    }
    int val = atoi(str);
    if (val <= 0) return 0;
    return 1;
}

int main(int argc, char *argv[]) {
    // Initialize random number generator
    srand(time(NULL));
    int minrand = 1;
    int maxrand = 100;

    // Check number of arguments
    if (argc - 1 != 2) {
        printf("Incorrect usage. You provided %d arguments. The correct number of arguments is 2\n", argc - 1);
        return 1;
    }

    // Check if arguments are positive integers greater than 0
    if (!is_positive_integer(argv[1]) || !is_positive_integer(argv[2])) {
        printf("Incorrect usage. The parameters you provided are not positive integers\n");
        return 1;
    }

    // Get the integer values
    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);

    // Create dynamically allocated matrix
    int **matrix = malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        // Initialize each entry with a random integer between 1 and 100
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = minrand + rand() % (maxrand - minrand + 1);
        }
    }

    // Create and write to "matrix.txt"
    FILE *fp = fopen("matrix.txt", "w");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(fp, "%d", matrix[i][j]);
            if (j != cols - 1) {
                fprintf(fp, " ");
            }
        }
        fprintf(fp, "\n");
    }
    fclose(fp);

    // Free allocated memory
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
