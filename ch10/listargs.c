/* listargs.c
 *	print the number of command line args, list the agrs,
 *	then print a message to stderr
 */

#include <stdio.h>

void main( int ac, char *av[])
{
	int i;
	printf("Number of args: %d, Args are:\n", ac);

	for ( i = 0; i<ac; i++ )
		printf("args[%d] %s\n", i, av[i]);

	fprintf(stderr, "This message is sent to stderr.\n");
}
