#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
TODO: 判断是否有人入住
TODO: 数据校验
TODO: 统计空床数
*/

// 学生结构体
typedef struct student
{
	char stu_no[20];	 /*学号*/
	char stu_name[20]; /*姓名*/
	int bed;					 /*床位号 */
	int room;					 /*宿舍号*/
	int class;				 /*班级*/
	char time[20];		 /*入住时间*/
	char yn;
} STU;

/*链表中每个节点的定义*/
typedef struct node
{
	STU data;					 /*数据域 */
	struct node *next; /*指针 */
} NODE;

// 函数定义
NODE *create();
STU *findNode(char *no);
void find(NODE *head);
void print(NODE *head);
void insert(NODE *head);
void insertBypos(NODE *head);
void deleteBypos(NODE *head);
void xiugai(NODE *head);
void showMenu();
void SUSHE(NODE *head);
bool isValidDate(int yr, int mo, int d)
{
	// 月份与日期对应关系，month[0] = 1月 = 31天
	int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	// 闰年判断
	if (yr % 400 == 0 || (yr % 4 == 0 && yr % 100 != 0))
	{
		month[1] = 29;
	}

	if (mo > 0 && mo <= 12 && d > 0 && d <= month[mo - 1])
	{
		return true;
	}
	else
	{
		printf("输入的日期不合法，请重新输入");
		return false;
	}
}

/*用尾插法的思想，建立学生宿舍信息的单链表*/
NODE *create() /*建立单链表的函数 (尾插法的思路)*/
{
	NODE *head, *s, *p, *tail;
	int count, i; /*这个变量用来记录原始学生的人数*/
	char tempInput[20];
	head = (NODE *)malloc(sizeof(NODE)); /*建立头结点 */
	head->next = NULL;
	printf("请输入学生的人数:");
	scanf("%d", &count);
	for (i = 1; i <= count; i++)
	{
		/*申请空间*/
		p = (NODE *)malloc(sizeof(NODE));
		p->next = NULL;

		printf("请输入第%d个学生的信息:\n", i);
		printf("学号[xxx]:");
		fflush(stdin);
		gets(p->data.stu_no);

		printf("姓名:");
		fflush(stdin);
		gets(p->data.stu_name);

		printf("床位号[xx]:");
		scanf("%d", &p->data.bed);

		printf("宿舍号[xx]:");
		scanf("%d", &p->data.room);

		printf("班级[xx]");
		scanf("%d", &p->data.class);

		int yr, mo, d;
		do
		{
			printf("入住时间[xxxx/xx/xx]:");
			scanf("%4d/%2d/%2d", &yr, &mo, &d);
		} while (!isValidDate(yr, mo, d));
		sprintf(p->data.time, "%d/%d/%d", yr, mo, d);

		if (i == 1) /*第一个节点的挂链处理 */
		{
			head->next = p;
			tail = p;
		}
		else
		{
			tail->next = p;
			tail = p;
		}
	}
	return head;
}

/*查找指定学生信息 */
void find(NODE *head)
{
	NODE *p;
	char a[20];
	printf("请输入该学生的学号：");
	scanf("%s", a);
	p = head->next;
	while (p != NULL)
	{
		if (strcmp(a, *(p->data.stu_no)) == 0)
		{
			printf("%10s%10s%10s%10s%10s%10s\n", "学号", "姓名", "床位号", "宿舍号", "班级", "入住时间");
			printf("------------------------------------------------------------------\n");
			printf("%10s%10s%10d%10d%10d%10s年\n", p->data.stu_no, p->data.stu_name, p->data.bed, p->data.room, p->data.class, p->data.time);
			break;
		}
		p = p->next;
	}
}

void SUSHE(NODE *head)
{
	NODE *p;
	int a;
	printf("请输入宿舍号:");
	scanf("%d", &a);
	p = head->next;
	while (p != NULL)
	{
		if (p->data.room == a)
			break;
	}
	if (p == NULL)
	{
		printf("没有该寝室,查找失败");
		return;
	}
	p = head->next;
	printf("%10s%10s%10s%10s%10s%10s\n", "学号", "姓名", "床位号", "宿舍号", "班级", "入住时间");
	while (p != NULL)
	{
		if (p->data.room == a)
		{
			printf("------------------------------------------------------------------\n");
			printf("%10s%10s%10d%10d%10d%10s\n", p->data.stu_no, p->data.stu_name, p->data.bed, p->data.room, p->data.class, p->data.time);
			printf("------------------------------------------------------------------\n");
		}
		p = p->next;
	}
}

void xiugai(NODE *head)
{
	NODE *p;
	int ROOM, x;
	int BED;
	printf("请输入宿舍号和床位号:");
	scanf("%d%d", &ROOM, &BED);
	p = head->next;
	if (head == NULL)
	{
		printf("住宿信息为空,不能修改,按任意键返回...\n");
		/*system("cls");*/
		return;
	}
	while (p != NULL)
	{
		if (p->data.room == ROOM && p->data.bed == BED)
		{
			printf("已找到要修改的宿舍号、床位号!\n");
			printf("%10s%10s%10s%10s%10s%10s\n", "学号", "姓名", "床位号", "宿舍号", "班级", "入住时间");
			printf("------------------------------------------------------------------\n");
			printf("%10s%10s%10d%10d%10d%10s\n", p->data.stu_no, p->data.stu_name, p->data.bed, p->data.room, p->data.class, p->data.time);
			printf("请修改住宿信息:\n");
			printf("1.修改床学号\n");
			printf("2.修改姓名\n");
			printf("3.修改床位号\n");
			printf("4.修改宿舍号\n");
			printf("5.修改班级\n");
			printf("6.修改入住时间\n");
			scanf("%d", &x);
			if (x == 1)
			{
				printf("请输入新的学号:");
				scanf("%s", p->data.stu_no);
				printf("修改成功");
				return;
			}
			else if (x == 2)
			{
				printf("请输入新的姓名:");
				scanf("%s", p->data.stu_name);
				printf("修改成功");
				return;
			}
			else if (x == 3)
			{
				printf("请输入新的床位号：");
				scanf("%d", &p->data.bed);
				printf("修改成功");
				return;
			}
			else if (x == 4)
			{
				printf("请输入新的宿舍号：");
				scanf("%d", &p->data.room);
				printf("修改成功");
				return;
			}
			else if (x == 5)
			{
				printf("请输入新的班级");
				scanf("%d", &p->data.class);
				printf("修改成功");
				return;
			}
			else if (x == 6)
			{
				printf("请输入新的入住时间：");
				scanf("%s", p->data.time);
				printf("修改成功");
				return;
			}
			else
			{
				printf("输入错误");
				return;
			}
		}
		p = p->next;
	}
	if (p == NULL)
	{
		printf("信息输入错误");
		return;
	}
}

/*信息输出的函数*/
void print(NODE *head)
{
	NODE *p;
	p = head->next;
	printf("%10s%10s%10s%10s%10s%10s\n", "学号", "姓名", "床位号", "宿舍号", "班级", "入住时间"); /*输出表头*/
	while (p != NULL)
	{

		printf("------------------------------------------------------------------\n");
		printf("%10s%10s%10d%10d%10d%10s\n", p->data.stu_no, p->data.stu_name, p->data.bed, p->data.room, p->data.class, p->data.time);
		p = p->next;
	}
	printf("------------------------------------------------------------------\n");
}

/*插入一个新学生的信息（新增的信息位置由人指定）*/
void insertBypos(NODE *head)
{
	int pos, count = 0; /*表示插入学生的位置*/
	NODE *s, *p;
	printf("请输入新入住学生的信息:\n");
	printf("位置:");
	scanf("%d", &pos);
	s = (NODE *)malloc(sizeof(NODE));
	s->next = NULL;
	printf("学号:");
	fflush(stdin);
	gets(s->data.stu_no);
	printf("姓名:");
	fflush(stdin);
	gets(s->data.stu_name);
	printf("床位号:");
	scanf("%d", &s->data.bed);
	printf("宿舍号:");
	scanf("%d", &s->data.room);
	printf("班级:");
	scanf("%d", &s->data.class);
	printf("入住时间");
	scanf("%s", &s->data.time);
	/*通过循环，先找到pos-1这个位置*/
	p = head;
	while (p->next != NULL)
	{
		if (count == pos - 1)
		{
			break;
		}
		count++;
		p = p->next;
	}
	/*将新增的结点，插入到原来的链表中去*/
	s->next = p->next;
	p->next = s;
}

/*插入一个新学生的信息（新增的信息插入原链表的最后）*/
void insert(NODE *head)
{
	NODE *s, *p;
	p = head->next;
	while (p->next != NULL) /*循环的作用是查找链表中最后一个结点 */
	{
		p = p->next;
	}
	s = (NODE *)malloc(sizeof(NODE));
	s->next = NULL;
	printf("请输入新入住学生的信息:\n");
	printf("学号:");
	fflush(stdin);
	gets(s->data.stu_no);
	printf("姓名:");
	fflush(stdin);
	gets(s->data.stu_name);
	printf("床位号:");
	scanf("%d", &s->data.bed);
	printf("宿舍号:");
	scanf("%d", &s->data.room);
	printf("班级:");
	scanf("%d", &s->data.class);
	printf("入住时间");
	scanf("%s", &s->data.time);
	p->next = s;
}
/*删除指定位置的结点*/
void deleteBypos(NODE *head)
{
	int pos, count = 0; /*表示插入学生的位置*/
	NODE *r, *p;
	printf("请输入需要删除学生的位置:\n");
	scanf("%d", &pos);
	/*通过循环，先找到pos-1这个位置*/
	p = head;
	while (p->next != NULL)
	{
		if (count == pos - 1)
		{
			break;
		}
		count++;
		p = p->next; /*p指向的是第pos-1个位置 */
	}
	r = p->next; /*r就是指向的是第pos个位置*/
	p->next = r->next;
	free(r);
}

/*设计一个程序功能菜单*/
void showMenu()
{
	system("CLS");
	printf("欢迎使用学生宿舍管理系统\n");
	printf("1.建立学生基础信息\n");
	printf("2.新增学生信息\n");
	printf("3.输入宿舍号，床位号删除学生信息\n");
	printf("4.输入宿舍号查找学生信息\n");
	printf("5.输入宿舍号、床位号修改学生信息\n");
	printf("6.显示学生信息\n");
	printf("0.退出系统\n");
	printf("请输入你的选择:");
}

int main()
{
	int choice;
	NODE *head;
	while (1)
	{
		/*输出功能菜单*/
		showMenu();
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			head = create();
			system("PAUSE");
			break;
		case 2:
			print(head);
			insertBypos(head);
			system("PAUSE");
			break;
		case 3:
			print(head);
			deleteBypos(head);
			system("PAUSE");
			break;
		case 4:
			SUSHE(head);
			system("PAUSE");
			break;
		case 5:
			xiugai(head);
			system("PAUSE");
			break;
		case 6:
			print(head);
			system("PAUSE");
			break;
		case 0:
			printf("Bye bye!");
			return 0;
		}
	}

	/*建立单链表*/
	/*print(head)*/; /*输出链表信息*/
	/*insert(head);*/
	/*insertBypos(head); */
	/*deleteBypos(head);*/

	return 0;
}
