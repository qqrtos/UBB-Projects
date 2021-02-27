#include <stdio.h>

///Calculates the sum of even fibonacci terms that are smaller than an upper bound.
int FibonacciSumOfEvenTerms(int termUpperBound) {
	int current_fibonacci_term = 1, next_fibonacci_term = 1;
	int sum = 0;

	while (current_fibonacci_term < termUpperBound && next_fibonacci_term < termUpperBound) {
		if (current_fibonacci_term % 2 == 0) {
			sum += current_fibonacci_term;
		}
		
		///Get next fibo term.
		int auxiliary = next_fibonacci_term;
		next_fibonacci_term += current_fibonacci_term;
		current_fibonacci_term = auxiliary;
	}

	return sum;
}

int main() {
	int upperBound;
	scanf("%d", &upperBound);
	printf("%d", FibonacciSumOfEvenTerms(upperBound));
	return 0;
}