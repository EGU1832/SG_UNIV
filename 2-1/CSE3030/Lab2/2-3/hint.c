#include <stdio.h>

/* This function will print a secret string to you. Your goal is to execute this
 * function by exploiting buffer overflow vulnerability.
 */
void print_secret(void);

void use_array(void) {
    int arr[32];
    // ... (more variable declarations)

    puts("Input two integers:");

    /* Figure out what kind of operation is performed here */
    int num1, num2;

	if (scanf("%d %d", &num1, &num2) != 2) {
        puts("Invalid integer format");
        return;
    }

    arr[num2] = num1;

    // ... (?)
}

int main(void) {
    use_array();
    return 0;
}
