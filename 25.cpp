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
    int step;
};

char gamemap[1001][1001];
bool vis[1001][1001];

int main()
{
    struct pos start, end, next, now;
    memset(vis, false, sizeof(vis));
    int n, m, k, ch;
    int count = -1;
    queue<pos> q;
    scanf("%d %d %d\n", &n, &m, &k);
    for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < m; y++)
        {
            ch = getchar();
            gamemap[x][y] = ch;
        }
        getchar();
    }
    scanf("%d %d %d %d", &start.pos_x, &start.pos_y, &end.pos_x, &end.pos_y);

    start.pos_x--;
    start.pos_y--;
    end.pos_x--;
    end.pos_y--;

    // bfs code
    start.step=0;
    q.push(start);
    vis[start.pos_x][start.pos_y] = true;
    while (!q.empty())
    {
        now = q.front();
        q.pop();

        // set break condition
        if (now.pos_x == end.pos_x && now.pos_y == end.pos_y)
        {
            count = now.step;
            break;
        }

        // add next step to queue
        for (int i = 0; i < 4; i++)
        {
            int j = k;
            while (j--)
            {
                next.pos_x = now.pos_x + dir[0][i];
                next.pos_y = now.pos_y + dir[1][i];
                // judge the position is vaild or not
                if (next.pos_x < 0 || next.pos_y < 0 || next.pos_x > n - 1 || next.pos_y > m - 1 
                || gamemap[next.pos_x][next.pos_y] == '#' || vis[next.pos_x][next.pos_y])
                    continue;
                next.step = now.step+1;
                q.push(next);
                vis[next.pos_x][next.pos_y] = true;
            }
        }
    }
    printf("%d\n", count);
}