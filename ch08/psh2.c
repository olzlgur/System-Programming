/** prompting shell version 2 (psh2.c)
 **
 **	Soloves the 'one-shot'problem of version 1
 **		uses execvp(), but fork()s first so that the
 **		shell waits around to perform another command
 **	New problem: shell catches signals. Run vi, press ^c.
 **/
// author: 2019117891_이지혁
// datetime: 2021-11-04 11:00
/*
   description : 기존의 프로그램을 수정하여 exit를 직접 입력받을 경우에만 프로그램을 종료하도록 하고 Ctrl + C 커맨드를 통해서 쉘이 종료되지 못하도록 한다.
*/
#include	<stdio.h>
#include	<signal.h>
#include	<string.h>
#include	<stdlib.h>

#define	MAXARGS	   20	/* cmdline args	*/
#define	ARGLEN      100	/* token length	*/

char *makestring(char*);
void execute(char*[]);

int main(void)
{
	struct sigaction newhandler;
	void inthandler();
	char	*arglist[MAXARGS+1];		/* an array of ptrs*/
	int	numargs = 0;			/* index into array*/
	char	argbuf[ARGLEN];			/* read stuff here	*/
	char    buf[ARGLEN];
	sigset_t blocked;
	
	newhandler.sa_handler = inthandler;
	newhandler.sa_flags = SA_RESTART;
	
	sigemptyset(&blocked);
	sigaddset(&blocked, SIGQUIT);
	newhandler.sa_mask = blocked;
	sigaction(SIGINT, &newhandler, NULL); //sigaction을 통해서 Ctrl + C 커맨드 시 	
	
	while ( numargs < MAXARGS )
	{	
		printf("Arg[%d]? ", numargs);
		if ( fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n' )
		{	
			strcpy(buf, argbuf);
			printf("\n%s\n", buf);
			buf[strlen(buf) - 1] = '\0';
			if(strcmp(buf,"exit")==0) // 입력받은 문자열이 exit이면 프로그램 종료
				exit(1);
			arglist[numargs++] = makestring(argbuf);
		}
		else if ( numargs > 0 ){		/* any args?	*/
			arglist[numargs]=NULL;	/* close list	*/
			execute( arglist );	/* do it	*/
			numargs = 0;		/* and reset	*/
		}
	}
	return 0;
}

void execute( char *arglist[] )
/*
 *	use fork and execvp and wait to do it
 */
{
	int	pid,exitstatus;				/* of child	*/

	pid = fork();					/* make new process */
	switch( pid ){
		case -1:	
			perror("fork failed");
			exit(1);
		case 0:
			execvp(arglist[0], arglist);		/* do it */
			perror("execvp failed");
			exit(1);
		default:
			while( wait(&exitstatus) != pid )
				;
			printf("child exited with status %d,%d\n",
					exitstatus>>8, exitstatus&0377);
	}
}

char *makestring( char *buf )
/*
 * trim off newline and create storage for the string
 */
{
	char	*cp /* *malloc() */;

	buf[strlen(buf)-1] = '\0';		/* trim newline	*/
	cp = malloc( strlen(buf)+1 );		/* get memory	*/
	if ( cp == NULL ){			/* or die	*/
		fprintf(stderr,"no memory\n");
		exit(1);
	}
	strcpy(cp, buf);		/* copy chars	*/
	return cp;			/* return ptr	*/
}


void inthandler(int s)
{
}