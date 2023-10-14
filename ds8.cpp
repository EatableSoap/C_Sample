#include <iostream>
#include <malloc.h>
#include <cstdio>
using namespace std;
int count_id = 1;

struct NODE
{
	int orderid;     // 订单号
	int code;        // 股票编码s
	double price;    // 价格
	int quantity;    // 数量
	bool quest_type; // true表示买，false表示卖
	NODE* next;
};

// 所有买卖的头节点
NODE* SELL = (NODE*)malloc(sizeof(NODE));
NODE* BUY = (NODE*)malloc(sizeof(NODE));

// 删除节点
void deleteNODE(NODE* phead) // 传入删除节点的上一个节点地址
{
	NODE* temp = phead->next;
	phead->next = temp->next;
	free(temp);
	return;
}

// 插入委托
void insertrequest(NODE* insertNODE, NODE* insertedNODE, double Sharesprice, bool Sharetype)
{
	NODE* p1 = insertNODE;
	if (Sharetype)
	{
		while (p1->next != NULL && p1->next->price >= Sharesprice) // 买方价格降序，时间升序
			p1 = p1->next;
	}
	else
	{
		while (p1->next != NULL && p1->next->price <= Sharesprice) // 卖方价格升序，时间升序
			p1 = p1->next;
	}
	insertedNODE->next = p1->next;
	p1->next = insertedNODE;
	return;
}

// 查询委托
void queryrequest(int n)
{
	NODE* p1 = BUY->next;
	NODE* p2 = SELL->next;
	cout << "buy orders:" << endl;
	while (p1 != NULL)
	{
		if (p1->code == n)
			printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: b\n", p1->orderid, p1->code, p1->price, p1->quantity);
		p1 = p1->next;
	}
	cout << "sell orders:" << endl;
	while (p2 != NULL)
	{
		if (p2->code == n)
			printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: s\n", p2->orderid, p2->code, p2->price, p2->quantity);
		p2 = p2->next;
	}
}

// 删除委托
void deleterequest(int n) // n表示委托序号
{
	NODE* phead = BUY;
	int flag = 0;
	while (phead->next != NULL)
	{
		phead = phead->next;
		if (phead->next != NULL && phead->next->orderid == n)
		{
			flag = 2;
			break;
		}
	}
	if (!flag)
	{
		phead = SELL;
		while (phead->next != NULL)
		{
			phead = phead->next;
			if (phead->next != NULL && phead->next->orderid == n)
			{
				flag = 1;
				break;
			}
		}
	}
	if (flag)
	{
		NODE* temp = phead->next;
		printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", temp->orderid, temp->code, temp->price, temp->quantity, (flag - 1) ? 98 : 115);
		deleteNODE(phead);
		return;
	}
	cout << "not found" << endl;
}
// 找买家
NODE* mathchbuyer(NODE* cur)
{
	int findstockid = cur->code;
	NODE* phead = BUY, * preturn = NULL;
	while (phead != NULL)
	{
		if (phead->code == findstockid && phead->price >= cur->price)
			return preturn;
		preturn = phead;
		phead = phead->next;
	}
	return NULL;
}
// 找卖家
NODE* mathchseller(NODE* cur)
{
	int findstockid = cur->code;
	NODE* phead = SELL, * preturn = NULL;
	while (phead != NULL)
	{
		if (phead->code == findstockid && phead->price <= cur->price)
			return preturn;
		preturn = phead;
		phead = phead->next;
	}
	return NULL;
}

//申请委托(新建一个委托)
void applyrequest(int Sharescode, double Sharesprice, int Sharesnum, bool Sharestype)
{
	NODE* Shares = (NODE*)malloc(sizeof(NODE) * 2), * temp;
	Shares->orderid = count_id++;
	Shares->code = Sharescode;
	Shares->price = Sharesprice;
	Shares->quantity = Sharesnum;
	Shares->quest_type = Sharestype;
	printf("orderid: %04d\n", Shares->orderid);
	if (Sharestype)
	{
		temp = mathchseller(Shares);
		while (temp != NULL)
		{
			if (temp->next->quantity > Shares->quantity)
			{
				printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (temp->next->price + Shares->price) / 2, Shares->quantity, Shares->orderid, temp->next->orderid);
				temp->next->quantity = temp->next->quantity - Shares->quantity;
				Shares->quantity = 0;
				break;
			}
			else
			{
				printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (temp->next->price + Shares->price) / 2, temp->next->quantity, Shares->orderid, temp->next->orderid);
				Shares->quantity = Shares->quantity - temp->next->quantity;
				temp->next->quantity = 0;
				deleteNODE(temp);
			}
			temp = mathchseller(Shares);
		}
		if (Shares->quantity != 0)
			insertrequest(BUY, Shares, Shares->price, Shares->quest_type);
	}
	else
	{
		temp = mathchbuyer(Shares);
		while (temp != NULL)
		{
			if (temp->next->quantity > Shares->quantity)
			{
				printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (temp->next->price + Shares->price) / 2, Shares->quantity, Shares->orderid, temp->next->orderid);
				temp->next->quantity -= Shares->quantity;
				Shares->quantity = 0;
				break;
			}
			else
			{
				printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (temp->next->price + Shares->price) / 2, temp->next->quantity, Shares->orderid, temp->next->orderid);
				Shares->quantity -= temp->next->quantity;
				temp->next->quantity = 0;
				deleteNODE(temp);
			}
			temp = mathchbuyer(Shares);
		}
		if (Shares->quantity != 0)
			insertrequest(SELL, Shares, Shares->price, Shares->quest_type);
	}
}

int main()
{
	SELL->next = NULL;
	BUY->next = NULL;
	int choice = -1;
	int stockid = 0;
	double money = 0;
	int sharequantity = 0;
	bool sharekind = true;
	while (choice != 0)
	{
		scanf("%d", &choice);
		getchar();
		if (choice == 0)
			break;
		switch (choice)
		{
		case 1:
		{
			char temp = 0;
			scanf("%d %lf %d %c", &stockid, &money, &sharequantity, &temp);
			if (temp == 'b')
				sharekind = true;
			else
				sharekind = false;
			applyrequest(stockid, money, sharequantity, sharekind);
			break;
		}
		case 2:
		{
			scanf("%d", &stockid);
			queryrequest(stockid);
			break;
		}
		case 3:
		{
			int temp = 0;
			scanf("%d", &temp);
			deleterequest(temp);
			break;
		}
		}
	}
	free(BUY); free(SELL);
}