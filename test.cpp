#include<iostream>
#include<cstring>
using namespace std;
struct NODE
{
    char *ch;
    NODE *next; 
};

int main()
{
    char vischar[94]={'!'};
    for (int i = 1; i < 94; i++)
        vischar[i]=vischar[i-1]+1;
    NODE* HEAD=(NODE*)malloc(sizeof(NODE));
    HEAD->next=NULL;
    int m,n=0;
    cin>>n>>m;
    NODE* p=HEAD;
    while (n--)
    {
        char tempch;
        cin>>tempch;
        NODE* temp=(NODE*)malloc(sizeof(NODE));
        temp->next=NULL;
        temp->ch=strchr(vischar,tempch);
        HEAD->next=temp;
        HEAD=HEAD->next;
    }
    while (m--)
    {
        char temp1,temp2;
        char*p1=NULL,*p2=NULL;
        cin>>temp1>>temp2;
        char temp=0;
        p1=strchr(vischar,temp1);
        p2=strchr(vischar,temp2);
        temp=*p1;
        *p1=*p2;
        *p2=temp;
    }
    while (p!=NULL)
    {
        p=p->next;
        if(p!=NULL)
        cout<<*(p->ch);
        else
        break;
    }
    cout<<endl;
}