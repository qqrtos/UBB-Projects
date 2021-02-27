#include "ValueIterator.h"


ValueIterator::ValueIterator(const SortedMultiMap& map, const TKey k) :
	map{ map },
	key{ k }
{
	this->current = NULL;
}

/*
Complexities:
	Best case - Theta(1)
	Worst case - Theta(n)
	Total - O(n)
*/
void ValueIterator::first() {
	NODE* currentNode = this->map.head;

	while (NULL != currentNode) {
		if (currentNode->value.first == this->key) {
			this->current = currentNode;
			return;
		}
	}

	this->current = NULL;
}

void ValueIterator::next() {
	if (false == this->valid()) {
		throw std::exception("Invalid iterator.");
	}

	this->current = this->current->next;
}

bool ValueIterator::valid() const {
	return (NULL != this->current) and (this->current->value.first == this->key);
}

TValue ValueIterator::getCurrent() const {
	if (false == this->valid()) {
		throw std::exception("Invalid iterator.");
	}
	return this->current->value.second;
}
