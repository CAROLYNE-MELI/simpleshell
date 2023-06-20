#include "shell.h"
/**
 * main - entry point
 * @ac: argument count
 * @argv: array pointing to the arguments
 * Return: 0
 */
int main(int ac, char **argv)
{
	char *prompt = "#cisfun$ ", *lineptr = NULL, *lineptr_cp = NULL;
	size_t n = 0;
	ssize_t nchars_read;
	const char *delim = " \n";
	int num = 0, m;
	char *token;
	(void)ac;

	while (1)
	{
		printf("%s", prompt);
		nchars_read = getline(&lineptr, &n, stdin);
		if (nchars_read == -1)
		{
			printf("shell exiting...\n");
			return (-1);
		}
		lineptr_cp = malloc(sizeof(char) * nchars_read);
		if (lineptr_cp == NULL)
		{
			perror("tsh: memory allocation error");
			return (-1);
		}
		strcpy(lineptr_cp, lineptr);
		token = strtok(lineptr, delim);
		while (token != NULL)
		{
			num++;
			token = strtok(NULL, delim);
		}
		num++;
		argv = malloc(sizeof(char *) * num);
		token = strtok(lineptr_cp, delim);
		for (m = 0; token != NULL; m++)
		{
			argv[m] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[m], token);
			token = strtok(NULL, delim);
		}
		argv[m] = NULL;
		execmd(argv);
	}
	free(lineptr_cp);
	free(lineptr);
	return (0);
}
