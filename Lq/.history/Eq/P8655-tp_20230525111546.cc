/*
 * @Author       : Outsider
 * @Date         : 2023-05-24 21:47:59
 * @LastEditors  : Outsider
 * @LastEditTime : 2023-05-25 11:15:46
 * @Description  : In User Settings Edit
 * @FilePath     : \Lq\Eq\P8655-tp.cc
 */
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
const int c = 1005;
int s[c];
int vis[c];
int n;

vector<int> G[c];

int main()
{
    cin >> n;
    for (int i = 0; i <= n + 1; i++)
    {
        s[i] = i;
    }
    int x, y;
    int src, dst;
    for (int i = 0; i < n; i++)
    {
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for (int i = 1; i <= n; i++)
    {
        vis[src] = 1;
        dfs(i, 1);
        memset(vis, 0, (n + 1) * 4);
    }
    return 0;
}