#pragma once
#include <iostream>
#include <string>

using namespace std;

class number
{
public:
	string value = "";
	int base = -1;


private:
	friend istream& operator >> (istream& in, number& n) {
		try {
			cout << "Input value: "; in >> n.value;
			cout << "Input base: "; in >> n.base;
			cout << "\n";
		}
		catch (char e) {
			cout << "Invalid input!\n";
		}

		return in;
	}
	friend ostream& operator << (ostream& out, number n) {
		cout << n.value << " (" << n.base << ")\n";
		return out;
	}


	int bitValue(char bit) {
		/*
			Returns the value of the given bit in base 10.
			ex: bit 'F'->15, bit '8'->8
		*/
		if (isdigit(bit))return bit - '0';
		return bit - 'A' + 10;
	}
	char convertToChar(int val) {
		/*
			Returns the character coresponding to the value in base 10.
			ex: val 12->'C', 8->'8'
		*/
		if (val <= 9)return (char)(val + '0');
		return (char)(val - 10 + 'A');
	}
	int convertToBase10(string val, int b) {
		//...
		int res = 0, p = 1;
		int len = val.length() - 1;
		while (len >= 0) {
			res += bitValue(val[len]) * p;
			p = b;
			--len;
		}
		return res;
	}
	bool validateInput() {
		/*
			Criteria for a valid input:
				-base >= 2
				-every bit in the representation is < than the base
				-every bit is either a digit or a letter (for bases > 10)
			This function returns TRUE or FALSE, depending on whether the input meets the criteria above.
		*/
		if (this->base < 2)return false;
		for (int i = 0; i < this->value.length(); i++) {
			char character = this->value[i];
			int b = this->base;
			if (bitValue(character) >= b)return false;
			else if (!isalpha(character) && !isdigit(character))return false;
		}

		return true;
	}

public:
	bool getValidInput() {
		//Returns TRUE for a valid input and FALSE for an invalid one.
		return validateInput();
	}


	number operator + (number add2) {
		/*
			This is the overloaded operator that adds 2 numbers.
			The idea is to add the right-most bits (+carry) in the variable s, keep
				s%base in the final result and carry the s/base forward.
			Because we worked from right to left, the end result is flipped.
		*/
		number res;
		if (this->base == add2.base && this->base != -1 && add2.base != -1) { //Verifies whether the numbers meet the criteria to be added
			res.base = this->base; //Initializes the base of the result
			int l_this = this->value.length() - 1, l_add2 = add2.value.length() - 1; //These are used to facilitate the movement from right to left
			int carry = 0;

			while (l_this >= 0 && l_add2 >= 0) { //Adds the two numbers
				int s = bitValue(this->value[l_this]) + bitValue(add2.value[l_add2]) + carry;
				res.value.append(1u, convertToChar(s % res.base));
				carry = s / res.base;
				--l_this, --l_add2;
			}
			while (l_this >= 0) { //Places the remaining part of the number in the result.
				int s = bitValue(this->value[l_this]) + carry;
				res.value.append(1u, convertToChar(s % res.base));
				carry = s / res.base;
				--l_this;
			}
			while (l_add2 >= 0) { //Places the remaining part of the number in the result.
				int s = bitValue(add2.value[l_add2]) + carry;
				res.value.append(1u, convertToChar(s % res.base));
				carry = s / res.base;
				--l_add2;
			}
			if (carry)res.value.append(1u, convertToChar(carry)); //Puts the remaining carry in the result.

			reverse(res.value.begin(), res.value.end()); //Flip the result so that the shown number is correct.
			return res;
		}
		else {
			number empty;
			cout << "Numbers are represented in different bases or the input is invalid.";
			return empty;
		}
	}


	number operator * (number multiplier) {
		/*
			/../
		*/
		number res;
		if (this->base == multiplier.base && this->base != -1 && multiplier.base != -1 && multiplier.value.length() < 2) { //Verifies whether the numbers meet the criteria to be multiplied
			res.base = this->base;
			int l_this = this->value.length() - 1;
			char multChar = multiplier.value[0]; //this variable is the 1-digit multiplier
			int carry = 0;

			while (l_this >= 0) { //Multiplies the 2 numbers
				int s = bitValue(this->value[l_this]) * bitValue(multChar) + carry;
				res.value.append(1u, convertToChar(s % res.base));
				carry = s / res.base;
				--l_this;
			}
			if (carry)res.value.append(1u, convertToChar(carry)); //Appends the remeining carry (if there is one) to the result

			reverse(res.value.begin(), res.value.end());
			return res;
		}
		else {
			number empty;
			cout << "Numbers are represented in different bases or the input is invalid.";
			return empty;
		}
		return res;
	}


	number operator - (number subtrahend) {
		/*
			/../
		*/
		number res;
		if (this->base == subtrahend.base && this->base != -1 && subtrahend.base != -1) { //Verifies whether the numbers meet the criteria to be subtracted
			res.base = this->base;
			int l_this = this->value.length() - 1, l_sub = subtrahend.value.length() - 1; //These are used to facilitate the movement from right to left
			int carry = 0;

			while (l_this >= 0 && l_sub >= 0) { //Subtracts the two numbers
				int s = bitValue(this->value[l_this]) - bitValue(subtrahend.value[l_sub]) + carry;
				if (s < 0) {
					carry = -1;
					s += res.base;
				}
				else carry = 0;
				res.value.append(1u, convertToChar(s));
				--l_this, --l_sub;
			}
			while (l_this >= 0) { //Places the remaining part of the number in the result.
				int s = bitValue(this->value[l_this]) + carry;
				if (s < 0) {
					carry = -1;
					s += res.base;
				}
				else carry = 0;
				res.value.append(1u, convertToChar(s));
				--l_this;
			}
			while (l_sub >= 0) { //Places the remaining part of the number in the result.
				int s = bitValue(subtrahend.value[l_sub]) + carry;
				if (s < 0) {
					carry = -1;
					s += res.base;
				}
				else carry = 0;
				res.value.append(1u, convertToChar(s));
				--l_sub;
			}

			reverse(res.value.begin(), res.value.end());
			return res;
		}
		else {
			number empty;
			cout << "Numbers are represented in different bases or the input is invalid.";
			return empty;
		}
	}


	number operator / (number divisor) {
		number res;
		if (divisor.value.length() < 2 && divisor.value[0] != '0') {
			int div = divisor.convertToBase10(divisor.value, divisor.base);
			//
		}
		else {
			number empty;
			cout << "Numbers are represented in different bases or the input is invalid.";
			return empty;
		}
		return res;
	}


	void convertToBase(int destinationBase) {
		if (destinationBase < this->base)
			//substitution method
			return;
		else if (destinationBase > this->base)
			//successive divisions
			return;
		else cout << "Number is already represented in this base.\n";
	}
};