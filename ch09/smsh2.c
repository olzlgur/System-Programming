/** smsh2.c small-shell version 2
 **		small shell that supports command line parsing
 **		and if..then..else..fi logic (by calling process())
 **/
// author: 2019117891_이지혁
// datetime: 작2021-11-13-23:00
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	<sys/wait.h>
#include	"smsh.h"

#define DFL_PROMPT	"> "

int main(void)
{
	char	*cmdline, *prompt, **arglist;
	int 	result, process(char **);
	void	setup();

	prompt = DFL_PROMPT;
	setup();

	while( (cmdline = next_cmd(prompt, stdin) ) != NULL ){
		if( (arglist = splitline(cmdline)) != NULL ){
			result = process(arglist);
			freelist(arglist);
		}

		free(cmdline);
	}

	return 0;
}		

void setup(void)
/*
 * purpose: initialize shell
 * returns: nothing. calls fatal() if trouble
 */
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}


void fatal(char *s1, char *s2, int n)
{
	fprintf(stderr, "Error: %s, %s\n", s1, s2);
	exit(n);
}


