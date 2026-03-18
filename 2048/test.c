#include <stdio.h>
#include <stdlib.h>

// 定义4x4矩阵的大小
#define ROWS 4
#define COLS 4

// 打印矩阵
void printMatrix(int matrix[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// 上移并合并相同的元素
void moveAndMergeElementsUp(int matrix[ROWS][COLS]) {
    for (int col = 0; col < COLS; col++) {
        int nonZeroIndex = 0; // 跟踪下一非零元素的位置

        for (int row = 0; row < ROWS; row++) {
            if (matrix[row][col] != 0) {
                if (nonZeroIndex > 0 && matrix[nonZeroIndex - 1][col] == matrix[row][col]) {
                    // 合并相同元素
                    matrix[nonZeroIndex - 1][col] *= 2;
                    matrix[row][col] = 0;
                } else {
                    if (row != nonZeroIndex) {
                        // 上移非零元素
                        matrix[nonZeroIndex][col] = matrix[row][col];
                        matrix[row][col] = 0;
                    }
                    nonZeroIndex++;
                }
            }
        }
    }
}

// 下移并合并相同的元素
void moveAndMergeElementsDown(int matrix[ROWS][COLS]) {
    for (int col = 0; col < COLS; col++) {
        int nonZeroIndex = ROWS - 1; // 跟踪下一非零元素的位置

        for (int row = ROWS - 1; row >= 0; row--) {
            if (matrix[row][col] != 0) {
                if (nonZeroIndex < ROWS - 1 && matrix[nonZeroIndex + 1][col] == matrix[row][col]) {
                    // 合并相同元素
                    matrix[nonZeroIndex + 1][col] *= 2;
                    matrix[row][col] = 0;
                } else {
                    if (row != nonZeroIndex) {
                        // 下移非零元素
                        matrix[nonZeroIndex][col] = matrix[row][col];
                        matrix[row][col] = 0;
                    }
                    nonZeroIndex--;
                }
            }
        }
    }
}

// 左移并合并相同的元素
void moveAndMergeElementsLeft(int matrix[ROWS][COLS]) {
    for (int row = 0; row < ROWS; row++) {
        int nonZeroIndex = 0; // 跟踪下一非零元素的位置

        for (int col = 0; col < COLS; col++) {
            if (matrix[row][col] != 0) {
                if (nonZeroIndex > 0 && matrix[row][nonZeroIndex - 1] == matrix[row][col]) {
                    // 合并相同元素
                    matrix[row][nonZeroIndex - 1] *= 2;
                    matrix[row][col] = 0;
                } else {
                    if (col != nonZeroIndex) {
                        // 左移非零元素
                        matrix[row][nonZeroIndex] = matrix[row][col];
                        matrix[row][col] = 0;
                    }
                    nonZeroIndex++;
                }
            }
        }
    }
}

// 右移并合并相同的元素
void moveAndMergeElementsRight(int matrix[ROWS][COLS]) {
    for (int row = 0; row < ROWS; row++) {
        int nonZeroIndex = COLS - 1; // 跟踪下一非零元素的位置

        for (int col = COLS - 1; col >= 0; col--) {
            if (matrix[row][col] != 0) {
                if (nonZeroIndex < COLS - 1 && matrix[row][nonZeroIndex + 1] == matrix[row][col]) {
                    // 合并相同元素
                    matrix[row][nonZeroIndex + 1] *= 2;
                    matrix[row][col] = 0;
                } else {
                    if (col != nonZeroIndex) {
                        // 右移非零元素
                        matrix[row][nonZeroIndex] = matrix[row][col];
                        matrix[row][col] = 0;
                    }
                    nonZeroIndex--;
                }
            }
        }
    }
}

int main() {
    // 示例矩阵
    int matrix[ROWS][COLS] = {
        {2, 0, 2, 0},
        {2, 0, 2, 2},
        {0, 2, 0, 0},
        {2, 0, 2, 2}
    };

    printf("原矩阵:\n");
    printMatrix(matrix);

    moveAndMergeElementsUp(matrix);
    printf("上移并合并非零元素后的矩阵:\n");
    printMatrix(matrix);

    // 重置矩阵
    int matrixDown[ROWS][COLS] = {
        {2, 0, 2, 0},
        {2, 0, 2, 2},
        {0, 2, 0, 0},
        {2, 0, 2, 2}
    };

    moveAndMergeElementsDown(matrixDown);
    printf("下移并合并非零元素后的矩阵:\n");
    printMatrix(matrixDown);

    // 重置矩阵
    int matrixLeft[ROWS][COLS] = {
        {2, 0, 2, 0},
        {2, 0, 2, 2},
        {0, 2, 0, 0},
        {2, 0, 2, 2}
    };

    moveAndMergeElementsLeft(matrixLeft);
    printf("左移并合并非零元素后的矩阵:\n");
    printMatrix(matrixLeft);

    // 重置矩阵
    int matrixRight[ROWS][COLS] = {
        {2, 0, 2, 0},
        {2, 0, 2, 2},
        {0, 2, 0, 0},
        {2, 0, 2, 2}
    };

    moveAndMergeElementsRight(matrixRight);
    printf("右移并合并非零元素后的矩阵:\n");
    printMatrix(matrixRight);

    return 0;
}
