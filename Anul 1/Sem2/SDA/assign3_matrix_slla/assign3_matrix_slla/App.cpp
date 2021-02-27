#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"

/*
ADT Matrix

//sets all the values from the main diagonal to the value elem.
//throws an exception if it is not a square matrix.
void setMainDiagonal(TElem elem);
*/

using namespace std;

int main() {
	testAll();
	testAllExtended();
	cout << "Test End" << endl;
	system("pause");
}