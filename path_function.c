#include "shell.h"

/**
 * path_check - Check if a file exists in the specified paths
 *
 * This function searches for a file in a list of paths separated by colons.
 * It returns the first path where the file is found, or the original path
 * if not found.
 *
 * @path: String containing many  paths defferietiated by colons.
 * Return: Pointer to the first path where the file is found.
 */
char *path_check(char path[])
{
	char *token, *path_ex, *short_path, final_path[256];
	int i = 0;
	const char *delimiter = ":";

	token = strtok(path, delimiter);
	while (token)
	{
		path_ex = token;
		if (access(path_ex, F_OK) != -1)
		{
			while (path_ex[i] != '\0')
			{
				final_path[i] = path_ex[i];
				i++;
			}
			final_path[i] = '\0';

			_strcpy(path_ex, final_path);
			return (path_ex);
		}
		token = strtok(NULL, delimiter);
	}
	short_path = path_ex;
	return (short_path);
}

/**
 * full_path - Get whole path of a command in the environment
 *
 * This function extracts the full path of a specified command by searching
 * through the environment variables. It returns the full path if found.
 *
 * @env: Array of strings with environment variables.
 * @cmd: String containing the command to search for in the environment.
 * Return: Pointer to the full path if found, or NULL if not found.
 */
char *full_path(char *env[], char cmd[])
{
	char full_path[1024], *path_returned = NULL, *result;
	int i, j, index = 0, cmd_i = 0;

	for (i = 0; env[i]; i++)
	{
		j = 0;
		if (env[i][j] == 'P' && env[i][j + 2] == 'T' && env[i][j + 4] == '=')
		{
			j += 5;
			while (env[i][j])
			{
				full_path[index] = env[i][j];
				if (env[i][j + 1] == ':')
				{
					index++;
					full_path[index++] = '/';
					while (cmd[cmd_i])
						full_path[index++] = cmd[cmd_i++];
					cmd_i = 0;
					index--;
				}
				j++;
				index++;
			}
			full_path[index++] = '/';
			while (cmd[cmd_i])
				full_path[index++] = cmd[cmd_i++];
			full_path[index] = '\0';
		}
	}
	path_returned = path_check(full_path);
	result = malloc(strlen(path_returned) + 1);
	if (!result)
	{
		perror("Failed to allocate memory");
		exit(1);
	}
	_strcpy(result, path_returned);
	return (result);
}

