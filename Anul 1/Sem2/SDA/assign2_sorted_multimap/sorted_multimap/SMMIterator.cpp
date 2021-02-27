#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d) {
	//TODO - Implementation
	this->current = this->map.head;
}

void SMMIterator::first() {
	//TODO - Implementation
	this->current = this->map.head;
}

void SMMIterator::next() {
	//TODO - Implementation
	if (NULL == this->current) {
		throw std::exception("Invalid iterator.");
	}
	this->current = this->current->next;
}

bool SMMIterator::valid() const {
	//TODO - Implementation
	return this->current != NULL;
}

TElem SMMIterator::getCurrent() const {
	//TODO - Implementation
	if (NULL == this->current) {
		throw std::exception("Invalid iterator.");
	}
	return this->current->value;
}