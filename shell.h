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
#include <dirent.h>
#include <stdarg.h>

/* Global Variables */
extern char **environ;

/* Function prototypes */
void print(const char *str);
char *_strdup(const char *str);
char *_strcpy(char *destination, const char *src);
void trim_buffer(char *buffer);
int main(int argc, char *argv[], char *env[]);
size_t strlen(const char *str);
void child(int argc, char *argv[], char *buf,
		char **args, char *only, int *status);
int strcmp(const char *string1, const char *string2);
void tok_buf(char *buf, char *args[], const char *delimiters,
		char *str, char *env[]);

char *take_only_cmd(char **buffer, int *no_exc,
		int argc, char *argv[], int *n_err);
void ls_check(char *args[], char *buf, char *only);
void change_dir(char *buffer, char *cmd, int argc, char *argv[], int *n_err);
void comments(char **buf, int *no_exc);
void tok(char **buffer, const char **delimiters,
		char **token, char **str, char *args[]);
void handle_input_command(char **buffer, size_t *n_buffer,
		int *no_exc, char **only_command, int status,
		int argc, char *argv[], int *n_err);
void handle_sigint(int sig_num);
char *name_program(int argc, char *argv[]);
void shell_exit(int status);
char *full_path(char *env[], char cmd[]);
void myprintf(const char *format, ...);
void tostring(int num);
char *path_check(char path[]);
void env(void);
void envNon(int *no_exc);
void non_interactive(int argc, char *argv[],
		char *env[], int *pipe);
void _memmove(void *destination, const void *src, size_t n);

#endif /* SHELL_H */
