#include "Matrix.h"
#include <exception>

using namespace std;

//Theta(1)
bool Matrix::isValidPosition(int line, int col) const {
	return not(line < 0 or line >= this->lines or col < 0 or col >= this->cols);
}


/*
	Complexity:
		-best case: Theta(1) when element is smaller than the first in the list
		-worst case: Theta(n) element needs to be inserted after the last
		-total: O(n)
*/
std::tuple<int, int> Matrix::getInsertionPosition(int line, int col) const {
	/**
		Returns a pair representing the index in list at which the element needs to be inserted and it's position in the elements array.
	**/
	int prevposition = -1;
	int position = this->head;
	int indexInList = 0;

	while (position != -1 and line > this->elements[position].line) {
		prevposition = position;
		position = this->next[position];
		indexInList += 1;
	}
	while (position != -1 and line == this->elements[position].line and col >= this->elements[position].col) {
		prevposition = position;
		position = this->next[position];
		indexInList += 1;
	}

	return std::make_tuple(indexInList, prevposition);
}


/*
	Complexity:
		-worst case = best case = total complexity: Theta(m)
*/
void Matrix::resizeLists() {
	//Resize the elements list.
	Entry* newElements = new Entry[this->size * 2];
	int* newNext = new int[this->size * 2];

	for (int i = 0; i < this->size; ++i) {
		newElements[i] = this->elements[i];
		newNext[i] = this->next[i];
	}
	for (int i = this->size; i < 2 * this->size - 1; ++i) {
		newNext[i] = i + 1;
	}

	newNext[2 * this->size - 1] = -1;
	this->firstEmpty = this->size;
	delete[] this->elements;
	delete[] this->next;
	this->next = newNext;
	this->elements = newElements;
	this->size *= 2;
}


Matrix::Matrix(int nrLines, int nrCols) :
	cols{ nrCols },
	lines{ nrLines },
	firstEmpty{ 0 },
	head{ -1 }
{
	this->size = INITIAL_CAPACITY;
	this->elements = new Entry[INITIAL_CAPACITY];
	this->next = new int[INITIAL_CAPACITY];

	for (int i = 0; i < INITIAL_CAPACITY - 1; ++i) {
		this->next[i] = i + 1;
	}
	this->next[INITIAL_CAPACITY - 1] = -1;
}


//Theta(1)
int Matrix::nrLines() const {
	return this->lines;
}


//Theta(1)
int Matrix::nrColumns() const {
	return this->cols;
}


/*
	Complexity:
		-best case: Theta(1) when element is the head of the list
		-worst case: Theta(n) when element is the last in the list.
		-total: O(n)
*/
TElem Matrix::element(int i, int j) const {
	///Get the element from position (i,j).
	if (not this->isValidPosition(i, j)) {
		throw std::exception("Index out of bound.");
	}

	int current = this->head;
	while (current != -1 and \
		(this->elements[current].line < i or \
			(this->elements[current].line == i and this->elements[current].col < j))) {
		current = this->next[current];
	}

	if (this->elements[current].line == i and this->elements[current].col == j)
		return this->elements[current].value;
	return NULL_TELEM;
}


/*
	Complexity:
		-best case: Theta(1)
		-worst case: Theta(n)
		-total: O(n)
*/
TElem Matrix::modify(int i, int j, TElem e) {
	///Modify the element at position (i,j) in the matrix.
	if (not this->isValidPosition(i, j))
		throw std::exception{ "Position out of bounds." };

	if (this->firstEmpty == -1)
		this->resizeLists();

	TElem previousElement;
	std::tuple<int, int> indices = this->getInsertionPosition(i, j);
	int indexInList = std::get<0>(indices);
	int previousInArray = std::get<1>(indices);
	Entry newEntry{ i,j,e };

	if (previousInArray == -1 and this->elements[this->head] == newEntry) { //Element is already in matrix and is the first => change value
		previousElement = this->elements[this->head].value;
		this->elements[this->head] = newEntry;
	}
	else if (previousInArray != -1 and this->elements[previousInArray] == newEntry) { //Element is already in the array => change it's value.
		previousElement = this->elements[previousInArray].value;
		this->elements[previousInArray].value = newEntry.value;
	}
	else if (indexInList == 0) { //Insert first element in the list.
		int newPosition = this->firstEmpty;
		previousElement = this->elements[this->head].value;
		this->elements[newPosition] = newEntry;
		this->firstEmpty = this->next[this->firstEmpty];
		this->next[newPosition] = this->head;
		this->head = newPosition;
	}
	else {
		int newPosition = this->firstEmpty;
		previousElement = this->elements[previousInArray].value;
		this->firstEmpty = this->next[this->firstEmpty];
		this->elements[newPosition] = newEntry;
		this->next[newPosition] = this->next[previousInArray];
		this->next[previousInArray] = newPosition;

	}

	return previousElement;
}

void Matrix::setDiagonal(TElem elem) {
	if (this->cols != this->lines) {
		throw std::exception("Matrix isn't square!.");
	}

	for (int i = 0; i < this->lines; ++i) {
		this->modify(i, i, elem);
	}
}

Matrix::~Matrix() {
	delete[] this->elements;
	delete[] this->next;
}
