#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include <libgen.h>
#include<sys/types.h>
#include<sys/wait.h>
/**
 * executeCommand - execute user cmds
 * @commandTokens: cmd tokens
 *
 * Return: void
 */
void executeCommand(char **commandTokens)
{
	pid_t childPid = fork();

	if (childPid == -1)
	{
		fprintf(stderr, "%s: Failed forking child process\n", basename(commandTokens[0]));
		return;
	}
	else if (childPid == 0)
	{
		if (execvp(commandTokens[0], commandTokens) < 0)
		{
			fprintf(stderr, "%s: not found\n", basename(commandTokens[0]));
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		/*
		 * Wait for the child process to terminate
		 */
		wait(NULL);
		return;
	}
}
