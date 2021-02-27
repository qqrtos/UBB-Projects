#include "number.h"

using namespace std;

void displayMenu() {
	cout << "\n\nChoose an option:\n";
	cout << "\t1. Add two numbers.\n";
	cout << "\t2. Subtract two numbers.\n";
	cout << "\t3. Multiply two numbers.\n";
	cout << "\t4. Divide two numbers.\n";
	cout << "\t5. Convert a number to a diffferent base.\n";
	cout << "\t6.Exit application.\n\n";
}

bool validateOption(char opt) {
	//Checks whether the user's input is correct
	return (opt == '1' || opt == '2' || opt == '3' || opt == '4' || opt == '5' || opt == '6');
}

number read_a_number() {
	number num;
	cin >> num;

	if (num.getValidInput() == false) {
		cout << "Invalid input.\n";
		number empty;
		return empty;
	}
	else return num;
}

int main() {
	char option='0';
	number n1, n2;

	while (option != '6') {
		displayMenu();
		cin >> option;
		if (validateOption(option)) {
			switch (option) {
				case '1':
					n1 = read_a_number(), n2 = read_a_number();
					cout << (n1 + n2);
					break;
				case '2':
					n1 = read_a_number(), n2 = read_a_number();
					cout << (n1 - n2);
					break;
				case '3':
					n1 = read_a_number(), n2 = read_a_number();
					cout << (n1 * n2);
					break;
				case '4':
					//Divide
					break;
				case '5':
					//
					break;
			}
		}
		else cout << "Invalid option. Try again.\n";
	}
	return 0;
}