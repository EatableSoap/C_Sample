
/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
	int data;
	struct node *next;
} NODE;

NODE *find(NODE *, int *);
void outputring(NODE *);
void change(int, int, NODE *);
void outputring(NODE *pring)
{
	NODE *p;
	p = pring;
	if (p == NULL)
		printf("NULL");
	else
		do
		{
			printf("%d", p->data);
			p = p->next;
		} while (p != pring);
	printf("\n");
	return;
}

int main()
{
	int n, m;
	NODE *head, *pring;

	scanf("%d%d", &n, &m);
	head = (NODE *)malloc(sizeof(NODE));
	head->next = NULL;
	head->data = -1;

	change(n, m, head);
	pring = find(head, &n);
	printf("ring=%d\n", n);
	outputring(pring);

	return 0;
}

void change(int N, int M, NODE *Head)
{
	int flag = 0, count = 100010, count1 = 0;
	NODE *nxt = (NODE *)malloc(sizeof(NODE));
	NODE *num[1000] = {NULL};
	long long left_n[1000][2] = {{-1, -1},{-1, -1},{-1, -1},{-1, -1},{-1, -1},{-1, -1},{-1, -1},{-1, -1},{-1, -1},{-1, -1},{-1, -1}};
	int pos = 0;
	nxt = Head;
	long long n = N;
	while (count--)
	{
		count1++;
		long long left = 0, now = n;
		n *= 10;
		left = n / M;
		n %= M;
		for (int i = 0; i < 1000; i++)
		{
			if (now == left_n[i][0] && n == left_n[i][1])
			{
				flag = 1;
				nxt->next = num[i];
				break;
			}
		}
		if (flag)
			break;
		NODE *temp = (NODE *)malloc(sizeof(NODE));
		nxt->next = temp;
		nxt = nxt->next;
		nxt->data = left;
		num[pos] = nxt;
		left_n[pos][0] = now;
		left_n[pos][1] = n;
		pos = (pos + 1) % 1000;
		if (n == 0)
			break;
	}
	if (!flag)
		nxt->next = NULL;
}

NODE *find(NODE *head, int *n)
{
	*n = 1;
	NODE *p1 = head, *p2 = head;
	while (p1 != NULL && p2 != NULL)
	{
		p1 = p1->next;
		p2 = p2->next;
		if (p2 != NULL)
			p2 = p2->next;
		if (p1 == p2)
			break;
	}
	if (p1 == NULL || p2 == NULL)
	{
		*n = 0;
		return NULL;
	}
	while (p2->next != p1)
	{
		p2 = p2->next;
		(*n)++;
	}
	p1 = p2 = head;
	int sub = *n;

	while (sub--)
		p2 = p2->next;

	while (p1 != p2)
	{
		p1 = p1->next;
		p2 = p2->next;
	}
	return p1;
}