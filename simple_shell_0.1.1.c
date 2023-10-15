#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include <unistd.h>

#define BUFFER_SIZE 1024

/**
 * custom_getline - Read a line from standard input
 *
 * Return: A dynamically allocated string containing the line.
 */
char *custom_getline(void)
{
	static char buffer[BUFFER_SIZE];
	static size_t buffer_pos = 0;
	static ssize_t bytes_read = 0;

	char *line = NULL;
	size_t line_size = 0;
	size_t i;
	size_t remaining_bytes = (size_t)bytes_read - buffer_pos;
	char *new_line = realloc(line, line_size + remaining_bytes);

	while (1)
	{
		if (buffer_pos >= (size_t)bytes_read)
		{
			bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			if (bytes_read <= 0)
			{
				return (NULL);
			}
			buffer_pos = 0;
		}

		/*size_t i;*/

		for (i = buffer_pos; i < (size_t)bytes_read; i++)
		{
			if (buffer[i] == '\n')
			{
				size_t line_length = i - buffer_pos + 1;
				char *new_line = realloc(line, line_size + line_length);

				if (new_line == NULL)
				{
					free(line);
					return (NULL);
				}
				line = new_line;


				memcpy(line + line_size, buffer + buffer_pos, line_length);

				line_size += line_length;
				buffer_pos = i + 1;
				return (line);
			}
		}


		/*size_t remaining_bytes = (size_t)bytes_read - buffer_pos;*/
		/*char *new_line = realloc(line, line_size + remaining_bytes);*/

		if (new_line == NULL)
		{
			free(line);
			return (NULL);
		}
		line = new_line;

		memcpy(line + line_size, buffer + buffer_pos, remaining_bytes);
		line_size += remaining_bytes;
		buffer_pos = bytes_read;
	}
}

/**
 * main5 - Simple shell program
 *
 * Return: Always 0
 */
int main5(void)
{
	char *line;

	while (1)
	{
		printf("$ ");
		line = custom_getline();
		if (line == NULL)
		{
			break;
		}
		printf("You entered: %s", line);
		free(line);
	}

	return (0);
}
