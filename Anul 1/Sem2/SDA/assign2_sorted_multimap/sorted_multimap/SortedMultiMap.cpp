#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include "ValueIterator.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) :
	relation{r},
	count{0},
	head{NULL}
{}

/*
Add function complexity: 
	Best case - Theta(1) adding at the beginning of the DLL.
	Worst case - Theta(n) adding at the end of the DLL
	Total - O(n)
*/
void SortedMultiMap::add(TKey c, TValue v) {
	NODE* current = this->head;

	NODE* toBeAdded = new NODE();
	toBeAdded->value.first = c;
	toBeAdded->value.second = v;
	toBeAdded->next = NULL;
	toBeAdded->previous = NULL;

	if (this->count == 0) {
		//Add the node to an empty list.
		this->head = toBeAdded;
	}
	else if (this->relation(this->head->value.first, c) == false) {
		//Add node at the beginning.
		toBeAdded->next = this->head;
		toBeAdded->next->previous = toBeAdded;
		this->head = toBeAdded;
	}
	else {
		//Add node somewhere else.
		while (current->next != NULL and this->relation(current->next->value.first, c) == true) {
			current = current->next;
		}

		toBeAdded->next = current->next;

		//the node is not inserted at the end
		if (current->next != NULL)
			toBeAdded->next->previous = toBeAdded;

		current->next = toBeAdded;
		toBeAdded->previous = current;
	}

	++this->count;
}

/*
Search function complexity:
	Best case = worst case = total - Theta(n) because we always go through the entire list
*/
vector<TValue> SortedMultiMap::search(TKey c) const {
	vector<TValue> found;
	NODE* current = this->head;

	while (NULL != current) {
		if (current->value.first == c) {
			found.push_back(current->value.second);
		}
		current = current->next;
	}

	return found;
}

//vector<TValue> SortedMultiMap::search(TKey c) const {
//	vector<TValue> found;
//
//	ValueIterator itv = this->valueIterator(c);
//	itv.first();
//
//	while (itv.valid()) {
//		found.push_back(itv.getCurrent());
//		itv.next();
//	}
//
//	return found;
//}

/*
Remove function complexity:
	Best case - Theta(1) the element we need to remove is the first one.
	Worst case - Theta(n) the element is the last in the list.
	Total - O(n)
*/
bool SortedMultiMap::remove(TKey c, TValue v) {
	NODE* current = this->head;

	while (NULL != current) {
		if (current->value.first == c and current->value.second == v) {
			if (NULL == current->previous and NULL == current->next) {
				//Only node in the list.
				delete current;
				this->count = 0;
				this->head = NULL;
				return true;
			}
			else if (NULL == current->previous) {
				//First node removed.
				NODE** intermediary = &this->head;
				*intermediary = (*intermediary)->next;
				(*intermediary)->previous = NULL;
			}
			else if (current->next == NULL) {
				//Last node removed.
				current->previous->next = NULL;
			}
			else {
				//Node from the middle removed.
				current->previous->next = current->next;
				current->next->previous = current->previous;
			}

			--this->count;
			delete current;
			return true;
		}

		current = current->next;
	}

	return false;
}

//Complexity: Theta(1)
int SortedMultiMap::size() const {
	return this->count;
}

//Complexity: Theta(1)
bool SortedMultiMap::isEmpty() const {
	return (this->count == 0);
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

ValueIterator SortedMultiMap::valueIterator(TKey k) const {
	return ValueIterator(*this, k);
}

SortedMultiMap::~SortedMultiMap() {
	NODE* current = this->head;

	while (NULL != current) {
		NODE* intermediary = current;
		current = current->next;
		delete intermediary;
	}
}
