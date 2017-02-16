//
// Created by Ryan Morales on 9/23/16.
//

#ifndef SPARSE_PHASE_2_ARRAYMATRIX_H
#define SPARSE_PHASE_2_ARRAYMATRIX_H

#define COLUMN_WIDTH 20

#include "array.h"

class ArrayMatrix {
private:
    int rows;
    int cols;
    int lastRow;
    int lastCol;
    bool sorted;
    Array *arrayList;
    int count = 0;
    int count2 = 0;

public:
    static int counter;

    ArrayMatrix();

    ArrayMatrix(string filename, string outfile);

    ArrayMatrix(ArrayMatrix *copy);

    ~ArrayMatrix();

    void readFile(string filename, string outfile);

    bool isMatrixSorted();

    double getValueAtCoordinate(int row, int col);

    void setValueAtCoordinate(int row, int col, double value);

    void copyMatrix(ArrayMatrix *copy);

    bool multiplicationCompatible(ArrayMatrix *matrix);

    ArrayMatrix *matrixMultiplication(ArrayMatrix *matrix);

    //void addPoints(Array *newPoints);

    //Array *scalarMultiplyRow(int row, int value);

    //Array *scalarMultiplyCol(int col, int value);

    double binarySearch(int row, int col);

    bool additionCompatible(ArrayMatrix *matrix);

    bool addMatrix(ArrayMatrix *matrix);

    bool addMatrixRecursive(ArrayMatrix *matrix);

    void addMatrixRecursive(ArrayMatrix *matrix, int current);

    void cleanZeroes();

    void sortMatrix();

    void merge(int l, int m, int r);

    void mergeSort(int l, int r);

    void printMatrix();

    void nlogn();

    int numOfentries();

    void printBigO(string algorithm, int entries, double bigO);

    void printToFile(string filename);
};

#endif //SPARSE_PHASE_2_ARRAYMATRIX_H
