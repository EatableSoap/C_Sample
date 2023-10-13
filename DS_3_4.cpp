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

// 插入委托
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
void queryrequest(int n)
{
    NODE *p1 = BUY;
    NODE *p2 = SELL;
    cout << "buy orders:" << endl;
    while (p1->next != NULL)
    {
        if (p1->next->quantity == 0)
        {
            deleteNODE(p1);
            if (p1->next != NULL)
                p1 = p1->next;
            continue;
        }
        p1 = p1->next;
        if (p1->code == n)
            printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: b\n",
                   p1->orderid, p1->code, p1->price, p1->quantity);
    }
    cout << "buy orders:" << endl;
    while (p2->next != NULL)
    {
        if (p2->next->quantity == 0)
        {
            deleteNODE(p2);
            if (p2->next != NULL)
                p2 = p2->next;
            continue;
        }
        p2 = p2->next;
        if (p2->code == n)
            printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: s\n",
                   p2->orderid, p2->code, p2->price, p2->quantity);
    }
    cout << endl;
}

// 删除委托
void deleterequest(int n) // n表示委托序号
{
    NODE *phead = BUY->next;
    int flag = 0;
    while (phead != NULL)
    {
        if (phead->orderid == n)
        {
            flag = 2;
            break;
        }
        phead = phead->next;
    }
    if (!flag)
    {
        phead = SELL->next;
        while (phead != NULL)
        {
            if (phead->orderid == n)
            {
                flag = 1;
                break;
            }
            phead = phead->next;
        }
    }
    if (flag)
    {
        NODE *temp = phead->next;
        printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n",
               temp->orderid, temp->code, temp->price, (flag - 1) ? 98 : 115);
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
        if (phead->next->quantity == 0)
            deleteNODE(phead);
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
        if (phead->next->quantity == 0)
            deleteNODE(phead);
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
                temp->quantity = 0;
                Shares->quantity -= temp->quantity;
                printf("deal--price: %6.1f quantity:%d sellorder:%04d buyorder:%04d",
                       (temp->price + Shares->price) / 2, temp->quantity, temp->orderid, Shares->orderid);
            }
            temp = mathchseller(Shares);
        }
        if (Shares->quantity != 0)
            insertrequest(BUY, Shares, Shares->price);
    }
    else
    {
        NODE *temp = mathchbuyer(Shares);
        while (temp != NULL)
        {
            if (temp->quantity > Shares->quantity)
            {
                temp->quantity -= Shares->quantity;
                Shares->quantity = 0;
                printf("deal--price: %6.1f quantity:%d sellorder:%04d buyorder:%04d",
                       (temp->price + Shares->price) / 2, Shares->quantity, Shares->orderid, temp->orderid);
            }
            else
            {
                temp->quantity = 0;
                Shares->quantity -= temp->quantity;
                printf("deal--price: %6.1f quantity:%d sellorder:%04d buyorder:%04d",
                       (temp->price + Shares->price) / 2, temp->quantity, Shares->orderid, temp->orderid);
            }
            temp = mathchbuyer(Shares);
        }
        if (Shares->quantity != 0)
            insertrequest(SELL, Shares, Shares->price);
    }
}
int main()
{
    SELL->next=NULL;
    BUY->next=NULL;
    int choice = -1;
    int stockid = 0;
    double money = 0;
    int sharequantity = 0;
    bool sharekind = true;
    while (choice != 0)
    {
        cin >> choice;
        if (!choice)
            break;
        switch (choice)
        {
        case 1:
        {
            char temp = 0;
            cin >> stockid >> money >> sharequantity >> temp;
            if (temp == 'b')
                sharekind = true;
            else
                sharekind = false;
            applyrequest(stockid, money, sharequantity, sharekind);
            break;
        }
        case 2:
        {
            cin >> stockid;
            queryrequest(stockid);
            break;
        }
        case 3:
        {
            int temp = 0;
            cin >> temp;
            deleterequest(temp);
            break;
        }
        }
        getchar();
    }
}