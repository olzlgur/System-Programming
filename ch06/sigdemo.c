#include<stdio.h>
#include<signal.h>

main()
{
	void f(int);
	int i;
	
	signal(SIGINT, f);
	for(i=0; i<5; i++){
		printf("hello\n");
		sleep(1);
		fflush(stdout);
	}
}

void f(int signum)
{
	int input;
	printf("\nInterrupt OK to quit (y/n)?\n");
	input=getchar();
	if(input=='y')     // y를 입력받았을 경우 프로그램 종료
	{
		exit(1);
	}
	else
	{
		return 0;
	}
}