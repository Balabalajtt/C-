/*
 * Studio_UI.c
 *
 *  Created on: 2015年4月24日
 *      Author: Administrator
 */
#include "Studio_UI.h"

#include "../Common/list.h"
#include "../Service/studio.h"
#include "../Service/seat.h"
#include "../Service/EntityKey.h"
#include "Seat_UI.h"

static const int STUDIO_PAGE_SIZE = 5;

#include <stdio.h>

void Studio_UI_MgtEntry(void) {




	int i, id;
	char choice;

	studio_list_t head;
	studio_node_t *pos;
	Pagination_t paging;

	List_Init(head, studio_node_t);
	paging.offset = 0;
	paging.pageSize = STUDIO_PAGE_SIZE;

	//载入数据
	paging.totalRecords = Studio_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);

	do {
		system("cls");
				printf("\n\n");
						printf("\n\t    ☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★\n\n");
						printf("\t\t\t\t\t\t\t演出厅列表 \n\n");
						printf("\t§§§§-----------------------------------------------------"
								"------------------------------------§§§§\n\n");
						printf("\t\t\t   %-5s  %-18s  %-10s  %-10s  %-10s\n\n", "ID", "Name", "Row Count",
								"ColumnsCount", "SeatsCount");
						printf("\t========================================================================================================\n");

				//显示数据
				for (i = 0, pos = (studio_node_t *) (paging.curPos);
						pos != head && i < paging.pageSize; i++) {
					printf("\t\t\t   %-6d  %-19s  %-12d  %-13d  %-14d\n", pos->data.id,
							pos->data.name, pos->data.rowsCount, pos->data.colsCount,
							pos->data.seatsCount);
					pos = pos->next;
				}
				printf("\t========================Total Records:%2d ========================= Page %2d/%2d="
								"==========================\n\n",paging.totalRecords, Pageing_CurPage(paging),
								Pageing_TotalPages(paging));
				printf(
								"\n\t\t\t[A]\t增加新的演出厅\t\t[D]\t删除演出厅\n\n"
								"\t\t\t[U]\t更新\t\t\t[S]\t座位\n\n"
								 "\t\t\t[N]\t下一页\t\t\t[P]\t上一页\n\n"
								 "\t\t\t[R]\t返回 \t\t\n");
				printf("\n\t\t\t请输入你想要办的业务:");

		fflush(stdin);
		scanf("%c", &choice);
				fflush(stdin);
		switch (choice) {
		case 'a':
		case 'A':
			if (Studio_UI_Add()) //新添加成功，跳到最后一页显示
			{
				paging.totalRecords = Studio_Srv_FetchAll(head);
				Paging_Locate_LastPage(head, paging, studio_node_t);
			}
			break;
		case 'd':
		case 'D':
			printf("\n\t\t\t请输入演出厅的ID:");
			scanf("%d", &id);
			if (Studio_UI_Delete(id)) {	//从新载入数据
				paging.totalRecords = Studio_Srv_FetchAll(head);
				List_Paging(head, paging, studio_node_t);
			}
			break;
		case 'u':
		case 'U':
			printf("\n\t\t\t请输入演出厅的ID:");
			scanf("%d", &id);
			if (Studio_UI_Modify(id)) {	//从新载入数据
				paging.totalRecords = Studio_Srv_FetchAll(head);
				List_Paging(head, paging, studio_node_t);
			}
			break;
		case 's':
		case 'S':
			printf("\n\t\t\t请输入演出厅的ID:");
			scanf("%d", &id);
			Seat_UI_MgtEntry(id);
			paging.totalRecords = Studio_Srv_FetchAll(head);
			List_Paging(head, paging, studio_node_t);
			break;
		case 'p':
		case 'P':
			if (1 < Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, studio_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, studio_node_t);
			}
			break;
		}
	} while (choice != 'r' && choice != 'R');
	//释放链表空间
	List_Destroy(head, studio_node_t);

}











void Studio_UI_ListAll(void) {
	int i;
	char choice;

	studio_list_t head;
	studio_node_t *pos;
	Pagination_t paging;

	List_Init(head, studio_node_t);
	paging.offset = 0;
	paging.pageSize = STUDIO_PAGE_SIZE;

	//载入数据
	paging.totalRecords = Studio_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);

	do {
		system("cls");
				printf("\n\n");
						printf("\n\t    ☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★\n\n");
						printf("\t\t\t\t\t\t\t演出厅列表 \n\n");
						printf("\t§§§§-----------------------------------------------------"
								"------------------------------------§§§§\n\n");
						printf("\t\t\t   %-5s  %-18s  %-10s  %-10s  %-10s\n\n", "ID", "Name", "Row Count",
								"ColumnsCount", "SeatsCount");
						printf("\t========================================================================================================\n");

				//显示数据
				for (i = 0, pos = (studio_node_t *) (paging.curPos);
						pos != head && i < paging.pageSize; i++) {
					printf("\t\t\t   %-6d  %-19s  %-12d  %-13d  %-14d\n", pos->data.id,
							pos->data.name, pos->data.rowsCount, pos->data.colsCount,
							pos->data.seatsCount);
					pos = pos->next;
				}
				printf("\t========================Total Records:%2d ========================= Page %2d/%2d="
								"==========================\n\n",paging.totalRecords, Pageing_CurPage(paging),
								Pageing_TotalPages(paging));
				printf(
								"\n\t\t\t[N]  下一页\t[P]  上一页\t[R]  返回 \t\t\n");
		//		printf("\n\t\t\t请输入你想要办的业务:");

		fflush(stdin);
		scanf("%c", &choice);
		fflush(stdin);

		switch (choice) {
/*		case 's':
		case 'S':
			printf("Input the ID:");
			scanf("%d", &id);
			Seat_UI_MgtEntry(id);
			paging.totalRecords = Studio_Srv_FetchAll(head);
			List_Paging(head, paging, studio_node_t);
			break;
	*/	case 'p':
		case 'P':
			if (1 < Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, studio_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, studio_node_t);
			}
			break;
		}
	} while (choice != 'r' && choice != 'R');
	//释放链表空间
	List_Destroy(head, studio_node_t);

}










int Studio_UI_Add(void) {
	studio_t rec;
	int newRecCount = 0;
	char choice;

	do {
		system("cls");
		printf("\n\t☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★\n");
			printf("\n\t\t\t\t\t\t添加新的演出厅\n");
			printf("\n\t☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★\n");
			printf("\n\t演出厅的名字:");
		fflush(stdin);
		gets(rec.name);
		printf("\n\t演出厅座位的行数:");
		scanf("%d", &(rec.rowsCount));
		printf("\n\t演出厅座位的列数:");
		scanf("%d", &(rec.colsCount));
		rec.seatsCount = 0;
		printf("\t=======================================================\n");

		//获取主键
		rec.id = EntKey_Srv_CompNewKey("Studio");

		if (Studio_Srv_Add(&rec)) {
			newRecCount += 1;
			printf("\n\t新的演出厅添加成功了!\n\n");
		} else
			printf("\n\t演出厅添加失败了\n\n");
				printf("\n\t-------------------------------------------------------\n\n");
				printf("\n\t[A]\t继续添加 \t\t[R]\t返回:");
		fflush(stdin);
		scanf("%c", &choice);
	} while ('a' == choice || 'A' == choice);
	return newRecCount;
}

int Studio_UI_Modify(int id) {
	studio_t rec;
	int rtn = 0;
	int newrow, newcolumn;
	seat_list_t list;
	int seatcount;

	/*Load record*/
	if (!Studio_Srv_FetchByID(id, &rec)) {
		printf("\t不存在这个演出厅!\n按[Enter]键返回!\n");
		fflush(stdin);
		getchar();
		return 0;
	}
system("cls");
	printf("\n\t☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★\n");
	printf("\n\t\t\t\t\t更改演出厅数据\n");
	printf("\n\t☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★\n");
	printf("\n\t\t你要修改的演出厅的ID:%d\n", rec.id);
	printf("\n\t\t演出厅的名字[%s]:", rec.name);
	fflush(stdin);
	gets(rec.name);

	List_Init(list, seat_node_t);
	seatcount = Seat_Srv_FetchByRoomID(list, rec.id);
	if(seatcount){
		do{			//如果座位文件中已有座位信息，则更新的行列必须比以前大，否则不允许更改
			printf("\n\t\t更新后的座位行数[%d](更新后的座位的行数必须大于原来的行数呦！)", rec.rowsCount);
						scanf("%d", &(newrow));
						printf("\n\t\t更新后的座位列数[%d](更新后的座位的列数必须大于原来的列数呦！)", rec.colsCount);
						scanf("%d", &(newcolumn));
		}while(	newrow<rec.rowsCount||newcolumn<rec.colsCount);
		rec.rowsCount=newrow;
		rec.colsCount=newcolumn;
		rec.seatsCount=seatcount;
	}
	else{
		printf("\n\t\t请输入更新后的行数和列数:");
				scanf("%d", &rec.rowsCount);
				printf("\n\t\t请输入更新后的座位总数:");
				scanf("%d", &rec.colsCount);
		rec.seatsCount=0;
	}


	printf("-------------------------------------------------------\n");

	if (Studio_Srv_Modify(&rec)) {
		rtn = 1;
		printf(
							"\n\t\t演出厅数据更改成功!\n按[Enter]键进行返回!\n");
				} else
					printf("\t\tO演出厅数据更改失败!\n按[Enter]键返回!\n");

	getchar();
	return rtn;
}

int Studio_UI_Delete(int id) {

	int rtn = 0;

	if (Studio_Srv_DeleteByID(id)) {
		//在删除放映厅时，同时根据放映厅id删除座位文件中的座位
		if(Seat_Srv_DeleteAllByRoomID(id))
			printf("\n\t\t成功将该演出厅的座位删除\n");
						printf(
								"\n\t\t成功将该演出厅删除!\n按[Enter]键返回!\n");
						rtn = 1;
					} else {
						printf("\n\t\t不存在该演出厅!\n按[Enter]键继续!\n");
	}

	getchar();
	return rtn;
}

