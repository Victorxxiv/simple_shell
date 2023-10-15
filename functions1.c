#include "shell.h"

/**
 * child - Spawn a child process and execute a command within it.
 *
 * This function creates a child process to run a specified command
 * using the execve system call. It gracefully handles forking, execution,
 * and error scenarios.
 *
 * @argc:  argument count.
 * @argv: argument vector.
 * @buf: command buffer.
 * @ave: argument vector for execve.
 * @only: command to execute.
 * @status: The exit status.
 */
void child(int argc, char *argv[], char *buf, char *ave[],
		char *only, int *status)
{
	signed int pid;

	/* Ignore unused arguments */
	(void)argv;
	(void)argc;

	/* Create a child process using the fork system call */
	pid = fork();
	if (pid == -1)
	{
		perror("Failed to spawn a child process");
		free(buf);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		/* In child process, attempt to execute command using execve */
		execve(ave[0], ave, NULL);

		/* Handle when execve fails, print error message, free memory */
		perror("execve failed");
		free(buf);
		free(only);
		exit(1);
	}
	else
	{
		/* In parent process, wait child process to collect status */
		wait(status);
	}
}

