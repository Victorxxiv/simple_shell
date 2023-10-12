#include "shell.h"

/**
 * main - Entry point for the simple shell program
 * @ac: Argument count
 * @av: Argument vector
 * @env: Environmental variables
 * Return: 0 on success
 */
int main(int ac, char **av, char **env)
{
	/* Avoid unused argument warnings */
	(void)ac;
	(void)av;

	/* Start the shell by displaying a prompt */
	prompt(env);

	return (0);
}

