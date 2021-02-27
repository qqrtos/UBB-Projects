#include <assert.h>

#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <exception>
#include <vector>
#include <iostream>

using namespace std;

bool relation1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedMultiMap smm = SortedMultiMap(relation1);
	assert(smm.size() == 0);
	assert(smm.isEmpty());
    smm.add(1,2);
    smm.add(1,3);
    assert(smm.size() == 2);
    assert(!smm.isEmpty());
    vector<TValue> v= smm.search(1);
    assert(v.size()==2);
    v= smm.search(3);
    assert(v.size()==0);
    SMMIterator it = smm.iterator();
    it.first();
    while (it.valid()){
    	TElem e = it.getCurrent();
    	it.next();
    }
    assert(smm.remove(1, 2) == true);
    assert(smm.remove(1, 3) == true);
    assert(smm.remove(2, 1) == false);
    assert(smm.isEmpty());

    /*
        -Replace- tests.
    */
    std::cout << "Replace tests:\n";
    SortedMultiMap smm2{relation1};
    smm2.add(2, 1);
    smm2.add(2, 9);
    smm2.add(1, 3);
    smm2.add(1, 7);


    smm2.replace(1, 3, 30); //replaces
    smm2.replace(1, -1, 0); //inexistent value
    smm2.replace(2, 1, 10); //replaces
    smm2.replace(2, 9, 90); //replaces
    smm2.replace(5, 0, 1); //inexistent key

    smm2.replace(1, 30, 15); //changes already replaced key

    smm2.remove(2, 90); //remove replaced key

    smm2.add(2, 9); //add previously replaced key

    SMMIterator itt = smm2.iterator();
    itt.first();
    while (itt.valid()) {
        TElem e = itt.getCurrent();
        std::cout << e.first << " " << e.second << "\n";
        itt.next();
    }
    std::cout << "\n";
}

