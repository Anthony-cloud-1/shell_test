#include "shell.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
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
	char *token;
	char *args[1024];
	int arg_count = 0;

	char *path = "../usr/bin";
	setenv("PATH", path, 1);

	while (1)
	{
		printf("$ "); /* Display prompt */
		if (getline(&line, &len, stdin) == -1)
			break; /* Exit on Ctrl+D or EOF */

		line[strcspn(line, "\n")] = '\0';

		/*
		* char *token;
		char *args[1024];
		int arg_count = 0;*/

		token = strtok(line, " ");
		while (token != NULL)
		{
			args[arg_count] = token;
			arg_count++;
			token = strtok(NULL, " ");
		}

		args[arg_count] = NULL;

		if (arg_count > 0)
		{
			if (strcmp(args[0], "exit") == 0)
			{
				free(line);
				exit(0);
			}
			else if (strcmp(args[0], "env") == 0)
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
				char *command_path = args[0];

				if (access(command_path, F_OK) == 0)
				{
					pid_t child_pid = fork();

					if (child_pid == -1)
					{
						perror("fork");
						exit(EXIT_FAILURE);
					}
					if (child_pid == 0)
					{
						execve(command_path, args, environ);
						perror("execve");
						exit(EXIT_FAILURE);
					}
					else
					{
						int status;

						wait(&status);
					}
				}
				else
				{
					printf("Command not found: %s\n", args[0]);
				}
			}
		}

		free(line); /* Free allocated memory */
	}

	return (0);
}
