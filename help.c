#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
/**
 * shellHelp - Simple help display
 *
 * Return: void
 */
void shellHelp(void)
{
	printf("\nList of Commands supported:");
	printf("\n>cd");
	printf("\n>ls");
	printf("\n>exit");
	printf("\n>all other general commands available in UNIX shell");
	printf("\n>pipe handling");
	printf("\n>improper space handling\n");
}
