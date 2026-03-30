#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int SIZE = 4; // Global variable for matrix size

class Matrix {
private:
  int data[SIZE][SIZE];  // 2D array for matrix data (using int for simplicity)

public:
  // Constructor: zero-initialize all elements
  Matrix() {
    for (int i = 0; i < SIZE; i++)
      for (int j = 0; j < SIZE; j++)
        data[i][j] = 0;
  }

  // 1. Read values from a file into a matrix
  void readFromFile(ifstream& file) {
    for (int i = 0; i < SIZE; i++)
      for (int j = 0; j < SIZE; j++)
        file >> data[i][j];
  }

  // 2. Display a matrix
  void display() const {
    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        cout << setw(5) << data[i][j];
      }
      cout << endl;
    }
    cout << endl;
  }

  // 3. Add two matrices (operator overloading for +)
  Matrix operator+(const Matrix& other) const {
    Matrix result;
    for (int i = 0; i < SIZE; i++)
      for (int j = 0; j < SIZE; j++)
        result.data[i][j] = data[i][j] + other.data[i][j];
    return result;
  }

  // 4. Multiply two matrices (operator overloading for *)
  Matrix operator*(const Matrix& other) const {
    Matrix result;
    for (int i = 0; i < SIZE; i++)
      for (int j = 0; j < SIZE; j++)
        for (int k = 0; k < SIZE; k++)
          result.data[i][j] += data[i][k] * other.data[k][j];
    return result;
  }

  // 5. Compute the sum of matrix diagonal elements
  int sumOfDiagonals() const {
    int sum = 0;
    for (int i = 0; i < SIZE; i++) {
      sum += data[i][i];              // main diagonal
      sum += data[i][SIZE - 1 - i];  // secondary diagonal
    }
    // If SIZE is odd, center element is on both diagonals -- subtract once
    if (SIZE % 2 != 0)
      sum -= data[SIZE / 2][SIZE / 2];
    return sum;
  }

  // 6. Swap matrix rows
  void swapRows(int row1, int row2) {
    if (row1 < 0 || row1 >= SIZE || row2 < 0 || row2 >= SIZE) {
      cerr << "Error: row indices (" << row1 << ", " << row2 << ") out of range." << endl;
      return;
    }
    for (int j = 0; j < SIZE; j++) {
      int temp      = data[row1][j];
      data[row1][j] = data[row2][j];
      data[row2][j] = temp;
    }
  }
};

int main() {
  // Open the data file
  string filePath = "matrix-data.txt";
  ifstream file(filePath);
  if (!file.is_open()) {
    cerr << "Error: Failed to open file: " << filePath << endl;
    return 1;
  }

  // 1. Read both matrices from the file
  Matrix mat1, mat2;
  mat1.readFromFile(file);
  mat2.readFromFile(file);
  file.close();

  // 2. Display both matrices
  cout << "Matrix 1:" << endl;
  mat1.display();
  cout << endl;

  cout << "Matrix 2:" << endl;
  mat2.display();
  cout << endl;

  // 3. Add and display
  Matrix sum = mat1 + mat2;
  cout << "Sum of matrices:" << endl;
  sum.display();
  cout << endl;

  // 4. Multiply and display
  Matrix product = mat1 * mat2;
  cout << "Product of matrices:" << endl;
  product.display();
  cout << endl;

  // 5. Diagonal sum
  cout << "Sum of diagonals of Matrix 1: " << mat1.sumOfDiagonals() << endl;
  cout << endl;

  // 6. Swap rows and display
  mat1.swapRows(0, 2);
  cout << "Matrix 1 after swapping rows:" << endl;
  mat1.display();

  return 0;
}