#include "shell.h"

/**
 * myprintf - Custom printf-like function
 *
 * This function emulates a simplified version of `printf`. It processes the
 * format string and supports `%s` for strings and `%d` for integers.
 *
 * @format: The format string.
 * @...: Variable number of arguments.
 */
void myprintf(const char *format, ...)
{
	char *str;
	int num;
	va_list args;

	va_start(args, format);

	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			if (*format == 's')
			{
				str = va_arg(args, char*);
				write(1, str, strlen(str));
			}
			else if (*format == 'd')
			{
				num = va_arg(args, int);
				tostring(num);
			}
		}
		else
		{
			write(1, format, 1);
		}
		format++;
	}
	va_end(args);
}

/**
 * _strcpy - Copy a string to another buffer
 *
 * This function copies a string from source to destination and returns a
 * pointer to the destination buffer. It handles NULL destination buffers.
 *
 * @destin: Destination buffer.
 * @source: Source buffer.
 * Return: Pointer to the destination buffer.
 */
char *_strcpy(char *destin, const char *source)
{
	char *ptr;

	if (!destin)
	return (NULL);

	ptr = destin;
	while (*source != '\0')
	{
		*destin = *source;
		destin++;
		source++;
	}

	*destin = '\0';
	return (ptr);
}

/**
 * tok_buf - Tokenize a string into tokens
 *
 * This function splits a string into tokens using a specified delimiter.
 * It also handles the execution of commands and file path validation.
 *
 * @buf: string to tokenize.
 * @args: Array to store the tokens.
 * @delimiter: Delimiter for tokenization.
 * @str: String to store the first token separately.
 * @env: environment variables.
 */
void tok_buf(char *buf, char *args[],
		const char *delimiter, char *str, char *env[])
{
	int i = 0, j = 0;
	char *token, *find_path = NULL, get_cmd[50], new_buf[512];

	if (buf[i] != '/' && buf[i] != '.')
	{
		while (buf[i])
		{
			if (buf[i] == ' ')
				break;
			get_cmd[i] = buf[i];
			i++;
		}
		get_cmd[i] = '\0';
		find_path = full_path(env, get_cmd);
		while (find_path[j] != '\0')
		{
			new_buf[j] = find_path[j];
			j++;
		}
		while (buf[i])
			new_buf[j++] = buf[i++];
		new_buf[j] = '\0';
		_strcpy(buf, new_buf), free(find_path);
	}
	else if (buf[i] == '.' && buf[i + 1] == '/')
	{
		j = 0;
		i += 2;
		if (getcwd(new_buf, sizeof(new_buf)) == NULL)
			perror("getcwd"), exit(EXIT_FAILURE);
		while (new_buf[j])
			j++;
		new_buf[j++] = '/';
		while (buf[i])
			new_buf[j++] = buf[i++];
		new_buf[j] = '\0';
		_strcpy(buf, new_buf);
	}
	tok(&buf, &delimiter, &token, &str, args);
}

/**
 * _strdup - Duplicate a string
 *
 * This function duplicates a string and returns pointer to duplicated string.
 *
 * @str: The string to duplicate.
 * Return: The pointer to the duplicated string or NULL if it fails.
 */
char *_strdup(const char *str)
{
	size_t len = 0;
	const char *s = str;
	char *c, *copy;

	while (*s++)
		len++;

	copy = malloc((len + 1) * sizeof(char));
	if (copy != NULL)
	{
		c = copy;
		while (*str)
			*c++ = *str++;
		*c = '\0';
	}
	return (copy);
}

/**
 * tostring - change an integer to a string and print it
 *
 * @num: The integer to change and print.
 */
void tostring(int num)
{
	char str[20];
	int i, rem, len = 0, n, dec;

	n = num;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	dec = len - 1;
	for (i = 0; i < len; i++)
	{
		rem = num % 10;
		num = num / 10;
		str[dec] = rem + '0';
		dec--;
	}
	str[len] = '\0';
	write(1, str, len);
}

