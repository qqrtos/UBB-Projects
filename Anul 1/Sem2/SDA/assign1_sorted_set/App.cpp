#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>
#include <ctime>

using namespace std;

int main() {
	double duration;
	clock_t start = clock();

	testAll();
	testAllExtended();

	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Test end " << duration << "s" << endl;
	system("pause");
	return 0;
}