#include <assert.h>
#include "Matrix.h"
#include <iostream>

using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	TElem old = m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);
	assert(old == 5);


	/*
		New operation: setDiagonal
	*/
	Matrix m2{ 4,4 };
	m.modify(1, 1, 4);
	m.modify(2, 2, 4);
	m.modify(3, 2, 2);
	m.modify(0, 3, 2);
	m.setDiagonal(5);
	for (int i = 0; i < m.nrLines(); ++i) {
		assert(m.element(i, i) == 5);
	}
	for (int i = 0; i < m.nrLines(); ++i) {
		for (int j = 0; j < m.nrColumns(); ++j) {
			cout << m.element(i, j) << " ";
		}
		cout << "\n";
	}

}