#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} NODE;

void change(int N, int M, NODE *Head)
{
    int flag = 0;
    NODE *nxt = (NODE*)malloc(sizeof(NODE));
    NODE *num[10] = {NULL};
    Head->next=nxt;
    nxt=Head;
    while (1)
    {
        int left=0;
        if (N == 0 || flag == 1)
            break;
        N *= 10;
        left = N / M;
        N = N % M;
        if (num[left] != NULL)
        {
            flag = 1;
            nxt->next = num[left];
        }
        else
        {
            NODE *temp=(NODE*)malloc(sizeof(NODE));
            nxt->next=temp;
            nxt=nxt->next;
            nxt->data=left;
            num[left] = nxt;
        }
    }
    return;
}

void output(NODE *head, int kk)
{
    int k = 0;

    printf("0.");
    while (head->next != NULL && k < kk)
    {
        printf("%d", head->next->data);
        head = head->next;
        k++;
    }
    printf("\n");
}

int main()
{
    int n, m, k;
    NODE *head;

    scanf("%d%d%d", &n, &m, &k);
    head = (NODE *)malloc(sizeof(NODE));
    head->next = NULL;
    head->data = -1;
    change(n, m, head);
    output(head, k);
    return 0;
}