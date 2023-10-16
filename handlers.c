#include "shell.h"

/**
 * tok - Tokenizes a string into an array of arguments.
 *
 * This function splits a string into tokens using a specified delimiter and
 * stores them in an array of arguments.
 *
 * @buf: Pointer to the input string buffer.
 * @delimiter: Pointer to the delimiter string.
 * @token: Pointer to the token string.
 * @str: Pointer to the output string.
 * @args: Array of arguments to store the tokens.
 */
void tok(char **buf, const char **delimiter,
		char **token, char **str, char *args[])
{
	int index;

	(*token) = strtok((*buf), (*delimiter));
	index = 0;
	while ((*token))
	{
		args[index] = (*token);
		(*token) = strtok(NULL, (*delimiter));
		index++;
	}
	args[index] = NULL;
	index = 0;
	while (args[0][index] != '\0')
	{
		(*str)[index] = args[0][index];
		index++;
	}
	(*str)[index] = '\0';
}

/**
 * comments - Processes and removes comments from a string.
 *
 * This function scans the input string for comments (lines starting with #)
 * and removes them, allowing further processing of the string.
 *
 * @buf: Pointer to string buffer.
 * @no_exc: Pointer to integer flag highlighting whether exception occurred.
 */
void comments(char **buf, int *no_exc)
{
	char *test;
	int i = 0;

	test = *buf;
	while (test[i])
	{
		if (test[0] == '#')
		{
			*no_exc = 0;
			break;
		}
		else if (test[i] == '#' && test[i - 1] == ' ')
		{
			*(*buf + i) = '\0';
			break;
		}
		i++;
	}
}

/**
 * handle_input_command - Handles the user's input command.
 *
 * This function processes the user's input command, handles specific built-in
 * commands (e.g., exit, env), and prepares the command for execution.
 *
 * @buffer: Pointer to the input command buffer.
 * @n_buffer: Pointer to the size of the input command buffer.
 * @no_exc: Pointer to integer flag highlighting whether an exception occurred.
 * @only_command: Pointer to the variable storing the main command.
 * @status: Array of environment variables.
 * @argc: Number of arguments.
 * @argv: Arguments vector.
 * @n_err: Pointer to the error status.
 */
void handle_input_command(char **buffer, size_t *n_buffer, int *no_exc,
		char **only_command, int status, int argc, char *argv[], int *n_err)
{
	int bytes;

	(void)status;
	bytes = getline(buffer, n_buffer, stdin);
	if (bytes == -1)
		free(*buffer), exit(1);
	if ((*buffer)[bytes - 1] == '\n')
		(*buffer)[bytes - 1] = '\0';
	trim_buffer(*buffer);
	comments(buffer, no_exc);
	if (strcmp(*buffer, "exit") == 0)
		free(*buffer), exit(0);
	if (strcmp(*buffer, "env") == 0)
	{
		*no_exc = 0;
		env();
	}
	*only_command = take_only_cmd(buffer, no_exc, argc, argv, n_err);
}

/**
 * handle_sigint - Works on the SIGINT signal.
 *
 * This function handles the SIGINT signal (e.g., Ctrl+C) and exits program.
 *
 * @sig_num: signal number.
 */
void handle_sigint(int sig_num)
{
	exit(sig_num);
}

/**
 * change_dir - alternates the current working directory.
 *
 * This function changes the current working directory based on user input,
 * and handles built-in 'cd' commands.
 *
 * @buffer: The input command buffer.
 * @cmd: The command name.
 * @argc: Number of arguments.
 * @argv: Arguments vector.
 * @n_err: Pointer to the error status.
 */
void change_dir(char *buffer, char *cmd, int argc, char *argv[], int *n_err)
{
	char *token, *back = NULL, *now = NULL;

	now = getenv("PWD");
	back = getenv("OLDPWD");
	token = strtok(buffer, " ");
	token = strtok(NULL, " ");
	if (token == NULL)
	{
		if (chdir(getenv("HOME")) != 0)
			perror("cd"), free(buffer), free(cmd), exit(1);
		setenv("OLDPWD", now, 1);
	}
	else if (strcmp(token, "-") == 0)
	{
		if (back == NULL)
			write(2, "cd: OLDPWD not set\n", strlen("cd: OLDPWD not set\n"));
		if (chdir(back) != 0)
			perror("cd"), free(buffer), free(cmd), exit(1);
		setenv("OLDPWD", now, 1);
		myprintf("%s\n", back);
	}
	else
	{
		if (chdir(token) != 0)
		{
			fprintf(stderr, "%s: %d: cd: can't cd to %s\n",
					argv[argc - 1], *n_err++, token);
		}
		setenv("OLDPWD", now, 1);
	}
}

