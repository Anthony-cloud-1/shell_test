#include "shell.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
/**
 * main - Simple shell program
 *
 * Return: Always 0
 */
extern char **environ;

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	int status;
	pid_t child_pid;

	char *path = getenv("PATH");
	setenv("PATH", "/bin:/usr/bin", 1);

	while (1)
	{
		printf("$ "); /* Display prompt */
		if (getline(&line, &len, stdin) == -1)
			break; /* Exit on Ctrl+D or EOF */

		if (line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';

		if ((child_pid = fork()) == -1)
		{
			perror("fork");
			continue;
		}

		if (child_pid == 0)
		{
			char *args[2];
			args[0] = line;
			args[1] = NULL;
			execve(line, args, environ);

			perror(line);
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
		}

		free(line); /* Free allocated memory */
	}

	return (0);
}
