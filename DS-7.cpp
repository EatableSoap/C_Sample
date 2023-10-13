#include <iostream>
#include <vector>
using namespace std;

int n = 0;

struct Step
{
    int x, y;
};

bool vis[100][101] = {false};
int gamemap[100][101] = {0};
vector<Step> step_sol;
vector<Step> sol;

void dfs(int n_x, int n_y)
{
    if (n_x == n - 1 && n_y == n - 1)
    {
        step_sol.push_back(Step{n_x, n_y});
        sol = step_sol;
        return;
    }

    if (gamemap[0][0])
        return;

    step_sol.push_back(Step{n_x, n_y});
    vis[n_x][n_y] = true;

    if (n_x < n - 1 && !gamemap[n_x + 1][n_y] && !vis[n_x + 1][n_y])
    {
        dfs(n_x + 1, n_y);
        vis[n_x + 1][n_y] = false;
        step_sol.pop_back();
    }
    if (n_y < n - 1 && !gamemap[n_x][n_y + 1] && !vis[n_x][n_y + 1])
    {
        dfs(n_x, n_y + 1);
        vis[n_x][n_y + 1] = false;
        step_sol.pop_back();
    }
    if (n_y > 0 && !gamemap[n_x][n_y - 1] && !vis[n_x][n_y - 1])
    {
        dfs(n_x, n_y - 1);
        vis[n_x][n_y - 1] = false;
        step_sol.pop_back();
    }
    if (n_x > 0 && !gamemap[n_x - 1][n_y] && !vis[n_x - 1][n_y])
    {
        dfs(n_x - 1, n_y);
        vis[n_x - 1][n_y] = false;
        step_sol.pop_back();
    }
}

int main()
{
    scanf("%d %*d", &n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cin >> gamemap[i][j];
    } // 读入地图
    dfs(0, 0);
    if (sol.empty())
        cout << "There is no solution!";
    else
        for (int i = 0; i < sol.size(); i++)
            printf("<%d,%d> ", sol[i].x + 1, sol[i].y + 1);
    cout << endl;
}