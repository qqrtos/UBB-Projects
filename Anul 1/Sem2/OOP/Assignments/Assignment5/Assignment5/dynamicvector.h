#pragma once

template <typename TElem>
class DynamicVector {
private:
	TElem* elements;
	int size, count;

public:
	DynamicVector();

	DynamicVector(const DynamicVector& copyVector);

	int getCount() const;

	TElem* getMaterials() const;

	void add(TElem& element);

	void remove(TElem& element);

	void update(TElem& element, TElem& newElement);

	TElem& operator[](int index);

	~DynamicVector();

	friend void resize(DynamicVector& vector);
};

