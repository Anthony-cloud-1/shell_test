#include "shell.h"
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_ARGS 64

/**
 * main1 - Simple shell program
 *
 * Return: Always 0
 */
int main1(void)
{
	char *line = NULL;
	size_t len = 0;
	char *path = getenv("PATH");
	setenv("PATH", "/bin:/usr/bin", 1);

	while (1)
	{
		char *token;
		pid_t child_pid;
		int status;
		char *args[MAX_ARGS];
		int arg_count = 0;

		printf("$ "); /* Display prompt */
		if (getline(&line, &len, stdin) == -1)
			break; /* Exit on Ctrl+D or EOF */

		/* Tokenize the input line */
		token = strtok(line, " \n");
		while (token != NULL)
		{
			args[arg_count] = token;
			arg_count++;
			token = strtok(NULL, " \n");
		}

		args[arg_count] = NULL;

		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
		{
			execve(args[0], args, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
		}

		free(line);
	}

	return (0);
}
