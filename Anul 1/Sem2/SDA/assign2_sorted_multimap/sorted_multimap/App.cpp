#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"
#include <chrono>
#include <crtdbg.h>

/*
ADT SortedMultimap

Create an iterator over the values associated to one key.

//creates an iterator over the values associated to key k.
If k is not in the SortedMultiMap the iterator is invalid after creation,
otherwise, the current element is the first value associated to the key
ValueIterator iterator(TKey k);

Create the ValueIterator class with the same operations as the regular SortedMultiMapIterator, 
except that the constructor of the ValueIterator receives as parameter the SortedMultiMap and
the key and the getCurrent operation returns a TValue
*/

using namespace std::chrono;

int main() {
	{
		auto start = steady_clock::now();

		testAll();
		testAllExtended();

		std::cout << "Finished SMM Tests in " << duration_cast<milliseconds>(steady_clock::now() - start).count() << "ms!" << std::endl;
	}

	_CrtDumpMemoryLeaks();

	system("pause");
}
