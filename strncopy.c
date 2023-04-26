#include "shell.h"

/**
 * _strchr - locate character in string
 * @s: pointer to the string
 * @c: character to locate
 *
 * Return: pointer to the first occurrence of the character in the
 * string,or NULL if the character is not found
 */
char *_strchr(char *s, char c)
{
	int i = 0;

	while (s[i])
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}

	return (NULL);
}
/**
 * _strspn - gets the length of a prefix substring.
 * @s: The string to search in.
 * @accept: The string containing the characters to match.
 *
 * Return: The number of bytes in the initial segment of s that
 * consists only of bytes from accept.
 */
int _strspn(char *s, char *accept)
{
	int matched = 0;
	int i = 0;

	while (*s)
	{
		i = 0;
		while (accept[i])
		{
			if (*s == accept[i])
			{
				matched++;
				break;
			}
			i++;
		}
		if (!accept[i])
			break;
		s++;
	}

	return (matched);
}
/**
 * _strcmp - compares two strings.
 * @s1: The first string to compare.
 * @s2: The second string to compare.
 *
 * Return: An integer greater than, equal to, or less than 0, according to
 * whether s1 is greater than, equal to, or less than s2.
 */
int _strcmp(char *s1, char *s2)
{
	for (; *s1 && *s2 && *s1 == *s2; s1++, s2++)
		;

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}
/**
 * _strncmp - compares at most n characters of two strings.
 * @s1: The first string to compare.
 * @s2: The second string to compare.
 * @n: The maximum number of characters to compare.
 *
 * Return: An integer greater than, equal to, or less than 0, according to
 * whether the substring of s1 is greater than, equal to, or less
 * than the substring of s2.
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t index = 0;

	while (s1[index] && s2[index] && index < n)
	{
		if (s1[index] > s2[index])
			return (s1[index] - s2[index]);
		else if (s1[index] < s2[index])
			return (s1[index] - s2[index]);

		index++;
	}

	if (index == n)
		return (0);
	else
		return (-15);
}
