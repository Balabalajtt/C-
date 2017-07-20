/*标准库包含*/

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

/*管理员*/
typedef struct STAFF {
	char staff_id[9];
//	char staff_name[20];
	char staff_password[21];
	int staff_limit;//管理员权限 1：最高 2：次级
	struct STAFF *link;
}Staff;

/*顾客*/
typedef struct CUSTOMER {
	char customer_phonenumber[12];
//	char customer_name[20];
	char customer_password[21];
//	char question[100];
//	char answer[100];
	struct CUSTOMER *link;
}Customer;

/*当前登录用户*/
typedef struct USER {
	char user_id[20];
	char user_password[20];
	char user_limit;
	Staff *present_staff_information;
	Customer *present_customer_information;
}User;

/*电影信息*/
typedef struct MOVIE {
	char movie_id[20];
	char movie_name[50];
	char starring[50];//主演信息
	char derector[50];//导演信息
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
	int booking;//票房
//	float average;//平均分
	struct MOVIE *link;
}Movie;

/*大厅*/
typedef struct HALL {
	int hall_id;
	int seat_sum;
//	char hall_description[100];

	struct HALL *link;
}Hall;

/*座位*/
typedef struct SEAT {
	int seat_id;
	int show_id;
	int row;
	int ver;
	int seat_status;
	struct SEAT *link;
}Seat;

/*场次*/
typedef struct SHOW {
	char show_id[50];//场次号
	char film_id[50];
	int hall_id;//厅号
	float cost;//票价
	struct BEGINTIME {//场次时间
		int year;
		int month;
		int day;
		int hour;
		int minute;
	}begintime;
	struct SHOW *link;
}Show;

/*订单*/
typedef struct ORDER {
//	int order_id;
	char customer_id[20];
//	Movie *movie_o;
	char movie_name[50];
	int hall_id;//厅号
	float cost;//票价
	struct BEGINTIME {//场次时间
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





/*全局变量*/
User *user = (User *)malloc(sizeof(User));

Customer *customer_head = (Customer *)malloc(sizeof(Customer));
Staff *staff_head = (Staff *)malloc(sizeof(Staff));
Movie *movie_head = (Movie *)malloc(sizeof(Movie));
Show *show_head = (Show *)malloc(sizeof(Show));
Hall *hall_head = (HALL *)malloc(sizeof(HALL));
Order *order_head = (ORDER *)malloc(sizeof(ORDER));
/*当天日期时间*/




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



/*入口*/
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


/*初始*/
void init(void)
{
	/*初始化头指针*/
	customer_head->link = NULL;
	staff_head->link = NULL;
	movie_head->link = NULL;
	hall_head->link = NULL;
	show_head->link = NULL;
	order_head->link = NULL;
	/*分配新两个账号*/

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


	/*影厅初始   1-8号厅 */
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


	/*读文件*/
	FILE *fp;

	/*顾客账户*/
	Customer *customer_p;
	for (customer_p = customer_head; customer_p->link != NULL; customer_p = customer_p->link);
	Customer *init_customer;
	
	if ((fp = fopen("Customer.txt", "r")) == NULL)//打开文件
	{
		printf("Customer.txt文件不存在或文件打开失败！\n");
		Sleep(800);
		exit(1);
	}
	else if (feof(fp) == 1)//判断文件是否为空
	{
		printf("Customer.txt文件为空！\n");
		Sleep(800);
	}
	else {//文件不为空时
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
	
	
	/*员工账户*/
	Staff *staff_p;
	for (staff_p = staff_head; staff_p->link != NULL; staff_p = staff_p->link);
	Staff *init_staff;

	if ((fp = fopen("Staff.txt", "r")) == NULL)//打开文件
	{
		printf("Staff.txt文件不存咋或文件打开失败！\n");
		Sleep(800);
		exit(1);
	}
	else if (feof(fp) == 1)//判断文件是否为空
	{
		printf("Staff.txt文件为空！\n");
		Sleep(800);
	}
	else {//文件不为空时
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
	
	/*所有影片*/
	Movie *movie_p;
	for (movie_p = movie_head; movie_p->link != NULL; movie_p = movie_p->link);
	Movie *init_movie;

	if ((fp = fopen("Movie.txt", "rb")) == NULL)//打开文件
	{
		printf("Movie.txt文件不存咋或文件打开失败！\n");
		Sleep(800);
		exit(1);
	}
	else if (feof(fp) == 1)//判断文件是否为空
	{
		printf("Movie.txt文件为空！\n");
		Sleep(800);
	}
	else {//文件不为空时
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
	

	/*场次*/

	
	Show *show_p;
	for (show_p = show_head; show_p->link != NULL; show_p = show_p->link);
	Show *init_show;

	if ((fp = fopen("Show.txt", "r")) == NULL)//打开文件
	{
		printf("Show.txt文件不存咋或文件打开失败！\n");
		Sleep(800);
		exit(1);
	}
	else if (feof(fp) == 1)//判断文件是否为空
	{
		printf("Show.txt文件为空！\n");
		Sleep(800);
	}
	else {//文件不为空时
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




	/*订单*/
	Order *order_p;
	for (order_p = order_head; order_p->link != NULL; order_p = order_p->link);
	Order *init_order;

	if ((fp = fopen("Order.txt", "rb")) == NULL)//打开文件
	{
		printf("Order.txt文件不存咋或文件打开失败！\n");
		Sleep(800);
		exit(1);
	}
	else if (feof(fp) == 1)//判断文件是否为空
	{
		printf("Order.txt文件为空！\n");
		Sleep(800);
	}
	else {//文件不为空时
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
	














	/*删掉今天之前的排场*/
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


/*111111111111111111111111111登录注册界面*/
void sign_ui(void)
{
	char key;
	while (1)
	{
		do {
			system("cls");
			printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
			printf("\t\t\t‖              欢 迎 来 到 剧 院 管 理 系 统            ‖ \n");
			printf("\t\t\t╠ = = = = = = = = = = = = = = = = = = = = = = = = = = = ╣\n");
			printf("\t\t\t‖                                                       ‖\n");
			printf("\t\t\t‖                                                       ‖\n");
			printf("\t\t\t‖     【 1 】 登  录                                    ‖\n");
			printf("\t\t\t‖                                                       ‖\n");
			printf("\t\t\t‖     【 2 】 注  册                                    ‖\n");
			printf("\t\t\t‖                                                       ‖\n");
			printf("\t\t\t‖     【 0 】 退  出                                    ‖\n");
			printf("\t\t\t‖                                                       ‖\n");
			printf("\t\t\t‖                                                       ‖\n");
//			printf("\t\t\t‖       ╭⌒╮¤                                        ‖\n");
//			printf("\t\t\t‖       ╭╭ ⌒╮ ●╭○╮                              ‖\n");
//			printf("\t\t\t‖       ╰ ----╯/█∨█\\                               ‖\n");
//			printf("\t\t\t‖       ~~~~~~~~~~∏~~∏~~~~~~~~~~~                     ‖\n");
			printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
			printf("\t\t\t请输入选项：");
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

/*22222222222222222222退出系统界面*/
void exit_ui(void)
{
	char key;

	do {
		system("cls");
		printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
		printf("\t\t\t‖              确 定 退 出 剧 院 管 理 系 统            ‖ \n");
		printf("\t\t\t╠ = = = = = = = = = = = = = = = = = = = = = = = = = = = ╣\n");
		printf("\t\t\t‖                                                       ‖\n");
		printf("\t\t\t‖                                                       ‖\n");
		printf("\t\t\t‖     【 1 】 退  出                                    ‖\n");
		printf("\t\t\t‖                                                       ‖\n");
		printf("\t\t\t‖     【 0 】 返  回                                    ‖\n");
		printf("\t\t\t‖                                                       ‖\n");
		printf("\t\t\t‖                                                       ‖\n");
		printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
		printf("\t\t\t请输入选项：");

		key=getch();
	} while (key != '1'&& key != '0');

	if (key == '1')
	{
		system("cls");
		printf("\n\n");
		printf("\t\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
		printf("\t\t\t\t‖                                                 ‖\n");
		printf("\t\t\t\t‖            感  谢  您  的  使  用               ‖ \n");
		printf("\t\t\t\t‖                                                 ‖\n");
		printf("\t\t\t\t‖            期 待 您 的 再 次 光 临              ‖\n");
		printf("\t\t\t\t‖                                                 ‖\n");
		printf("\t\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
		printf("\n\n\n\n\n\t\t");
		exit(1);
	}
}

/*222222222222222222222登陆身份选择界面*/
void sign_in_ui(void)
{
	char key;
//	while (1)
//	{
		do {
			system("cls");
			printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
			printf("\t\t\t‖              请 选 择 您 的 登 录 身 份               ‖ \n");
			printf("\t\t\t╠ = = = = = = = = = = = = = = = = = = = = = = = = = = = ╣\n");
			printf("\t\t\t‖                                                       ‖\n");
			printf("\t\t\t‖                                                       ‖\n");
			printf("\t\t\t‖     【 1 】 顾  客                                    ‖\n");
			printf("\t\t\t‖                                                       ‖\n");
			printf("\t\t\t‖     【 2 】 员  工                                    ‖\n");
			printf("\t\t\t‖                                                       ‖\n");
			printf("\t\t\t‖     【 0 】 返  回                                    ‖\n");
			printf("\t\t\t‖                                                       ‖\n");
			printf("\t\t\t‖                                                       ‖\n");
			printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
			printf("\t\t\t请输入选项：");
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

/*3333333333333333333333顾客登录界面*/
void sign_in_customer(void)
{
	Customer *p;//用来遍历顾客账号链表
	int count = 3;//错误次数

	while (count--)
	{

		system("cls");
//		printf("【客户您好,请登录！】\n");
//		printf("您有%d次机会尝试登录\n机会用完将自动退出程序\n", count+1);
		printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
		printf("\t\t\t‖                     登    录                      ‖\n");
		printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
		printf("\n\n");
		printf("\t\t\t\t○ 手机号：");
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

		printf("\n\n\n\t\t\t\t○ 密码：  ");
		input_password(user->user_password);
		printf("\n\n\n\n\n\n");
		/*验证账号密码*/
		int flag;
		for (flag=0,p = customer_head->link; p != NULL; p = p->link)
		{
			
			if (strcmp(p->customer_phonenumber, user->user_id) == 0)
			{
				
				if (strcmp(p->customer_password, user->user_password) == 0)
				{
					user->present_customer_information = p;
					/*顾客登录成功了，跳转顾客主菜单*/
//					system("cls");
					printf("\t\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n");
					printf("\t\t\t%s用户登录成功！\n", user->present_customer_information->customer_phonenumber);
					printf("\t\t\t正在跳转，请稍后");
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
						printf("\t\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔\n");
						printf("\t\t\t▽ 输入密码有误!      \n"); Sleep(800);
						printf("\t\t\t▽ [1]重新输入 [0]返回 \n");
						printf("\t\t\t▽ 请输入选项：");
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
			printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
			printf("\t\t\t‖              该手机号尚未注册!                    ‖\n");
			printf("\t\t\t‖        【1】重新输入   【0】 返 回                ‖\n");
			printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
			printf("\t\t\t请输入选项：");
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
	printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
	printf("\t\t\t‖              您已尝试登录多次登录                 ‖\n");
	printf("\t\t\t‖                为了您的账号安全                   ‖\n");
	printf("\t\t\t‖                 系统将自动退出！                  ‖\n");
	printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
	Sleep(1000);
	exit(1);

}

/*333333333333333333333员工登录界面*/
void sign_in_staff(void)
{
	Staff *p;//用来遍历员工账号链表
	int count = 3;//错误次数

	while (count--)
	{
		char ch;
		int i = 0;
		system("cls");
		printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
		printf("\t\t\t‖                     登    录                      ‖\n");
		printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
		printf("\n\n");
		printf("\t\t\t\t○ 工号：");
//		printf("【员工您好,请登录！】\n");
//		printf("您有%d次机会尝试登录\n机会用完将自动退出程序\n", count+1);
//		printf("\n工号(8位)：");
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

		printf("\n\n\n\t\t\t\t○ 密码：  ");
		input_password(user->user_password);
		printf("\n\n\n");
		/*验证账号密码*/
		for (p = staff_head->link; p != NULL; p = p->link)
		{

			if (strcmp(p->staff_id, user->user_id) == 0)
			{

				if (strcmp(p->staff_password,user->user_password) == 0)
				{
					user->present_staff_information = p;
					/*顾客登录成功了，跳转员工主菜单*/
				//	system("cls");
					printf("\t\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n");
					printf("\n\t\t\t员工%s，您已登录成功！\n", user->present_staff_information->staff_id);
					Sleep(1000);
//					if (p->staff_limit == 1)
						su_staff_ui();
					//else
						//staff_ui();
					return;
				}

				else
				{
					printf("\t\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n");
					printf("\n\t\t\t输入密码有误！请重试\n");
					Sleep(500);
					break;
				}

			}
		}

		if (p == NULL)
		{
			printf("\t\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n");
			printf("\n\t\t\t输入账号有误！请重试\n");
			Sleep(500);
		}
	}

	system("cls");
	printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
	printf("\t\t\t‖            您 已 尝 试 登 录 多 次                ‖\n");
	printf("\t\t\t‖            为 了 您 的 账 号 安 全                ‖\n");
	printf("\t\t\t‖             系 统 将 自 动 退 出                  ‖\n");
	printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
	Sleep(1000);
	exit(1);

}


/*2222222222222222222222222222222注册界面*/
void sign_up_ui(void)
{	

	Customer *new_customer = (Customer *)malloc(sizeof(Customer));

	FILE *fp;
	Customer *customer_p;
	char key;
new_customer_again:
	system("cls");
	printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
	printf("\t\t\t‖                     注    册                      ‖\n");
	printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
	printf("\n\n");
	printf("\t\t\t\t○ 手机号：");
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
				printf("\t\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔\n");
				printf("\t\t\t▽ 该手机号已注册!      \n\n"); Sleep(500);
				printf("\t\t\t▽ [1]重新输入 [2]直接登录 [0]返回 \n");
				printf("\t\t\t▽ 请输入选项：");
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
		printf("\t\t\t\t○ 密 码：");
		input_password(new_customer->customer_password);
		printf("\n\n");
		printf("\t\t\t\t○ 确认密码：");
		char buff[21];
		input_password(buff);
		
		printf("\n");
		if (strcmp(buff, new_customer->customer_password) != 0)
		{
			printf("\t\t\t\t密码不一致，请重试！\n");
			Sleep(800);
			system("cls");

			printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
			printf("\t\t\t‖                     注    册                      ‖\n");
			printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
			printf("\n\n");
			printf("\t\t\t\t○ 手机号：%s\n",new_customer->customer_phonenumber);
			goto passwo;
		}

		printf("\n\n\n\n\n");
		printf("\t\t\t▔▔▔▔▔▔▔▔▔▔▔▔▔\n");
		printf("\t\t\t▽ [1]确定 [0]返回 \n");
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

			if ((fp = fopen("Customer.txt", "w")) == NULL)//打开文件
			{
				printf("Customer.txt文件打开失败！\n");
				Sleep(800);
				exit(1);
			}
			else {//打开文件成功

				for (customer_p = customer_head->link; customer_p != NULL; customer_p = customer_p->link)
				{
					fwrite(customer_p, sizeof(Customer), 1, fp);
				}

				fclose(fp);
			}

			//system("cls");
			printf("\n\t\t\t%s用户，您已注册成功......\n", new_customer->customer_phonenumber);
			Sleep(1000);
		}
	

}

/*管理员主界面*/
void su_staff_ui(void)
{
	char key;
	while (1)
	{
		do {
			system("cls");
			printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
			printf("\t\t\t                  欢迎您 %8s                     \n", user->present_staff_information->staff_id);
			printf("\t\t\t╠ = = = = = = = = = = = = = = = = = = = = = = = = = ╣\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 1 】 电影管理                        ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 2 】 场次管理                        ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 3 】 员工管理                        ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 4 】 订单管理                        ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 0 】  退 出                          ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
			printf("\t\t\t请输入选项：");
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

/*电影*/
void movie_manage_ui(void)
{
	char key;
	while (1)
	{
		do {
			system("cls");

			printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
			printf("\t\t\t‖               电  影  管  理                      ‖\n");
			printf("\t\t\t╠ = = = = = = = = = = = = = = = = = = = = = = = = = ╣\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 1 】 添加电影                        ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 2 】 删除电影                        ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 3 】 电影修改                        ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 4 】 电影查看                        ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 0 】  返 回                          ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
			printf("\t\t\t请输入选项：");
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
	printf("\t\t\t请输入电影信息：\n");
//	getchar();
	new_movie->booking = 0;
	printf("\t\t\t电影名：");
	mygets(new_movie->movie_name, 49, stdin);
movie_id_again:
	printf("\t\t\t电影ID：");
	mygets(new_movie->movie_id, 49, stdin);
	for (movie_p = movie_head->link; movie_p != NULL; movie_p = movie_p->link)
	{
		if (strcmp(movie_p->movie_id, new_movie->movie_id) == 0)
		{
			char i;
			printf("\t\t\tid重复！\n");
			printf("\t\t\t【1】重新输入\n【0】返回\n");
			do {
				i = getch();
			} while (i != '0'&&i != '1');
			if (i == '0')return;
			else
			{
				system("cls");
				printf("\t\t\t请输入电影信息：\n");
				//	getchar();
				printf("\t\t\t电影名：");
				printf("\t\t\t%s\n", new_movie->movie_name);
				goto movie_id_again;
			}
		}
	}

	printf("\t\t\t主演：");
	mygets(new_movie->starring, 49, stdin);
	printf("\t\t\t导演：");
	mygets(new_movie->derector, 49, stdin);
	dateagain:
	printf("\t\t\t首映时间（年 月 日）：");
	scanf("%d %d %d", &(new_movie->Date.year), &(new_movie->Date.month), &(new_movie->Date.day));
	while ((ch = getchar()) != '\n'&&ch != EOF);
	if (new_movie->Date.year < 1500 || new_movie->Date.month>12 || new_movie->Date.month < 1 || new_movie->Date.day < 1 || new_movie->Date.day>31)
	{
		printf("\t\t\t输入日期有误\n");
		goto dateagain;
	}
	printf("\t\t\t国家：");
	mygets(new_movie->nation,49,stdin);
	printf("\t\t\t片长（分钟）：");
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
	printf("\t\t\t语言：");
	mygets(new_movie->language, 49, stdin);
	printf("\t\t\t类型：");
	mygets(new_movie->type,49,stdin);
	printf("\t\t\t电影简介：");
	mygets(new_movie->movie_description,99,stdin);

	printf("\t\t\t【1】确认添加\n");
	printf("\t\t\t【2】重新输入\n");
	printf("\t\t\t【0】返回\n");
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
		if ((fp = fopen("Movie.txt", "w")) == NULL)//打开文件
		{
			printf("Movie.txt文件打开失败！\n");
			Sleep(800);
			exit(1);
		}
		else {//打开文件成功
			for (movie_p = movie_head->link; movie_p != NULL; movie_p = movie_p->link)
			{
				fwrite(movie_p, sizeof(Movie), 1, fp);
			}
			fclose(fp);
		}
		printf("\t\t\t添加成功！\n");
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
		printf("\t\t\t输入电影ID：");
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
			printf("\t\t\t未找到\n");
			printf("\t\t\t【1】重新输入\n【0】返回\n");
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
				printf("\t\t\t是否删除次电影？\n");
				printf("\t\t\t********************************\n");
				printf("\t\t\t电影名：%s\n", p->link->movie_name);
				printf("\t\t\t主演：%s\n", p->link->starring);
				printf("\t\t\t导演：%s\n", p->link->derector);
				printf("\t\t\t上映日期：%d %d %d\n", p->link->Date.year, p->link->Date.month, p->link->Date.day);
				printf("\t\t\t国家：%s\n", p->link->nation);
				printf("\t\t\t语言：%s\n", p->link->language);
				printf("\t\t\t时长：%smin\n", p->link->length);
				printf("\t\t\t类型：%s\n",p->link->type);
				printf("\t\t\t电影描述：%s\n", p->link->movie_description);
				printf("\t\t\t电影ID：%s\n", p->link->movie_id);
				printf("\t\t\t********************************\n");
				printf("\t\t\t【1】确定 【0】返回\n");

				key = getch();
			} while (key != '1'&&key != '0');
			switch (key)
			{
			case '1':
				pfree = p->link;
				p->link = p->link->link;
				free(pfree);


				if ((fp = fopen("Movie.txt", "w")) == NULL)//打开文件
				{
					printf("Movie.txt文件打开失败！\n");
					Sleep(800);
					exit(1);
				}
				else {//打开文件成功
					for (movie_p = movie_head->link; movie_p != NULL; movie_p = movie_p->link)
					{
						fwrite(movie_p, sizeof(Movie), 1, fp);
					}
					fclose(fp);
				}
				printf("\t\t\t删除成功\n");
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
	printf("\t\t\t请输入需要修改的电影ID：");
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
		printf("\t\t\t未找到\n");
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
				printf("\t\t\t请选择需要修改的选项：\n\n");
				printf("\t\t\t【1】电影名：%s\n", p->movie_name);
				printf("\t\t\t【2】主演：%s\n", p->starring);
				printf("\t\t\t【3】导演：%s\n", p->derector);
				printf("\t\t\t【4】上映日期：%d %d %d\n", p->Date.year, p->Date.month, p->Date.day);
				printf("\t\t\t【5】国家：%s\n", p->nation);
				printf("\t\t\t【6】语言：%s\n", p->language);
				printf("\t\t\t【7】时长：%smin\n", p->length);
				printf("\t\t\t【8】类型：%s\n",p->type);
				printf("\t\t\t【9】电影描述：%s\n", p->movie_description);
				printf("\t\t\t【0】保存退出\n\n");

				key = getch();
			} while (key<'0' || key>'9');
			char ch;
			int i;
			int year, month, day;
			switch (key)
			{
			case '1':
				printf("\t\t\t【1】电影名：");
				mygets(p->movie_name, 49, stdin);
				break;

			case '2':
				printf("\t\t\t【2】主演：");
				mygets(p->starring, 49, stdin);
				break;

			case '3':
				printf("\t\t\t【3】导演：");
				mygets(p->derector,49,stdin);
				break;

			case '4':
				dateagain:
				printf("\t\t\t【4】上映日期：");
				scanf("%d %d %d", &(year), &(month), &(day));
				while ((ch = getchar()) != '\n'&&ch != EOF);
				if (year < 1500 || month>12 || month < 1 || day < 1 || day>31)
				{
					printf("\t\t\t输入日期有误\n");
					goto dateagain;
				}
				p->Date.year = year;
				p->Date.month = month;
				p->Date.day = day;
				break;

			case '5':
				printf("\t\t\t【5】国家：");
				mygets(p->nation, 49, stdin);
				break;
			case '6':
				printf("\t\t\t【6】语言：");
				mygets(p->language,49,stdin);
				break;
			case '7':
				printf("\t\t\t【7】时长：");
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
				printf("\t\t\t【8】类型：");
				mygets(p->type, 49, stdin);
				break;
			case '9':
				printf("\t\t\t【9】电影描述：");
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
		if ((fp = fopen("Movie.txt", "w")) == NULL)//打开文件
		{
			printf("Movie.txt文件打开失败！\n");
			Sleep(800);
			exit(1);
		}
		else {//打开文件成功
			for (movie_p = movie_head->link; movie_p != NULL; movie_p = movie_p->link)
			{
				fwrite(movie_p, sizeof(Movie), 1, fp);
			}
			fclose(fp);
		}
		printf("\t\t\t修改成功！\n");
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
		printf("\t\t\t电影名：%s\n", p->movie_name);
		printf("\t\t\t主演：%s\n", p->starring);
		printf("\t\t\t导演：%s\n", p->derector);
		printf("\t\t\t上映日期：%d年%d月%d日\n", p->Date.year, p->Date.month, p->Date.day);
		printf("\t\t\t国家：%s\n", p->nation);
		printf("\t\t\t语言：%s\n", p->language);
		printf("\t\t\t时长：%smin\n", p->length);
		printf("\t\t\t类型：%s\n",p->type);
		printf("\t\t\t电影描述：%s\n", p->movie_description);
		printf("\t\t\t电影ID：%s\n", p->movie_id);
		printf("\t\t\t********************************\n");
	}

	printf("\t\t\t任意键返回\n");
	getch();

}


/*场次*/
void show_manage_ui(void)
{
	char key;
	while (1)
	{
		do {
			system("cls");

			printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
			printf("\t\t\t‖               场  次  管  理                      ‖\n");
			printf("\t\t\t╠ = = = = = = = = = = = = = = = = = = = = = = = = = ╣\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 1 】 添加场次                        ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 2 】 删除场次                        ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 3 】 场次修改                        ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 4 】 场次查看                        ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 0 】  返 回                          ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
			printf("\t\t\t请输入选项：");
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
	printf("\t\t\t请输入场次id：");
	mygets(new_show->show_id,49,stdin);
	for (show_p = show_head->link; show_p != NULL; show_p = show_p->link)
	{
		if (strcmp(show_p->show_id, new_show->show_id) == 0)
		{
			char i;
			printf("\t\t\tid重复！\n");
			printf("\t\t\t【1】重新输入\n\t\t\t【0】返回\n");
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
	printf("\t\t\t请输入电影ID：");
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
			printf("\t\t\tid输入错误\n");
			printf("\t\t\t【1】重新输入 【0】返回\n");
			key = getch();
		} while (key != '1'&&key != '0');
		if (key == '1')goto newida;
		else return;
	}

	while (1) 
	{
		printf("\t\t\t请输入放映厅编号：");
		scanf("%d", &(new_show->hall_id));
		if (new_show->hall_id < 1 || new_show->hall_id>8)
		{
			printf("\t\t\t放映厅不存在!\n");
			while ((ch = getchar()) != '\n'&&ch != EOF);
		}
		else break;
	}

	printf("\t\t\t请输入票价(经不起折腾)：");
	scanf("%f", &(new_show->cost));
	while ((ch = getchar()) != '\n'&&ch != EOF);

	showdata:
	int timeflag=1;
	dateagain:
	printf("\t\t\t开场日期：");
	scanf("%d %d %d", &new_show->begintime.year, &new_show->begintime.month, &new_show->begintime.day);
	while ((ch = getchar()) != '\n'&&ch != EOF);
	if (new_show->begintime.year < 1500 || new_show->begintime.month>12 || new_show->begintime.month < 1 || new_show->begintime.day < 1 || new_show->begintime.day>31)
	{
		printf("\t\t\t输入日期有误\n");
		goto dateagain;
	}

	if(movie_p->Date.year>new_show->begintime.year||(movie_p->Date.year==new_show->begintime.year&&movie_p->Date.month>new_show->begintime.month)||(movie_p->Date.year==new_show->begintime.year&&movie_p->Date.month==new_show->begintime.month)&& movie_p->Date.day>new_show->begintime.day)
	{
		printf("\t\t\t输入日期有误\n");
		goto dateagain;
	}


	timeagain:
	printf("\t\t\t开场时间：");
	scanf("%d %d", &new_show->begintime.hour, &new_show->begintime.minute);
	while ((ch = getchar()) != '\n'&&ch != EOF);
	if (new_show->begintime.hour < 0 || new_show->begintime.hour>23|| new_show->begintime.minute < 0 || new_show->begintime.minute >59 )
	{
		printf("\t\t\t输入时间有误\n");
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
		printf("\t\t\t时间有误！\n");
		printf("\t\t\t【1】重新输入时间\n\t\t\t【2】全部重新输入\n\t\t\t【0】返回\n");
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

			//printf("相同的厅");
			//		show_p->begintime.year == new_show->begintime.year&&show_p->begintime.month == new_show->begintime.month&&show_p->begintime.day == new_show->begintime.day
			long int a, b;
			if (show_p->begintime.year == new_show->begintime.year&&show_p->begintime.month == new_show->begintime.month&&show_p->begintime.day == new_show->begintime.day)
			{
				//printf("同一天");
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
			//	printf("12月 1月");
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
			printf("\t\t\t时间有误！\n");
			printf("\t\t\t【1】重新输入时间\n\t\t\t【2】全部重新输入\n\t\t\t【0】返回\n");
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
		printf("\t\t\t【1】确认添加\n");
		printf("\t\t\t【2】重新输入\n");
		printf("\t\t\t【0】返回\n");
		key = getch();
	} while (key != '1'&&key != '2'&&key != '0');
	
	switch (key)
	{
		case '1':
			for (show_p = show_head; show_p->link != NULL; show_p = show_p->link);
			show_p->link = new_show;
			new_show->link = NULL;
			if ((fp = fopen("Show.txt", "w")) == NULL)//打开文件
			{
				printf("Show.txt文件打开失败！\n");
				Sleep(800);
				exit(1);
			}
			else {//打开文件成功
				for (show_p = show_head->link; show_p != NULL; show_p = show_p->link)
				{
					fwrite(show_p, sizeof(Show), 1, fp);
				}
				fclose(fp);
			}
			printf("\t\t\t添加成功！\n");
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
		printf("\t\t\t输入场次ID：");
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
			printf("\t\t\t未找到\n");
			printf("\t\t\t【1】重新输入\n\t\t\t【0】返回\n");
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
				printf("\t\t\t是否删除此场次？\n");
				printf("\t\t\t********************************\n");
				printf("\t\t\t场次ID：%s\n", p->link->show_id);
				printf("\t\t\t时间：%d时%d分\n", p->link->begintime.hour, p->link->begintime.minute);
				printf("\t\t\t日期：%d年%d月%d日\n", p->link->begintime.year, p->link->begintime.month, p->link->begintime.day);
				printf("\t\t\t票价：%f\n", p->link->cost);
				printf("\t\t\t电影ID：%s\n", p->link->film_id);
				printf("\t\t\t放映厅：%d\n", p->link->hall_id);
				printf("\t\t\t********************************\n");
				printf("\t\t\t【1】确定 【0】返回\n");

				key = getch();
			} while (key != '1'&&key != '0');
			switch (key)
			{
			case '1':
				pfree = p->link;
				p->link = p->link->link;
				free(pfree);


				if ((fp = fopen("Show.txt", "w")) == NULL)//打开文件
				{
					printf("Show.txt文件打开失败！\n");
					Sleep(800);
					exit(1);
				}
				else {//打开文件成功
					for (show_p = show_head->link; show_p != NULL; show_p = show_p->link)
					{
						fwrite(show_p, sizeof(Show), 1, fp);
					}
					fclose(fp);
				}
				printf("\t\t\t删除成功\n");
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
	printf("\t\t\t请输入需要修改的场次ID：");
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
		printf("\t\t\t未找到\n");
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
				printf("\t\t\t请选择需要修改的选项：\n");
				printf("\t\t\t【1】价格：%f\n", p->cost);
				printf("\t\t\t【2】放映厅：%d\n", p->hall_id);
				printf("\t\t\t【3】放映日期：%d年%d月%d日\n", p->begintime.year,p->begintime.month,p->begintime.day);
				printf("\t\t\t【4】放映时间：%d时%d分\n", p->begintime.hour,p->begintime.minute);
				printf("\t\t\t【0】保存退出\n\n");

				key = getch();
			} while (key<'0' || key>'9');

			int timeflag = 1;
			Show *show_p;
			char ch;
			int ha_id;
			switch (key)
			{
			case '1':
				printf("\t\t\t【1】价格：");
				scanf("%f", &(p->cost));
				while ((ch = getchar()) != '\n'&&ch != EOF);
				break;
			case '2':
				haag:
				printf("\t\t\t【2】放映厅：");
				scanf("%d", &ha_id);
				if (ha_id < 1 || ha_id>8)
				{
					printf("\t\t\t放映厅不存在!\n");
					while ((ch = getchar()) != '\n'&&ch != EOF);
					goto haag;
				}
				p->hall_id = ha_id;
				break;
			case '3':
				printf("\t\t\t【3】放映日期：");
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
						printf("\t\t\t时间冲突！\n");/*为什么不显示这句话 吐血*/
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
				printf("\t\t\t【4】放映时间：");
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
						printf("\t\t\t时间冲突！\n");
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
		if ((fp = fopen("Show.txt", "w")) == NULL)//打开文件
		{
			printf("Show.txt文件打开失败！\n");
			Sleep(800);
			exit(1);
		}
		else {//打开文件成功
			for (show_p = show_head->link; show_p != NULL; show_p = show_p->link)
			{
				fwrite(show_p, sizeof(Show), 1, fp);
			}
			fclose(fp);
		}
		printf("修改成功！\n");
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
		printf("\t\t\t场次ID：%s\n", p->show_id);
		printf("\t\t\t时间：%d时%d分\n", p->begintime.hour,p->begintime.minute);
		printf("\t\t\t日期：%d年%d月%d日\n", p->begintime.year,p->begintime.month,p->begintime.day);
		printf("\t\t\t票价：%f\n", p->cost);
		printf("\t\t\t电影ID：%s\n",p->film_id);
		printf("\t\t\t放映厅：%d\n", p->hall_id);
		printf("\t\t\t********************************\n");
	}
	printf("\t\t\t任意键返回\n");
	getch();
}


/*员工*/
void staff_manage_ui(void)
{
	char key;
	while (1)
	{
		do {
			system("cls");

			printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
			printf("\t\t\t‖               员  工  管  理                      ‖\n");
			printf("\t\t\t╠ = = = = = = = = = = = = = = = = = = = = = = = = = ╣\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 1 】 添加员工                        ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 2 】 删除员工                        ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 3 】 员工修改                        ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 4 】 员工查看                        ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 0 】  返 回                          ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
			printf("\t\t\t请输入选项：");
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
	printf("\t\t\t请输入新员工ID：");
	mygets(new_staff->staff_id,19,stdin);
	for (staff_p = staff_head->link; staff_p != NULL; staff_p = staff_p->link)
	{
		if (strcmp(new_staff->staff_id, staff_p->staff_id) == 0)
		{
			printf("\t\t\t重复ID！\n");
			printf("\t\t\t【1】重新输入\n\t\t\t【0】返回\n");
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
	printf("\t\t\t请输入员工密码（6-12位）：");
	input_password(new_staff->staff_password);
	if (strlen(new_staff->staff_password) < 6)
	{
		printf("\t\t\t位数不对");
		Sleep(500);
		goto new_staff_password;
	}
	printf("\n\t\t\t请输入员工权限等级：");
	scanf("%d", &new_staff->staff_limit);
	printf("\t\t\t【1】确定添加\n\t\t\t【2】重新输入\n\t\t\t【0】返回");
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

		if ((fp = fopen("Staff.txt", "wb")) == NULL)//打开文件
		{
			printf("Staff.txt文件打开失败！\n");
			Sleep(800);
			exit(1);
		}
		else {//打开文件成功

			for (staff_p = staff_head->link; staff_p != NULL; staff_p = staff_p->link)
			{
				fwrite(staff_p, sizeof(Staff), 1, fp);
			}
			
			fclose(fp);
		}
		printf("\t\t\t新员工添加成功！\n");
		Sleep(800);
	}

}

void staff_removation(void)
{
	char id[20];
	while (1)
	{
		system("cls");
		printf("\n\t\t\t输入员工ID：");
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
			printf("\t\t\t未找到\n");
			printf("\t\t\t【1】重新输入\n\t\t\t【0】返回\n");
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
				printf("\t\t\t是否删除此员工？\n");
				printf("\t\t\t********************************\n");
				printf("\t\t\t员工ID：%s\n", p->link->staff_id);
				printf("\t\t\t员工权限：%d\n", p->link->staff_limit);
				printf("\t\t\t********************************\n");
				printf("\t\t\t【1】确定 【0】返回\n");

				key = getch();
			} while (key != '1'&&key != '0');
			switch (key)
			{
			case '1':
				pfree = p->link;
				p->link = p->link->link;
				free(pfree);


				if ((fp = fopen("Staff.txt", "w")) == NULL)//打开文件
				{
					printf("Staff.txt文件打开失败！\n");
					Sleep(800);
					exit(1);
				}
				else {//打开文件成功
					for (staff_p = staff_head->link; staff_p != NULL; staff_p = staff_p->link)
					{
						fwrite(staff_p, sizeof(Staff), 1, fp);
					}
					fclose(fp);
				}
				printf("\n\t\t\t删除成功\n");
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
	printf("\t\t\t功能暂未实现，敬请期待！\n");
	Sleep(500);

}

void staff_check(void)
{
	system("cls");
	Staff *p;

	printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
	printf("\t\t\t‖              查 看 所 有 员 工                    ‖\n");
	printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
	for (p = staff_head->link; p != NULL; p = p->link)
	{

		printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
		printf("\t\t\t      员工ID：%20s               \n", p->staff_id);
		printf("\t\t\t      员工权限：%d                                  \n", p->staff_limit);
		printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
	}

	printf("\t\t\t任意键返回\n");
	getch();
}

/*订单*/
void order_manage_ui(void)
{
	system("cls");
	Order *p;

	printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
	printf("\t\t\t‖              所 有 订 单 列 表                    ‖\n");
	printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
	for (p = order_head->link; p != NULL; p = p->link)
	{


		printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
		printf("\t\t\t         用户：%12s             \n", p->customer_id);
		printf("\t\t\t         电影名：%20s           \n", p->movie_name);
		printf("\t\t\t         时间：%d年%2d月%2d日%2d时%2d分           \n", p->begintime.year, p->begintime.month, p->begintime.day, p->begintime.hour, p->begintime.minute);
		printf("\t\t\t         厅号：%d号厅                              \n", p->hall_id);
		printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");

		
	}
	printf("\t\t\t任意键返回\n");
	getch();
}





/*顾客*/
void customer_ui(void)
{
	char key;
	while (1)
	{
		do {
			system("cls");
			printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
			printf("\t\t\t‖            欢迎您 %s                     ‖\n",user->present_customer_information->customer_phonenumber);
			printf("\t\t\t╠ = = = = = = = = = = = = = = = = = = = = = = = = = ╣\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 1 】 查看电影                        ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 2 】 查看订单                        ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 0 】  退  出                         ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
			printf("\t\t\t请输入选项：");
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
			printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
			printf("\t\t\t‖               电     影                           ‖\n");
			printf("\t\t\t╠ = = = = = = = = = = = = = = = = = = = = = = = = = ╣\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 1 】 正在热映                        ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 2 】 即将上映                        ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 3 】 票房排行                        ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖           【 0 】  返  回                         ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
			printf("\t\t\t请输入选项：");
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
	printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
	printf("\t\t\t‖               正  在  热  映                      ‖\n");
	printf("\t\t\t╠ = = = = = = = = = = = = = = = = = = = = = = = = = ╣\n");
	for (movie_p = movie_head->link; movie_p != NULL; movie_p = movie_p->link)
	{
		for (show_p = show_head->link; show_p != NULL; show_p = show_p->link)
		{
			if (strcmp(movie_p->movie_id, show_p->film_id) == 0 && show_p->begintime.year == (1900 + p->tm_year) && show_p->begintime.month == (p->tm_mon) + 1 && show_p->begintime.day == p->tm_mday)
			{


				printf("\t\t\t‖     电影名：%10s           \n",movie_p->movie_name);
				printf("\t\t\t‖     电影ID：%10s           \n", movie_p->movie_id);
				printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
				count++;
				break;
			}
		}
	}
	if (count == 1)
	{

		printf("\t\t\t‖                暂无热映电影                       ‖\n");
		printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
		Sleep(800);
		return;
	}


	printf("\n\n");
	printf("\t\t\t【1】输入电影ID查看详细\n");
	printf("\t\t\t【0】返回\n");
	printf("\t\t\t请输入选项：");
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
		printf("\t\t\t电影ID：");
		int i = 0;
		mygets(id, 49, stdin);
//		scanf("%s", id);

		int findflag = 0;
		for (movie_p = movie_head->link; movie_p != NULL; movie_p = movie_p->link)
		{
			if (strcmp(movie_p->movie_id, id) == 0)
			{
				system("cls");
				printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
				printf("\t\t\t                %s                 \n",movie_p->movie_name);
				printf("\t\t\t╠ = = = = = = = = = = = = = = = = = = = = = = = = = ╣\n");
				printf("\t\t\t‖                                                   ‖\n");
				printf("\t\t\t‖         主演：    %s                \n", movie_p->starring);
				printf("\t\t\t‖         导演：    %s                          \n",movie_p->derector);
				printf("\t\t\t‖         上映时间：%d年%2d月%2d日                  \n", movie_p->Date.year, movie_p->Date.month, movie_p->Date.day);
				printf("\t\t\t‖         国家：    %s                          \n" , movie_p ->nation);
				printf("\t\t\t‖         语言：    %s                          \n" , movie_p ->language);
				printf("\t\t\t‖         时长：    %s                             \n", movie_p ->length);
				printf("\t\t\t‖         类型：    %s                          \n", movie_p ->type);
				printf("\t\t\t‖         电影描述：%s...                \n", movie_p ->movie_description);
				printf("\t\t\t‖         电影ID：  %s                \n", movie_p->movie_id);
				printf("\t\t\t‖                                                   ‖\n");
				printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
				findflag = 1;
				break;
			}
			
		}

		if (findflag == 0)
		{
			printf("\n\t\t\t输入有误\n");
			goto findida;
		}

		printf("\n\n\n");

		printf("\t\t\t【1】查看%s排场\n", movie_p->movie_name);
		printf("\t\t\t【0】返回\n");
		char keyy;
		do
		{
			keyy = getch();
		} while (keyy != '1'&&keyy != '0');
		if (keyy == '1')
		{
			count = 1;
			printf("\t\t\t【1】今日排场\n");
			printf("\t\t\t【2】明日排场\n");
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
							printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
							printf("\t\t\t‖    场次ID：%s               \n", show_p->show_id);
							printf("\t\t\t‖    时间：%2d时 %2d分                            \n", show_p->begintime.hour, show_p->begintime.minute);
							printf("\t\t\t‖    价格：%5.2f元                                  \n", show_p->cost);
							printf("\t\t\t‖    大厅：%d号厅                                  \n", show_p->hall_id);
							printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
							count++;
						}
					}
				}

				printf("\t\t\t【1】输入场次ID购票\n");
				printf("\t\t\t【0】返回\n");
				do
				{
					keyy = getch();
				} while (keyy != '1'&&keyy != '0');
				if (keyy == '1')
				{
					char showid[20];
				findsida:
					printf("\n");
					printf("\t\t\t场次ID：");
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
									printf("\t\t\t确定购买？（y or n）");
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

										if ((fp = fopen("Order.txt", "wb")) == NULL)//打开文件
										{
											printf("Order.txt文件打开失败！\n");
											Sleep(800);
											exit(1);
										}
										else {//打开文件成功
											for (order_p = order_head->link; order_p != NULL; order_p = order_p->link)
											{
												fwrite(order_p, sizeof(Order), 1, fp);
											}
											fclose(fp);
										}


										if ((fp = fopen("Movie.txt", "wb")) == NULL)//打开文件
										{
											printf("Movie.txt文件打开失败！\n");
											Sleep(800);
											exit(1);
										}
										else {//打开文件成功
											for (movie_p = movie_head->link; movie_p != NULL; movie_p = movie_p->link)
											{
												fwrite(movie_p, sizeof(Movie), 1, fp);
											}
											fclose(fp);
										}

										printf("\n\t\t\t【订票成功!】\n");
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
						printf("\t\t\t输入ID有误\n");
						goto findsida;
					}
				}



			}
			else
			{
				system("cls");
				printf("即将实现功能");
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
			printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
			printf("\t\t\t                 %s                      \n",movie_p->movie_name);
			printf("\t\t\t╠ = = = = = = = = = = = = = = = = = = = = = = = = = ╣\n");
			printf("\t\t\t‖                                                   \n");
			printf("\t\t\t‖     主演：    %s                \n", movie_p->starring);
			printf("\t\t\t‖     导演：    %s                          \n", movie_p->derector);
			printf("\t\t\t‖     上映时间：%d年%2d月%2d日                  \n", movie_p->Date.year, movie_p->Date.month, movie_p->Date.day);
			printf("\t\t\t‖     国家：    %s                          \n", movie_p->nation);
			printf("\t\t\t‖     语言：    %s                          \n", movie_p->language);
			printf("\t\t\t‖     时长：    %s                             \n", movie_p->length);
			printf("\t\t\t‖     类型：    %s                          \n", movie_p->type);
			printf("\t\t\t‖     电影描述：%s...                \n", movie_p->movie_description);
			printf("\t\t\t‖     电影ID：  %s                \n", movie_p->movie_id);
			printf("\t\t\t‖                                                   ‖\n");
			printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
			printf("\n");
			count++;
		}
	}
	if(count == 1)
	{
		printf("\t\t\t暂无电影预告\n");
		Sleep(800);
		return;
	}

	printf("\t\t\t按任意键返回\n");
	getch();
}

void customer_movie_rank(void)
{
	char key;
	do {
		system("cls");
		printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
		printf("\t\t\t‖                   票       房                     ‖\n");
		printf("\t\t\t╠ = = = = = = = = = = = = = = = = = = = = = = = = = ╣\n");
		printf("\t\t\t‖                                                   ‖\n");
		printf("\t\t\t‖                                                   ‖\n");
		printf("\t\t\t‖           【 1 】 总 票 房 排 行                  ‖\n");
		printf("\t\t\t‖                                                   ‖\n");
		printf("\t\t\t‖           【 2 】 热 映 排 行                     ‖\n");
		printf("\t\t\t‖                                                   ‖\n");
		printf("\t\t\t‖           【 0 】  返   回                        ‖\n");
		printf("\t\t\t‖                                                   ‖\n");
		printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
		printf("\t\t\t请输入选项：");

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

	printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
	printf("\t\t\t‖                总 票 房 排 行                     ‖\n");
	printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
	for (movie_p = movie_head->link,n=5; movie_p != NULL&&n>=0; movie_p = movie_p->link,n--)
	{
		printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
		printf("\t\t\t‖                   第%d名                          \n", 6- n);
		printf("\t\t\t‖       电影名：%s            \n", movie_p->movie_name);
		printf("\t\t\t‖       电影票房：%d                              \n", movie_p->booking);
		printf("\t\t\t‖       电影描述：%s          \n", movie_p->movie_description);
		printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
	}
	printf("\t\t\t任意键返回\n");
	getch();

}


void customer_movie_rank_now(void)
{
	sort_movie();
	Movie *movie_p;
	Show *show_p;
	int n = 5;
	system("cls");
	printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
	printf("\t\t\t‖                总 票 房 排 行                     ‖\n");
	printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
	for (movie_p = movie_head->link,n=5; movie_p != NULL&&n>=0; movie_p = movie_p->link,n--)
	{
		for (show_p = show_head->link; show_p != NULL; show_p = show_p->link)
		{
			if (strcmp(movie_p->movie_id, show_p->film_id) == 0 && show_p->begintime.year == (1900 + p->tm_year) && show_p->begintime.month == (p->tm_mon) + 1 && show_p->begintime.day == p->tm_mday)
			{

				printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
				printf("\t\t\t‖                   第%d名                          \n", 6 - n);
				printf("\t\t\t‖       电影名：%s            \n", movie_p->movie_name);
				printf("\t\t\t‖       电影票房：%d                              \n", movie_p->booking);
				printf("\t\t\t‖       电影描述：%s          \n", movie_p->movie_description);
				printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
				break;
			}
		}
	}

	printf("\t\t\t任意键返回\n");
	getch();
}


void sort_movie(void)
{
	Movie *p1, *p2, *temp, *prep1, *prep2;
	if (movie_head->link->link == NULL)
		return ;
	for (p1 = movie_head->link->link, prep1 = movie_head->link; p1 != NULL; p1 = p1->link, prep1 = prep1->link)
	{
		temp = p1;    /*保存待插入节点*/
		for (p2 = movie_head->link, prep2 = movie_head; p2 != p1; p2 = p2->link, prep2 = prep2->link)
		{
			if (p2->booking < p1->booking)
			{
				p1 = p1->link;
				prep1->link = temp->link;    /*删除待插入节点*/
				prep2->link = temp;              /*将其插入对应位置*/
				temp->link = p2;
				break;
			}
			else if (p2->booking == p1->booking &&( (p2->Date.year < p1->Date.year) || (p2->Date.year == p1->Date.year)&&(p2->Date.month < p1->Date.month)|| (p2->Date.year == p1->Date.year) && (p2->Date.month == p1->Date.month)&&(p2->Date.day<p1->Date.day)))
			{
				p1 = p1->link;
				prep1->link = temp->link;    /*删除待插入节点*/
				prep2->link = temp;              /*将其插入对应位置*/
				temp->link = p2;
				break;
			}
		}
	}


}


void customer_order_ui(void)
{
	system("cls");
	printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
	printf("\t\t\t‖                我  的  订  单                     ‖\n");
	printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");
	Order *p;
	for (p = order_head->link; p != NULL; p = p->link)
	{
		if (strcmp(p->customer_id, user->user_id) == 0)
		{

			printf("\t\t\t╔ = = = = = = = = = = = = = = = = = = = = = = = = = ╗\n");
			printf("\t\t\t‖       电影名：%20s            \n", p->movie_name);
			printf("\t\t\t‖       时间：%d年%2d月%2d日%2d时%2d分            \n", p->begintime.year, p->begintime.month, p->begintime.day, p->begintime.hour, p->begintime.minute);
			printf("\t\t\t‖       厅号：%d号厅                             \n", p->hall_id);
			printf("\t\t\t╚ = = = = = = = = = = = = = = = = = = = = = = = = = ╝\n");

		}
	}

	printf("\t\t\t任意键返回\n");
	getch();


}



/*ccccccccccccccccccccccccccccccccccc密码读取*/
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

	/*写文件*/
	FILE *fp;

	/*顾客账户*/
	Customer *customer_p;
	if ((fp = fopen("Customer.txt", "w")) == NULL)//打开文件
	{
		printf("Customer.txt文件打开失败！\n");
		Sleep(800);
		exit(1);
	}
	else {//打开文件成功

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