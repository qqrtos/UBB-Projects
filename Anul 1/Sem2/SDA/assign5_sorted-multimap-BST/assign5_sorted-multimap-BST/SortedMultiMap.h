#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);

typedef struct _NODE{
    _NODE* left;
    _NODE* right;
    TKey key;
    vector<TValue> values;

    _NODE(TKey k, TValue v) : left{ NULL }, right{ NULL }, key{ k }, values{ vector<TValue>(1, v) } {}
}Node;

class SortedMultiMap {
	friend class SMMIterator;
private:
    Relation relation;
    Node* root;
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

    //replaces the value currently mapped to a key k, with value newValue, only if the current value is equal to oldValue.
    //if the current value is not oldValue, or if k is not in the sortedmap, nothing is changes.
    void replace(TKey k, TValue oldValue, TValue newValue);

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();

private:
    Node* insertNode(Node* insertFrom, TElem data);

    vector<TValue> getValues(Node* current, TKey k) const;

    Node* deleteNode(Node* current, TKey k, vector<TValue> v, bool& wasDeleted);

    void deleteBST(Node* current);

    void replaceValueRecursive(Node* current, TKey k, TValue oldValue, TValue newValue);
};
