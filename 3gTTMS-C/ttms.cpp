/*��׼�����*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>
#include<math.h>
#define HALL_NUM 8

time_t timep;
struct tm *p;

/*����Ա*/
typedef struct STAFF {
	char staff_id[9];
//	char staff_name[20];
	char staff_password[21];
	int staff_limit;//����ԱȨ�� 1����� 2���μ�
	struct STAFF *link;
}Staff;

/*�˿�*/
typedef struct CUSTOMER {
	char customer_phonenumber[12];
//	char customer_name[20];
	char customer_password[21];
//	char question[100];
//	char answer[100];
	struct CUSTOMER *link;
}Customer;

/*��ǰ��¼�û�*/
typedef struct USER {
	char user_id[20];
	char user_password[20];
	char user_limit;
	Staff *present_staff_information;
	Customer *present_customer_information;
}User;

/*��Ӱ��Ϣ*/
typedef struct MOVIE {
	char movie_id[20];
	char movie_name[50];
	char starring[50];//������Ϣ
	char derector[50];//������Ϣ
	struct DATE {
		int year;
		int month;
		int day;
	}Date;
	char nation[50];
	char language[50];
	char length[4];
	char type[50];
	char movie_description[100];
	int booking;//Ʊ��
//	float average;//ƽ����
	struct MOVIE *link;
}Movie;

/*����*/
typedef struct HALL {
	int hall_id;
	int seat_sum;
//	char hall_description[100];

	struct HALL *link;
}Hall;

/*��λ*/
typedef struct SEAT {
	int seat_id;
	int show_id;
	int row;
	int ver;
	int seat_status;
	struct SEAT *link;
}Seat;

/*����*/
typedef struct SHOW {
	char show_id[50];//���κ�
	char film_id[50];
	int hall_id;//����
	float cost;//Ʊ��
	struct BEGINTIME {//����ʱ��
		int year;
		int month;
		int day;
		int hour;
		int minute;
	}begintime;
	struct SHOW *link;
}Show;

/*����*/
typedef struct ORDER {
//	int order_id;
	char customer_id[20];
//	Movie *movie_o;
	char movie_name[50];
	int hall_id;//����
	float cost;//Ʊ��
	struct BEGINTIME {//����ʱ��
		int year;
		int month;
		int day;
		int hour;
		int minute;
	}begintime;
	int seat_id;
	char pay_status;
	char ticket_code[10];
	struct ORDER *link;
}Order;





/*ȫ�ֱ���*/
User *user = (User *)malloc(sizeof(User));

Customer *customer_head = (Customer *)malloc(sizeof(Customer));
Staff *staff_head = (Staff *)malloc(sizeof(Staff));
Movie *movie_head = (Movie *)malloc(sizeof(Movie));
Show *show_head = (Show *)malloc(sizeof(Show));
Hall *hall_head = (HALL *)malloc(sizeof(HALL));
Order *order_head = (ORDER *)malloc(sizeof(ORDER));
/*��������ʱ��*/




void init(void);
void ending(void);
void mygets(char* bu, int max, FILE *fp);


void sign_ui(void);

void exit_ui(void);
void sign_in_ui(void);
void sign_up_ui(void);

void sign_in_customer(void);
void sign_in_staff(void);


void su_staff_ui(void);

void movie_manage_ui(void);
void movie_addition(void);
void movie_removation(void);
void movie_revise(void);
void movie_check(void);

void show_manage_ui(void);
void show_addition(void);
void show_removation(void);
void show_revise(void);
void show_check(void);

void staff_manage_ui(void);
void staff_addition(void);
void staff_removation(void);
void staff_revise(void);
void staff_check(void);

void order_manage_ui(void);

void input_password(char *);



void customer_ui(void);
void customer_movie_ui(void);
void customer_movie_present(void);
void customer_movie_advance(void);
void customer_movie_rank(void);

void  customer_order_ui(void);

void customer_movie_rank_all(void);
void customer_movie_rank_now(void);

void sort_movie(void);



/*���*/
int main(void)
{
	printf("."); Sleep(150);
	printf("."); Sleep(150);
	printf("."); Sleep(150);
	printf("."); Sleep(150);
	printf("."); Sleep(150);
	printf("."); Sleep(150);

	init();
	
	sign_ui();

	//ending();

	return 0;
}


/*��ʼ*/
void init(void)
{
	/*��ʼ��ͷָ��*/
	customer_head->link = NULL;
	staff_head->link = NULL;
	movie_head->link = NULL;
	hall_head->link = NULL;
	show_head->link = NULL;
	order_head->link = NULL;
	/*�����������˺�*/

/*
	Customer *my_customer = (Customer *)malloc(sizeof(Customer));
	customer_head->link = my_customer;
	strcpy(my_customer->customer_phonenumber, "18792898826");
	strcpy(my_customer->customer_password, "199898");
	my_customer->link = NULL;

	Staff *my_staff = (Staff *)malloc(sizeof(Staff));
	staff_head->link = my_staff;
	strcpy(my_staff->staff_id, "04163216");
	strcpy(my_staff->staff_password, "199898");
	my_staff->staff_limit = 1;
	my_staff->link = NULL;
*/


	/*Ӱ����ʼ   1-8���� */
	int n = 1;
	Hall *init_hall;
	Hall *hall_p=hall_head;
	while (n<=HALL_NUM)
	{
		init_hall = (Hall *)malloc(sizeof(Hall));
		init_hall->hall_id = n;
		init_hall->seat_sum = 100;
		hall_p->link = init_hall;
		hall_p = init_hall;
		init_hall->link = NULL;
		n++;
	}


	/*���ļ�*/
	FILE *fp;

	/*�˿��˻�*/
	Customer *customer_p;
	for (customer_p = customer_head; customer_p->link != NULL; customer_p = customer_p->link);
	Customer *init_customer;
	
	if ((fp = fopen("Customer.txt", "r")) == NULL)//���ļ�
	{
		printf("Customer.txt�ļ������ڻ��ļ���ʧ�ܣ�\n");
		Sleep(800);
		exit(1);
	}
	else if (feof(fp) == 1)//�ж��ļ��Ƿ�Ϊ��
	{
		printf("Customer.txt�ļ�Ϊ�գ�\n");
		Sleep(800);
	}
	else {//�ļ���Ϊ��ʱ
		init_customer = (Customer *)malloc(sizeof(Customer));
		while (fread(init_customer, sizeof(Customer), 1, fp) == 1)
		{
			customer_p->link = init_customer;
			init_customer->link = NULL;
			customer_p = init_customer;
			init_customer = (Customer *)malloc(sizeof(Customer));
		}
		
		free(init_customer);
		fclose(fp);
	}
	
	
	/*Ա���˻�*/
	Staff *staff_p;
	for (staff_p = staff_head; staff_p->link != NULL; staff_p = staff_p->link);
	Staff *init_staff;

	if ((fp = fopen("Staff.txt", "r")) == NULL)//���ļ�
	{
		printf("Staff.txt�ļ�����զ���ļ���ʧ�ܣ�\n");
		Sleep(800);
		exit(1);
	}
	else if (feof(fp) == 1)//�ж��ļ��Ƿ�Ϊ��
	{
		printf("Staff.txt�ļ�Ϊ�գ�\n");
		Sleep(800);
	}
	else {//�ļ���Ϊ��ʱ
		init_staff = (Staff *)malloc(sizeof(Staff));
		while (fread(init_staff, sizeof(Staff), 1, fp) == 1)
		{

			staff_p->link = init_staff;
			init_staff->link = NULL;
			staff_p = init_staff;
			init_staff = (Staff *)malloc(sizeof(Staff));
		}

		free(init_staff);
		fclose(fp);
	}
	
	/*����ӰƬ*/
	Movie *movie_p;
	for (movie_p = movie_head; movie_p->link != NULL; movie_p = movie_p->link);
	Movie *init_movie;

	if ((fp = fopen("Movie.txt", "rb")) == NULL)//���ļ�
	{
		printf("Movie.txt�ļ�����զ���ļ���ʧ�ܣ�\n");
		Sleep(800);
		exit(1);
	}
	else if (feof(fp) == 1)//�ж��ļ��Ƿ�Ϊ��
	{
		printf("Movie.txt�ļ�Ϊ�գ�\n");
		Sleep(800);
	}
	else {//�ļ���Ϊ��ʱ
		init_movie = (Movie *)malloc(sizeof(Movie));

		while (fread(init_movie, sizeof(Movie), 1, fp)==1)
		{

			movie_p->link = init_movie;
			init_movie->link = NULL;
			movie_p = init_movie;
			init_movie = (Movie *)malloc(sizeof(Movie));

		}
		free(init_movie);
		fclose(fp);
	}
	

	/*����*/

	
	Show *show_p;
	for (show_p = show_head; show_p->link != NULL; show_p = show_p->link);
	Show *init_show;

	if ((fp = fopen("Show.txt", "r")) == NULL)//���ļ�
	{
		printf("Show.txt�ļ�����զ���ļ���ʧ�ܣ�\n");
		Sleep(800);
		exit(1);
	}
	else if (feof(fp) == 1)//�ж��ļ��Ƿ�Ϊ��
	{
		printf("Show.txt�ļ�Ϊ�գ�\n");
		Sleep(800);
	}
	else {//�ļ���Ϊ��ʱ
		init_show = (Show *)malloc(sizeof(Show));
		while (fread(init_show, sizeof(Show), 1, fp) == 1)
		{
			show_p->link = init_show;
			init_show->link = NULL;
			show_p = init_show;
			init_show = (Show *)malloc(sizeof(Show));
		}
		free(init_show);
		fclose(fp);
	}




	/*����*/
	Order *order_p;
	for (order_p = order_head; order_p->link != NULL; order_p = order_p->link);
	Order *init_order;

	if ((fp = fopen("Order.txt", "rb")) == NULL)//���ļ�
	{
		printf("Order.txt�ļ�����զ���ļ���ʧ�ܣ�\n");
		Sleep(800);
		exit(1);
	}
	else if (feof(fp) == 1)//�ж��ļ��Ƿ�Ϊ��
	{
		printf("Order.txt�ļ�Ϊ�գ�\n");
		Sleep(800);
	}
	else {//�ļ���Ϊ��ʱ
		init_order = (Order *)malloc(sizeof(Order));
		while (fread(init_order, sizeof(Order), 1, fp) == 1)
		{
			order_p->link = init_order;
			init_order->link = NULL;
			order_p = init_order;
			init_order = (Order *)malloc(sizeof(Order));
		}
		free(init_order);
		fclose(fp);
	}
	














	/*ɾ������֮ǰ���ų�*/
	time(&timep);
	p = localtime(&timep);

//	printf("%d %d %d",(1900 + p->tm_year), (1 + p->tm_mon), p->tm_mday);
//	printf(" %d %d ", p->tm_hour, p->tm_min);
//	Sleep(1000);
	Show *showp;
	Show *qian;
	Show *freep;
	long int a, b;
	a = (1900 + p->tm_year) * 365 + (p->tm_mon) * 30 + p->tm_mday;
	for (qian=show_head,showp = show_head->link; showp != NULL; showp = showp->link)
	{
//		printf("*****\n");
//		Sleep(800);
		b = (showp->begintime.year) * 365 + (showp->begintime.month-1) * 30 + showp->begintime.day;
//		printf("%d %d", a, b);
		if (a > b)
		{
//			printf("****11*\n");
			qian->link = showp->link;
			freep = showp;
			showp = qian;
			free(freep);
		}
		else
		{
			qian = qian->link;
		}
	
	}


}


/*111111111111111111111111111��¼ע�����*/
void sign_ui(void)
{
	char key;
	while (1)
	{
		do {
			system("cls");
			printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
			printf("\t\t\t��              �� ӭ �� �� �� Ժ �� �� ϵ ͳ            �� \n");
			printf("\t\t\t�d = = = = = = = = = = = = = = = = = = = = = = = = = = = �g\n");
			printf("\t\t\t��                                                       ��\n");
			printf("\t\t\t��                                                       ��\n");
			printf("\t\t\t��     �� 1 �� ��  ¼                                    ��\n");
			printf("\t\t\t��                                                       ��\n");
			printf("\t\t\t��     �� 2 �� ע  ��                                    ��\n");
			printf("\t\t\t��                                                       ��\n");
			printf("\t\t\t��     �� 0 �� ��  ��                                    ��\n");
			printf("\t\t\t��                                                       ��\n");
			printf("\t\t\t��                                                       ��\n");
//			printf("\t\t\t��       �q�Шr��                                        ��\n");
//			printf("\t\t\t��       �q�q �Шr ��q��r                              ��\n");
//			printf("\t\t\t��       �t ----�s/���Ũ�\\                               ��\n");
//			printf("\t\t\t��       ~~~~~~~~~~��~~��~~~~~~~~~~~                     ��\n");
			printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
			printf("\t\t\t������ѡ�");
			key = getch();
		} while (key != '1'&&key != '2'&&key != '0');
		
		switch (key)
		{
		case '1':
			sign_in_ui();
			break;
		case '2':
			sign_up_ui();
			break;
		case '0':
			exit_ui();
			break;
		}
	
	}

}

/*22222222222222222222�˳�ϵͳ����*/
void exit_ui(void)
{
	char key;

	do {
		system("cls");
		printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
		printf("\t\t\t��              ȷ �� �� �� �� Ժ �� �� ϵ ͳ            �� \n");
		printf("\t\t\t�d = = = = = = = = = = = = = = = = = = = = = = = = = = = �g\n");
		printf("\t\t\t��                                                       ��\n");
		printf("\t\t\t��                                                       ��\n");
		printf("\t\t\t��     �� 1 �� ��  ��                                    ��\n");
		printf("\t\t\t��                                                       ��\n");
		printf("\t\t\t��     �� 0 �� ��  ��                                    ��\n");
		printf("\t\t\t��                                                       ��\n");
		printf("\t\t\t��                                                       ��\n");
		printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
		printf("\t\t\t������ѡ�");

		key=getch();
	} while (key != '1'&& key != '0');

	if (key == '1')
	{
		system("cls");
		printf("\n\n");
		printf("\t\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
		printf("\t\t\t\t��                                                 ��\n");
		printf("\t\t\t\t��            ��  л  ��  ��  ʹ  ��               �� \n");
		printf("\t\t\t\t��                                                 ��\n");
		printf("\t\t\t\t��            �� �� �� �� �� �� �� ��              ��\n");
		printf("\t\t\t\t��                                                 ��\n");
		printf("\t\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
		printf("\n\n\n\n\n\t\t");
		exit(1);
	}
}

/*222222222222222222222��½���ѡ�����*/
void sign_in_ui(void)
{
	char key;
//	while (1)
//	{
		do {
			system("cls");
			printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
			printf("\t\t\t��              �� ѡ �� �� �� �� ¼ �� ��               �� \n");
			printf("\t\t\t�d = = = = = = = = = = = = = = = = = = = = = = = = = = = �g\n");
			printf("\t\t\t��                                                       ��\n");
			printf("\t\t\t��                                                       ��\n");
			printf("\t\t\t��     �� 1 �� ��  ��                                    ��\n");
			printf("\t\t\t��                                                       ��\n");
			printf("\t\t\t��     �� 2 �� Ա  ��                                    ��\n");
			printf("\t\t\t��                                                       ��\n");
			printf("\t\t\t��     �� 0 �� ��  ��                                    ��\n");
			printf("\t\t\t��                                                       ��\n");
			printf("\t\t\t��                                                       ��\n");
			printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
			printf("\t\t\t������ѡ�");
			key = getch();
		} while (key != '1'&&key != '2'&&key != '0');

		switch (key)
		{
		case '1':
			sign_in_customer();
			break;
		case '2':
			sign_in_staff();
			break;
		case '0':
			return;
		}
//	}
	return;
}

/*3333333333333333333333�˿͵�¼����*/
void sign_in_customer(void)
{
	Customer *p;//���������˿��˺�����
	int count = 3;//�������

	while (count--)
	{

		system("cls");
//		printf("���ͻ�����,���¼����\n");
//		printf("����%d�λ��᳢�Ե�¼\n�������꽫�Զ��˳�����\n", count+1);
		printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
		printf("\t\t\t��                     ��    ¼                      ��\n");
		printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
		printf("\n\n");
		printf("\t\t\t\t�� �ֻ��ţ�");
		char ch;
		int i = 0;
		while (ch = getch())
		{

			if (ch == '\r' && i==11)
			{
				user->user_id[i] = '\0';
				break;
			}

			if (ch == '\b')
			{
				if (i == 0)
				{
					printf("\a");
					continue;
				}
				printf("\b \b");
				i--;
				continue;
			}
			if (i >= 11)
			{
				printf("\a");
				continue;
			}
			if (ch >= '0'&&ch <= '9')
			{
				putchar(ch);
				user->user_id[i] = ch;
				i++;
			}
		}

		printf("\n\n\n\t\t\t\t�� ���룺  ");
		input_password(user->user_password);
		printf("\n\n\n\n\n\n");
		/*��֤�˺�����*/
		int flag;
		for (flag=0,p = customer_head->link; p != NULL; p = p->link)
		{
			
			if (strcmp(p->customer_phonenumber, user->user_id) == 0)
			{
				
				if (strcmp(p->customer_password, user->user_password) == 0)
				{
					user->present_customer_information = p;
					/*�˿͵�¼�ɹ��ˣ���ת�˿����˵�*/
//					system("cls");
					printf("\t\t\t����������������������������������\n");
					printf("\t\t\t%s�û���¼�ɹ���\n", user->present_customer_information->customer_phonenumber);
					printf("\t\t\t������ת�����Ժ�");
					printf("."); Sleep(500);
					printf("."); Sleep(500);
					printf("."); Sleep(500);
					customer_ui();
					return;
				}
				
				else
				{
					if (count != 0) 
					{
						flag = 1;
						printf("\t\t\t��������������������������\n");
						printf("\t\t\t�� ������������!      \n"); Sleep(800);
						printf("\t\t\t�� [1]�������� [0]���� \n");
						printf("\t\t\t�� ������ѡ�");
						char ch;
						do
						{
							ch = getch();
						} while (ch != '1'&&ch != '0');
						if (ch == '0')return;
						break;
					}
				}

			}
		}

		if (p == NULL&&flag==0&&count!=0)
		{
			printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
			printf("\t\t\t��              ���ֻ�����δע��!                    ��\n");
			printf("\t\t\t��        ��1����������   ��0�� �� ��                ��\n");
			printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
			printf("\t\t\t������ѡ�");
			char ch;
			do
			{
				ch = getch();
			} while (ch != '1'&&ch != '0');
			if (ch == '0')return;
			Sleep(1000);
		}
	}

	system("cls");
	printf("\n\n\n");
	printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
	printf("\t\t\t��              ���ѳ��Ե�¼��ε�¼                 ��\n");
	printf("\t\t\t��                Ϊ�������˺Ű�ȫ                   ��\n");
	printf("\t\t\t��                 ϵͳ���Զ��˳���                  ��\n");
	printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
	Sleep(1000);
	exit(1);

}

/*333333333333333333333Ա����¼����*/
void sign_in_staff(void)
{
	Staff *p;//��������Ա���˺�����
	int count = 3;//�������

	while (count--)
	{
		char ch;
		int i = 0;
		system("cls");
		printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
		printf("\t\t\t��                     ��    ¼                      ��\n");
		printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
		printf("\n\n");
		printf("\t\t\t\t�� ���ţ�");
//		printf("��Ա������,���¼����\n");
//		printf("����%d�λ��᳢�Ե�¼\n�������꽫�Զ��˳�����\n", count+1);
//		printf("\n����(8λ)��");
		while (ch = getch())
		{

			if (ch == '\r' && i == 8)
			{
				user->user_id[i] = '\0';
				break;
			}

			if (ch == '\b')
			{
				if (i == 0)
				{
					printf("\a");
					continue;
				}
				printf("\b \b");
				i--;
				continue;
			}
			if (i >= 8)
			{
				printf("\a");
				continue;
			}
			if (ch >= '0'&&ch <= '9')
			{
				putchar(ch);
				user->user_id[i] = ch;
				i++;
			}
		}

		printf("\n\n\n\t\t\t\t�� ���룺  ");
		input_password(user->user_password);
		printf("\n\n\n");
		/*��֤�˺�����*/
		for (p = staff_head->link; p != NULL; p = p->link)
		{

			if (strcmp(p->staff_id, user->user_id) == 0)
			{

				if (strcmp(p->staff_password,user->user_password) == 0)
				{
					user->present_staff_information = p;
					/*�˿͵�¼�ɹ��ˣ���תԱ�����˵�*/
				//	system("cls");
					printf("\t\t\t����������������������������������\n");
					printf("\n\t\t\tԱ��%s�����ѵ�¼�ɹ���\n", user->present_staff_information->staff_id);
					Sleep(1000);
//					if (p->staff_limit == 1)
						su_staff_ui();
					//else
						//staff_ui();
					return;
				}

				else
				{
					printf("\t\t\t����������������������������������\n");
					printf("\n\t\t\t������������������\n");
					Sleep(500);
					break;
				}

			}
		}

		if (p == NULL)
		{
			printf("\t\t\t����������������������������������\n");
			printf("\n\t\t\t�����˺�����������\n");
			Sleep(500);
		}
	}

	system("cls");
	printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
	printf("\t\t\t��            �� �� �� �� �� ¼ �� ��                ��\n");
	printf("\t\t\t��            Ϊ �� �� �� �� �� �� ȫ                ��\n");
	printf("\t\t\t��             ϵ ͳ �� �� �� �� ��                  ��\n");
	printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
	Sleep(1000);
	exit(1);

}


/*2222222222222222222222222222222ע�����*/
void sign_up_ui(void)
{	

	Customer *new_customer = (Customer *)malloc(sizeof(Customer));

	FILE *fp;
	Customer *customer_p;
	char key;
new_customer_again:
	system("cls");
	printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
	printf("\t\t\t��                     ע    ��                      ��\n");
	printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
	printf("\n\n");
	printf("\t\t\t\t�� �ֻ��ţ�");
//	scanf("%s", new_customer->customer_phonenumber);
	
	char ch;
	int i = 0;

	while (ch = getch())
	{
		if (ch == '\r'&&i == 11)
		{
			new_customer->customer_phonenumber[i] = '\0';
			break;
		}

		if (ch == '\b')
		{
			if (i == 0)
			{
				printf("\a");
				continue;
			}
			printf("\b \b");
			i--;
			continue;
		}
		if (i >= 11)
		{
			printf("\a");
			continue;
		}
		if (ch <= '9'&&ch >= '0')
		{
			new_customer->customer_phonenumber[i] = ch;
			putchar(ch);
			i++;
		}
	}

		printf("\n");
		for (customer_p = customer_head->link; customer_p != NULL; customer_p = customer_p->link)
		{
			if (strcmp(new_customer->customer_phonenumber, customer_p->customer_phonenumber) == 0)
			{
				printf("\n\n\n\n\n");
				printf("\t\t\t��������������������������\n");
				printf("\t\t\t�� ���ֻ�����ע��!      \n\n"); Sleep(500);
				printf("\t\t\t�� [1]�������� [2]ֱ�ӵ�¼ [0]���� \n");
				printf("\t\t\t�� ������ѡ�");
				do
				{
					key = getch();
				} while (key != '0'&&key != '1'&&key != '2');
				if (key == '0')
				{
					free(new_customer);
					return;
				}
				else if (key == '1')
				{
					goto new_customer_again;
				}
				else
				{
					free(new_customer);
					sign_in_customer();
					return;
				}
			}
		}

	passwo:
		printf("\n\n");
		printf("\t\t\t\t�� �� �룺");
		input_password(new_customer->customer_password);
		printf("\n\n");
		printf("\t\t\t\t�� ȷ�����룺");
		char buff[21];
		input_password(buff);
		
		printf("\n");
		if (strcmp(buff, new_customer->customer_password) != 0)
		{
			printf("\t\t\t\t���벻һ�£������ԣ�\n");
			Sleep(800);
			system("cls");

			printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
			printf("\t\t\t��                     ע    ��                      ��\n");
			printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
			printf("\n\n");
			printf("\t\t\t\t�� �ֻ��ţ�%s\n",new_customer->customer_phonenumber);
			goto passwo;
		}

		printf("\n\n\n\n\n");
		printf("\t\t\t��������������������������\n");
		printf("\t\t\t�� [1]ȷ�� [0]���� \n");
		do
		{
			key = getch();
		} while (key != '0'&&key != '1');
		if (key == '0')
		{
			free(new_customer);
			return;
		}
		else
		{
			for (customer_p = customer_head; customer_p->link != NULL; customer_p = customer_p->link);
			customer_p->link = new_customer;
			new_customer->link = NULL;

			if ((fp = fopen("Customer.txt", "w")) == NULL)//���ļ�
			{
				printf("Customer.txt�ļ���ʧ�ܣ�\n");
				Sleep(800);
				exit(1);
			}
			else {//���ļ��ɹ�

				for (customer_p = customer_head->link; customer_p != NULL; customer_p = customer_p->link)
				{
					fwrite(customer_p, sizeof(Customer), 1, fp);
				}

				fclose(fp);
			}

			//system("cls");
			printf("\n\t\t\t%s�û�������ע��ɹ�......\n", new_customer->customer_phonenumber);
			Sleep(1000);
		}
	

}

/*����Ա������*/
void su_staff_ui(void)
{
	char key;
	while (1)
	{
		do {
			system("cls");
			printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
			printf("\t\t\t                  ��ӭ�� %8s                     \n", user->present_staff_information->staff_id);
			printf("\t\t\t�d = = = = = = = = = = = = = = = = = = = = = = = = = �g\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 1 �� ��Ӱ����                        ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 2 �� ���ι���                        ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 3 �� Ա������                        ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 4 �� ��������                        ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 0 ��  �� ��                          ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
			printf("\t\t\t������ѡ�");
			key = getch();
		} while (key != '1'&&key != '2'&&key != '3'&&key != '4'&&key != '0');

		switch (key)
		{
		case '1':
			movie_manage_ui();
			break;
		case '2':
			show_manage_ui();
			break;
		case '3':
			staff_manage_ui();
			break;
		case '4':
			order_manage_ui();
			break;
		case '0':
			exit_ui();
			break;
		}

	}

}

/*��Ӱ*/
void movie_manage_ui(void)
{
	char key;
	while (1)
	{
		do {
			system("cls");

			printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
			printf("\t\t\t��               ��  Ӱ  ��  ��                      ��\n");
			printf("\t\t\t�d = = = = = = = = = = = = = = = = = = = = = = = = = �g\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 1 �� ��ӵ�Ӱ                        ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 2 �� ɾ����Ӱ                        ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 3 �� ��Ӱ�޸�                        ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 4 �� ��Ӱ�鿴                        ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 0 ��  �� ��                          ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
			printf("\t\t\t������ѡ�");
			key = getch();
		} while (key != '1'&&key != '2'&&key != '3'&&key != '4'&&key != '0');
		switch (key)
		{
		case '1':
			movie_addition();
			break;
		case '2':
			movie_removation();
			break;
		case '3':
			movie_revise();
			break;
		case '4':
			movie_check();
			break;
		case '0':
			return;
		}
	}
}

void movie_addition(void)
{

	char ch;
	int count;
	Movie *new_movie = (Movie*)malloc(sizeof(Movie));

	FILE *fp;
	Movie *movie_p;
	char key;

new_movie_again:
	system("cls");

	ch = 'y';
	count = 0;
	printf("\t\t\t�������Ӱ��Ϣ��\n");
//	getchar();
	new_movie->booking = 0;
	printf("\t\t\t��Ӱ����");
	mygets(new_movie->movie_name, 49, stdin);
movie_id_again:
	printf("\t\t\t��ӰID��");
	mygets(new_movie->movie_id, 49, stdin);
	for (movie_p = movie_head->link; movie_p != NULL; movie_p = movie_p->link)
	{
		if (strcmp(movie_p->movie_id, new_movie->movie_id) == 0)
		{
			char i;
			printf("\t\t\tid�ظ���\n");
			printf("\t\t\t��1����������\n��0������\n");
			do {
				i = getch();
			} while (i != '0'&&i != '1');
			if (i == '0')return;
			else
			{
				system("cls");
				printf("\t\t\t�������Ӱ��Ϣ��\n");
				//	getchar();
				printf("\t\t\t��Ӱ����");
				printf("\t\t\t%s\n", new_movie->movie_name);
				goto movie_id_again;
			}
		}
	}

	printf("\t\t\t���ݣ�");
	mygets(new_movie->starring, 49, stdin);
	printf("\t\t\t���ݣ�");
	mygets(new_movie->derector, 49, stdin);
	dateagain:
	printf("\t\t\t��ӳʱ�䣨�� �� �գ���");
	scanf("%d %d %d", &(new_movie->Date.year), &(new_movie->Date.month), &(new_movie->Date.day));
	while ((ch = getchar()) != '\n'&&ch != EOF);
	if (new_movie->Date.year < 1500 || new_movie->Date.month>12 || new_movie->Date.month < 1 || new_movie->Date.day < 1 || new_movie->Date.day>31)
	{
		printf("\t\t\t������������\n");
		goto dateagain;
	}
	printf("\t\t\t���ң�");
	mygets(new_movie->nation,49,stdin);
	printf("\t\t\tƬ�������ӣ���");
//	char ch;
	int i = 0;
	while (ch = getch())
	{
		if (ch == '\r'&&i > 0)
		{
			new_movie->length[i] = '\0';
			break;
		}
		if (ch == '\r'&&i == 0)
		{
			printf("\a");
			continue;
		}
		if (ch == '\b')
		{
			if (i == 0)
			{
				printf("\a");
				continue;
			}
			printf("\b \b");
			i--;
			continue;
		}
		if (i > 2)
		{
			printf("\a");
			continue;
		}
		if (ch>='0'&&ch<='9')
		{
			putchar(ch);
			new_movie->length[i] = ch;
			i++;
		}
	}
	printf("\n");
	printf("\t\t\t���ԣ�");
	mygets(new_movie->language, 49, stdin);
	printf("\t\t\t���ͣ�");
	mygets(new_movie->type,49,stdin);
	printf("\t\t\t��Ӱ��飺");
	mygets(new_movie->movie_description,99,stdin);

	printf("\t\t\t��1��ȷ�����\n");
	printf("\t\t\t��2����������\n");
	printf("\t\t\t��0������\n");
	do 
	{
		key = getch();
	} while (key != '1'&&key != '2'&&key != '0');
	switch (key)
	{
	case '1':
		for (movie_p = movie_head; movie_p->link != NULL; movie_p = movie_p->link);
		movie_p->link = new_movie;
		new_movie->link = NULL;
		if ((fp = fopen("Movie.txt", "w")) == NULL)//���ļ�
		{
			printf("Movie.txt�ļ���ʧ�ܣ�\n");
			Sleep(800);
			exit(1);
		}
		else {//���ļ��ɹ�
			for (movie_p = movie_head->link; movie_p != NULL; movie_p = movie_p->link)
			{
				fwrite(movie_p, sizeof(Movie), 1, fp);
			}
			fclose(fp);
		}
		printf("\t\t\t��ӳɹ���\n");
		Sleep(800);
		break;
	case '2':
		goto new_movie_again;
		break;
	case '0':
		free(new_movie);
		return;
	}

}

void movie_removation(void)
{
	char id[20];
	while (1)
	{
		system("cls");
		printf("\t\t\t�����ӰID��");
		mygets(id, 19, stdin);
		int flag = 0;
		Movie *p;
		for (p = movie_head; p->link != NULL; p = p->link)
		{
			if (strcmp(id, p->link->movie_id) == 0)
			{
				flag = 1;
				break;
			}
		}

		if (flag == 0)
		{
			printf("\t\t\tδ�ҵ�\n");
			printf("\t\t\t��1����������\n��0������\n");
			char i;
			do {
				i = getch();
			} while (i != '0'&&i != '1');
			if (i == '1')continue;
			else return;
		}
		else
		{

			char key;
			Movie *pfree;
			Movie *movie_p;
			FILE *fp;
			do {
				system("cls");
				printf("\t\t\t�Ƿ�ɾ���ε�Ӱ��\n");
				printf("\t\t\t********************************\n");
				printf("\t\t\t��Ӱ����%s\n", p->link->movie_name);
				printf("\t\t\t���ݣ�%s\n", p->link->starring);
				printf("\t\t\t���ݣ�%s\n", p->link->derector);
				printf("\t\t\t��ӳ���ڣ�%d %d %d\n", p->link->Date.year, p->link->Date.month, p->link->Date.day);
				printf("\t\t\t���ң�%s\n", p->link->nation);
				printf("\t\t\t���ԣ�%s\n", p->link->language);
				printf("\t\t\tʱ����%smin\n", p->link->length);
				printf("\t\t\t���ͣ�%s\n",p->link->type);
				printf("\t\t\t��Ӱ������%s\n", p->link->movie_description);
				printf("\t\t\t��ӰID��%s\n", p->link->movie_id);
				printf("\t\t\t********************************\n");
				printf("\t\t\t��1��ȷ�� ��0������\n");

				key = getch();
			} while (key != '1'&&key != '0');
			switch (key)
			{
			case '1':
				pfree = p->link;
				p->link = p->link->link;
				free(pfree);


				if ((fp = fopen("Movie.txt", "w")) == NULL)//���ļ�
				{
					printf("Movie.txt�ļ���ʧ�ܣ�\n");
					Sleep(800);
					exit(1);
				}
				else {//���ļ��ɹ�
					for (movie_p = movie_head->link; movie_p != NULL; movie_p = movie_p->link)
					{
						fwrite(movie_p, sizeof(Movie), 1, fp);
					}
					fclose(fp);
				}
				printf("\t\t\tɾ���ɹ�\n");
				Sleep(500);
				return;
			
			case '0':
				return;
			}
		}
	}
}

void movie_revise(void)
{

	char id[20];
	system("cls");
	printf("\t\t\t��������Ҫ�޸ĵĵ�ӰID��");
	mygets(id, 19, stdin);
	Movie *p ;
	int flag = 0;
	for (p = movie_head->link; p != NULL; p = p->link)
	{

//		printf("id:%s\npid:%s\n\n", id, p->movie_id);
		if (strcmp(id, p->movie_id) == 0)
		{
			flag = 1;
			break;
		}
	}
	if (flag==0)
	{
		printf("\t\t\tδ�ҵ�\n");
		Sleep(800);
		getchar();
	}
	else
	{
		char key;
		while (1)
		{
			int count = 0;
			do {
				system("cls");
				printf("\t\t\t��ѡ����Ҫ�޸ĵ�ѡ�\n\n");
				printf("\t\t\t��1����Ӱ����%s\n", p->movie_name);
				printf("\t\t\t��2�����ݣ�%s\n", p->starring);
				printf("\t\t\t��3�����ݣ�%s\n", p->derector);
				printf("\t\t\t��4����ӳ���ڣ�%d %d %d\n", p->Date.year, p->Date.month, p->Date.day);
				printf("\t\t\t��5�����ң�%s\n", p->nation);
				printf("\t\t\t��6�����ԣ�%s\n", p->language);
				printf("\t\t\t��7��ʱ����%smin\n", p->length);
				printf("\t\t\t��8�����ͣ�%s\n",p->type);
				printf("\t\t\t��9����Ӱ������%s\n", p->movie_description);
				printf("\t\t\t��0�������˳�\n\n");

				key = getch();
			} while (key<'0' || key>'9');
			char ch;
			int i;
			int year, month, day;
			switch (key)
			{
			case '1':
				printf("\t\t\t��1����Ӱ����");
				mygets(p->movie_name, 49, stdin);
				break;

			case '2':
				printf("\t\t\t��2�����ݣ�");
				mygets(p->starring, 49, stdin);
				break;

			case '3':
				printf("\t\t\t��3�����ݣ�");
				mygets(p->derector,49,stdin);
				break;

			case '4':
				dateagain:
				printf("\t\t\t��4����ӳ���ڣ�");
				scanf("%d %d %d", &(year), &(month), &(day));
				while ((ch = getchar()) != '\n'&&ch != EOF);
				if (year < 1500 || month>12 || month < 1 || day < 1 || day>31)
				{
					printf("\t\t\t������������\n");
					goto dateagain;
				}
				p->Date.year = year;
				p->Date.month = month;
				p->Date.day = day;
				break;

			case '5':
				printf("\t\t\t��5�����ң�");
				mygets(p->nation, 49, stdin);
				break;
			case '6':
				printf("\t\t\t��6�����ԣ�");
				mygets(p->language,49,stdin);
				break;
			case '7':
				printf("\t\t\t��7��ʱ����");
//				scanf("%s", p->length);
				i = 0;
				while (ch = getch())
				{
					if (ch == '\r'&&i > 0)
					{
						p->length[i] = '\0';
						break;
					}
					if (ch == '\r'&&i == 0)
					{
						printf("\a");
						continue;
					}
					if (ch == '\b')
					{
						if (i == 0)
						{
							printf("\a");
							continue;
						}
						printf("\b \b");
						i--;
						continue;
					}
					if (i > 2)
					{
						printf("\a");
						continue;
					}
					if (ch >= '0'&&ch <= '9')
					{
						putchar(ch);
						p->length[i] = ch;
						i++;
					}
				}
				break;
			case '8':
				printf("\t\t\t��8�����ͣ�");
				mygets(p->type, 49, stdin);
				break;
			case '9':
				printf("\t\t\t��9����Ӱ������");
				mygets(p->movie_description, 99, stdin);
				break;
			case '0':
				break;
			}
			if (key == '0') 
				break;

		}
		Movie *movie_p;
		FILE *fp;
		if ((fp = fopen("Movie.txt", "w")) == NULL)//���ļ�
		{
			printf("Movie.txt�ļ���ʧ�ܣ�\n");
			Sleep(800);
			exit(1);
		}
		else {//���ļ��ɹ�
			for (movie_p = movie_head->link; movie_p != NULL; movie_p = movie_p->link)
			{
				fwrite(movie_p, sizeof(Movie), 1, fp);
			}
			fclose(fp);
		}
		printf("\t\t\t�޸ĳɹ���\n");
		Sleep(500);

	}



}

void movie_check(void)
{
	system("cls");
	Movie *p;
	for (p = movie_head->link; p != NULL; p = p->link)
	{
		printf("\t\t\t********************************\n");
		printf("\t\t\t��Ӱ����%s\n", p->movie_name);
		printf("\t\t\t���ݣ�%s\n", p->starring);
		printf("\t\t\t���ݣ�%s\n", p->derector);
		printf("\t\t\t��ӳ���ڣ�%d��%d��%d��\n", p->Date.year, p->Date.month, p->Date.day);
		printf("\t\t\t���ң�%s\n", p->nation);
		printf("\t\t\t���ԣ�%s\n", p->language);
		printf("\t\t\tʱ����%smin\n", p->length);
		printf("\t\t\t���ͣ�%s\n",p->type);
		printf("\t\t\t��Ӱ������%s\n", p->movie_description);
		printf("\t\t\t��ӰID��%s\n", p->movie_id);
		printf("\t\t\t********************************\n");
	}

	printf("\t\t\t���������\n");
	getch();

}


/*����*/
void show_manage_ui(void)
{
	char key;
	while (1)
	{
		do {
			system("cls");

			printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
			printf("\t\t\t��               ��  ��  ��  ��                      ��\n");
			printf("\t\t\t�d = = = = = = = = = = = = = = = = = = = = = = = = = �g\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 1 �� ��ӳ���                        ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 2 �� ɾ������                        ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 3 �� �����޸�                        ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 4 �� ���β鿴                        ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 0 ��  �� ��                          ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
			printf("\t\t\t������ѡ�");
			key = getch();
		} while (key != '1'&&key != '2'&&key != '3'&&key != '4'&&key != '0');
		switch (key)
		{
		case '1':
			show_addition();
			break;
		case '2':
			show_removation();
			break;
		case '3':
			show_revise();
			break;
		case '4':
			show_check();
			break;
		case '0':
			return;
		}
	}
}

void show_addition(void)
{

	char key;
	char ch;
	Show *new_show = (Show *)malloc(sizeof(Show));
	FILE *fp;
	Show *show_p;
	Movie *movie_p;
	int flag=0;

	showida:
	system("cls");
	printf("\t\t\t�����볡��id��");
	mygets(new_show->show_id,49,stdin);
	for (show_p = show_head->link; show_p != NULL; show_p = show_p->link)
	{
		if (strcmp(show_p->show_id, new_show->show_id) == 0)
		{
			char i;
			printf("\t\t\tid�ظ���\n");
			printf("\t\t\t��1����������\n\t\t\t��0������\n");
			do {
				i = getch();
			} while (i != '0'&&i != '1');
			if (i == '0')return;
			else
			{
				goto showida;
			}
		}
	}

	newida:
	printf("\t\t\t�������ӰID��");
	mygets( new_show->film_id,49,stdin);
	for (movie_p = movie_head->link; movie_p != NULL; movie_p = movie_p->link)
	{
		if (strcmp(movie_p->movie_id, new_show->film_id) == 0)
		{
			flag = 1;
			break;
		}
	}
//	while ((ch = getchar()) != '\n'&&ch != EOF);

	
	if (flag == 0)
	{
		do
		{
			printf("\t\t\tid�������\n");
			printf("\t\t\t��1���������� ��0������\n");
			key = getch();
		} while (key != '1'&&key != '0');
		if (key == '1')goto newida;
		else return;
	}

	while (1) 
	{
		printf("\t\t\t�������ӳ����ţ�");
		scanf("%d", &(new_show->hall_id));
		if (new_show->hall_id < 1 || new_show->hall_id>8)
		{
			printf("\t\t\t��ӳ��������!\n");
			while ((ch = getchar()) != '\n'&&ch != EOF);
		}
		else break;
	}

	printf("\t\t\t������Ʊ��(����������)��");
	scanf("%f", &(new_show->cost));
	while ((ch = getchar()) != '\n'&&ch != EOF);

	showdata:
	int timeflag=1;
	dateagain:
	printf("\t\t\t�������ڣ�");
	scanf("%d %d %d", &new_show->begintime.year, &new_show->begintime.month, &new_show->begintime.day);
	while ((ch = getchar()) != '\n'&&ch != EOF);
	if (new_show->begintime.year < 1500 || new_show->begintime.month>12 || new_show->begintime.month < 1 || new_show->begintime.day < 1 || new_show->begintime.day>31)
	{
		printf("\t\t\t������������\n");
		goto dateagain;
	}

	if(movie_p->Date.year>new_show->begintime.year||(movie_p->Date.year==new_show->begintime.year&&movie_p->Date.month>new_show->begintime.month)||(movie_p->Date.year==new_show->begintime.year&&movie_p->Date.month==new_show->begintime.month)&& movie_p->Date.day>new_show->begintime.day)
	{
		printf("\t\t\t������������\n");
		goto dateagain;
	}


	timeagain:
	printf("\t\t\t����ʱ�䣺");
	scanf("%d %d", &new_show->begintime.hour, &new_show->begintime.minute);
	while ((ch = getchar()) != '\n'&&ch != EOF);
	if (new_show->begintime.hour < 0 || new_show->begintime.hour>23|| new_show->begintime.minute < 0 || new_show->begintime.minute >59 )
	{
		printf("\t\t\t����ʱ������\n");
		goto timeagain;
	}
	

	timeflag = 1;
	char i;
	long int a, b;
	a = (1900 + p->tm_year) * 365 + (p->tm_mon - 1) * 30 + p->tm_mday;
	b = (new_show->begintime.year) * 365 + (new_show->begintime.month - 1) * 30 + new_show->begintime.day;
//	printf("%d %d %d\n", (1900 + p->tm_year), (p->tm_mon), p->tm_mday);
//	printf("%d %d %d", (new_show->begintime.year), (new_show->begintime.month - 1), new_show->begintime.day);
//	printf("%d %d %d", (1900 + p->tm_year), (1 + p->tm_mon), p->tm_mday);
//	Sleep(5000);
	if (a>b)
	{
		timeflag = 0;
	}
	if (timeflag == 0)
	{
		printf("\t\t\tʱ������\n");
		printf("\t\t\t��1����������ʱ��\n\t\t\t��2��ȫ����������\n\t\t\t��0������\n");
		do {
			i = getch();
		} while (i != '0'&&i != '1'&&i != '2');
		if (i == '0')return;
		else if (i == '1')
		{
			goto showdata;
		}
		else goto showida;
	}

	for (show_p = show_head->link; show_p != NULL; show_p = show_p->link)
	{
		if (show_p->hall_id==new_show->hall_id)
		{

			//printf("��ͬ����");
			//		show_p->begintime.year == new_show->begintime.year&&show_p->begintime.month == new_show->begintime.month&&show_p->begintime.day == new_show->begintime.day
			long int a, b;
			if (show_p->begintime.year == new_show->begintime.year&&show_p->begintime.month == new_show->begintime.month&&show_p->begintime.day == new_show->begintime.day)
			{
				//printf("ͬһ��");
				a = show_p->begintime.hour * 60 + show_p->begintime.minute;
				b = new_show->begintime.hour * 60 + new_show->begintime.minute;
				if (fabs(a - b) < 180)timeflag = 0;
			}
			else if (show_p->begintime.year == new_show->begintime.year&&show_p->begintime.month == new_show->begintime.month)
			{
				//printf("24dian 0dian");
				if (show_p->begintime.day - new_show->begintime.day == 1)
				{
					a = show_p->begintime.hour * 60 + show_p->begintime.minute;
					b = 24 * 60 - (new_show->begintime.hour * 60 + new_show->begintime.minute);
					if (a + b < 180)timeflag = 0;
				}
				else if (show_p->begintime.day - new_show->begintime.day == -1)
				{
					a = 24 * 60 - (show_p->begintime.hour * 60 + show_p->begintime.minute);
					b = new_show->begintime.hour * 60 + new_show->begintime.minute;
					if (a + b < 180)timeflag = 0;
				}
			}
			else if ((show_p->begintime.month == 12 && new_show->begintime.month == 1) || (show_p->begintime.month == 1 && new_show->begintime.month == 12))
			{
			//	printf("12�� 1��");
				if (show_p->begintime.month == 12 && new_show->begintime.month == 1)
				{
					if (show_p->begintime.day == 31 && new_show->begintime.day == 1)
					{
						a = 24 * 60 - (show_p->begintime.hour * 60 + show_p->begintime.minute);
						b = new_show->begintime.hour * 60 + new_show->begintime.minute;
						if (a + b < 180)timeflag = 0;
					}
				}
				else
				{
					if (show_p->begintime.day == 1 && new_show->begintime.day == 31)
					{
						a = show_p->begintime.hour * 60 + show_p->begintime.minute;
						b = 24 * 60 - (new_show->begintime.hour * 60 + new_show->begintime.minute);
						if (a + b < 180)timeflag = 0;
					}
				}
			}
		}



		if (timeflag == 0)
		{
			printf("\t\t\tʱ������\n");
			printf("\t\t\t��1����������ʱ��\n\t\t\t��2��ȫ����������\n\t\t\t��0������\n");
			do {
				i = getch();
			} while (i != '0'&&i != '1'&&i != '2');
			if (i == '0')return;
			else if (i == '1')
			{
				goto showdata;
			}
			else goto showida;
		}
	}

	if (((1900 + p->tm_year) * 365 + (p->tm_mon) * 30 + p->tm_mday) > (new_show->begintime.year) * 365 + (new_show->begintime.month) * 30 + new_show->begintime.day)
	{
		timeflag = 0;
	}


	do 
	{
		printf("\t\t\t��1��ȷ�����\n");
		printf("\t\t\t��2����������\n");
		printf("\t\t\t��0������\n");
		key = getch();
	} while (key != '1'&&key != '2'&&key != '0');
	
	switch (key)
	{
		case '1':
			for (show_p = show_head; show_p->link != NULL; show_p = show_p->link);
			show_p->link = new_show;
			new_show->link = NULL;
			if ((fp = fopen("Show.txt", "w")) == NULL)//���ļ�
			{
				printf("Show.txt�ļ���ʧ�ܣ�\n");
				Sleep(800);
				exit(1);
			}
			else {//���ļ��ɹ�
				for (show_p = show_head->link; show_p != NULL; show_p = show_p->link)
				{
					fwrite(show_p, sizeof(Show), 1, fp);
				}
				fclose(fp);
			}
			printf("\t\t\t��ӳɹ���\n");
			Sleep(800);
			break;
		case '2':
			goto showida;
			break;
		case '0':
			free(new_show);
			return;
	}

}

void show_removation(void)
{
	char id[20];
	while (1)
	{
		system("cls");
		printf("\t\t\t���볡��ID��");
		mygets(id, 19, stdin);
		int flag = 0;
		Show *p;
		for (p = show_head; p->link != NULL; p = p->link)
		{
			if (strcmp(id, p->link->show_id) == 0)
			{
				flag = 1;
				break;
			}
		}

		if (flag == 0)
		{
			printf("\t\t\tδ�ҵ�\n");
			printf("\t\t\t��1����������\n\t\t\t��0������\n");
			char i;
			do {
				i = getch();
			} while (i != '0'&&i != '1');
			if (i == '1')continue;
			else return;
		}
		else
		{

			char key;
			Show *pfree;
			Show *show_p;
			FILE *fp;
			do {
				system("cls");
				printf("\t\t\t�Ƿ�ɾ���˳��Σ�\n");
				printf("\t\t\t********************************\n");
				printf("\t\t\t����ID��%s\n", p->link->show_id);
				printf("\t\t\tʱ�䣺%dʱ%d��\n", p->link->begintime.hour, p->link->begintime.minute);
				printf("\t\t\t���ڣ�%d��%d��%d��\n", p->link->begintime.year, p->link->begintime.month, p->link->begintime.day);
				printf("\t\t\tƱ�ۣ�%f\n", p->link->cost);
				printf("\t\t\t��ӰID��%s\n", p->link->film_id);
				printf("\t\t\t��ӳ����%d\n", p->link->hall_id);
				printf("\t\t\t********************************\n");
				printf("\t\t\t��1��ȷ�� ��0������\n");

				key = getch();
			} while (key != '1'&&key != '0');
			switch (key)
			{
			case '1':
				pfree = p->link;
				p->link = p->link->link;
				free(pfree);


				if ((fp = fopen("Show.txt", "w")) == NULL)//���ļ�
				{
					printf("Show.txt�ļ���ʧ�ܣ�\n");
					Sleep(800);
					exit(1);
				}
				else {//���ļ��ɹ�
					for (show_p = show_head->link; show_p != NULL; show_p = show_p->link)
					{
						fwrite(show_p, sizeof(Show), 1, fp);
					}
					fclose(fp);
				}
				printf("\t\t\tɾ���ɹ�\n");
				Sleep(500);
				return;

			case '0':
				return;
			}
		}
	}
}

void show_revise(void)
{
	char id[20];
	system("cls");
	printf("\t\t\t��������Ҫ�޸ĵĳ���ID��");
	mygets( id,19,stdin);
	Show *p;
	int flag = 0;
	for (p = show_head->link; p != NULL; p = p->link)
	{

//		printf("id:%s\npid:%s\n\n", id, p->show_id);
		if (strcmp(id, p->show_id) == 0)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		printf("\t\t\tδ�ҵ�\n");
		Sleep(800);
		getchar();
	}
	else
	{
		char key;
		while (1)
		{
			int count = 0;
			int year=p->begintime.year, month=p->begintime.month, day=p->begintime.day, hour=p->begintime.hour, minute=p->begintime.minute;
			do {
				system("cls");
				printf("\t\t\t��ѡ����Ҫ�޸ĵ�ѡ�\n");
				printf("\t\t\t��1���۸�%f\n", p->cost);
				printf("\t\t\t��2����ӳ����%d\n", p->hall_id);
				printf("\t\t\t��3����ӳ���ڣ�%d��%d��%d��\n", p->begintime.year,p->begintime.month,p->begintime.day);
				printf("\t\t\t��4����ӳʱ�䣺%dʱ%d��\n", p->begintime.hour,p->begintime.minute);
				printf("\t\t\t��0�������˳�\n\n");

				key = getch();
			} while (key<'0' || key>'9');

			int timeflag = 1;
			Show *show_p;
			char ch;
			int ha_id;
			switch (key)
			{
			case '1':
				printf("\t\t\t��1���۸�");
				scanf("%f", &(p->cost));
				while ((ch = getchar()) != '\n'&&ch != EOF);
				break;
			case '2':
				haag:
				printf("\t\t\t��2����ӳ����");
				scanf("%d", &ha_id);
				if (ha_id < 1 || ha_id>8)
				{
					printf("\t\t\t��ӳ��������!\n");
					while ((ch = getchar()) != '\n'&&ch != EOF);
					goto haag;
				}
				p->hall_id = ha_id;
				break;
			case '3':
				printf("\t\t\t��3����ӳ���ڣ�");
				scanf("%d %d %d", &year,&month,&day);
				while ((ch = getchar()) != '\n'&&ch != EOF);
				for (show_p = show_head->link; show_p != NULL; show_p = show_p->link)
				{
					if ((show_p->hall_id == p->hall_id)&&(show_p!=p))
					{
						long int a, b;
						if (show_p->begintime.year == year&&show_p->begintime.month == month&&show_p->begintime.day == day)
						{
							a = show_p->begintime.hour * 60 + show_p->begintime.minute;
							b = hour * 60 + minute;
							if (fabs(a - b) < 180)timeflag = 0;
						}
						else if (show_p->begintime.year == year&&show_p->begintime.month == month)
						{
							if (show_p->begintime.day - day == 1)
							{
								a = show_p->begintime.hour * 60 + show_p->begintime.minute;
								b = 24 * 60 - (hour * 60 + minute);
								if (a + b < 180)timeflag = 0;
							}
							else if (show_p->begintime.day - day == -1)
							{
								a = 24 * 60 - (show_p->begintime.hour * 60 + show_p->begintime.minute);
								b = hour * 60 + minute;
								if (a + b < 180)timeflag = 0;
							}
						}
						else if ((show_p->begintime.month == 12 && month == 1) || (show_p->begintime.month == 1 && month == 12))
						{
							if (show_p->begintime.month == 12 && month == 1)
							{
								if (show_p->begintime.day == 31 && day == 1)
								{
									a = 24 * 60 - (show_p->begintime.hour * 60 + show_p->begintime.minute);
									b = hour * 60 + minute;
									if (a + b < 180)timeflag = 0;
								}
							}
							else
							{
								if (show_p->begintime.day == 1 && day == 31)
								{
									a = show_p->begintime.hour * 60 + show_p->begintime.minute;
									b = 24 * 60 - (hour * 60 + minute);
									if (a + b < 180)timeflag = 0;
								}
							}
						}
					}

					char i;
					char c;
					while ((c = getchar()) != '\n' && c != EOF);
					if (timeflag == 0)
					{
						printf("\t\t\tʱ���ͻ��\n");/*Ϊʲô����ʾ��仰 ��Ѫ*/
						Sleep(500);
						break;
					}
				}
				if (timeflag == 1)
				{
					p->begintime.year = year;
					p->begintime.month = month;
					p->begintime.day = day;
				}
				break;
			case '4':
				printf("\t\t\t��4����ӳʱ�䣺");
				scanf("%d %d", &hour, &minute);
				while ((ch = getchar()) != '\n'&&ch != EOF);
				for (show_p = show_head->link; show_p != NULL; show_p = show_p->link)
				{
					if ((show_p->hall_id == p->hall_id) && (show_p != p))
					{
						long int a, b;
						if (show_p->begintime.year == year&&show_p->begintime.month == month&&show_p->begintime.day == day)
						{
							a = show_p->begintime.hour * 60 + show_p->begintime.minute;
							b = hour * 60 + minute;
							if (fabs(a - b) < 180)timeflag = 0;
						}
						else if (show_p->begintime.year == year&&show_p->begintime.month == month)
						{
							if (show_p->begintime.day - day == 1)
							{
								a = show_p->begintime.hour * 60 + show_p->begintime.minute;
								b = 24 * 60 - (hour * 60 + minute);
								if (a + b < 180)timeflag = 0;
							}
							else if (show_p->begintime.day - day == -1)
							{
								a = 24 * 60 - (show_p->begintime.hour * 60 + show_p->begintime.minute);
								b = hour * 60 + minute;
								if (a + b < 180)timeflag = 0;
							}
						}
						else if ((show_p->begintime.month == 12 && month == 1) || (show_p->begintime.month == 1 && month == 12))
						{
							if (show_p->begintime.month == 12 && month == 1)
							{
								if (show_p->begintime.day == 31 && day == 1)
								{
									a = 24 * 60 - (show_p->begintime.hour * 60 + show_p->begintime.minute);
									b = hour * 60 + minute;
									if (a + b < 180)timeflag = 0;
								}
							}
							else
							{
								if (show_p->begintime.day == 1 && day == 31)
								{
									a = show_p->begintime.hour * 60 + show_p->begintime.minute;
									b = 24 * 60 - (hour * 60 + minute);
									if (a + b < 180)timeflag = 0;
								}
							}
						}
					}

					char i;
					if (timeflag == 0)
					{
						printf("\t\t\tʱ���ͻ��\n");
						break;
					}
				}
				if (timeflag == 1)
				{
					p->begintime.hour = hour;
					p->begintime.minute = minute;
				}
				break;
			case '0':
				break;
			}
			if (key == '0')
				break;
		}
		Show *show_p;
		FILE *fp;
		if ((fp = fopen("Show.txt", "w")) == NULL)//���ļ�
		{
			printf("Show.txt�ļ���ʧ�ܣ�\n");
			Sleep(800);
			exit(1);
		}
		else {//���ļ��ɹ�
			for (show_p = show_head->link; show_p != NULL; show_p = show_p->link)
			{
				fwrite(show_p, sizeof(Show), 1, fp);
			}
			fclose(fp);
		}
		printf("�޸ĳɹ���\n");
		Sleep(500);

	}

}

void show_check()
{
	system("cls");
	Show *p;
	for (p = show_head->link; p != NULL; p = p->link)
	{
		printf("\t\t\t********************************\n");
		printf("\t\t\t����ID��%s\n", p->show_id);
		printf("\t\t\tʱ�䣺%dʱ%d��\n", p->begintime.hour,p->begintime.minute);
		printf("\t\t\t���ڣ�%d��%d��%d��\n", p->begintime.year,p->begintime.month,p->begintime.day);
		printf("\t\t\tƱ�ۣ�%f\n", p->cost);
		printf("\t\t\t��ӰID��%s\n",p->film_id);
		printf("\t\t\t��ӳ����%d\n", p->hall_id);
		printf("\t\t\t********************************\n");
	}
	printf("\t\t\t���������\n");
	getch();
}


/*Ա��*/
void staff_manage_ui(void)
{
	char key;
	while (1)
	{
		do {
			system("cls");

			printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
			printf("\t\t\t��               Ա  ��  ��  ��                      ��\n");
			printf("\t\t\t�d = = = = = = = = = = = = = = = = = = = = = = = = = �g\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 1 �� ���Ա��                        ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 2 �� ɾ��Ա��                        ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 3 �� Ա���޸�                        ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 4 �� Ա���鿴                        ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 0 ��  �� ��                          ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
			printf("\t\t\t������ѡ�");
			key = getch();
		} while (key != '1'&&key != '2'&&key != '3'&&key != '4'&&key != '0');
		switch (key)
		{
		case '1':
			staff_addition();
			break;
		case '2':
			staff_removation();
			break;
		case '3':
			staff_revise();
			break;
		case '4':
			staff_check();
			break;
		case '0':
			return;
		}
	}
}

void staff_addition(void)
{

	Staff *new_staff = (Staff*)malloc(sizeof(Staff));

	FILE *fp;
	Staff *staff_p;
	char key;
	new_staff_again:
	system("cls");
	printf("\t\t\t��������Ա��ID��");
	mygets(new_staff->staff_id,19,stdin);
	for (staff_p = staff_head->link; staff_p != NULL; staff_p = staff_p->link)
	{
		if (strcmp(new_staff->staff_id, staff_p->staff_id) == 0)
		{
			printf("\t\t\t�ظ�ID��\n");
			printf("\t\t\t��1����������\n\t\t\t��0������\n");
			do
			{
				key = getch();
			} while (key != '0'&&key != '1');
			if (key == '0')
			{
				free(new_staff);
				return;
			}
			else
			{
				goto new_staff_again;
			}
		}
	}

	new_staff_password:
	printf("\t\t\t������Ա�����루6-12λ����");
	input_password(new_staff->staff_password);
	if (strlen(new_staff->staff_password) < 6)
	{
		printf("\t\t\tλ������");
		Sleep(500);
		goto new_staff_password;
	}
	printf("\n\t\t\t������Ա��Ȩ�޵ȼ���");
	scanf("%d", &new_staff->staff_limit);
	printf("\t\t\t��1��ȷ�����\n\t\t\t��2����������\n\t\t\t��0������");
	do
	{
		key = getch();
	} while (key != '0'&&key != '1'&&key != '2');
	if (key == '0')
	{
		free(new_staff);
		return;
	}
	else if (key == '2')
		goto new_staff_again;
	else
	{
		for (staff_p = staff_head; staff_p->link != NULL; staff_p = staff_p->link);
		staff_p->link = new_staff;
		new_staff->link = NULL;

		if ((fp = fopen("Staff.txt", "wb")) == NULL)//���ļ�
		{
			printf("Staff.txt�ļ���ʧ�ܣ�\n");
			Sleep(800);
			exit(1);
		}
		else {//���ļ��ɹ�

			for (staff_p = staff_head->link; staff_p != NULL; staff_p = staff_p->link)
			{
				fwrite(staff_p, sizeof(Staff), 1, fp);
			}
			
			fclose(fp);
		}
		printf("\t\t\t��Ա����ӳɹ���\n");
		Sleep(800);
	}

}

void staff_removation(void)
{
	char id[20];
	while (1)
	{
		system("cls");
		printf("\n\t\t\t����Ա��ID��");
		mygets(id,19,stdin);
		int flag = 0;
		Staff *p;
		for (p = staff_head; p->link != NULL; p = p->link)
		{
			if (strcmp(id, p->link->staff_id) == 0)
			{
				flag = 1;
				break;
			}
		}

		if (flag == 0)
		{
			printf("\t\t\tδ�ҵ�\n");
			printf("\t\t\t��1����������\n\t\t\t��0������\n");
			char i;
			do {
				i = getch();
			} while (i != '0'&&i != '1');
			if (i == '1')continue;
			else return;
		}
		else
		{

			char key;
			Staff *pfree;
			Staff *staff_p;
			FILE *fp;
			do {
				system("cls");
				printf("\t\t\t�Ƿ�ɾ����Ա����\n");
				printf("\t\t\t********************************\n");
				printf("\t\t\tԱ��ID��%s\n", p->link->staff_id);
				printf("\t\t\tԱ��Ȩ�ޣ�%d\n", p->link->staff_limit);
				printf("\t\t\t********************************\n");
				printf("\t\t\t��1��ȷ�� ��0������\n");

				key = getch();
			} while (key != '1'&&key != '0');
			switch (key)
			{
			case '1':
				pfree = p->link;
				p->link = p->link->link;
				free(pfree);


				if ((fp = fopen("Staff.txt", "w")) == NULL)//���ļ�
				{
					printf("Staff.txt�ļ���ʧ�ܣ�\n");
					Sleep(800);
					exit(1);
				}
				else {//���ļ��ɹ�
					for (staff_p = staff_head->link; staff_p != NULL; staff_p = staff_p->link)
					{
						fwrite(staff_p, sizeof(Staff), 1, fp);
					}
					fclose(fp);
				}
				printf("\n\t\t\tɾ���ɹ�\n");
				Sleep(500);
				return;

			case '0':
				return;
			}
		}
	}




}

void staff_revise(void)
{
	printf("\t\t\t������δʵ�֣������ڴ���\n");
	Sleep(500);

}

void staff_check(void)
{
	system("cls");
	Staff *p;

	printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
	printf("\t\t\t��              �� �� �� �� Ա ��                    ��\n");
	printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
	for (p = staff_head->link; p != NULL; p = p->link)
	{

		printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
		printf("\t\t\t      Ա��ID��%20s               \n", p->staff_id);
		printf("\t\t\t      Ա��Ȩ�ޣ�%d                                  \n", p->staff_limit);
		printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
	}

	printf("\t\t\t���������\n");
	getch();
}

/*����*/
void order_manage_ui(void)
{
	system("cls");
	Order *p;

	printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
	printf("\t\t\t��              �� �� �� �� �� ��                    ��\n");
	printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
	for (p = order_head->link; p != NULL; p = p->link)
	{


		printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
		printf("\t\t\t         �û���%12s             \n", p->customer_id);
		printf("\t\t\t         ��Ӱ����%20s           \n", p->movie_name);
		printf("\t\t\t         ʱ�䣺%d��%2d��%2d��%2dʱ%2d��           \n", p->begintime.year, p->begintime.month, p->begintime.day, p->begintime.hour, p->begintime.minute);
		printf("\t\t\t         ���ţ�%d����                              \n", p->hall_id);
		printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");

		
	}
	printf("\t\t\t���������\n");
	getch();
}





/*�˿�*/
void customer_ui(void)
{
	char key;
	while (1)
	{
		do {
			system("cls");
			printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
			printf("\t\t\t��            ��ӭ�� %s                     ��\n",user->present_customer_information->customer_phonenumber);
			printf("\t\t\t�d = = = = = = = = = = = = = = = = = = = = = = = = = �g\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 1 �� �鿴��Ӱ                        ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 2 �� �鿴����                        ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 0 ��  ��  ��                         ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
			printf("\t\t\t������ѡ�");
			key = getch();
		} while (key != '1'&&key != '2'&&key != '0');

		switch (key)
		{
		case '1':
			customer_movie_ui();
			break;
		case '2':
			customer_order_ui();
			break;
		case '0':
			exit_ui();
			break;
		}
	}
}


void customer_movie_ui(void)
{
	char key;
	while (1)
	{
		do {
			system("cls");
			printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
			printf("\t\t\t��               ��     Ӱ                           ��\n");
			printf("\t\t\t�d = = = = = = = = = = = = = = = = = = = = = = = = = �g\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 1 �� ������ӳ                        ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 2 �� ������ӳ                        ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 3 �� Ʊ������                        ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��           �� 0 ��  ��  ��                         ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
			printf("\t\t\t������ѡ�");
			key = getch();
		} while (key != '1'&&key != '2'&&key != '3'&&key != '0');

		switch (key)
		{
		case '1':
			customer_movie_present();
			break;
		case '2':
			customer_movie_advance();
			break;
		case '3':
			customer_movie_rank();
			break;
		case '0':
			return;

		}
	}
}

void customer_movie_present(void)
{
	Movie *movie_p;
	Show *show_p;
	Order *order_p;
	int count = 1;
	system("cls");
	printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
	printf("\t\t\t��               ��  ��  ��  ӳ                      ��\n");
	printf("\t\t\t�d = = = = = = = = = = = = = = = = = = = = = = = = = �g\n");
	for (movie_p = movie_head->link; movie_p != NULL; movie_p = movie_p->link)
	{
		for (show_p = show_head->link; show_p != NULL; show_p = show_p->link)
		{
			if (strcmp(movie_p->movie_id, show_p->film_id) == 0 && show_p->begintime.year == (1900 + p->tm_year) && show_p->begintime.month == (p->tm_mon) + 1 && show_p->begintime.day == p->tm_mday)
			{


				printf("\t\t\t��     ��Ӱ����%10s           \n",movie_p->movie_name);
				printf("\t\t\t��     ��ӰID��%10s           \n", movie_p->movie_id);
				printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
				count++;
				break;
			}
		}
	}
	if (count == 1)
	{

		printf("\t\t\t��                ������ӳ��Ӱ                       ��\n");
		printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
		Sleep(800);
		return;
	}


	printf("\n\n");
	printf("\t\t\t��1�������ӰID�鿴��ϸ\n");
	printf("\t\t\t��0������\n");
	printf("\t\t\t������ѡ�");
	char key;
	do
	{
		key = getch();
	} while (key != '1'&&key != '0');

	if (key == '1')
	{

		char id[20];
		char ch;
		printf("\n\n");
	findida:
		printf("\t\t\t��ӰID��");
		int i = 0;
		mygets(id, 49, stdin);
//		scanf("%s", id);

		int findflag = 0;
		for (movie_p = movie_head->link; movie_p != NULL; movie_p = movie_p->link)
		{
			if (strcmp(movie_p->movie_id, id) == 0)
			{
				system("cls");
				printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
				printf("\t\t\t                %s                 \n",movie_p->movie_name);
				printf("\t\t\t�d = = = = = = = = = = = = = = = = = = = = = = = = = �g\n");
				printf("\t\t\t��                                                   ��\n");
				printf("\t\t\t��         ���ݣ�    %s                \n", movie_p->starring);
				printf("\t\t\t��         ���ݣ�    %s                          \n",movie_p->derector);
				printf("\t\t\t��         ��ӳʱ�䣺%d��%2d��%2d��                  \n", movie_p->Date.year, movie_p->Date.month, movie_p->Date.day);
				printf("\t\t\t��         ���ң�    %s                          \n" , movie_p ->nation);
				printf("\t\t\t��         ���ԣ�    %s                          \n" , movie_p ->language);
				printf("\t\t\t��         ʱ����    %s                             \n", movie_p ->length);
				printf("\t\t\t��         ���ͣ�    %s                          \n", movie_p ->type);
				printf("\t\t\t��         ��Ӱ������%s...                \n", movie_p ->movie_description);
				printf("\t\t\t��         ��ӰID��  %s                \n", movie_p->movie_id);
				printf("\t\t\t��                                                   ��\n");
				printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
				findflag = 1;
				break;
			}
			
		}

		if (findflag == 0)
		{
			printf("\n\t\t\t��������\n");
			goto findida;
		}

		printf("\n\n\n");

		printf("\t\t\t��1���鿴%s�ų�\n", movie_p->movie_name);
		printf("\t\t\t��0������\n");
		char keyy;
		do
		{
			keyy = getch();
		} while (keyy != '1'&&keyy != '0');
		if (keyy == '1')
		{
			count = 1;
			printf("\t\t\t��1�������ų�\n");
			printf("\t\t\t��2�������ų�\n");
			char keyy;
			do
			{
				keyy = getch();
			} while (keyy != '1'&&keyy != '2');

			if (keyy == '1')
			{
				system("cls");
				for (show_p = show_head->link; show_p != NULL; show_p = show_p->link)
				{
					if (strcmp(movie_p->movie_id, show_p->film_id) == 0 && show_p->begintime.year == (1900 + p->tm_year) && show_p->begintime.month == (p->tm_mon) + 1 && show_p->begintime.day == p->tm_mday)
					{
						if (((show_p->begintime.hour * 60) + show_p->begintime.minute) > (p->tm_hour * 60 + p->tm_min) + 15)
						{
							printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
							printf("\t\t\t��    ����ID��%s               \n", show_p->show_id);
							printf("\t\t\t��    ʱ�䣺%2dʱ %2d��                            \n", show_p->begintime.hour, show_p->begintime.minute);
							printf("\t\t\t��    �۸�%5.2fԪ                                  \n", show_p->cost);
							printf("\t\t\t��    ������%d����                                  \n", show_p->hall_id);
							printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
							count++;
						}
					}
				}

				printf("\t\t\t��1�����볡��ID��Ʊ\n");
				printf("\t\t\t��0������\n");
				do
				{
					keyy = getch();
				} while (keyy != '1'&&keyy != '0');
				if (keyy == '1')
				{
					char showid[20];
				findsida:
					printf("\n");
					printf("\t\t\t����ID��");
					int i = 0;
					mygets(showid, 49, stdin);
//					scanf("%s", showid);
//					printf("%s\n", showid);

					int ticketflag = 0;
					for (show_p = show_head->link; show_p != NULL; show_p = show_p->link)
					{
						//printf("%s\n", show_p->show_id);
						if (strcmp(showid, show_p->show_id) == 0)
						{
							//printf("id*******");
							if (show_p->begintime.year == (1900 + p->tm_year) && show_p->begintime.month == (p->tm_mon) + 1 && show_p->begintime.day == p->tm_mday)
							{
							//	printf("shijiannian");

								if (((show_p->begintime.hour * 60) + show_p->begintime.minute) > (p->tm_hour * 60 + p->tm_min) + 15)
								{
							//		printf("%d %d       %d %d", show_p->begintime.hour, show_p->begintime.minute, p->tm_hour, p->tm_min);
									printf("\t\t\tȷ�����򣿣�y or n��");
									do
									{
										key = getch();
									} while (key != 'y'&&key != 'n');

									if (key == 'y')
									{
										movie_p->booking++;
										FILE *fp;


										Order *new_order = (Order *)malloc(sizeof(Order));

										for (order_p = order_head; order_p->link != NULL; order_p = order_p->link);
										order_p->link = new_order;
										new_order->link = NULL;
										new_order->begintime.day = show_p->begintime.day;
										new_order->begintime.year = show_p->begintime.year;
										new_order->begintime.month = show_p->begintime.month;
										new_order->begintime.hour = show_p->begintime.hour;
										new_order->begintime.minute = show_p->begintime.minute;
										new_order->cost = show_p->cost;
										new_order->hall_id = show_p->hall_id;
										//	new_order->movie_o = movie_p;
										strcpy(new_order->movie_name, movie_p->movie_name);
										strcpy(new_order->customer_id, user->user_id);

										if ((fp = fopen("Order.txt", "wb")) == NULL)//���ļ�
										{
											printf("Order.txt�ļ���ʧ�ܣ�\n");
											Sleep(800);
											exit(1);
										}
										else {//���ļ��ɹ�
											for (order_p = order_head->link; order_p != NULL; order_p = order_p->link)
											{
												fwrite(order_p, sizeof(Order), 1, fp);
											}
											fclose(fp);
										}


										if ((fp = fopen("Movie.txt", "wb")) == NULL)//���ļ�
										{
											printf("Movie.txt�ļ���ʧ�ܣ�\n");
											Sleep(800);
											exit(1);
										}
										else {//���ļ��ɹ�
											for (movie_p = movie_head->link; movie_p != NULL; movie_p = movie_p->link)
											{
												fwrite(movie_p, sizeof(Movie), 1, fp);
											}
											fclose(fp);
										}

										printf("\n\t\t\t����Ʊ�ɹ�!��\n");
										ticketflag = 1;
										Sleep(800);
										return;
									}
									else
									{
										return;
									}
								}
							}

						}
					}
					if (ticketflag == 0)
					{
						printf("\t\t\t����ID����\n");
						goto findsida;
					}
				}



			}
			else
			{
				system("cls");
				printf("����ʵ�ֹ���");
				Sleep(800);
			}



		}
		else return;

	}
	else return;
}

void customer_movie_advance(void)
{
	system("cls");
	Movie *movie_p;
	int count = 1;
	long int a, b;
	a = (1900 + p->tm_year) * 365 + (p->tm_mon) * 30 + p->tm_mday;
	for (movie_p = movie_head->link; movie_p != NULL; movie_p = movie_p->link)
	{
		b = movie_p->Date.year * 365 + (movie_p->Date.month - 1) * 30 + movie_p->Date.day;
		if (a < b)
		{
			printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
			printf("\t\t\t                 %s                      \n",movie_p->movie_name);
			printf("\t\t\t�d = = = = = = = = = = = = = = = = = = = = = = = = = �g\n");
			printf("\t\t\t��                                                   \n");
			printf("\t\t\t��     ���ݣ�    %s                \n", movie_p->starring);
			printf("\t\t\t��     ���ݣ�    %s                          \n", movie_p->derector);
			printf("\t\t\t��     ��ӳʱ�䣺%d��%2d��%2d��                  \n", movie_p->Date.year, movie_p->Date.month, movie_p->Date.day);
			printf("\t\t\t��     ���ң�    %s                          \n", movie_p->nation);
			printf("\t\t\t��     ���ԣ�    %s                          \n", movie_p->language);
			printf("\t\t\t��     ʱ����    %s                             \n", movie_p->length);
			printf("\t\t\t��     ���ͣ�    %s                          \n", movie_p->type);
			printf("\t\t\t��     ��Ӱ������%s...                \n", movie_p->movie_description);
			printf("\t\t\t��     ��ӰID��  %s                \n", movie_p->movie_id);
			printf("\t\t\t��                                                   ��\n");
			printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
			printf("\n");
			count++;
		}
	}
	if(count == 1)
	{
		printf("\t\t\t���޵�ӰԤ��\n");
		Sleep(800);
		return;
	}

	printf("\t\t\t�����������\n");
	getch();
}

void customer_movie_rank(void)
{
	char key;
	do {
		system("cls");
		printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
		printf("\t\t\t��                   Ʊ       ��                     ��\n");
		printf("\t\t\t�d = = = = = = = = = = = = = = = = = = = = = = = = = �g\n");
		printf("\t\t\t��                                                   ��\n");
		printf("\t\t\t��                                                   ��\n");
		printf("\t\t\t��           �� 1 �� �� Ʊ �� �� ��                  ��\n");
		printf("\t\t\t��                                                   ��\n");
		printf("\t\t\t��           �� 2 �� �� ӳ �� ��                     ��\n");
		printf("\t\t\t��                                                   ��\n");
		printf("\t\t\t��           �� 0 ��  ��   ��                        ��\n");
		printf("\t\t\t��                                                   ��\n");
		printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
		printf("\t\t\t������ѡ�");

		key = getch();
	} while (key != '1'&&key != '2'&&key != '0');

	switch (key)
	{
	case '1':
		customer_movie_rank_all();
		break;
	case '2':
		customer_movie_rank_now();
		break;
	case '0':
		return;


	}

}


void customer_movie_rank_all(void)
{
	sort_movie();
	int n = 5;
	Movie *movie_p;
	Show *show_p;

	system("cls");

	printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
	printf("\t\t\t��                �� Ʊ �� �� ��                     ��\n");
	printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
	for (movie_p = movie_head->link,n=5; movie_p != NULL&&n>=0; movie_p = movie_p->link,n--)
	{
		printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
		printf("\t\t\t��                   ��%d��                          \n", 6- n);
		printf("\t\t\t��       ��Ӱ����%s            \n", movie_p->movie_name);
		printf("\t\t\t��       ��ӰƱ����%d                              \n", movie_p->booking);
		printf("\t\t\t��       ��Ӱ������%s          \n", movie_p->movie_description);
		printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
	}
	printf("\t\t\t���������\n");
	getch();

}


void customer_movie_rank_now(void)
{
	sort_movie();
	Movie *movie_p;
	Show *show_p;
	int n = 5;
	system("cls");
	printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
	printf("\t\t\t��                �� Ʊ �� �� ��                     ��\n");
	printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
	for (movie_p = movie_head->link,n=5; movie_p != NULL&&n>=0; movie_p = movie_p->link,n--)
	{
		for (show_p = show_head->link; show_p != NULL; show_p = show_p->link)
		{
			if (strcmp(movie_p->movie_id, show_p->film_id) == 0 && show_p->begintime.year == (1900 + p->tm_year) && show_p->begintime.month == (p->tm_mon) + 1 && show_p->begintime.day == p->tm_mday)
			{

				printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
				printf("\t\t\t��                   ��%d��                          \n", 6 - n);
				printf("\t\t\t��       ��Ӱ����%s            \n", movie_p->movie_name);
				printf("\t\t\t��       ��ӰƱ����%d                              \n", movie_p->booking);
				printf("\t\t\t��       ��Ӱ������%s          \n", movie_p->movie_description);
				printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
				break;
			}
		}
	}

	printf("\t\t\t���������\n");
	getch();
}


void sort_movie(void)
{
	Movie *p1, *p2, *temp, *prep1, *prep2;
	if (movie_head->link->link == NULL)
		return ;
	for (p1 = movie_head->link->link, prep1 = movie_head->link; p1 != NULL; p1 = p1->link, prep1 = prep1->link)
	{
		temp = p1;    /*���������ڵ�*/
		for (p2 = movie_head->link, prep2 = movie_head; p2 != p1; p2 = p2->link, prep2 = prep2->link)
		{
			if (p2->booking < p1->booking)
			{
				p1 = p1->link;
				prep1->link = temp->link;    /*ɾ��������ڵ�*/
				prep2->link = temp;              /*��������Ӧλ��*/
				temp->link = p2;
				break;
			}
			else if (p2->booking == p1->booking &&( (p2->Date.year < p1->Date.year) || (p2->Date.year == p1->Date.year)&&(p2->Date.month < p1->Date.month)|| (p2->Date.year == p1->Date.year) && (p2->Date.month == p1->Date.month)&&(p2->Date.day<p1->Date.day)))
			{
				p1 = p1->link;
				prep1->link = temp->link;    /*ɾ��������ڵ�*/
				prep2->link = temp;              /*��������Ӧλ��*/
				temp->link = p2;
				break;
			}
		}
	}


}


void customer_order_ui(void)
{
	system("cls");
	printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
	printf("\t\t\t��                ��  ��  ��  ��                     ��\n");
	printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");
	Order *p;
	for (p = order_head->link; p != NULL; p = p->link)
	{
		if (strcmp(p->customer_id, user->user_id) == 0)
		{

			printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
			printf("\t\t\t��       ��Ӱ����%20s            \n", p->movie_name);
			printf("\t\t\t��       ʱ�䣺%d��%2d��%2d��%2dʱ%2d��            \n", p->begintime.year, p->begintime.month, p->begintime.day, p->begintime.hour, p->begintime.minute);
			printf("\t\t\t��       ���ţ�%d����                             \n", p->hall_id);
			printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = �a\n");

		}
	}

	printf("\t\t\t���������\n");
	getch();


}



/*ccccccccccccccccccccccccccccccccccc�����ȡ*/
void input_password(char *password)
{
	char ch;
	int i=0;
	while (ch = getch())
	{
		if (ch == '\r'&&i>5)
		{
			password[i] = '\0';
			break;
		}
		if (ch == '\r'&&i <= 5)
		{
			printf("\a");
			continue;
		}
		if (ch == '\b')
		{
			if (i == 0)
			{
				printf("\a");
				continue;
			}
			printf("\b \b");
			i--;
			continue;
		}
		if (i >= 20)
		{
			printf("\a");
			continue;
		}
		if (ch != '\t'&&ch != '\v'&&ch != ' ')
		{
			putchar('*');
			password[i] = ch;
			i++;
		}
	}
}

void ending(void)
{

	/*д�ļ�*/
	FILE *fp;

	/*�˿��˻�*/
	Customer *customer_p;
	if ((fp = fopen("Customer.txt", "w")) == NULL)//���ļ�
	{
		printf("Customer.txt�ļ���ʧ�ܣ�\n");
		Sleep(800);
		exit(1);
	}
	else {//���ļ��ɹ�

		for(customer_p = customer_head->link;customer_p!=NULL;customer_p=customer_p->link)
		{
			fwrite(customer_p, sizeof(Customer), 1, fp);
		}

		fclose(fp);
	}




}

void mygets(char* bu, int max, FILE *fp)
{
	char ch;
	int i;
	/*
	while (ch = getch())
	{
		if (ch == '\r'&&i > 0)
		{
			bu[i] = '\0';
			break;
		}
		if (ch == '\r'&&i == 0)
		{
			printf("\a");
			continue;
		}
		if (ch == '\b')
		{
			if (i == 0)
			{
				printf("\a");
				continue;
			}
			printf("\b \b");
			i--;
			continue;
		}
		if (i >= max)
		{
			printf("\a");
			continue;
		}
			putchar(ch);
			bu[i] = ch;
			i++;
	}
	printf("\n");*/
	int flag;
	do {
		flag = 0;
		fgets(bu, max, fp);
		for (i = 0; i <= max; i++)
		{
			if (bu[i] == '\n')
			{
				flag = 1;
				bu[i] = '\0';
			}

		}
	} while (bu[0] == '\0');
	if (flag == 0)while ((ch = getchar()) != '\n'&&ch != EOF);
}