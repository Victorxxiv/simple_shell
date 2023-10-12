#include "shell.h"

/**
* builtin - Checks for and handles built-in shell commands
* @info: Information about the shell
* @arguments: Array of command and arguments
* Return: _TRUE if built-in command, _FALSE otherwise
*/

int builtin(general_t *info, char **arguments)
{
	int status;

	status = check_builtin(info, arguments);
	if (status == _FALSE)
	{
		return (_FALSE);
	}
	return (_TRUE);
}

/**
* bin_env - Implements the 'env' command
* @info: General information about the shell
* @command: Command and arguments (unused)
**/
void bin_env(general_t *info, char **command)
{
	(void) info;
	(void) command;

	display_environment();
}

/**
* display_environment - Displays the entire environment
**/
void display_environment(void)
{
	char **env_var;
	int index;

	for (index = 0, env_var = environ; env_var[index] != NULL; index++)
	{
		print(env_var[index]);
		_putchar('\n');
	}
}

/**
* is_current_path - Checks if the PATH variable starts with a colon
* @path: PATH variable to check
* @info: General information about the shell
**/
void is_current_path(char *path, general_t *info)
{
	info->is_current_path = _FALSE;

	if (path == NULL)
	{
		return;
	}
	if (path[0] == ':')
	{
		info->is_current_path = _TRUE;
	}
}

