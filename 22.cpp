#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

int dir[2][4] = {{1, 0, 0, -1},
                 {0, 1, -1, 0}};

struct pos
{
    int pos_x;
    int pos_y;
    int time;
};

char gamemap[101][101];
bool vis[101][101];

int main()
{
    int T;
    scanf("%d\n", &T);
    while (T--)
    {
        struct pos start, end, next, now;
        memset(vis, false, sizeof(vis));
        int n, m, k, ch;
        int count=-1;
        queue <pos> q;
        scanf("%d %d %d\n", &n, &m, &k);
        for (int x = 0; x < n; x++)
        {
            for (int y = 0; y < m; y++)
            {
                ch = getchar();
                gamemap[x][y] = ch;
                if (ch == 'S')
                {
                    start.pos_x = x;
                    start.pos_y = y;
                    start.time = 0;
                }
                if (ch == 'E')
                { 
                    end.pos_x=x;
                    end.pos_y=y;
                }
            }
            getchar();
        }
        q.push(start);
    }
}