#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int coef, exp;
    struct node *next;
} NODE;

void multiplication(NODE *p1, NODE *p2, NODE *p3)
{
    NODE *x1 = p1->next, *x2 = p2->next, *x3 = p3; // x1为第一个多项式的头结点，x2为第二个多项式头结点，x3表示结果头结点

    while (x1 != NULL)
    {
        x3 = p3;
        while (x2 != NULL)
        {
            int newexp = x1->exp + x2->exp;
            int newcoef = x1->coef * x2->coef;

            if (newcoef != 0)
            {
                while (x3->next != NULL && x3->next->exp < newexp)
                    x3 = x3->next;

                if (x3->next != NULL && x3->next->exp == newexp)
                {
                    x3->next->coef += newcoef;
                }
                else
                {
                    NODE *temp = (NODE *)malloc(sizeof(NODE *));
                    temp->exp = newexp;
                    temp->coef = newcoef;
                    temp->next = x3->next;
                    x3->next = temp;
                }
            }
            x2 = x2->next;
        }

        x1 = x1->next;
        x2 = p2->next;
    }

    x3 = p3;
    while (x3->next != NULL)
    {
        if (!x3->next->coef)
        {
            NODE *useless = x3->next;
            x3->next = x3->next->next;
            free(useless);
        }
        else
            x3 = x3->next;
    }
    if (p3->next == NULL)
    {
        NODE *temp = (NODE *)malloc(sizeof(NODE *));
        temp->exp = 0;
        temp->coef = 0;
        temp->next = NULL;
        p3->next = temp;
        return;
    }
}

void input(NODE *head)
{
    int flag, sign, sum, x;
    char c;

    NODE *p = head;

    while ((c = getchar()) != '\n')
    {
        if (c == '<')
        {
            sum = 0;
            sign = 1;
            flag = 1;
        }
        else if (c == '-')
            sign = -1;
        else if (c >= '0' && c <= '9')
        {
            sum = sum * 10 + c - '0';
        }
        else if (c == ',')
        {
            if (flag == 1)
            {
                x = sign * sum;
                sum = 0;
                flag = 2;
                sign = 1;
            }
        }
        else if (c == '>')
        {
            p->next = (NODE *)malloc(sizeof(NODE));
            p->next->coef = x;
            p->next->exp = sign * sum;
            p = p->next;
            p->next = NULL;
            flag = 0;
        }
    }
}

void output(NODE *head)
{
    while (head->next != NULL)
    {
        head = head->next;
        printf("<%d,%d>,", head->coef, head->exp);
    }
    printf("\n");
}

int main()
{
    NODE *head1, *head2, *head3;

    head1 = (NODE *)malloc(sizeof(NODE));
    input(head1);

    head2 = (NODE *)malloc(sizeof(NODE));
    input(head2);

    head3 = (NODE *)malloc(sizeof(NODE));
    head3->next = NULL;
    multiplication(head1, head2, head3);

    output(head3);
    return 0;
}
