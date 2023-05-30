#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* This function will print a secret string to you. Your goal is to execute this
 * function by exploiting buffer overflow vulnerability.
 */
void print_secret(void);

void string_test(void) {
    int i, len;
    char buf[48];

    puts("Welcom to string testing service!");
    gets(buf);

    for (len = 0; buf[len] != '\0'; len++)
        ;

    /* TODO: Figure out what kind of test is performed here */

	if (len <= 3) {
		puts("String is too short!");
		exit(1);
	}

	for (i = 0; i < len; i++) {
		if (buf[i] == buf[len - i - 1])
			continue;
		else {
			puts("String is not a palindrome!");
			exit(1);
		}
	}

    puts("Your string passed the test!");
}

int main(void) {
    string_test();
    return 0;
}
