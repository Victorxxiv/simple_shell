#include "shell.h"

/**
 * non_interactive - Entry point for non-interactive mode execution.
 *
 * This function handles the execution of non-interactive mode for the shell,
 * where commands are read from standard input without a command prompt.
 *
 * @argc: Number of arguments.
 * @argv: Array of strings.
 * @env: Environment variables.
 * @pipe: Flag to indicate non-interactive mode (set to 0).
 * Return: Always returns an integer.
 */
void non_interactive(int argc, char *argv[], char *env[], int *pipe)
{
	int bytes, err_count = 1, no_exc = 1, status = 0;
	const char *delimiter = " ";
	size_t n_buffer = 0;
	char *buffer = NULL, command[50], *args[20], *only_command;

	*pipe = 0;
	while ((bytes = getline(&buffer, &n_buffer, stdin) != -1))
	{
		no_exc = 1;
		trim_buffer(buffer);
		comments(&buffer, &no_exc);
		if (strcmp(buffer, "exit") == 0)
		{
			free(buffer);
			if (status == 512)
				shell_exit(status);
			exit(0);
		}
		if (strcmp(buffer, "env") == 0)
			envNon(&no_exc);
		only_command = take_only_cmd(&buffer, &no_exc, argc, argv, &err_count);
		if (*buffer && no_exc)
		{
			tok_buf(buffer, args, delimiter, command, env);
			if (access(command, X_OK) == 0)
				child(argc, argv, buffer, args, only_command, &status);
			else
				fprintf(stderr, "%s: %d: %s: not found\n",
						argv[argc - 1], err_count++, only_command), fflush(stdout);
		}
		free(only_command);
	}
	free(buffer);
}

