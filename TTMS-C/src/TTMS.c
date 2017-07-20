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


//定义全局变量，用于存储登陆用户信息
account_t gl_CurUser={0, USR_ANOMY, "Anonymous",""};

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);


	printf("\n\t\t★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n");
	printf("\t\t\t\t\t\t 魔仙堡剧院欢迎您  \n\n");
	printf("\t\t★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n\n");
	printf("\n");
	printf("\n\n\n\t\t\t\t\t[N]\t\t匿名进入\n");
	printf("\n\n\n\t\t\t\t\t[S]\t\t实名进入\n");

	printf("\n\n\n\t\tжжжжжжжжжжжжжжжжжжжжжжжжжжжжжжжжжжжжжжжжжжжж\n");


	char ch;
	do
	{
		ch=getch();
	} while(ch!='n'&&ch!='N'&&ch!='s'&&ch!='S');
	fflush(stdin);

	if(ch=='S'||ch=='s')
	{
		if(!SysLogin()) {
			printf("\n对不起您无权登录本系统请按任意键退出......\n");
			getchar();
			exit(0);
		}
	}

	Main_Menu();
	return EXIT_SUCCESS;
}
