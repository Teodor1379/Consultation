#include <assert.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <limits.h>



#define MAX 32


void clearStandardInput();


unsigned int    readNumb();
unsigned int    readSize();


int*    buildArray(unsigned int size);
void    clearArray(int* array);

void inputArray(int* array, unsigned int size);
void printArray(const int* array, unsigned int size);

unsigned int countPalindromes(const int* array, unsigned int size);
void onlyPalindromes(int** array, unsigned int size);

void printNumberBinary(unsigned int number) {
    unsigned int array[32] = { 0 };

    unsigned int counter = 32 - 1;

    while (number > 0) {
        array[counter] = number % 2;

        number  = number    / 2;
        counter = counter   - 1;
    }

    for (unsigned int i = 0; i < 32; ++i) {
        printf("%u", array[i]);
    }

    putchar('\n');
}


int isPalindrome(int number) {
    int temporary = number;

    unsigned int counter = 0;

    while (number != 0) {
        number = number / 2;
        counter += 1;
    }

    unsigned int index1 = counter - 1;
    unsigned int index2 = 0;

    while (index1 >= index2) {
        unsigned int bit1 = ((temporary & (1 << index1)) >> (index1)) & 1;  // Left     Bit
        unsigned int bit2 = ((temporary & (1 << index2)) >> (index2)) & 1;  // Right    Bit

        if (bit1 != bit2) {
            return 0;
        }

        index1 -= 1;
        index2 += 1;
    }

    return 1;
}


int main() {
    unsigned int size = readSize();

    int* array = buildArray(size);

    if (array == NULL) {
        puts("Allocating Memory... ERROR!");

        return 1;
    }

    unsigned int counter = countPalindromes(array, size);

    onlyPalindromes(&array, size);

    printArray(array, counter);

    clearArray(array);

    array = NULL;

    return 0;
}



void clearStandardInput() {
    int c = 0;

    while ((c = getchar()) && c != '\n' && c != EOF);
}

unsigned int readNumb() {
    unsigned int numb   =   0;
    int inputArgument   =   0;

    do {
        inputArgument = scanf("%u", &numb);

        if (inputArgument != 1) {
            clearStandardInput();
        }
    } while (inputArgument != 1);

    return numb;
}

unsigned int readSize() {
    unsigned int size = 0;
    int inputArgument = 0;

    do {
        printf("Enter the size of the array: ");

        inputArgument = scanf("%u", &size);

        if (inputArgument != 1) {
            clearStandardInput();
        }
    } while (inputArgument != 1);

    return size;
}


int* buildArray(unsigned int size) {
    assert(size > 0);
    
    int* result = (int*)(malloc(size * sizeof(int)));

    if (result != NULL) {
        inputArray(result, size);
        printArray(result, size);
    }

    return result;
}

void clearArray(int* array) {
    if (array == NULL) {
        puts("Freeing Memory... ERROR!");

        exit(EXIT_FAILURE);
    }
    
    free(array);
}

void inputArray(int* array, unsigned int size) {
    assert(array != NULL);
    assert(size  != 0);
    
    printf("Enter the elements of the array: ");

    for (unsigned int i = 0; i < size; ++i) {
        array[i] = readNumb();
    }
}

void printArray(const int* array, unsigned int size) {
    assert(array != NULL);
    assert(size  != 0   );

    printf("The elements of the array are: ");

    for (unsigned int i = 0; i < size; ++i) {
        printf("%d ", array[i]);
    }

    putchar('\n');
}


unsigned int countPalindromes(const int* array, unsigned int size) {
    unsigned int count = 0;

    for (unsigned int i = 0; i < size; ++i) {
        if (isPalindrome(array[i])) {
            count = count + 1;
        }
    }

    return count;
}

void onlyPalindromes(int** array, unsigned int size) {
    unsigned int counter = countPalindromes(*array, size);

    for (unsigned int i = 0; i < size; ++i) {
        if (!isPalindrome((*array)[i])) {
            for (unsigned int j = i; j < size - 1; ++j) {
                (*array)[j] = (*array)[j + 1];
            }
        }
    }

    printArray(*array, counter);

    int* result = (int*)(realloc(*array, sizeof(int) * counter));

    if (result != NULL) {
        printf("Hello World!");
    }

    unsigned int index = 0;

    *array = result;
}