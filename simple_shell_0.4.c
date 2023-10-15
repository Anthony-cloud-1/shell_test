#include "shell.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
/**
 * main3 - Simple shell program
 *
 * Return: Always 0
 */
int main3(void)
{
	char *line = NULL;
	size_t len = 0;
	char *token;

	char *path = "../bin";
	setenv("../bin", path, 1);

	while (1)
	{
		printf("$ "); /* Display prompt */
		if (getline(&line, &len, stdin) == -1)
			break; /* Exit on Ctrl+D or EOF */

		/* Remove trailing newline character */
		line[strcspn(line, "\n")] = '\0';

		/* Handle 'exit' built-in command */
		if (strcmp(line, "exit") == 0)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}

		/* Tokenize the command line */
		token = strtok(line, " ");
		while (token != NULL)
		{
			/* Search for the command in the PATH */
			char *command_path = token; /* For simplicity, assume the token is the command name */

			/* Check if the command exists in PATH before calling fork */
			if (access(command_path, F_OK) == 0)
			{
				/* Execute the command with arguments */
				/* Display output */
				printf("Command: %s\n", token);
			}
			else
			{
				/* Print an error message if the command doesn't exist */
				printf("Command not found: %s\n", token);
				break;
			}

			token = strtok(NULL, " ");
		}

		free(line); /* Free allocated memory */
	}

	return (EXIT_SUCCESS);
}
