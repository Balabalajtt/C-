#include <stdio.h>

#include "Main_Menu.h"
#include "Schedule_UI.h"
#include "Studio_UI.h"
#include "Play_UI.h"
#include "Queries_Menu.h"
#include "Account_UI.h"
#include "Sale_UI.h"
#include "SalesAnalysis_UI.h"


#include<windows.h>
#include<conio.h>
void Main_Menu(void) {




	char choice;
	do {
		system("cls");
/*		printf("\n==================================================================\n");
		printf("**************** Theater Ticket Management System ****************\n");
		printf("[S]tudio Management.\n");
		printf("[P]lay Management.\n");
		printf("[T]icket Sale.\n");
		printf("[R]eturn Ticket.\n");
		printf("[Q]ueries\n");
		printf("Ra[n]king and Statistics.\n");
		printf("[A]ccount Management.\n");
		printf("[E]xist.\n");
		printf("\n==================================================================\n");
		printf("Please input your choice:");
*/
/*		printf("\n\t\t���������������������������������������������\n\n");
				printf("\t\t\t\t\t\t ħ�ɱ���Ժ��ӭ��  \n\n");
				printf("\t\t���������������������������������������������\n\n");
				printf("\n");
				printf("\t\t\t\t\t[S]\t\t�ݳ������� \n");
				printf("\n");
				printf("\t\t\t\t\t[P]\t\t��Ŀ����\n");
				printf("\n");
				printf("\t\t\t\t\t[T]\t\tƱ�����\n");
				printf("\n");
				printf("\t\t\t\t\t[R]\t\t��Ʊ����\n");
				printf("\n");
				printf("\t\t\t\t\t[Q]\t\t��ѯ\n");
				printf("\n");
				printf("\t\t\t\t\t[N]\t\t��������\n");
				printf("\n");
				printf("\t\t\t\t\t[A]\t\t�û����� \n");
				printf("\n");
				printf("\t\t\t\t\t[E]\t\t�˳�\n");
				printf("\n");
				printf("\t\t�ااااااااااااااااااااااااااااااااااااااااااا�\n");
				printf("\t\t��������Ҫ�����ҵ��:");
*/




	while(!kbhit()){
		printf("\n\t\t��������������������������������������������\n");
		printf("\t\t��������������������������������������������\n");
		printf("\t\t���                                 ħ�ɱ���Ժ��ӭ��                             ���\n");
		printf("\t\t��������������������������������������������\n");
				printf("\t\t��������������������������������������������\n\n");
				printf("\n");
				printf("\t\t\t\t\t��[S]\t\t�ݳ������� \n");
				printf("\n");
				printf("\t\t\t\t\t��[P]\t\t��Ŀ����\n");
				printf("\n");
				printf("\t\t\t\t\t��[T]\t\tƱ�����\n");
				printf("\n");
				printf("\t\t\t\t\t��[R]\t\t��Ʊ����\n");
				printf("\n");
				printf("\t\t\t\t\t��[Q]\t\t��ѯ\n");
				printf("\n");
				printf("\t\t\t\t\t��[N]\t\t���ݷ���\n");
				printf("\n");
				printf("\t\t\t\t\t��[A]\t\t�û����� \n");
				printf("\n");
				printf("\t\t\t\t\t��[E]\t\t�˳�\n");
				printf("\n");
			//	printf("\t\t�ااااااااااااااااااااااااااااااااااااااااااا�\n");
				printf("\t\t��������������������������������������������\n\n");printf("\t\t��������������������������������������������\n\n");
				Sleep(50);
				system("cls");
				printf("\n\t\t��������������������������������������������\n");
				printf("\t\t��������������������������������������������\n");
				printf("\t\t���                                 ħ�ɱ���Ժ��ӭ��                             ���\n");
				printf("\t\t��������������������������������������������\n");
				printf("\t\t��������������������������������������������\n\n");
				printf("\n");
				printf("\t\t\t\t\t��[S]\t\t�ݳ������� \n");
				printf("\n");
				printf("\t\t\t\t\t��[P]\t\t��Ŀ����\n");
				printf("\n");
				printf("\t\t\t\t\t��[T]\t\tƱ�����\n");
				printf("\n");
				printf("\t\t\t\t\t��[R]\t\t��Ʊ����\n");
				printf("\n");
				printf("\t\t\t\t\t��[Q]\t\t��ѯ\n");
				printf("\n");
				printf("\t\t\t\t\t��[N]\t\t���ݷ���\n");
				printf("\n");
				printf("\t\t\t\t\t��[A]\t\t�û����� \n");
				printf("\n");
				printf("\t\t\t\t\t��[E]\t\t�˳�\n");
				printf("\n");
			//	printf("\t\t�ااااااااااااااااااااااااااااااااااااااااااا�\n");
				printf("\t\t��������������������������������������������\n\n");printf("\t\t��������������������������������������������\n\n");
				Sleep(50);
				printf("\t\t��������Ҫ�����ҵ��:");
				system("cls");
		}

				printf("\n\t\t���������������������������������������������\n\n");
						printf("\t\t\t\t\t\t ħ�ɱ���Ժ��ӭ��  \n\n");
						printf("\t\t���������������������������������������������\n\n");
						printf("\n");
						printf("\t\t\t\t\t[S]\t\t�ݳ������� \n");
						printf("\n");
						printf("\t\t\t\t\t[P]\t\t��Ŀ����\n");
						printf("\n");
						printf("\t\t\t\t\t[T]\t\tƱ�����\n");
						printf("\n");
						printf("\t\t\t\t\t[R]\t\t��Ʊ����\n");
						printf("\n");
						printf("\t\t\t\t\t[Q]\t\t��ѯ\n");
						printf("\n");
						printf("\t\t\t\t\t[N]\t\t���ݷ���\n");
						printf("\n");
						printf("\t\t\t\t\t[A]\t\t�û����� \n");
						printf("\n");
						printf("\t\t\t\t\t[E]\t\t�˳�\n");
						printf("\n");
						printf("\t\t�ااااااااااااااااااااااااااااااااااااااااااا�\n");
						printf("\t\t��������Ҫ�����ҵ��:");












		fflush(stdin);
		choice = getchar();
		switch (choice) {
		case 'S':
		case 's':
			Studio_UI_MgtEntry();
			break;
		case 'P':
		case 'p':
			Play_UI_MgtEntry(0);
			break;
		case 'Q':
		case 'q':
			Queries_Menu();
			break;
		case 'T':
		case 't':
			Sale_UI_MgtEntry();
			break;
		case 'R':
		case 'r':
			Sale_UI_ReturnTicket();
			break;
		case 'N':
		case 'n':
			SalesAanalysis_UI_MgtEntry();
			break;
		case 'A':
		case 'a':
			Account_UI_MgtEntry();
			break;
		}
	} while ('E' != choice && 'e' != choice);
}

