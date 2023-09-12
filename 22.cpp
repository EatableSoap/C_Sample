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
bool vis[101][101][51];

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

        //bfs code
        q.push(start);
        vis[start.pos_x][start.pos_y][start.time%k]=true;
        while(!q.empty())
        {
            now=q.front();
            q.pop();

            //set break condition
            if(now.pos_x==end.pos_x&&now.pos_y==end.pos_y)
            {
                count=now.time;
                break;
            }

            //add next step to queue
            for (int i = 0; i < 4; i++)
            {
                next.pos_x=now.pos_x+dir[0][i];
                next.pos_y=now.pos_y+dir[1][i];
                next.time=now.time+1;
                //judge the position is vaild or not
                if(next.pos_x<0 || next.pos_y<0||next.pos_x>n-1||next.pos_y>m-1
                ||gamemap[next.pos_x][next.pos_y]=='#'||vis[next.pos_x][next.pos_y][next.time%k]
                ||(gamemap[next.pos_x][next.pos_y]=='*'&&next.time%k))
                {
                    continue;
                }
                q.push(next);
                vis[next.pos_x][next.pos_y][next.time%k]=true;
            }
        }
        printf("%d\n",count);
    }
}