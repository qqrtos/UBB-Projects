#include <assert.h>

#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include "ValueIterator.h"
#include <exception>
#include <vector>

using namespace std;

bool relation1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll() {
	SortedMultiMap smm = SortedMultiMap(relation1);
	assert(smm.size() == 0);
	assert(smm.isEmpty());
	smm.add(1, 2);
	smm.add(1, 3);
	assert(smm.size() == 2);
	assert(!smm.isEmpty());
	vector<TValue> v = smm.search(1);
	assert(v.size() == 2);
	v = smm.search(3);
	assert(v.size() == 0);
	SMMIterator it = smm.iterator();
	it.first();
	while (it.valid()) {
		TElem e = it.getCurrent();
		it.next();
	}
	assert(smm.remove(1, 2) == true);
	assert(smm.remove(1, 3) == true);
	assert(smm.remove(2, 1) == false);
	assert(smm.isEmpty());


	/*
	Tests for ValueIterator.
	*/
	int i = 0;
	smm.add(1, 2);
	smm.add(1, 0);
	smm.add(1, 2);
	smm.add(1, 0);
	smm.add(4, 5);
	smm.add(5, 5);

	ValueIterator itv = smm.valueIterator(1);
	itv.first();

	while (itv.valid()) {
		TValue currentVal = itv.getCurrent();

		if (i % 2 == 0) {
			assert(currentVal == 2);
		}
		else {
			assert(currentVal == 0);
		}
		
		++i;
		itv.next();
	}
}

