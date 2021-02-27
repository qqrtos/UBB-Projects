#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -11111
#define NULL_TELEM pair<TKey, TValue>(-11111, -11111);
using namespace std;
class SMMIterator;
class ValueIterator;
typedef bool(*Relation)(TKey, TValue);

typedef struct _NODE{
	TElem value;
	_NODE* next;
	_NODE* previous;
}NODE;

class SortedMultiMap {
	friend class SMMIterator;
	friend class ValueIterator;
private:
	Relation relation;
	NODE* head;
	int count;

public:
	// constructor
	SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
	void add(TKey c, TValue v);

	//returns the values belonging to a given key
	vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
	bool remove(TKey c, TValue v);

	//returns the number of key-value pairs from the sorted multimap
	int size() const;

	//verifies if the sorted multi map is empty
	bool isEmpty() const;

	// returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
	SMMIterator iterator() const;

	ValueIterator valueIterator(TKey k) const;

	// destructor
	~SortedMultiMap();
};
