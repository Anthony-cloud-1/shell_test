#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include<sys/types.h>
#include<sys/wait.h>
/**
 * executePipedCommands - execute piped cmds
 * @firstCommand: 1st cmd
 * @secondCommand: 2nd cmd
 *
 * Return: Always 0
 */
void executePipedCommands(char **firstCommand, char **secondCommand);

void executePipedCommands(char **firstCommand, char **secondCommand)
{
	int pipefd[2];
	pid_t child1, child2;

	if (pipe(pipefd) < 0)
	{
		printf("\nError: Pipe initialization failed");
		return;
	}
	child1 = fork();
	if (child1 < 0)
	{
		printf("\nError: Forking child process failed");
		return;
	}

	if (child1 == 0)
	{
		/*
		 * Child 1 executing the first command
		 *It only needs to write at the write end
		 */
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		if (execvp(firstCommand[0], firstCommand) < 0)
		{
			printf("\nError: Failed to execute the first command");
			exit(0);
		}
	}
	else
	{
		/*
		 * Parent executing
		 */
		child2 = fork();

		if (child2 < 0)
		{
			printf("\nError: Forking child process failed");
			return;
		}

		/*
		 * Child 2 executing the second command
		 *It only needs to read at the read end
		 */
		if (child2 == 0)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			if (execvp(secondCommand[0], secondCommand) < 0)
			{
				printf("\nError: Failed to execute the second command");
				exit(0);
			}
		}
		else
		{
			/*
			 * Parent executing, waiting for two children
			 */
			wait(NULL);
			wait(NULL);
		}
	}
}
