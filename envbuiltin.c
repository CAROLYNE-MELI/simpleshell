#include <stdio.h>
#include <stdlib.h>
#inlude < unistd.h >
/**
 * main - main function begins
 * @environ - character to print
 * return - zero when success
 * void - main retrn
 */

int main(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}

	return (0);
}
