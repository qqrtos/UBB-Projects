#include "dynamicvector.h"
#include <exception>
#define INITIAL_VECTOR_SIZE 1

template <typename TElem>
void resize(DynamicVector<TElem>& vector) {
	TElem* moreMaterials = new TElem[2 * vector.size];

	for (int i = 0; i < vector.count; ++i) {
		moreMaterials[i] = vector.elements[i];
	}

	vector.size *= 2;
	delete[] vector.elements;
	vector.elements = moreMaterials;
}

template <typename TElem>
DynamicVector<TElem>::DynamicVector() {
	this->elements = new TElem[INITIAL_VECTOR_SIZE];
	this->size = INITIAL_VECTOR_SIZE;
	this->count = 0;
}

template <typename TElem>
DynamicVector<TElem>::DynamicVector(const DynamicVector<TElem>& copyVector) {
}

template <typename TElem>
int DynamicVector<TElem>::getCount() const {
	return this->count;
}

template <typename TElem>
TElem* DynamicVector<TElem>::getMaterials() const {
	return this->elements;
}

template <typename TElem>
void DynamicVector<TElem>::add(TElem& element) {
	if (this->count >= this->size - 1) {
		resize(*this);
	}

	this->elements[this->count++] = element;
}

template<typename TElem>
void DynamicVector<TElem>::remove(TElem& element) {
	for (int i = 0; i < this->count; ++i) {
		if (this->elements[i] == element) {
			for (int j = i; j < this->count - 1; ++j) {
				this->elements[j] = this->elements[j + 1];
			}
			--this->count;
			return;
		}
	}
	throw std::exception("Element not found.");
}

template<typename TElem>
void DynamicVector<TElem>::update(TElem& element, TElem& newElement) {
	for (int i = 0; i < this->count; ++i) {
		if (this->elements[i] == element) {
			this->elements[i] = newElement;
			return;
		}
	}
	throw std::exception("Element not found.");
}

template<typename TElem>
TElem& DynamicVector<TElem>::operator[](int index) {
	if (0 >= index or index>=this->count) {
		throw std::exception("Index out of bound.");
	}

	return this->elements[index];
}

template <typename TElem>
DynamicVector<TElem>::~DynamicVector() {
	delete[] this-> elements;
}
