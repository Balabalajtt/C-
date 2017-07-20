/*
 * SalesAnalysis_UI.c
 *
 *  Created on: 2015年5月8日
 *      Author: Administrator
 */
#include "SalesAnalysis_UI.h"
#include "../Common/list.h"
#include "../Common/common.h"
#include "../Service/SalesAnalysis.h"
#include <conio.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <windows.h>

//外部变量gl_CurUser 用于存储登录用户信息
extern account_t gl_CurUser;

//定义分页机制中页面大小为5
static const int SALESANALYSIS_PAGE_SIZE = 5;

//剧院销售排行榜函数,降序显示截止目前剧院电影票房排行榜
void SalesAnalysis_UI_BoxOffice()
{
	salesanalysis_list_t head;
	char choice;
	salesanalysis_node_t* pos;
	int i;

	List_Init(head, salesanalysis_node_t);

	Pagination_t paging;
	paging.totalRecords = Salesanalysis_Srv_StaticSale(head);
	SalesAnalysis_Srv_SortBySale(head);

	paging.offset = 0;
	paging.pageSize = SALESANALYSIS_PAGE_SIZE;

	Paging_Locate_FirstPage(head, paging);

	do {

		system("cls");
		printf(
				"\n                                 【    票    房    排    行    】                                    \n\n");
		printf(
				"============================================================================================\n");
		printf("%-5s  %-30s  %-10s  %-5s  %-5s  %-8s  %-8s\n", "ID", "剧目名", "区域",
				"售票数", "票房", "上映时间", "下映时间");
		printf(
				"--------------------------------------------------------------------------------------------\n\n");

		for (i = 0, pos = (salesanalysis_node_t *) (paging.curPos);
				pos != head && i < paging.pageSize; i++) {
			printf("%-5d  %-30s  %-10s  %-5ld  %-5ld  %d年%d月%d日 %d年%d月%d日\n",
					pos->data.play_id, pos->data.name, pos->data.area, pos->data.totaltickets, pos->data.sales,
					pos->data.start_date.year, pos->data.start_date.month, pos->data.start_date.day,
					pos->data.end_date.year, pos->data.start_date.month, pos->data.start_date.day);

			pos = pos->next;
		}
		printf(
				"\n--------------------- 总 记 录:%2d ----------------------- 页数 %2d/%2d -----------------------\n\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		printf(
				"******************************************************************\n");
		printf(
				"             [P]revPage | [N]extPage  | [R]eturn");
		printf(
				"\n==================================================================\n");
		printf("Your Choice:");
		fflush(stdin);
		scanf("%c", &choice);
		fflush(stdin);

		switch (choice)
		{

		case 'p':
		case 'P':
			if (1 < Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, salesanalysis_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, salesanalysis_node_t);
			}
			break;
		}
	} while (choice != 'r' && choice != 'R');

	List_Destroy(head, salesanalysis_node_t);

}

//显示售票员在给定日期区间的售票情况
void SalesAnalysis_UI_StatSale(int usrID, user_date_t stDate, user_date_t endDate)
{

	account_t* usr=(account_t*)malloc(sizeof(account_t));
	int salecount;


	salecount = Salesanalysis_Srv_CompSaleVal(usrID, stDate, endDate);

	Account_Srv_FetchByID(usrID, usr);


	printf("销售员：%s\n",usr->username);
	printf("销售员ID：%d\n",usr->id);
	printf("区间销售额：%d\n\n",salecount);
	fflush(stdin);
	printf("回车继续...");
	getchar();
	return ;

}

//销售分析入口函数，显示菜单，菜单包含"降序显示截止目前剧院电影票房排行榜"，“显示或查询当日售票员售票情况”，
//“查询给定日期区间某售票员售票情况”
void SalesAanalysis_UI_MgtEntry()
{


	char choice;
	char salerName[30];
	account_t buf;

	user_date_t nowTime = DateNow();
	user_date_t bTime;
	user_date_t eTime;

	do {
		system("cls");

		printf(
				"\n                                 【    选   项     列    表    】                                    \n\n");
		printf(
				"============================================================================================\n");
		printf(
				"\t\t\t[B]票房排行\n\t\t\t[D]今日销售额\n\t\t\t[S]区间销售额\n\t\t\t[R]返回");

		printf(
				"\n============================================================================================\n");
		printf("Your Choice:");
		fflush(stdin);
		scanf("%c", &choice);
		fflush(stdin);

		switch (choice) {
		case 'b':
		case 'B':
			if( gl_CurUser.type == USR_MANG )
			{
				SalesAnalysis_UI_BoxOffice();
			}
			else
			{
				printf("您无权使用此功能！\n回车返回\n");
				getchar();
			}
			break;
		case 'd':
		case 'D':
			if( gl_CurUser.type == USR_CLERK )
			{
				SalesAnalysis_UI_StatSale(gl_CurUser.id, nowTime, nowTime);

			}
			else
			{
				printf("请输入需要查看的售票员账户：\n");
				gets(salerName);

				if ( Account_Srv_FetchByName(salerName,&buf) == 1 )
				{

					SalesAnalysis_UI_StatSale(buf.id, nowTime, nowTime);
				}
				else
				{
					printf("用户不存在！\n回车返回\n");
					getchar();
				}

			}

			break;
		case 's':
		case 'S':
			//printf("%d",gl_CurUser.type);
			if( gl_CurUser.type ==  USR_MANG)
			{
				printf("请输入需要查看的售票员账号：\n");
				gets(salerName);
				if ( Account_Srv_FetchByName(salerName,&buf) == 1)
				{
					printf("请输入起始时间：");
					scanf("%d %d %d",&bTime.year, &bTime.month, &bTime.day);
					printf("请输入结束时间：");
					scanf("%d %d %d",&eTime.year, &eTime.month, &eTime.day);

					fflush(stdin);
					SalesAnalysis_UI_StatSale(buf.id, bTime, eTime);

				}
				else
				{
					printf("用户不存在！\n回车返回\n");
					getchar();
				}
			}
			else
			{
				printf("您无权使用此功能！\n回车返回\n");
				getchar();
			}
			break;
		}
	} while (choice != 'r' && choice != 'R');

	return;
}

