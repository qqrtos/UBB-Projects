#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m) {
	this->index = 0;
}


void SortedSetIterator::first() {
	this->index = 0;
}


void SortedSetIterator::next() {
	if (this->valid()) {
		this->index += 1;
	}
	else {
		throw exception();
	}
}


TComp SortedSetIterator::getCurrent()
{
	if (this->valid()) {
		return this->multime.elements[this->index];
	}
	else {
		throw exception();
	}
}

bool SortedSetIterator::valid() const {
	return this->index < this->multime.count;
}

