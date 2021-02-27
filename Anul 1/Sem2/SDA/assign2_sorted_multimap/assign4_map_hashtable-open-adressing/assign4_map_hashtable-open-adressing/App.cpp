#include "ExtendedTest.h"
#include "ShortTest.h"

#include "Map.h"

#include <iostream>

/*
ADT Map

//keeps in the Map only those pairs whose key respects the given condition
void filter(Condition cond);

where Condition is a function which takes as parameter a key and returns true or false depending on whether the key respects the condition.
Obs. add the following typedef to the beginning of Map.h

typedef bool (*Condition)(TKey);
*/

using namespace std;


int main() {
	testAll();
	testAllExtended();

	cout << "That's all!" << endl;
	system("pause");

	return 0;
}


