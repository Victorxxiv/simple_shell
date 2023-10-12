#ifndef _SHELL_H
#define _SHELL_H

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stddef.h>
#include <limits.h>
#include <sys/cdefs.h>

/* Macros */
#define _TRUE 0
#define _FALSE 1

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define NON_INTERACTIVE 0
#define INTERACTIVE 1

#define PERMISSIONS 1
#define NON_PERMISSIONS -1

#define _FILE 10
#define NON_FILE -10

#define _ENOENT "No such file or directory"
#define _EACCES "Permission denied"
#define _CMD_NOT_EXISTS "not found"
#define _ILLEGAL_NUMBER "Illegal number"

#define _CODE_ENOENT 3
#define _CODE_EACCES 13
#define _CODE_CMD_NOT_EXISTS 132
#define _CODE_ILLEGAL_NUMBER 133

/* Global Variables */
extern char **environ;

/* Structures */

/* Structure to hold general shell-related information */
typedef struct general_s
{
	int argc; /* Number of arguments passed to the shell */
	char **argv; /* Array of argument strings */
	int mode; /* Operating mode: INTERACTIVE or NON_INTERACTIVE */
	int error_code; /* Error code for error messages */
	char *command; /* Command to execute */
	int n_commands; /* Number of commands executed */
	char *value_path; /* Path of the executed command */
	int is_current_path; /* Flag to check if path starts with a colon */
	int status_code; /* Last exit status code */
	char *buffer; /* Line read using getline */
	char **arguments; /* Arguments split from the command line */
	char *environment; /* Last retrieved environment variable */
	int pid; /* Process ID of the shell */
} general_t;

/* Structure to represent error messages and codes */
typedef struct
{
	char *message; /* Error message associated with the error */
	int code; /* Error code used to identify the error message */
} error_t;

/* Structure to define built-in shell commands */
typedef struct
{
	char *command; /* The name of the built-in command */
	void (*func)(general_t *info, char **arguments);
	/* Function pointer to the implementation of the built-in command */
} builtin_t;

void prompt(char **env);
int check_builtin(general_t *info, char **arguments);
void print(char *str);
int _putchar(char c);
int builtin(general_t *info, char **arguments);
void bin_env(general_t *info, char **command);
void display_environment(void);
void is_current_path(char *path, general_t *info);

#endif /* SHELL_H */
