#pragma once
#define INITIAL_VECTOR_SIZE 1
#include <exception>


template <typename TElem>
class DynamicVector {
private:
	TElem* elements;
	int size, count;
	int index;

public:
	DynamicVector();

	DynamicVector(const DynamicVector<TElem>& copyVector);

	///Return the number of elements in the vector.
	int getCount() const;

	///Add an element to the end of the vector.
	void append(TElem element);

	///Remove the first occurence of a given element.
	void remove(const TElem& element);

	TElem& operator[](const int index) const;

	~DynamicVector();

private:
	void resize();

public:
	class Iterator {
	private:
		TElem* currentElement;
	public:
		Iterator(TElem* initialElement);

		Iterator operator++();

		bool operator!=(const Iterator otherIterator) const;

		bool operator==(const Iterator otherIterator) const;

		TElem& operator*() const;
	};

	Iterator begin() const;

	Iterator end() const;
};

template <typename TElem>
void DynamicVector<TElem>::resize() {
	TElem* newElements = new TElem[2 * this->size];

	for (int i = 0; i < this->count; ++i) {
		newElements[i] = this->elements[i];
	}

	delete[] this->elements;

	this->elements = newElements;
	this->size *= 2;
}

template<typename TElem>
DynamicVector<TElem>::DynamicVector() {
	this->size = INITIAL_VECTOR_SIZE;
	this->elements = new TElem[this->size];
	this->count = 0;
}

template<typename TElem>
inline DynamicVector<TElem>::DynamicVector(const DynamicVector<TElem>& copyVector) {
	TElem* copyOfElements = new TElem[copyVector.size];

	for (int i = 0; i < copyVector.count; ++i) {
		copyOfElements[i] = copyVector.elements[i];
	}

	//delete[] this->elements;

	this->count = copyVector.count;
	this->size = copyVector.size;
	this->elements = copyOfElements;
}

template<typename TElem>
inline int DynamicVector<TElem>::getCount() const {
	return this->count;
}

template<typename TElem>
void DynamicVector<TElem>::append(TElem element) {
	if (this->count >= this->size) {
		this->resize();
	}

	this->elements[this->count++] = element;
}

template<typename TElem>
inline void DynamicVector<TElem>::remove(const TElem& element) {
	for (int i = 0; i < this->count; ++i) {
		if (this->elements[i] == element) {
			for (int j = i; j < this->count - 1; ++j) {
				this->elements[j] = this->elements[j + 1];
			}
			--this->count;
			return;
		}
	}
	throw std::exception("[Removal Error] Element not found.");
}

template<typename TElem>
inline TElem& DynamicVector<TElem>::operator[](const int index) const {
	if (index < 0 or index >= this->count) {
		throw std::exception("Index out of bound.");
	}

	return this->elements[index];
}

template<typename TElem>
DynamicVector<TElem>::~DynamicVector() {
	delete[] this->elements;
}

template<typename TElem>
inline DynamicVector<TElem>::Iterator::Iterator(TElem* initialElement) {
	this->currentElement = initialElement;
}

template<typename TElem>
inline typename DynamicVector<TElem>::Iterator DynamicVector<TElem>::Iterator::operator++() {
	this->currentElement += 1;
	return *this;
}

template<typename TElem>
inline typename bool DynamicVector<TElem>::Iterator::operator!=(const Iterator otherIterator) const {
	return this->currentElement != otherIterator.currentElement;
}

template<typename TElem>
inline typename bool DynamicVector<TElem>::Iterator::operator==(const Iterator otherIterator) const {
	return this->currentElement == otherIterator.currentElement;
}

template<typename TElem>
inline typename TElem& DynamicVector<TElem>::Iterator::operator*() const {
	return *this->currentElement;
}

template<typename TElem>
inline typename DynamicVector<TElem>::Iterator DynamicVector<TElem>::begin() const {
	return Iterator(this->elements);
}

template<typename TElem>
inline typename DynamicVector<TElem>::Iterator DynamicVector<TElem>::end() const {
	return Iterator(this->elements + this->count);
}