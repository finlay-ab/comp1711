#include <stdio.h>

//prints column at index colindex
void printColumn(int a[][4], int colIndex, int rows, char when) {
    switch (when) {
        case 'B':
            printf("Values in column %d before change:\n", colIndex); break;

        case 'A':
            printf("Values in column %d after change:\n", colIndex); break;

        default: 
            printf("Invalid option\n");
            return;
    }

    for (int i = 0; i < rows; ++i) {
        printf("%d\n", a[i][colIndex]);
    }
}

//changes all values in colum and colindex to newvalue.
void changeColumn(int a[][4], int colIndex, int rows, int newValue) {
    for (int i = 0; i < rows; ++i) {
        a[i][colIndex] = newValue;
    }
}

int main() {
    int array1[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    int colIndexToChange = 0; // Change the values in the third column (column at index 2)
    int newValue = 43; //value that colum in colindextochange gets changed to

    printColumn(array1, colIndexToChange, 3, 'B'); // 'B' stands for Before
    changeColumn(array1, colIndexToChange, 3, newValue);
    printColumn(array1, colIndexToChange, 3, 'A'); // 'A' stands for After

    return 0;
}
