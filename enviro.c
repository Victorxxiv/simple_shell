#include "shell.h"

/**
 * env - Display the current environment variables
 *
 * This function is responsible for printing all the environment variables
 * that are currently set. It iterates through the environment variables
 * and displays each one.
 */
void env(void)
{
	char **env_ptr = environ;

	while (*env_ptr)
	{
		myprintf("%s\n", *env_ptr);
		env_ptr++;
	}
}

/**
 * envNon - Display the current environment variables without forking
 *
 * @no_exc: A variable to handle 'continue' in a forked process
 * This function is used to print environment variables when a shell command
 * is executed without forking. It allows for the use of the 'continue'
 * option within a child process.
 */
void envNon(int *no_exc)
{
	char **env_ptr = environ;
	*no_exc = 0;

	while (*env_ptr)
	{
		myprintf("%s\n", *env_ptr);
		env_ptr++;
	}
}

