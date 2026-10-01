
// Program name: Matrix Operations
// Description: Take input file specifing a matrix to perform specified operation
// Inputs: Filename
// Outputs: Completed Matrices
// Author: Francis Tryban
// Date: 2026-09-31
// Help received from: GPT-5 and the GCC compiler.


#include <iostream> // cin, cout
#include <fstream>  // ifstream for reading the input file
#include <vector>   // vector = resizable array, basically a python list
#include <iomanip>  // setw, for aligned columns
#include <string>
#include <algorithm> // max
#include <cctype>    // isspace


using namespace std; // so i can write cout instead of std::cout

// shorthand so i don't have to type vector<vector<long long>> everywhere
// long long holds way bigger numbers than int, so A * B won't overflow on big inputs
using Matrix = vector<vector<long long>>;

// reads an n x n matrix from the file
// file is passed by reference (&) so the read position carries over between calls
// returns false if the file runs out of numbers or has something that isn't an int
bool readMatrix(ifstream& file, int n, Matrix& matrix) {
    for (int i = 0; i < n; i++) {
        vector<long long> row;
        for (int j = 0; j < n; j++) {
            int value;
            // file >> value fails on letters, decimals like 3.7, numbers too big for int, or end of file
            if (!(file >> value)) {
                return false;
            }
            // reading an int stops at the '.' in 3.7, so check the next char isn't part of the same token
            int next = file.peek();
            if (next != EOF && !isspace(next)) {
                return false;
            }
            row.push_back(value); //  .append()
        }
        matrix.push_back(row);
   }
   return true;
}

// how many characters it takes to print x (counts the minus sign)
int numWidth(long long x) {
    return to_string(x).size();
}

//prints a matrix with aligned columns
// column width is 4 like the sample, but grows if a number is too wide to fit
void printMatrix(const Matrix& matrix) {
    int n = matrix.size();
    int width = 4;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            width = max(width, numWidth(matrix[i][j]) + 1); // +1 so numbers never touch
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(width) << matrix[i][j]; // setw pads the next value to width chars
        }
        cout << endl; //end row
    }

}

// adds A and B element by element and prints the result
void addMatrices(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<long long>(n, 0)); // n x n grid of zeros
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    printMatrix(C);
}

// multiplies A and B and prints the result
// each C[i][j] = row i of A dotted with column j of B
void multiplyMatrices(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j]; // walk across A's row and down B's column
            }
        }
    }
    printMatrix(C);
}

// prints the sum of the main diagonal (top left to bottom right)
// and the secondary diagonal (top right to bottom left)
void diagonalSums(const Matrix& matrix) {
    int n = matrix.size();
    long long mainSum = 0;
    long long secondarySum = 0;
    for (int i = 0; i < n; i++) {
        mainSum += matrix[i][i];             // row i, col i
        secondarySum += matrix[i][n - 1 - i]; // row i, col counting back from the right
    }
    cout << "Main diagonal sum: " << mainSum << endl;
    cout << "Secondary diagonal sum: " << secondarySum << endl;
}

// true if index is a valid row/col for an n x n matrix
bool inBounds(int index, int n) {
    return index >= 0 && index < n;
}

// matrix is passed by value (no &) so this swaps a copy and the original stays the same
void swapRows(Matrix matrix, int r1, int r2) {
    int n = matrix.size();
    if (!inBounds(r1, n) || !inBounds(r2, n)) {
        cout << "Error: row indices must be between 0 and " << n - 1 << "." << endl;
        return;
    }
    swap(matrix[r1], matrix[r2]); // swaps the whole row vectors at once
    cout << "Problem 5 - Rows " << r1 << " and " << r2 << " swapped:" << endl;
    printMatrix(matrix);
}

// same idea as swapRows but columns aren't their own vectors,
// so swap the two values in every row
void swapCols(Matrix matrix, int c1, int c2) {
    int n = matrix.size();
    if (!inBounds(c1, n) || !inBounds(c2, n)) {
        cout << "Error: column indices must be between 0 and " << n - 1 << "." << endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        swap(matrix[i][c1], matrix[i][c2]);
    }
    cout << "Problem 6 - Columns " << c1 << " and " << c2 << " swapped:" << endl;
    printMatrix(matrix);
}

// sets matrix[row][col] to value on a copy and prints it
void updateElement(Matrix matrix, int row, int col, long long value) {
    int n = matrix.size();
    if (!inBounds(row, n) || !inBounds(col, n)) {
        cout << "Error: row and column indices must be between 0 and " << n - 1 << "." << endl;
        return;
    }
    matrix[row][col] = value;
    cout << "Problem 7 - Updated matrix:" << endl;
    printMatrix(matrix);
}


int main() {
    string filename;
    cout << "Enter input filename: ";
    getline(cin, filename); // getline instead of cin >> so filenames with spaces work

    ifstream file(filename);
    if (!file) { // file is false if it didn't open
        cout << "Error opening file." << endl;
        return 1;
    }

    int n;
    // first number in the file is the size. fails if the file is empty or it's not a number
    if (!(file >> n)) {
        cout << "Error: first value in the file must be the matrix size N." << endl;
        return 1;
    }
    int next = file.peek();
    if (next != EOF && !isspace(next)) { // catches things like 4.5 or 4abc
        cout << "Error: matrix size N must be a whole number." << endl;
        return 1;
    }
    if (n <= 0) {
        cout << "Error: matrix size N must be a positive integer." << endl;
        return 1;
    }

    // A gets the first n*n numbers, B gets the next n*n
    // anything after that in the file is ignored
    Matrix A, B;
    if (!readMatrix(file, n, A) || !readMatrix(file, n, B)) {
        cout << "Error: file must contain two " << n << " x " << n
             << " matrices of integers." << endl;
        return 1;
    }

    cout << "Matrix A:" << endl;
    printMatrix(A);
    cout << endl;

    cout << "Matrix B:" << endl;
    printMatrix(B);
    cout << endl;

    cout << "A + B:" << endl;
    addMatrices(A, B);
    cout << endl;

    cout << "A * B:" << endl;
    multiplyMatrices(A, B);
    cout << endl;

    cout << "Diagonal sums for Matrix A:" << endl;
    diagonalSums(A);
    cout << endl;

    // 5-7 each get their own copy of A, so they all start from the original
    swapRows(A, 0, 2);
    cout << endl;

    swapCols(A, 0, 2);
    cout << endl;

    updateElement(A, 1, 2, 99);

    return 0;
}
