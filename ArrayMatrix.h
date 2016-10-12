//
// Created by Ryan Morales on 9/23/16.
//

#ifndef SPARSE_PHASE_2_ARRAYMATRIX_H
#define SPARSE_PHASE_2_ARRAYMATRIX_H

#include "array.h"

class ArrayMatrix {
private:
    int rows;
    int cols;
    int lastRow;
    int lastCol;
    bool sorted;
    Array *arrayList;
public:
    ArrayMatrix();

    ArrayMatrix(string filename);

    ArrayMatrix(ArrayMatrix *copy);

    ~ArrayMatrix();

    void readFile(string filename);

    bool isMatrixSorted();

    double getValueAtCoordinate(int row, int col);

    void setValueAtCoordinate(int row, int col, double value);

    void copyMatrix(ArrayMatrix *copy);

    bool multiplicationCompatible(ArrayMatrix *matrix);

    ArrayMatrix *matrixMultiplication(ArrayMatrix *matrix);

    double binarySearch(int row, int col);

    bool additionCompatible(ArrayMatrix *matrix);

    bool addMatrix(ArrayMatrix *matrix);

    bool addMatrixRecursive(ArrayMatrix *matrix);

    void addMatrixRecursive(ArrayMatrix *matrix, int current);

    void cleanZeroes();

    void sortMatrix();

    void printMatrix();

    void printToFile(string filename);
};

#endif //SPARSE_PHASE_2_ARRAYMATRIX_H
