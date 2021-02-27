#include <stdio.h>
#include <string.h>

int main() {
	char s[50];
	scanf("%s", s);
	if (strcmp(s, "exit") == 0)
	{
		return 0;
	}
	printf("%s", s);
	return 0;
}