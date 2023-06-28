#include "shell.h"
/**
 * execmd - executext the commands printed by user
 * @argv: array pointing to the commands typed by user
 * Return: void
 */
void execmd(char **argv)
{
	char *command = NULL, *actual_command = NULL;

	while (argv)
	{
		command = argv[0];
		actual_command = get_path(command);

		if (execve(actual_command, argv, NULL) == -1)
		{
			perror("Error:");
		}
	}
}
