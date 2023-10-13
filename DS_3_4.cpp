#include <iostream>
#include <vector>
#include <stack>
using namespace std;
int count_id = 1;

struct NODE
{
    int orderid;     // 订单号
    int code;        // 股票编码
    double price;    // 价格
    int quantity;    // 数量
    bool quest_type; // true表示买，false表示卖
    NODE *next;
};

// 所有买卖的头节点
NODE *SELL = (NODE *)malloc(sizeof(NODE *));
NODE *BUY = (NODE *)malloc(sizeof(NODE *));

// 删除节点
void deleteNODE(NODE *phead) // 传入删除节点的上一个节点地址
{
    NODE *temp = phead->next;
    if (phead->next != NULL)
        phead->next = temp->next;
    free(temp);
    return;
}

// 插入节点
void insertrequest(NODE *insertNODE, NODE *insertedNODE, double Sharesprice)
{
    NODE *p1 = insertNODE;
    while (p1->next != NULL && p1->next->price >= Sharesprice) // 价格降序，时间升序
        p1 = p1->next;
    insertedNODE->next = p1->next;
    p1->next = insertedNODE;
    return;
}

// 查询委托
void queryrequest(NODE *phead)
{
    NODE *p1 = BUY;
    NODE *p2 = SELL;
    cout << "buy orders:" << endl;
    while (p1->next != NULL)
    {
        p1 = p1->next;
        printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: b\n",
               p1->orderid, p1->code, p1->price);
    }
    cout << "buy orders:" << endl;
    while (p2->next != NULL)
    {
        p2 = p2->next;
        printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: s\n",
               p2->orderid, p2->code, p2->price);
    }
    cout << endl;
}

// 删除委托
void deleterequest(int n) // n表示委托序号
{
    NODE*phead=BUY;
    while (phead->next != NULL)
    {
        if(phead->next->orderid==n)
            break;
        phead = phead->next;
    }
    if (phead->next->orderid == n)
    {
        NODE *temp = phead->next;
        printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n",
               temp->orderid, temp->code, temp->price, temp->quest_type ? 's' : 'b');
        deleteNODE(phead);
        return;
    }
    cout << "not found" << endl;
}
// 找买家
NODE *mathchbuyer(NODE *cur)
{
    int findstockid = cur->code;
    NODE *phead = BUY;
    while (phead->next != NULL)
    {
        phead = phead->next;
        if (phead->code == findstockid && phead->price >= cur->price)
            return phead;
    }
    return NULL;
}
// 找卖家
NODE *mathchseller(NODE *cur)
{
    int findstockid = cur->code;
    NODE *phead = SELL;
    while (phead->next != NULL)
    {
        phead = phead->next;
        if (phead->code == findstockid && phead->price <= cur->price)
            return phead;
    }
    return NULL;
}

// 申请委托(新建一个委托)
void applyrequest(int Sharescode, double Sharesprice, int Sharesnum, bool Sharestype)
{
    NODE *Shares = (NODE *)malloc(sizeof(NODE *));
    Shares->orderid = count_id++;
    Shares->code = Sharescode;
    Shares->price = Sharesprice;
    Shares->quantity = Sharesnum;
    Shares->quest_type = Sharestype;
    printf("%04d", Shares->orderid);
    if (Sharestype)
    {
        NODE *temp = mathchseller(Shares);
        while (temp != NULL)
        {
            if (temp->quantity > Shares->quantity)
            {
                temp->quantity -= Shares->quantity;
                Shares->quantity = 0;
                printf("deal--price: %6.1f quantity:%d sellorder:%04d buyorder:%04d",
                       (temp->price + Shares->price) / 2, Shares->quantity, temp->orderid, Shares->orderid);
            }
            else
            {
            }
            temp = mathchseller(Shares);
        }
        if (Shares->quantity != 0)
            insertrequest(BUY, Shares, Shares->price);
    }
    else
    {
    }
}
