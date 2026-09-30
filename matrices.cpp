#include <iostream>
#include <fstream> //reading input files
#include <vector>
#include <iomanip> // setw, for aligned columns
#include <string>


using namespace std;

vector<vector<int>> readMatrix(ifstream& file, int n) {
    <vector<vector<int>> matrix;
    for (int i = 0; i < n; i++) {
        vector<int> row;
        for (int j = 0; i < n; j++) {
            int value;
            row.push_back(value);
        }
        matrix.push_back();
   }
   return matrix;
}

//prints a matrix with each number in a 4 wide column
void printMatrix(vector<vector<int>> matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(4) << matrix[i][j]
        }

    }
    cout << endl; //end row
}


int main() {
    string filename;
    cout << "Enter input filename: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cout << "Error opening file." << endl;
        return 1;
    }

    int n;
    file >> n;

    vector<vector<int>> A = readMatrix(file, n);
    vector<vector<int>> B = readMatrix(file, n);

    cout << "Matrix A:" << endl;
    printMatrix(A);
    cout << endl;

    cout << "Matrix B:" << endl;
    printMatrix(B);
    cout << endl;

    return 0;
}