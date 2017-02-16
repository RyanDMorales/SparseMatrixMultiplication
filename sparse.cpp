//
// Created by Ryan Morales on 9/23/16.
//

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#include "ArrayMatrix.h"
#include "LinkedListMatrix.h"
#include "ArgumentManager.h"

int main(int argc, char *argv[]) {

//    ArgumentManager am(argc, argv);
//    string op = am.get("operation");
//    string str = am.get("storage");
//    string rec = am.get("recursive");
//    string inputA = am.get("A");
//    string inputB = am.get("B");
//    string output = am.get("result");
//    string sort = am.get("sort");

    string inputA = "a1.txt";
    string inputB = "b1.txt";
    string output = "1.out";
    //string str = "array";
    string str = "linkedlist";
    //string op = "add";
    string op = "multiply";
    //string rec = "Yes";
    string rec = "NO";
    //string sort = "nsquared";
    string sort = "nlogn";

    ofstream ofs(output);
    if (op == "multiply") {
        ArrayMatrix *matrixA = new ArrayMatrix(inputA, output);
        ArrayMatrix *matrixB = new ArrayMatrix(inputB, output);
        if (sort == "nsquared") {
            ofstream outStream;
            outStream.open("bigO.txt", ios::app);
            outStream << "algorithm" << " " << setw(COLUMN_WIDTH) << "#entries(n)" << " " << setw(COLUMN_WIDTH)
                      << "countComparisons" << " "
                      << setw(COLUMN_WIDTH) << "bigOcountComparisons" << endl;
            outStream.close();

            matrixA->sortMatrix();

            matrixB->sortMatrix();


        } else if (sort == "nlogn") {
            ofstream outStream;
            outStream.open("bigO.txt", ios::app);
            outStream << "algorithm" << " " << setw(COLUMN_WIDTH) << "#entries(n)" << " " << setw(COLUMN_WIDTH)
                      << "countComparisons" << " "
                      << setw(COLUMN_WIDTH) << "bigOcountComparisons" << endl;
            outStream.close();

            matrixA->nlogn();
            //matrixA->printMatrix();

            matrixB->nlogn();
            //matrixB->printMatrix();



        } else {
            ofstream outStream;
            outStream.open("bigO.txt", ios::app);
            outStream << "algorithm" << " " << setw(COLUMN_WIDTH) << "#entries(n)" << " " << setw(COLUMN_WIDTH)
                      << "countComparisons" << " "
                      << setw(COLUMN_WIDTH) << "bigOcountComparisons" << endl;
            outStream.close();
            matrixA->nlogn();
            matrixB->nlogn();

        }

        ArrayMatrix *matrixC = (matrixA->matrixMultiplication(matrixB));
        if (matrixC != nullptr) {
            matrixC->printMatrix();
            matrixC->printToFile(output);
        } else {

            ofs.close();
            //cout << "Not Matrix Multiplication Compatible" << endl;
            return 0;
        }
//        if (matrixA->isMatrixSorted()) {
//            cout << "matrixA is sorted" << endl;
//        } else cout << "matrixA is not sorted" << endl;
//
//        if (matrixB->isMatrixSorted()) {
//            cout << "matrixB is sorted" << endl;
//        } else cout << "matrixB is not sorted" << endl;
    }

//    bool recursive = rec.length() > 0 && rec[0] == 'Y';
//
//    if(str == "array") {
//        ArrayMatrix *matrixA = new ArrayMatrix(inputA, output);
//        ArrayMatrix *matrixB = new ArrayMatrix(inputB, output);
//        ArrayMatrix *matrixC = new ArrayMatrix(matrixA);
//        switch (op[0]) {
//            case 'a':
//                if (recursive) {
//                    if(matrixC->addMatrixRecursive(matrixB)){
//                        matrixC->cleanZeroes();
//                        matrixC->cleanZeroes();
//                        matrixC->sortMatrix();
//                        matrixC->printToFile(output);
//                        matrixC->printMatrix();
//                        //cout<<"R"<<endl;
//                        break;
//                    }
//                    cout<<"Matrix addition not possible!"<<endl;break;}
//                else
//                if(matrixC->addMatrix(matrixB)) {
//                    matrixC->cleanZeroes();
//                    matrixC->cleanZeroes();
//                    matrixC->sortMatrix();
//                    matrixC->printToFile(output);
//                    matrixC->printMatrix();
//                    //cout << "NR" << endl;
//                    break;
//                } else {cout<<"Matrix addition not possible!"<<endl;break;}
//
//            default:break;
//        }
//    }
//    else{
//        LinkedListMatrix *matrixA = new LinkedListMatrix(inputA);
//        LinkedListMatrix *matrixB = new LinkedListMatrix(inputB);
//        LinkedListMatrix *matrixC = new LinkedListMatrix(matrixA);
//
//        switch (op[0]) {
//            case 'a':
//                if (recursive) {
//                    if(matrixC->addMatrixRecursive(matrixB)){
//                        matrixC->cleanZeroes();
//                        matrixC->cleanZeroes();
//                        matrixC->sortMatrix();
//                        matrixC->printToFile(output);
//                        matrixC->printMatrix();
//                        //cout<<"R"<<endl;
//                        break;
//                    }
//                    cout<<"Matrix addition not possible!"<<endl;break;}
//                else
//                if(matrixC->addMatrix(matrixB)) {
//                    matrixC->cleanZeroes();
//                    matrixC->cleanZeroes();
//                    matrixC->sortMatrix();
//                    matrixC->printToFile(output);
//                    matrixC->printMatrix();
//                    //cout << "NR" << endl;
//                    break;
//                } else {cout<<"Matrix addition not possible!"<<endl;break;}
//
//            default:break;
//        }
//    }

    return 0;
}
