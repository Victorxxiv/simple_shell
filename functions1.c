#include "shell.h"

/**
 * name_program - Extract the name of the program from command-line arguments
 *
 * @argc: Number of arguments
 * @argv: Argument vector
 * Return: Pointer to the program name
 */
char *name_program(int argc, char *argv[])
{
	char *name = NULL;

	name = argv[argc - 1];
	name++;
	name++;
	return (name);
}

/**
 * take_only_cmd - Extort the first command from a string
 *
 * @buffer: Input string with one or more commands
 * @no_exc: Pointer to handle 'continue' in a forked process
 * @argc: Number of arguments
 * @argv: Argument vector
 * @n_err: Number of commands
 * Return: Pointer to the first command
 */
char *take_only_cmd(char **buffer, int *no_exc, int argc,
		char *argv[], int *n_err)
{
	int i = 0;
	char str_cmd[50], *cmd;

	if (_strlen(*buffer) >= 50)
	{
		perror("Command is too long\n");
		free(*buffer), exit(1);
	}
	while ((*buffer)[i])
	{
		if ((*buffer)[i] == ' ')
			break;
		str_cmd[i] = (*buffer)[i];
		i++;
	}
	str_cmd[i] = '\0';
	cmd = malloc(_strlen(str_cmd) + 1);
	if (!cmd)
	{
		perror("Failed to allocate memory");
		exit(1);
	}
	strcpy(cmd, str_cmd);
	if (_strcmp(cmd, "cd") == 0)
	{
		*no_exc = 0;
		change_dir(*buffer, cmd, argc, argv, n_err);
	}
	return (cmd);
}

/**
 * ls_check - Look if the cmd is 'ls' and validate directories
 *
 * @ave: Array of cmd-line
 * @buf: Buffer for storing cmd-line
 * @only: The title of the cmd
 */
void ls_check(char *ave[], char *buf, char *only)
{
	const char *dir_path = NULL;
	DIR *dir;
	int index = 1;

	if (_strcmp(only, "ls") == 0 || _strcmp(ave[0], "/usr/bin/ls") == 0 ||
			_strcmp(ave[0], "/bin/ls") == 0)
	{
		while (ave[index])
		{
			if (ave[index][0] != '-')
			{
				dir_path = ave[index];
				dir = opendir(dir_path);
				if (!dir)
				{
					fprintf(stderr, "%s: cannot access '%s': No such file or directory\n",
							only, dir_path);
					if (ave[index + 1] == NULL)
						free(buf), free(only), exit(2);
				}
				if (dir)
					closedir(dir);
			}
			index++;
		}
	}
}

/**
 * shell_exit - Exit the shell program with the appropriate status
 * @status: The exit status to be handled
 */
void shell_exit(int status)
{
	if (status == 512)
		exit(status / 256);
	exit(0);
}

