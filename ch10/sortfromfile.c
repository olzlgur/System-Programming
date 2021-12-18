// author: 2019117891_이지혁
// datetime:2021-11-21 10:32  

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h> // 헤더파일 선언

int main(int argc, char *av[])
{
	FILE *fp;
	char line[20];
	char buffer[100];
	char tmp;
	char buffer2[100];
	int i,j,k; // 필요한 변수들 선언
	
	if( (fp = open(av[1], O_RDONLY)) == NULL)
	{
		printf("error");
		exit(1);
	} // 입력받은 파일 오픈
	read(fp, buffer, 100); // 파일에서 데이터 읽어서 버퍼에 저장
	
	for(i = strlen(buffer); i > 1; i--)
	{
		for(j = 1; j < i; j++)
		{
			if( buffer[j-1] > buffer[j] )
			{
				tmp = buffer[j-1];
				buffer[j-1] = buffer[j];
				buffer[j] = tmp;
			}
		}
	}  // 데이터가 저장되어있는 버퍼 정렬
	
	k=0;
	for(i = 0; i < strlen(buffer); i++ ){
		if(buffer[i] != ' ' && buffer[i] !='\n'){
			buffer2[k] = buffer[i];
			k++;
		}
	} // 공백문자 삭제
	
	for(int i=0; i < strlen(buffer); i++)
	{
		printf("%c ", buffer2[i]);
	} // 출력
	printf("\n");
}