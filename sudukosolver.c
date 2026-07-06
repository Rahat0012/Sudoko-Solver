#include <stdio.h>
#include <stdbool.h>

#define N 9 // Size of the Sudoku grid

// Function to print the Sudoku grid in a formatted way
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        if (row % 3 == 0 && row != 0) {
            printf("---------------------\n");
        }
        for (int col = 0; col < N; col++) {
            if (col % 3 == 0 && col != 0) {
                printf("| ");
            }
            printf("%d ", grid[row][col]);
        }
        printf("\n");
    }
}

// Function to check if it's safe to place a number in a cell
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check the row
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num) {
            return false;
        }
    }

    // Check the column
    for (int x = 0; x < N; x++) {
        if (grid[x][col] == num) {
            return false;
        }
    }

    // Check the 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku using backtracking
bool solveSudoku(int grid[N][N]) {
    int row, col;
    bool isEmpty = false;

    // Find an empty cell
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty) {
            break;
        }
    }

    // If no empty cell is found, the Sudoku is solved
    if (!isEmpty) {
        return true;
    }

    // Try placing numbers 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            // Recursively try to fill the rest of the grid
            if (solveSudoku(grid)) {
                return true;
            }

            // Backtrack if placing num doesn't lead to a solution
            grid[row][col] = 0;
        }
    }

    return false; // Trigger backtracking
}

int main() {
    int grid[N][N];

    // User input
    printf("Enter the Sudoku puzzle (0 for empty cells):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    printf("\nInput Sudoku:\n");
    printGrid(grid);

    // Solve the puzzle
    if (solveSudoku(grid)) {
        printf("\nSolved Sudoku:\n");
        printGrid(grid);
    } else {
        printf("\nNo solution exists.\n");
    }

    return 0;
}

