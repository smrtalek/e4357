#include <stdio.h>


// "FAST" version
int my_strcmp(char const * const str1, char const * const str2) {
	const char *s1 = str1;
	const char *s2 = str2;
	while(*s1 && *s2 && *s1 == *s2) {
		s1++;
		s2++;
	}

	if (*s1 == '\0' && *s1 != *s2)
		return -1;
	else if (*s2 == '\0' && *s1 != *s2)
		return 1;

	return (*s1 - *s2);
}


int main(int argc, char *argv[]) {
	int result;


	if (argc < 3) {
		return -1;
	}
	fprintf(stdout, "strcmp(%s, %s) = %d\n", argv[1], argv[2], (result = my_strcmp(argv[1],argv[2])));

	if (result < 0)
		fprintf(stdout, "str %s is 'LESS' than %s\n", argv[1], argv[2]);
	else if (result > 0)
		fprintf(stdout, "str %s is 'MORE' than %s\n", argv[1], argv[2]);
	else
		fprintf(stdout, "str %s is 'EQUAL' to %s\n", argv[1], argv[2]);


	return result;
}

