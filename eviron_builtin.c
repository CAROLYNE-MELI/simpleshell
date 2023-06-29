#include "shell.h"
extern char **environ;
/**
 * shell_env - prints the current enviroment
 * Return: void
 */
void shell_env(void)
{
    	char **env = environ;
    	
	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
    	}
}
