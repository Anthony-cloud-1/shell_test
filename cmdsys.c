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
 * @programName: to display prog name
 * Return: void
 */
void executeCommand(char **commandTokens, char *programName)
{
	pid_t childPid = fork();

	if (childPid == -1)
	{
		fprintf(stderr, "%s: Failed forking child process\n", programName);
		return;
	}
	else if (childPid == 0)
	{
		/*
		 * Redirect stderr to stdout in the child process
		 */
		dup2(STDOUT_FILENO, STDERR_FILENO);

		if (commandTokens[0][0] == '"' && commandTokens[0][strlen(commandTokens[0]) - 1] == '"')
		{
			memmove(commandTokens[0], commandTokens[0] + 1, strlen(commandTokens[0]) - 2);
			commandTokens[0][strlen(commandTokens[0]) - 2] = '\0';
		}

		if (execvp(commandTokens[0], commandTokens) < 0)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", programName, commandTokens[0]);
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		/*
		 * Wait for the child process to terminate
		 */
		wait(NULL); /*wait(&status)*/
		return;

		/*
		 * if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			fprintf(stderr, "Command failed with status %d\n", WEXITSTATUS(status));
		}
		*/

	}
}
