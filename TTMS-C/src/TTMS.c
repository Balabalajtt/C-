/*
 ============================================================================
 Name        : TTMS.c
 Author      : shu xinfeng
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <io.h>
#include <conio.h>
#include "./View/Main_Menu.h"
#include "./View/Account_UI.h"


//����ȫ�ֱ��������ڴ洢��½�û���Ϣ
account_t gl_CurUser={0, USR_ANOMY, "Anonymous",""};

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);


	printf("\n\t\t���������������������������������������������\n\n");
	printf("\t\t\t\t\t\t ħ�ɱ���Ժ��ӭ��  \n\n");
	printf("\t\t���������������������������������������������\n\n");
	printf("\n");
	printf("\n\n\n\t\t\t\t\t[N]\t\t��������\n");
	printf("\n\n\n\t\t\t\t\t[S]\t\tʵ������\n");

	printf("\n\n\n\t\t�ااااااااااااااااااااااااااااااااااااااااااا�\n");


	char ch;
	do
	{
		ch=getch();
	} while(ch!='n'&&ch!='N'&&ch!='s'&&ch!='S');
	fflush(stdin);

	if(ch=='S'||ch=='s')
	{
		if(!SysLogin()) {
			printf("\n�Բ�������Ȩ��¼��ϵͳ�밴������˳�......\n");
			getchar();
			exit(0);
		}
	}

	Main_Menu();
	return EXIT_SUCCESS;
}
