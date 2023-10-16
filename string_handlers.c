#include "shell.h"

/**
 * strlen - Calculate the len of a string
 *
 * This function counts the number of characters in a string
 * and returns the length of the string.
 *
 * @str: Input string
 * Return: Length of the string
 */
size_t strlen(const char *str)
{
	const char *s;

	for (s = str; *s; ++s)
		;
	return (s - str);
}

/**
 * strcmp - Compare two strings
 *
 * This function compares two strings and returns an integer value
 * indicating their relationship (greater, equal, or less).
 *
 * @string1: The first input string
 * @string2: The second input string
 * Return: An integer value representing the comparison result
 */
int strcmp(const char *string1, const char *string2)
{
	while (*string1 && (*string1 == *string2))
	{
		string1++;
		string2++;
	}
	return (*(unsigned char *)string1 - *(unsigned char *)string2);
}

/**
 * c_memmov - This moves memory block
 *
 * @destination: The pointer to the destination memory block
 * @src: Pointer to the source memory block
 * @n: Number of bytes to be moved
 * Return: A pointer to the destination memory block
 */
void *c_memmov(void *destination, const void *src, size_t n)
{
	char *to_destination, *current;
	const char *from_src;
	unsigned int j;

	to_destination = (char *)destination;
	from_src = (const char *)src;
	current = malloc(sizeof(char) * n);
	if (!current)
		return (NULL);
	for (j = 0; j < n; ++j)
		*(current + j) = *(from_src + j);
	for (j = 0; j < n; ++j)
		*(to_destination + j) = *(current + j);
	free(current);
	return (destination);
}

/**
 * space - Check if character is whitespace character
 *
 * This function checks if a character is a whitespace character,
 * which includes space, tab, newline, and carriage return.
 *
 * @c: The character to check
 * Return: 1 if it's a whitespace character, 0 otherwise
 */
int space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

/**
 * trim_buffer - Remove leading and trailing whitespace from a buffer
 *
 * This function removes leading and trailing whitespace (space, tab, newline,
 * or carriage return) from a string buffer.
 *
 * @buffer: Input buffer
 */
void trim_buffer(char *buffer)
{
	size_t size = strlen(buffer), i = 0;

	if (size == 0)
		return;

	while (space((unsigned char)buffer[i]))
		i++;

	c_memmov(buffer, buffer + i, size - i + 1);
	size -= i;

	while (size > 0 && space((unsigned char)buffer[size - 1]))
		size--;
	buffer[size] = '\0';
}

