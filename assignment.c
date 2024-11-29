#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * Function: is_positive_integer
 * -----------------------------
 *   Checks if a given string represents a positive integer.
 *
 *   str: The string to check.
 *
 *   returns: 1 if the string is a positive integer, 0 otherwise.
 */
int is_positive_integer(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }

    // Check each character to ensure it's a digit
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
    }

    // Convert to integer and check if greater than 0
    long num = strtol(str, NULL, 10);
    if (num <= 0) {
        return 0;
    }

    return 1;
}

int main(int argc, char *argv[]) {
    // Initialize random number generator
    srand(time(NULL));

    // 1. Check the number of arguments
    if (argc != 3) {
        int provided_args = argc - 1;
        if (provided_args == 1) {
            printf("Incorrect usage. You provided %d argument. The correct number of arguments is 2\n", provided_args);
        } else {
            printf("Incorrect usage. You provided %d arguments. The correct number of arguments is 2\n", provided_args);
        }
        return 1;
    }

    // 2. Validate that both arguments are positive integers
    if (!is_positive_integer(argv[1]) || !is_positive_integer(argv[2])) {
        printf("Incorrect usage. The parameters you provided are not positive integers\n");
        return 1;
    }

    // Convert arguments to integers
    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);

    // 3. Dynamically allocate the matrix
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        perror("Failed to allocate memory for rows");
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            perror("Failed to allocate memory for columns");
            // Free previously allocated memory before exiting
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return 1;
        }
    }

    // Initialize matrix with random numbers between 1 and 100
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = (rand() % 100) + 1; // Generates a number between 1 and 100
        }
    }

    // 4. Write the matrix to matrix.txt
    FILE *file = fopen("matrix.txt", "w");
    if (file == NULL) {
        perror("Failed to create matrix.txt");
        // Free allocated memory before exiting
        for (int i = 0; i < rows; i++) {
            free(matrix[i]);
        }
        free(matrix);
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d", matrix[i][j]);
            if (j < cols - 1) {
                fprintf(file, " "); // Add space between numbers, but not after the last number in a row
            }
        }
        fprintf(file, "\n"); // Newline at the end of each row
    }

    fclose(file);

    // 5. Free allocated memory
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
