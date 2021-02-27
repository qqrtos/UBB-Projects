#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

#include <tuple>
#define INITIAL_CAPACITY 2

struct Entry {
	int line, col;
	TElem value;
	Entry() = default;
	Entry(int line, int col, TElem val) : line{ line }, col{ col }, value{ val } {}
	bool operator==(Entry other) { return (line == other.line and col == other.col); }
};

class Matrix {
private:
	int cols, lines;
	Entry* elements;
	int* next;
	int head, firstEmpty;
	int size;

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	void setDiagonal(TElem elem);

	~Matrix();

private:
	bool isValidPosition(int line, int col) const;

	std::tuple<int, int> getInsertionPosition(int line, int col) const;

	void resizeLists();
};
