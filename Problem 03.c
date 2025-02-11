#include <stdio.h>

#include <stdlib.h>

#include <limits.h>



void clearStandardInput();



int             readNumb(                   );
unsigned int    readSize(const char* size   );



int**   buildMatrix(                unsigned int rows, unsigned int cols);
void    clearMatrix(int*** matrix,  unsigned int rows                   );



void inputMatrix(           int**   matrix, unsigned int rows, unsigned int cols);
void printMatrix(const int* const*  matrix, unsigned int rows, unsigned int cols);

int traverseMatrix(int** matrix, unsigned int rows, unsigned int cols, unsigned int i, unsigned int j, int health, int* maxHealth, int counter);

void findPath(int** matrix, unsigned int rows, unsigned int cols);



int main() {
    unsigned int rows   =   readSize("ROWS");
    unsigned int cols   =   readSize("COLS");

    int** matrix = buildMatrix(rows, cols);
    
    if (matrix == NULL) {
        puts("Allocating Memory... ERROR!");

        return 1;
    } else {
        inputMatrix(                    matrix, rows, cols);
        printMatrix((const int* const*) matrix, rows, cols);
    }

    findPath(matrix, rows, cols);

    clearMatrix(&matrix, rows);

    return 0;
}



void clearStandardInput() {
    int c = 0;

    while ((c = getchar()) && c != '\n' && c != EOF);
}



int readNumb() {
    int numb            =   0;
    int inputArgument   =   0;

    do {
        inputArgument = scanf("%d", &numb);

        if (inputArgument != 1) {
            clearStandardInput();
        }
    } while (inputArgument != 1);

    return numb;
}

unsigned int readSize(const char* string) {
    unsigned int size   =   0;
    int inputArgument   =   0;

    do {
        printf("Enter the %s size of the matrix: ", string);

        inputArgument = scanf("%u", &size);

        if (inputArgument != 1) {
            clearStandardInput();
        }
    } while (inputArgument != 1 || size == 0);
    
    return size;
}



int** buildMatrix(unsigned int rows, unsigned int cols) {
    int** matrix = (int**)(malloc(rows * sizeof(int*)));

    for (unsigned int i = 0; i < cols; ++i) {
        matrix[i] = (int*)(malloc(cols * sizeof(int)));

        if (matrix[i] == NULL) {
            clearMatrix(&matrix, i);

            return NULL;
        }
    }

    return matrix;
}

void clearMatrix(int*** matrix, unsigned int rows) {
    for (unsigned int i = 0; i < rows; ++i) {
        free((*matrix)[i]);
    }

    free(*matrix);
}



void inputMatrix(int** matrix, unsigned int rows, unsigned int cols) {
    printf("Enter the elements of the matrix:\n");

    for (unsigned int i = 0; i < rows; ++i) {
        for (unsigned int j = 0; j < cols; ++j) {
            matrix[i][j] = readNumb();
        }
    }
}

void printMatrix(const int* const* matrix, unsigned int rows, unsigned int cols) {
    printf("The elements of the matrix are:\n");

    for (unsigned int i = 0; i < rows; ++i) {
        for (unsigned int j = 0; j < cols; ++j) {
            printf("%d ", matrix[i][j]);
        }

        putchar('\n');
    }
}

int isOutsideMatrix(unsigned int rows, unsigned int cols, unsigned int i, unsigned int j) {
    return i >= rows || j >= cols;
}

int max(int a, int b) { return a > b ? a : b; }

int traverseMatrix(int** matrix, unsigned int rows, unsigned int cols, unsigned int i, unsigned int j, int health, int* maxHealth, int counter) {
    // printf("We are at: %u %u, HP: %i\n", i, j, health);

    if (isOutsideMatrix(rows, cols, i, j)) {
        return 0;
    }

    if (health <= 0) {
        return 0;
    }
    int oldMax = *maxHealth;
    if (i == rows - 1 && j == cols - 1) {
        *maxHealth = max(health, *maxHealth);

        // printf("Are we here? %d\n", *maxHealth);
        return 1;
    }

    if (i != 0 || j != 0) {
        health = health + matrix[i][j] - counter;
    }

    int a =  traverseMatrix(matrix, rows, cols, i - 1, j, health, maxHealth, counter + 1) ||
            traverseMatrix(matrix, rows, cols, i + 1, j, health, maxHealth, counter + 1) ||
            traverseMatrix(matrix, rows, cols, i, j - 1, health, maxHealth, counter + 1) ||
            traverseMatrix(matrix, rows, cols, i, j + 1, health, maxHealth, counter + 1);
    if (a == 1) {
        return a;
    }
    if (i == rows - 1 && j == cols - 1) {
        *maxHealth = oldMax;
    }
    return a;

}

void findPath(int** matrix, unsigned int rows, unsigned int cols) {
    int hello = INT_MIN;
    int* result = &hello;

    int way = traverseMatrix(matrix, rows, cols, 0, 0, matrix[0][0], result, 0);

    printf("Is there a way: %d\n", way);
    printf("The result is: %d\n", *result);
}

/*'
5
5
1 2 3 4 5
100 0 0 0 6
100 0 0 1 7
100 0 0 0 8
100 100 100 100 9
*/
