#include "Play_UI.h"
#include "Schedule_UI.h"
#include "Sale_UI.h"
#include "Ticket_UI.h"
#include "../Service/ticket.h"
#include "../Service/seat.h"
#include "../Service/studio.h"
#include "../Service/EntityKey.h"
#include "../Service/Sale.h"
#include "../Common/common.h"
#include "../Common/list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//���õ�½�û���ȫ�����ݽṹ
extern account_t gl_CurUser;

//���ݼƻ�ID����ʾ�ݳ�Ʊ
void Sale_UI_ShowTicket(int schID)
{
	schedule_t* scheduleBuf = (schedule_t*)malloc(sizeof(schedule_t));
	Schedule_Srv_FetchByID(schID, scheduleBuf);

	seat_list_t seatList;
	List_Init(seatList, seat_node_t);
	Seat_Srv_FetchByRoomID(seatList, scheduleBuf->studio_id);

	ticket_node_t* pos;
	int i;
	char choice;
	Pagination_t paging;
	paging.offset = 0;
	paging.pageSize = TICKET_PAGE_SIZE;
	ticket_list_t ticketList;
	List_Init(ticketList, ticket_node_t);
	paging.totalRecords = Ticket_Srv_FetchBySchID(ticketList, schID);
	Paging_Locate_FirstPage(ticketList, paging);

	do {

		system("cls");
/*		printf(
					      "\n                              ��    ��    ��    Ʊ    ��    ��    ��                                    \n\n");
		printf(
							"======================================================================================================\n");
		printf("           %-10s  %-10s  %-10s %-10s\n", "�ݳ�ƱID", "Ʊ��","��λID", "�ݳ�Ʊ״̬");
		printf(
							"------------------------------------------------------------------------------------------------------\n\n");

	*/
		printf(
							      "\n                              ��    ��    ��    Ʊ    ��    ��    ��                                    \n\n");
		printf(  "========================================================================================================================\n");
		printf("           %-10s  %-10s  %-10s\n", "�ݳ�ƱID", "Ʊ��", "�ݳ�Ʊ״̬");
		printf(
					"------------------------------------------------------------------------------------------------------------------------\n\n");


		for (i = 0, pos = (ticket_node_t *) (paging.curPos);pos != ticketList && i < paging.pageSize; i++)
					{

						printf("\t\t%-10d  %-10d  ",pos->data.id, pos->data.price);
						switch(pos->data.status)
						{
						case TICKET_AVL:
							printf("%-10s","����");
							break;
						case TICKET_SOLD:
							printf("%-10s","����");
							break;
						case TICKET_RESV:
							printf("%-10s","Ԥ��");
							break;
						}

						printf("\n");


						pos = pos->next;

					}
			printf(
					"\n-------------------------- �� �� ¼:%2d ----------------------- ҳ�� %2d/%2d ----------------------------\n\n",
					paging.totalRecords, Pageing_CurPage(paging),
					Pageing_TotalPages(paging));

			printf(
					   "                      [B] �� Ʊ      |   [P] ��һҳ   |   [N] ��һҳ   |   [R] ����");
			printf(
					"\n=======================================================================================================\n");
			printf("��ѡ��:");
			fflush(stdin);
			scanf("%c", &choice);
			fflush(stdin);

			switch (choice)
			{
				case 'b':
				case 'B':
					Sale_UI_SellTicket(ticketList, seatList);
					break;
				case 'p':
				case 'P':
					if (1 < Pageing_CurPage(paging)) {
						Paging_Locate_OffsetPage(ticketList, paging, -1, ticket_node_t);
					}
					break;
				case 'n':
				case 'N':
					if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
						Paging_Locate_OffsetPage(ticketList, paging, 1, ticket_node_t);
					}
					break;
			}
		} while (choice != 'r' && choice != 'R');


		List_Destroy(ticketList, ticket_node_t);


}

int Sale_UI_SellTicket(ticket_list_t tickList, seat_list_t seatList)
{

	int row, column;
	printf("��������λ�кţ�");
	scanf("%d",&row);
	printf("��������λ�кţ�");
	scanf("%d",&column);
	seat_node_t* findSeat = Seat_Srv_FindByRowCol(seatList, row, column);
	if( findSeat ==  NULL )
	{
		printf("δ�ҵ�����λ��\n");
		fflush(stdin);
		getchar();
		return 0;
	}

	ticket_node_t* findTicket = Ticket_Srv_FindBySeatID(tickList, findSeat->data.id);
	if(findTicket == NULL)
	{
		printf("δ�ҵ�Ʊ\n");
		fflush(stdin);
		getchar();
		return 0;
	}
	if(findTicket->data.status == 1)
	{
		printf("��Ʊ����\n");
		fflush(stdin);
		getchar();
		return 0;
	}

	fflush(stdin);
	printf("ȷ�������Ʊ��\n");
	printf("��Y��ȷ�� ��N������");
	char ch;
	do
	{
		ch = getchar();
	}while(ch!='Y'&&ch!='y'&&ch!='N'&&ch!='n');

	if(ch=='N'||ch=='n')
	{
		return 0;
	}

	findTicket->data.status = TICKET_SOLD;
	Ticket_Srv_Modify(&findTicket->data);

	sale_t newSale;

	newSale.id = EntKey_Srv_CompNewKey("Sale");
	newSale.ticket_id = findTicket->data.id;
	newSale.user_id = gl_CurUser.id;
	newSale.value = findTicket->data.price;
	newSale.type = SALE_SELL;
	newSale.date = DateNow();
	newSale.time = TimeNow();
	Sale_Srv_Add(&newSale);

	printf("��Ʊ�ɹ���\n");
	Ticket_UI_Print(findTicket->data.id);
	fflush(stdin);
	getchar();
	return 0;

}



//���ݾ�ĿID��ʾ�ݳ��ƻ�
void Sale_UI_ShowScheduler(int playID) {

	play_t buf;
	Play_Srv_FetchByID(playID, &buf);

	schedule_list_t head;
	List_Init(head, schedule_node_t);

	schedule_node_t* pos;
	int i;
	char choice;
	

	Pagination_t paging;
	paging.offset = 0;
	paging.pageSize = SCHEDULE_PAGE_SIZE;

	paging.totalRecords = Schedule_Srv_FetchByPlay(head, playID);

	Paging_Locate_FirstPage(head, paging);


	do {

		system("cls");
		printf(
				"\n                                 ��    ��    ��    ��    ��    ��                                    \n\n");
		printf(
						"============================================================================================\n");
				printf("%-5s  %-5s  %-30s  %-8s  %-8s  %-5s\n", "�ƻ�ID", "��ӳ��ID", "��Ŀ��", "����", "ʱ��", "��λ����");
				printf(
						"--------------------------------------------------------------------------------------------\n\n");

				for (i = 0, pos = (schedule_node_t *) (paging.curPos);pos != head && i < paging.pageSize; i++)
				{

					printf("%-5d  %-5d  %-30s  %-8d %d %d  %-8d %d %d  %-5d\n",
							pos->data.id, pos->data.studio_id, buf.name, pos->data.date.year, pos->data.date.month, pos->data.date.day,
							pos->data.time.hour, pos->data.time.minute, pos->data.time.second, pos->data.seat_count);

					pos = pos->next;

				}
		printf(
				"\n--------------------- �� �� ¼:%2d ----------------------- ҳ�� %2d/%2d -----------------------\n\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));

		printf(
				   "             [T] �� �� �� �� Ʊ      |   [P] ��һҳ   |   [N] ��һҳ   |   [R] ����        ");
		printf(
				"\n=============================================================================================\n");
		printf("Your Choice:");
		fflush(stdin);
		scanf("%c", &choice);
		fflush(stdin);

		int schid;
		switch (choice)
		{
			case 't':
			case 'T':
				printf("�������ݳ��ƻ�ID��");
				scanf("%d",&schid);
				Sale_UI_ShowTicket(schid);
				break;
			case 'p':
			case 'P':
				if (1 < Pageing_CurPage(paging)) {
					Paging_Locate_OffsetPage(head, paging, -1, schedule_node_t);
				}
				break;
			case 'n':
			case 'N':
				if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
					Paging_Locate_OffsetPage(head, paging, 1, schedule_node_t);
				}
				break;
		}
	} while (choice != 'r' && choice != 'R');


	List_Destroy(head, schedule_node_t);

}

void Sale_UI_MgtEntry() {
	


//	char mf;
	char condt[100];
	char filter[100];
//	int index = 0;

	play_list_t head;
	List_Init(head, play_node_t);

	play_node_t* pos;
	Pagination_t paging;
	int i;
	int playID;
	char choice;



	paging.offset = 0;
	paging.pageSize = PLAY_PAGE_SIZE;

	paging.totalRecords = Play_Srv_FetchAll(head);

	Paging_Locate_FirstPage(head, paging);

	do {

		system("cls");
		printf(
				"\n                                 ��    ��    Ŀ    ��    ��    ��                                    \n\n");
		printf(
						"======================================================================================================\n");
				printf("%-5s  %-20s  %-10s  %-5s  %-5s  %-6s  %-6s  %-8s  %-12s\n\n", "ID", "��Ŀ��", "����",
						"ʱ��", "Ʊ��", "��Ŀ����","��Ŀ����","��ӳʱ��", "��ӳʱ��");
				printf(
						"------------------------------------------------------------------------------------------------------\n\n");

				for (i = 0, pos = (play_node_t *) (paging.curPos); pos != head && i < paging.pageSize; i++)
				{
					printf("%-5d  %-20s  %-10s  %-5d  %-5d",
							pos->data.id, pos->data.name, pos->data.area, pos->data.duration, pos->data.price);

					switch(pos->data.type)
					{
					case PLAY_TYPE_FILE:
						printf("  %-8s","��Ӱ");
						break;
					case PLAY_TYPE_OPEAR:
						printf("  %-8s","���");
						break;
					case PLAY_TYPE_CONCERT:
						printf("  %-8s","���ֻ�");
						break;
					}


					switch(pos->data.rating)
					{
					case PLAY_RATE_CHILD:
						printf("  %-8s","��ͯ");
						break;
					case PLAY_RATE_TEENAGE:
							printf("  %-8s","������");
							break;
					case PLAY_RATE_ADULT:
						printf("  %-8s","����");
						break;
					}

					printf("  %d��%d��%d��  %d��%d��%d��\n",pos->data.start_date.year, pos->data.start_date.month, pos->data.start_date.day,
							pos->data.end_date.year, pos->data.start_date.month, pos->data.start_date.day);


					pos = pos->next;
				}
		printf(
				"\n-------------------------- �� �� ¼:%2d ----------------------- ҳ�� %2d/%2d ----------------------------\n\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));

		printf(
				   "    [P] ��һҳ   |  [N] ��һҳ   |  [C] �ݳ��ƻ�   |  [S] ��Ŀ����ѯ   |  [F] �� ��   |  [R] �� ��        ");
		printf(
				"\n=======================================================================================================\n");
		printf("��ѡ��ѡ��:");
		fflush(stdin);
		scanf("%c", &choice);
		fflush(stdin);

		switch (choice)
		{
		case 'c':
		case 'C':
			printf("��������鿴�ݳ��ƻ��ľ�ĿID��");
			scanf("%d",&playID);
			Sale_UI_ShowScheduler(playID);
			break;
		case 's':
		case 'S':
			/*
			system("cls");
			while((mf=getch())!='\r')
			{
				condt[index]=mf;
				condt[index+1]='\0';
				index++;
				Play_Srv_FetchByName(head, condt);
				continue;
			}
			index = 0;*/
			printf("�������ѯ�ؼ��֣�");
			scanf("%s",condt);

			paging.totalRecords = Play_Srv_FetchByName(head, condt);
			List_Paging(head, paging, play_node_t);
			break;

		case 'f':
		case 'F':
			printf("��������˹ؼ��֣�");
			scanf("%s",filter);

			paging.totalRecords = Play_Srv_FilterByName(head, filter);
			List_Paging(head, paging, play_node_t);
			break;
		case 'p':
		case 'P':
			if (1 < Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, play_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, play_node_t);
			}
			break;
		}
	} while (choice != 'r' && choice != 'R');

	List_Destroy(head, play_node_t);


}

//��Ʊ
void Sale_UI_ReturnTicket()
{

	printf("������Ʊ��ID��");
	ticket_t *buf = (ticket_t*)malloc(sizeof(ticket_t));

	int id;
	scanf("%d",&id);
	fflush(stdin);
	if ( Ticket_Srv_FetchByID(id, buf) == 0)
	{
		printf("Ʊ�����ڣ�\n");
		getchar();
		return ;
	}

	if(buf->status == 0)
	{
		printf("Ʊ���ۣ�\n");
		getchar();
		return ;
	}
	if(buf->status == 9)
	{
		printf("ƱԤ����\n");
		getchar();
		return ;
	}

	buf->status = TICKET_AVL;
	Ticket_Srv_Modify(buf);

	sale_t newSale;

	newSale.id = EntKey_Srv_CompNewKey("Sale");
	newSale.ticket_id = buf->id;
	newSale.user_id = gl_CurUser.id;
	newSale.value = buf->price;
	newSale.type = SALE_RETURN;
	newSale.date = DateNow();
	newSale.time = TimeNow();
	Sale_Srv_Add(&newSale);

	printf("��Ʊ�ɹ���\n");
	getchar();
	return ;

	
}
