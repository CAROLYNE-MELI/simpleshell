#include <stdio.h>
#include <stdlib.h>
/**
 * main - main function begins
 * environ - character to print
 * return 1 on succes else 0
 */
extern char **environ;

int main(void) {
    char **env = environ;

    // Print each environment variable
    while (*env != NULL) {
        printf("%s\n", *env);
        env++;
    }

    return EXIT_SUCCESS;
}
