#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
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
		printf("\nFailed forking child process..");
		return;
	}
	else if (childPid == 0)
	{
		if (execvp(commandTokens[0], commandTokens) < 0)
		{
			printf("\nCould not execute the command..");
		}
		exit(0);
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
