#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAX_ID_LEN 30
#define MAX_NAME_LEN 30
#define MAX_DISCOUNT_LEN 30
int currentCnt = 0;//全局变量，存储当前商品的数量

typedef struct {
	char id[MAX_ID_LEN];
	char name[MAX_NAME_LEN];
	char discount[MAX_DISCOUNT_LEN];

	int price;
	int amount;
	int remain;
} Goods;

typedef struct node {
	Goods info;
	struct node *next;
} GoodsList;
GoodsList *list = NULL, *list_last = NULL;//链表的开头和结尾。全局变量的开始都定为null 


char s[180];//存入数据
void freeGoodInfo(GoodsList **L)
{
	GoodsList *p = NULL;
	while (p != NULL)
	{
		p = (*L)->next;
		free(*L);
		*L = p;
	}
	currentCnt = 0;
}
void save_and_exit(GoodsList ** L)
{
	FILE *fp;
	GoodsList *p = NULL;

	if (L == NULL)
	{
		printf("the linked list is empty!\n");
		exit(EXIT_FAILURE);
	}

	if ((fp = fopen("goodsinfo.txt", "wb")) == NULL)
	{
		perror("File open error:");
		exit(EXIT_FAILURE);
	}

	p = *L;
	while (*L != NULL)
	{
		if (fwrite(*L, sizeof(GoodsList), 1, fp) == 1)
		{
			*L = (*L)->next;
		}
	}

	fclose(fp);
	printf("\n|存盘成功！\n");

	*L = p;
	//释放内存
	freeGoodInfo(L);

	exit(EXIT_SUCCESS);
}



void outputMenu()
{
	puts("*******************************************");
	puts("1. 显示所有商品的信息；");
	puts("2. 修改某个商品的信息；");
	puts("3. 插入某个商品的信息；");
	puts("4. 删除某个商品的信息；");
	puts("5. 查找某个商品的信息；");
	puts("6. 商品存盘并退出系统；");
	puts("7. 对商品价格进行排序；");
	puts("8. （慎用）删除所有内容；");
	puts("其他. 不存盘并退出系统；");
	puts("*******************************************");
	return;
}

void jianlishuzu(GoodsList **L, GoodsList **LL)
{
	GoodsList *p;

	*L = (GoodsList *)malloc(sizeof(GoodsList));

	p = *L;
	p->next = NULL;

	FILE *fp = fopen("goodsinfo.txt", "r");

	if (fp == NULL)
	{
		printf("商品信息初始化文件不存在！程序将为您新建一个。\n");
		fclose(fp);
		fp = fopen("goodsinfo.txt", "w");
		fclose(fp);
		*LL = p;
		return;
	}

	while (1)
	{
		if (fgets(s, 180, fp) == NULL) break;
		int i, t = 0;

		for (i = 0; s[i] >= 32; i++) p->info.id[t++] = s[i];
		p->info.id[t++] = '\0'; t = 0;

		for (i++; s[i] != '\t'; i++) p->info.name[t++] = s[i];
		p->info.name[t++] = '\0'; t = 0;

		p->info.price = 0;
		for (i++; s[i] >= 32; i++) p->info.price = p->info.price * 10 + s[i] - '0';

		for (i++; s[i] >= 32; i++) p->info.discount[t++] = s[i];
		p->info.discount[t++] = '\0'; t = 0;

		p->info.amount = 0;
		for (i++; s[i] >= 32; i++) p->info.amount = p->info.amount * 10 + s[i] - '0';

		p->info.remain = 0;
		for (i++; s[i] >= 32; i++) p->info.remain = p->info.remain * 10 + s[i] - '0';

		++currentCnt;

		p->next = (GoodsList *)malloc(sizeof(GoodsList));
		p = p->next;
		p->next = NULL;
	}

	*LL = p;
	printf("商品的链表文件已建立，有 %d 个商品记录。\n", currentCnt);

	fclose(fp);
	return;
}
void read_line(char s[], int n)
{
	char ch; int i = 0;
	while ((ch = getchar()) < 32)
	{
		if (ch == EOF)
		{
			s[i] = '\0';
			return;
		}
	}
	s[i++] = ch;
	while ((ch = getchar()) >= 32 && i < n) s[i++] = ch;
	s[i] = '\0';
	return;
}

void printOneInfo(Goods a)
{
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("ID：%s\t名称：%s\t价格：%d\t折扣：%s\t数量：%d\t剩余：%d", a.id, a.name, a.price, a.discount, a.amount, a.remain);
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	return;
}

void printAllInfo(GoodsList *L)
{
	int i;
	for (i = 0; i < currentCnt; i++)
	{
		printOneInfo(L->info);
		L = L->next;
	}
	return;
}

void readItem(Goods *a)
{
	puts("输入新的商品信息：");
	printf("商品 ID："); read_line(a->id, 30);
	printf("商品名称："); read_line(a->name, 30);
	printf("商品价格："); scanf("%d", &a->price);
	printf("商品折扣："); read_line(a->discount, 30);
	printf("商品数量："); scanf("%d", &a->amount);
	printf("商品剩余："); scanf("%d", &a->remain);
	return;
}

void infoChange(GoodsList **L)
{
	int i = 0, f = 0;
	GoodsList *p = *L;

	printf("输入需要修改的商品 ID（-1 退出修改）：");
	read_line(s, 30);

	if (s[0] == '-' && s[1] == '1' && s[2] == '\0') return;

	while (i < currentCnt)
	{
		if (strcmp(p->info.id, s) == 0)
		{
			f = 1;
			break;
		}
		p = p->next;
		i++;
	}

	if (!f)
	{
		puts("您要修改的商品不存在！");
		return;
	}

	readItem(&p->info);

	puts("修改商品信息成功！修改后的商品为：");
	printOneInfo(p->info);

	return;
}

void infoInsert(GoodsList **L, GoodsList **LL)
{
	Goods a; int position, i;
	readItem(&a);

err:
	printf("输入数字以表示您要插入的商品位置：0. 商品列表尾部 1. 商品列表头部 2. 商品列表中间第 i 号位置：");
	scanf("%d", &position);

	if (!position)
	{
		(*LL)->info = a;
		(*LL)->next = (GoodsList*)malloc(sizeof(GoodsList));
		(*LL) = (*LL)->next;
		(*LL)->next = NULL;
		++currentCnt;
		return;
	}

	if (position == 1)
	{
		GoodsList *nHead = (GoodsList*)malloc(sizeof(GoodsList));
		nHead->info = a;
		nHead->next = *L;
		*L = nHead;
		++currentCnt;
		return;
	}

	GoodsList *p = *L, *nItem;
	nItem = (GoodsList*)malloc(sizeof(GoodsList));
	nItem->info = a;
	nItem->next = NULL;

	for (i = 1; i < position - 1; i++)
	{
		if (p->next == NULL)
		{
			puts("未找到该位置，请重新输入！");
			goto err;
		}
		else p = p->next;
	}

	nItem->next = p->next;
	p->next = nItem;
	++currentCnt;
	return;
}

void infoDelete(GoodsList **L)
{
	char option[3];
	int f = 0;
	GoodsList *p = *L, *q;

	printf("输入需要删除的商品 ID（-1 退出删除）：");
	read_line(s, 30);

	if (s[0] == '-' && s[1] == '1' && s[2] == '\0') return;

	if (strcmp((*L)->info.id, s) == 0)
	{
		printOneInfo((*L)->info);
		puts("是否删除该商品？（Y/N）：");
		scanf("%s", option);
		if (option[0] == 'N' || option[0] == 'n') return;
		else if (option[0] == 'Y' || option[0] == 'y')
		{
			p = p->next;
			free(*L);
			*L = p;
			currentCnt--;
			printf("Tips: 删除 ID 为 %s 的商品成功！", s);
			printf("Tips: 当前剩余商品 %d 个。\n", currentCnt);
			return;
		}
		else
		{
			puts("不合法的输入！");
			return;
		}
	}

	while ((p->next) != list_last)
	{
		if (strcmp((p->next)->info.id, s) == 0)
		{
			f = 1;
			break;
		}
		p = p->next;
	}

	if (!f)
	{
		puts("您要删除的商品不存在！");
		return;
	}

	printOneInfo((p->next)->info);
	puts("是否删除该商品？（Y/N）：");
	scanf("%s", option);

	if (option[0] == 'N' || option[0] == 'n') return;
	else if (option[0] == 'Y' || option[0] == 'y')
	{
		q = p;
		p = p->next;
		q->next = p->next;
		free(p);
		currentCnt--;
		printf("Tips: 删除 ID 为 %s 的商品成功！", s);
		printf("Tips: 当前剩余商品 %d 个。\n", currentCnt);
	}
	else puts("不合法的输入！");
	return;
}

void infoSearch(GoodsList *L)
{
	GoodsList *p = L;

	printf("输入需要查找的商品名称（-1 退出查找）：");
	read_line(s, 30);

	if (s[0] == '-' && s[1] == '1' && s[2] == '\0') return;

	while (p != list_last)
	{
		if (strcmp(p->info.id, s) == 0)
		{
			printOneInfo(p->info);
			return;
		}
		p = p->next;
	}

	puts("您要查找的商品不存在！");
	return;
}

void deleteAll(GoodsList **L)
{
	GoodsList *q;

	while ((*L) != NULL)
	{
		q = (*L)->next;
		free(*L);
		*L = q;
	}

	*L = NULL;
	list_last = NULL;
	currentCnt = 0;
	return;
}



void bubbleSort(GoodsList **L)
{
	int i, j;

	if (currentCnt <= 1) return;

	for (i = 0; i < currentCnt; i++)
	{
		GoodsList *p = *L, *q = (*L)->next, *r;

		if (p->info.price > q->info.price)
		{
			p->next = q->next;
			q->next = p;
			*L = q;
		}

		p = *L;

		for (j = 1; j < currentCnt - i - 1; j++)
		{
			q = p->next;
			r = q->next;

			if (q->info.price > r->info.price)
			{
				q->next = r->next;
				r->next = q;
				p->next = r;
			}

			p = p->next;
		}
	}
	return;
}



int main()
{
	jianlishuzu(&list, &list_last);
	puts("超市商品管理系统");
	while (1)
	{
		int option;

		outputMenu();
		printf("输入您的选择：");
		scanf("%d", &option);

		switch (option)
		{
		case 1: printAllInfo(list); break;
		case 2: infoChange(&list); break;
		case 3: infoInsert(&list, &list_last); break;
		case 4: infoDelete(&list); break;
		case 5: infoSearch(list); break;
		case 6: save_and_exit(&list); return 0;
		case 7: bubbleSort(&list); break;
		case 8: deleteAll(&list); break;
		default: return 0;
		}
	}
	return 0;
}
