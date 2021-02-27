#include "Map.h"
#include "MapIterator.h"


//Theta(1)
int Map::hash(TKey key) const {
	if (key < 0)key *= -1;
	return key % this->m;
}

//Theta(1)
int Map::hash_quadraticprobbing(TKey key, int i) const {
	int h = this->hash(key) + (0.5f * i) + (0.5f * i * i);
	return h % this->m;
}

/*
	Complexity:
		-best case: Theta(m)
		-worst case: Theta(m*n)
		-total: O(m*n)
*/
void Map::resize() {
	this->m *= 2;
	Entry* newElements = new Entry[this->m]{};

	for (int i = 0; i < this->m / 2; ++i) {
		Entry currentEntry = this->elements[i];
		
		if (currentEntry.isDeleted == true or currentEntry.entry == NULL_TELEM)
			continue;

		int j = 0;
		int h = this->hash_quadraticprobbing(currentEntry.entry.first, j);
		
		while (newElements[h].entry != NULL_TELEM) {
			h = this->hash_quadraticprobbing(currentEntry.entry.first, ++j);
		}

		newElements[h] = Entry{ currentEntry.entry,false };
	}

	delete[] this->elements;
	this->elements = newElements;
}


Map::Map() :
	n{ 0 },
	m{ INITIAL_CAPACITY },
	alpha{ 0 }
{
	this->elements = new Entry[INITIAL_CAPACITY]{};
}

/*
	Complexity:
		-best case: Theta(1) when the position returned by the hash function has no other element
		-worst case: Theta(n) when all the values are hashed to the same function
		-total: O(n)
*/
TValue Map::add(TKey c, TValue v) {
	if (this->alpha >= 0.65) { //arbitrarily chosen by me
		this->resize();
	}

	int h = this->hash_quadraticprobbing(c, 0);
	Entry newEntry = Entry{ std::pair<TKey, TValue>(c, v),false };

	if (this->elements[h].entry == NULL_TELEM or this->elements[h].isDeleted == true) { //Entry point for (c,v) is empty.
		this->elements[h] = newEntry;
		++this->n;
		this->alpha = float(this->n) / float(this->m);
		return NULL_TVALUE;
	}

	TValue oldValue;
	int i = 0;
	h = hash_quadraticprobbing(c, i);

	while (this->elements[h].entry != NULL_TELEM) {
		if (this->elements[h].isDeleted == true) { //Element is deleted => replace it.
			oldValue = NULL_TVALUE;
			this->elements[h] = newEntry;
			++this->n;
			this->alpha = float(this->n) / float(this->m);
			return oldValue;
		}
		else if (this->elements[h].entry.first == newEntry.entry.first) { //Element with given key found.
			oldValue = this->elements[h].entry.second;
			this->elements[h].entry.second = newEntry.entry.second;
			return oldValue;
		}

		h = hash_quadraticprobbing(c, ++i); //Go to the next element.
	}

	//Empty slot found => add element.
	oldValue = this->elements[h].entry.second;
	this->elements[h] = newEntry;
	++this->n;

	this->alpha = float(this->n) / float(this->m);

	return oldValue;
}

/*
	Complexity:
		-best case: Theta(1)
		-worst case: Theta(n)
		-total: O(n)
*/
TValue Map::search(TKey c) const {
	int i = 0;
	int position = this->hash_quadraticprobbing(c, i);

	while (this->elements[position].entry != NULL_TELEM and this->elements[position].isDeleted != true) {
		if (this->elements[position].entry.first == c) { //Element with given key found.
			return this->elements[position].entry.second;
		}

		position = hash_quadraticprobbing(c, ++i); //Get next position.
	}

	return NULL_TVALUE; //Not found.
}

/*
	Complexity:
		-best case: Theta(1)
		-worst case: Theta(n)
		-total: O(n)
*/
TValue Map::remove(TKey c) {
	int i = 0;
	int position = this->hash_quadraticprobbing(c, i);

	while (this->elements[position].entry != NULL_TELEM) {
		if (this->elements[position].entry.first == c and this->elements[position].isDeleted == false) { //Element with given key found.
			this->elements[position].isDeleted = true;
			--this->n;
			this->alpha = float(this->n) / float(this->m);
			return this->elements[position].entry.second;
		}

		position = hash_quadraticprobbing(c, ++i); //Get next position.
	}

	return NULL_TVALUE; //Inexistent key
}

//Theta(1)
int Map::size() const {
	return this->n;
}

//Theta(1)
bool Map::isEmpty() const {
	return this->n == 0;
}

//Theta(m)
void Map::filter(Condition cond) {
	int position = 0;

	while (position < this->m) {
		if (this->elements[position].isDeleted == false and cond(this->elements[position].entry.first)) {
			this->elements[position].isDeleted = true;
			--this->n;
			this->alpha = float(this->n) / float(this->m);
		}
		++position;
	}
}

MapIterator Map::iterator() const {
	return MapIterator(*this);
}

Map::~Map() {
	delete[] this->elements;
}