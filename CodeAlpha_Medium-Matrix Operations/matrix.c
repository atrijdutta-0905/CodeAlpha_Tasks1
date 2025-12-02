#include <stdio.h>
#define SIZE 10

// Function prototypes
void addMatrices(int mat1[SIZE][SIZE], int mat2[SIZE][SIZE], int result[SIZE][SIZE], int size);
void multiplyMatrices(int mat1[SIZE][SIZE], int mat2[SIZE][SIZE], int result[SIZE][SIZE], int size);
void transposeMatrix(int matrix[SIZE][SIZE], int result[SIZE][SIZE], int size);
void displayMatrix(int matrix[SIZE][SIZE], int size);

int main() {
    int size;
    int A[SIZE][SIZE] = {0}, B[SIZE][SIZE] = {0}, Result[SIZE][SIZE] = {0};

    // Prompt user for matrix size (assuming square matrices for this example)
    printf("Enter the size of the square matrices (up to %d): ", SIZE);
    scanf("%d", &size);

    if (size > SIZE || size <= 0) {
        printf("Invalid size.\n");
        return 1;
    }

    // Input Matrix A
    printf("Enter elements of Matrix A (%dx%d):\n", size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    // Input Matrix B
    printf("Enter elements of Matrix B (%dx%d):\n", size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    printf("\n--- Matrix A ---\n");
    displayMatrix(A, size);
    printf("\n--- Matrix B ---\n");
    displayMatrix(B, size);

    // Matrix Addition
    addMatrices(A, B, Result, size);
    printf("\n--- Matrix A + B ---\n");
    displayMatrix(Result, size);

    // Matrix Multiplication
    multiplyMatrices(A, B, Result, size);
    printf("\n--- Matrix A * B ---\n");
    displayMatrix(Result, size);

    // Transpose of Matrix A
    transposeMatrix(A, Result, size);
    printf("\n--- Transpose of Matrix A ---\n");
    displayMatrix(Result, size);

    return 0;
}

// Function to add two matrices
void addMatrices(int mat1[SIZE][SIZE], int mat2[SIZE][SIZE], int result[SIZE][SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

// Function to multiply two matrices
void multiplyMatrices(int mat1[SIZE][SIZE], int mat2[SIZE][SIZE], int result[SIZE][SIZE], int size) {
    // Initialize result matrix elements to 0
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = 0;
        }
    }

    // Perform multiplication
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

// Function to transpose a matrix
void transposeMatrix(int matrix[SIZE][SIZE], int result[SIZE][SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}

// Function to display a matrix
void displayMatrix(int matrix[SIZE][SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%5d ", matrix[i][j]);
        }
        printf("\n");
    }
}
