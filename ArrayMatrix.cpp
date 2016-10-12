//
// Created by Ryan Morales on 9/23/16.
//

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#include "ArrayMatrix.h"

//help functions
int max(int a, int b);

bool goodInput(string line);

bool greaterThan(MatrixElement a, MatrixElement b);

ArrayMatrix::ArrayMatrix() {
    rows = 0;
    cols = 0;
    lastRow = 0;
    lastCol = 0;
    sorted = true;
    arrayList = new Array;
}

ArrayMatrix::ArrayMatrix(string filename) : ArrayMatrix() {
    this->readFile(filename);
}

ArrayMatrix::~ArrayMatrix() {
    delete arrayList;
}

void ArrayMatrix::readFile(string filename) {
    fstream ifs(filename.c_str());
    if (ifs.fail()) {                                                                    //Checks to see if there is an input file
        cout << "Error File: " << filename << " " << "could not be opened!"
             << endl;          //Prints error is file does not open or exists
        return;
    } else {
        if (ifs.peek() == ifstream::traits_type::eof()) {    //Checks to see if the file is empty
            //cout << "Error: File is empty!!!" << endl;
            return;
        }
    }
    //Matrix that holds zero values
    ArrayMatrix *zeroMatrix = new ArrayMatrix();

    while (!ifs.eof()) {
        //break at end of file
        if (ifs.eof()) {
            break;
        }
        //get line
        string line;
        getline(ifs, line);

        //check if input is valid
        if (goodInput(line)) {
            //parse string
            int row = 0, col = 0;
            double value = 0;
            stringstream fn(line);
            fn >> row >> col >> value;

            //if value == 0, ad to zero matrix;
            if (value == 0) {
                zeroMatrix->setValueAtCoordinate(row, col, value);
            } else {
                this->setValueAtCoordinate(row, col, value);
            }
        }
    }
    //if zeroMatrix row, col or both are bigger, then add biggest zero to matrix
    if ((zeroMatrix->rows >= this->rows && zeroMatrix->cols >= this->cols)) {
        this->setValueAtCoordinate(zeroMatrix->rows, zeroMatrix->cols, 0);
    }

    //Delete zeroMatrix
    delete zeroMatrix;
}

ArrayMatrix::ArrayMatrix(ArrayMatrix *copy) : ArrayMatrix() {
    this->copyMatrix(copy);
}

//Copies Matrix
void ArrayMatrix::copyMatrix(ArrayMatrix *copy) {
    for (int i = 0; i < copy->arrayList->getNumElements(); i++) {
        MatrixElement *current = copy->arrayList->getMatrixElement(i);
        this->setValueAtCoordinate(current->row, current->col, current->value);
    }
}

//Checks to see if Matrix is Compatible for addition
bool ArrayMatrix::additionCompatible(ArrayMatrix *matrix) {
    return matrix->rows == this->rows && matrix->cols == this->cols;
}


//Adds matrices together
bool ArrayMatrix::addMatrix(ArrayMatrix *matrix) {
    if (!this->additionCompatible(matrix)) {
        return false;
    }
    for (int i = 0; i < matrix->arrayList->getNumElements(); i++) {
        MatrixElement *current = matrix->arrayList->getMatrixElement(i);
        this->setValueAtCoordinate(current->row, current->col, current->value
                                                               +
                                                               this->getValueAtCoordinate(current->row, current->col));
    }
    return true;
}

//Adds matrices together
bool ArrayMatrix::addMatrixRecursive(ArrayMatrix *matrix) {
    if (!this->additionCompatible(matrix)) {
        return false;
    }
    addMatrixRecursive(matrix, 0);
    return true;
}

//Adds matrices together
void ArrayMatrix::addMatrixRecursive(ArrayMatrix *matrix, int current) {
    if (current == matrix->arrayList->getNumElements()) {
        return;
    }
    MatrixElement currentElement = *matrix->arrayList->getMatrixElement(current);
    currentElement.value += this->getValueAtCoordinate(currentElement.row, currentElement.col);

    this->setValueAtCoordinate(currentElement.row, currentElement.col, currentElement.value);
    addMatrixRecursive(matrix, current + 1);
}

//Sorts Matrix
void ArrayMatrix::sortMatrix() {

    // simple insertion sort in ascending order
    int i, j;
    for (i = 1; i < this->arrayList->getNumElements(); i++) {
        MatrixElement currentElement = *this->arrayList->getMatrixElement(i);
        for (j = i - 1; j >= 0 && greaterThan(*this->arrayList->getMatrixElement(j), currentElement); j--) {
            this->arrayList->setMatrixElement(j + 1, this->arrayList->getMatrixElement(j));
        }
        this->arrayList->setMatrixElement(j + 1, &currentElement);
    }


}

void ArrayMatrix::cleanZeroes() {
    int i, j;
    for (i = 0; i < arrayList->getNumElements(); i++) {
        MatrixElement currentElement = *this->arrayList->getMatrixElement(i);
        if (currentElement.value == 0 && ((currentElement.row != rows) && (currentElement.col != cols))) {
            for (j = i; j < arrayList->getNumElements() - 1; j++) {
                currentElement = *this->arrayList->getMatrixElement(j + 1);
                this->arrayList->setMatrixElement(j, &currentElement);
            }
            arrayList->setNumOfElements(arrayList->getNumElements() - 1);
        }
    }
}

//Prints Matrix
void ArrayMatrix::printMatrix() {
    cout.setf(ios::fixed | ios::showpoint);
    cout.precision(2);
    cout << "#Matrix C=A*B" << endl;
    for (int i = 0; i < this->arrayList->getNumElements(); i++) {
        MatrixElement *current = this->arrayList->getMatrixElement(i);
        cout << current->row << " " << current->col << " " << current->value << endl;
    }
}

//Prints Matrix to file
void ArrayMatrix::printToFile(string filename) {
    ofstream ofs(filename.c_str());
    //ofs << "#Matrix C=A*B" << endl;
    ofs.setf(ios::fixed | ios::showpoint);
    ofs.precision(2);
    for (int i = 0; i < this->arrayList->getNumElements(); i++) {
        MatrixElement *current = this->arrayList->getMatrixElement(i);
        ofs << current->row << " " << current->col << " " << current->value << endl;
    }
}


double ArrayMatrix::binarySearch(int row, int col) {
    int max = this->arrayList->getNumElements() - 1;
    int min = 0;
    while (min <= max) {
        int mid = (max + min / 2);
        MatrixElement *current = this->arrayList->getMatrixElement(mid);
        if (current->row == row && current->col == col) {
            return current->value;
        } else if (row > current->row && col > current->col) {
            min = mid + 1;
        } else {
            max = mid - 1;
        }
    }
    return 0;
}

double ArrayMatrix::getValueAtCoordinate(int row, int col) {
    if (this->sorted) {
        return this->binarySearch(row, col);
    }
    for (int i = 0; i < this->arrayList->getNumElements(); i++) {
        MatrixElement *current = this->arrayList->getMatrixElement(i);
        if (current->row == row && current->col == col) {
            return current->value;
        }
    }
    return 0;
}

//Checks to see if Matrix is compatible for matrix multiplication
bool ArrayMatrix::multiplicationCompatible(ArrayMatrix *matrix) {
    return this->cols == matrix->rows;
}

ArrayMatrix *ArrayMatrix::matrixMultiplication(ArrayMatrix *matrix) {
    if (!this->multiplicationCompatible(matrix)) {
        return nullptr;
    }
    ArrayMatrix *matrixC = new ArrayMatrix();
    ArrayMatrix zeroMatrix = new ArrayMatrix();

    for (int i = 1; i <= this->rows; i++) {
        for (int j = 1; j <= matrix->cols; j++) {
            double sum = 0;
            for (int k = 1; k <= this->cols; k++) {
                sum += this->getValueAtCoordinate(i, k) * matrix->getValueAtCoordinate(k, j);
            }
            if (sum != 0) {
                matrixC->setValueAtCoordinate(i, j, sum);
            } else {
                zeroMatrix.setValueAtCoordinate(i, j, sum);
            }
        }
    }
    if ((zeroMatrix.rows >= matrixC->rows && zeroMatrix.cols >= matrixC->cols)) {
        matrixC->setValueAtCoordinate(zeroMatrix.rows, zeroMatrix.cols, 0);
    }

    return matrixC;
}


void ArrayMatrix::setValueAtCoordinate(int row, int col, double value) {
    //Update Max rows and cols

    this->rows = max(this->rows, row);
    this->cols = max(this->cols, col);
    for (int i = 0; i < this->arrayList->getNumElements(); i++) {
        MatrixElement *current = this->arrayList->getMatrixElement(i);
        if (current->row == row && current->col == col) {
            current->value = value;
            return;
        }
    }
    MatrixElement *newElement = new MatrixElement;
    newElement->row = row;
    newElement->col = col;
    newElement->value = value;

    if (sorted && ((row > this->lastRow) || (row >= this->lastRow && col > this->lastCol))) {
        sorted = true;
    } else {
        sorted = false;
    }
    if (row > this->lastRow) {
        this->lastRow = row;
        this->lastCol = col;
    } else if (row == this->lastRow && col > this->lastCol) {
        this->lastCol = col;
    }
    this->arrayList->addMatrixElement(newElement);
}

//Checks to see if matrix is sorted
bool ArrayMatrix::isMatrixSorted() {
    return sorted;
}
