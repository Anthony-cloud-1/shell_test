#include "shell.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
/**
 * main2 - Simple shell program
 * @extern char: environ variable
 * Return: Always 0
 */
extern char **environ;

int main2(void)
{
	char *line = NULL;
	size_t len = 0;
	char *token;
	pid_t child_pid;
	int status;

	char *path = "../bin";
	setenv("../bin", path, 1);

	while (1)
	{
		printf("$ "); /* Display prompt */
		if (getline(&line, &len, stdin) == -1)
			break; /* Exit on Ctrl+D or EOF */

		token = strtok(line, " \n");
		while (token != NULL)
		{
			char *path = getenv("PATH");
			char *dir = strtok(path, ":");

			while (dir != NULL)
			{
				char command_path[1024];

				snprintf(command_path, sizeof(command_path), "%s/%s", dir, token);

				if (access(command_path, F_OK) == 0)
				{
					char **args;
					args = malloc(2 * sizeof(char *));

					if (args == NULL)
					{
						perror("malloc");
						exit(EXIT_FAILURE);
					}
					args[0] = token;
					args[1] = NULL;

					child_pid = fork();

					if (child_pid == -1)
					{
						perror("fork");
						free(args);
						exit(EXIT_FAILURE);
					}
					if (child_pid == 0)
					{
						/*char *args[] = {token, NULL};*/

						execve(command_path, args, environ);
						perror(command_path);
						free(args);
						exit(EXIT_FAILURE);
					}
					else
					{
						waitpid(child_pid, &status, 0);
					}
					free(args);
					break;
				}

				dir = strtok(NULL, ":");
			}

			if (dir == NULL)
			{
				printf("Command not found: %s\n", token);
			}

			token = strtok(NULL, " \n");
		}

		free(line);
	}

	return (0);
}
