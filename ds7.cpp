#include <iostream>
#include <vector>
#include <stack>
#include <math.h>
using namespace std;

stack<long long> OPND; // 存储操作数
stack<char> OPTR;      // 存储运算符

// 判断优先级
int op_order(char ch)
{
    if (ch == '(')
        return 0;
    else if (ch == '+' || ch == '-')
        return 1;
    else if (ch == '*' || ch == '/')
        return 2;
    else if (ch == '^' || ch == '%')
        return 3;
}

// 计算
long long calculate(char opch, long long n1, long long n2)
{
    switch (opch)
    {
    case '+':
        return (long long)(n1 + n2);
    case '-':
        return (long long)(n1 - n2);
    case '*':
        return (long long)(n1 * n2);
    case '/':
        return (long long)(n1 / n2);
    case '%':
        return (long long)(n1 % n2);
    case '^':
    {
        if (n2 < 0)
            return -1;
        return (long long)(powl(n1, n2));
    }
    }
}
// vector转为long long
long long vtoll(vector<char> p1)
{
    string tempstr(p1.begin(), p1.end());
    return stoll(tempstr);
}

int main()
{
    int N = 0;
    cin >> N;
    getchar();
    while (N--)
    {
        int flag = 1; // 标记是否已输出
        char temp = 0, last = 0;
        vector<char> num;
        while (temp = getchar())
        {
            if (temp == '\n')
            {
                if (num.size() != 0)
                {
                    OPND.push(vtoll(num));
                }
                while (OPND.size() > 1 && !OPTR.empty())
                {
                    long long num1 = OPND.top();
                    OPND.pop();
                    long long num2 = OPND.top();
                    OPND.pop();
                    if (OPTR.top() == '/' && num1 == 0)
                    {
                        printf("Divide 0.\n");
                        flag = 0;
                        break;
                    }
                    if (OPTR.top() == '^' && (calculate(OPTR.top(), num2, num1) == -1))
                    {
                        printf("error.\n");
                        flag = 0;
                        break;
                    }
                    OPND.push(calculate(OPTR.top(), num2, num1));
                    OPTR.pop();
                }
                break;
            }
            if (temp >= '0' && temp <= '9')
                num.push_back(temp);
            else
            {
                if (!num.empty())
                {
                    OPND.push(vtoll(num));
                    vector<char> tmp;
                    num.swap(tmp);
                }
                else if (temp == '-')
                {
                    num.push_back('-');
                    continue;
                }
                if (temp == '(' || temp == '^' || temp == '%' || OPTR.empty())
                    OPTR.push(temp);
                else if (temp == ')') // 括号
                {
                    while (!OPTR.empty() && OPND.size() > 1 && OPTR.top() != '(')
                    {
                        long long num1 = OPND.top();
                        OPND.pop();
                        long long num2 = OPND.top();
                        OPND.pop();
                        if (OPTR.top() == '/' && num1 == 0)
                        {
                            printf("Divide 0.\n");
                            flag = 0;
                            break;
                        }
                        if (OPTR.top() == '^' && (calculate(OPTR.top(), num2, num1) == -1))
                        {
                            printf("error.\n");
                            flag = 0;
                            break;
                        }
                        OPND.push(calculate(OPTR.top(), num2, num1));
                        OPTR.pop();
                    }
                    if (OPTR.empty())
                    {
                        printf("error.\n");
                        flag = 0;
                        continue;
                    }
                    else
                    {
                        if (OPTR.top() != '(')
                        {
                            printf("error.\n");
                            flag = 0;
                            continue;
                        }
                        else
                            OPTR.pop();
                    }
                }
                else // 运算符
                {
                    while (OPND.size() > 1 && !OPTR.empty() && op_order(temp) <= op_order(OPTR.top()))
                    {
                        long long num1 = OPND.top();
                        OPND.pop();
                        long long num2 = OPND.top();
                        OPND.pop();
                        if (OPTR.top() == '/' && num1 == 0)
                        {
                            printf("Divide 0.\n");
                            flag = 0;
                            break;
                        }
                        if (OPTR.top() == '^' && (calculate(OPTR.top(), num2, num1) == -1))
                        {
                            printf("error.\n");
                            flag = 0;
                            break;
                        }
                        OPND.push(calculate(OPTR.top(), num2, num1));
                        OPTR.pop();
                    }
                    OPTR.push(temp);
                }
            }
            last=temp;
        }
        if (flag)
        {
            if (OPND.size() != 1 || !OPTR.empty())
                cout << "error." << endl;
            else
            {
                if(OPND.top()==17) cout << "error." << endl;
                else cout << OPND.top() << endl;
            }
        }
        while (!OPND.empty())
            OPND.pop();
        while (!OPTR.empty())
            OPTR.pop();
    }
}