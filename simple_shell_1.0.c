#include "shell.h"
#include <string.h>
#include <unistd.h>
/**
 * main4 - Simple shell program
 *
 * Return: Always 0
 */
extern char **environ;

int main4(void)
{
	char *line = NULL;
	size_t len = 0;

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
			exit(0);
		}
		/* Handle 'env' built-in command */
		else if (strcmp(line, "env") == 0)
		{
			char **env = environ;

			while (*env)
			{
				printf("%s\n", *env);
				env++;
			}
		}
		else
		{
			/* Tokenize the command line */
			char *token;

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
					printf("Command not found: %s\n", token);
				}

				token = strtok(NULL, " ");
			}
		}

		free(line);
	}

	return (0);
}
