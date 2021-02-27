#include "SortedSet.h"
#include "SortedSetIterator.h"

#define INITIAL_SET_SIZE 5

///Search an element in an array. Return -1 if not found, otherwise the index of the element.
int BinarySearch(TComp* elements, int elementsSize, TComp elem, Relation r) {
	int low = 0, high = elementsSize - 1;

	while (low <= high) {
		int middle = (low + high) / 2;

		if (elements[middle] == elem) {
			return middle;
		}

		if (r(elem, elements[middle]) == false) {
			low = middle + 1;
		}
		else {
			high = middle - 1;
		}
	}

	return -1;
}

SortedSet::SortedSet(Relation r) {
	this->relation = r;
	this->capacity = INITIAL_SET_SIZE;
	this->count = 0;
	this->elements = new TComp[INITIAL_SET_SIZE];
}

bool SortedSet::add(TComp elem) {
	///Check if element is already in the set
	if (-1 != BinarySearch(this->elements, this->count, elem, this->relation)) {
		return false;
	}

	///Resize
	if (this->count >= this->capacity) {
		this->capacity *= 2;
		
		TComp* newArray = new TComp[this->capacity];
		
		for (int i = 0; i < this->count; ++i) {
			newArray[i] = this->elements[i];
		}

		delete[] this->elements;

		this->elements = newArray;
	}

	///Insert element into the set
	int index = this->count - 1;
	while (index >= 0 && false == this->relation(this->elements[index], elem)) {
		this->elements[index + 1] = this->elements[index];
		--index;
	}
	this->elements[index + 1] = elem;
	this->count += 1;

	return true;
}


bool SortedSet::remove(TComp elem) {
	int elemIndex = BinarySearch(this->elements, this->count, elem, this->relation);

	///Element not in teh set.
	if (-1 == elemIndex) {
		return false;
	}

	///Remove element.
	for (int i = elemIndex; i < this->count - 1; ++i) {
		this->elements[i] = this->elements[i + 1];
	}
	--this->count;

	return true;
}


bool SortedSet::search(TComp elem) const {
	return (-1 != BinarySearch(this->elements, this->count, elem, this->relation));
}


int SortedSet::size() const {
	return this->count; //this->capacity;
}


bool SortedSet::isEmpty() const {
	return (0 == this->count);
}

int SortedSet::getRange() const {
	if (this->count <= 0) {
		return -1;
	}
	return this->elements[this->count - 1] - this->elements[0];
}

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}


SortedSet::~SortedSet() {
	delete[] this->elements;
}


