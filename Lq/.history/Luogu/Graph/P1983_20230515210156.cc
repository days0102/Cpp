/*
 * @Author       : Outsider
 * @Date         : 2023-05-03 21:21:35
 * @LastEditors  : Outsider
 * @LastEditTime : 2023-05-15 20:50:17
 * @Description  : In User Settings Edit
 * @FilePath     : \Lq\Luogu\Graph\P1983.cc
 */
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;
int n, m;

vector<int> v[1005];
vector<int> G[1005];
int in[1005];
int out[1005];
int qq[1005];
unordered_set<int> s;

int main()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x;
        for (int j = 0; j < x; j++)
        {
            cin >> y;
            v[i].push_back(y);
            s.insert(y);
        }
        for (auto x : v[i])
        {
            for (int j = 1; j <= n; j++)
            {
                if (s.find(j) == s.end())
                {
                    G[x].push_back(j);
                    in[j]++;
                    out[x]++;
                }
            }
        }
    }

    int hh = 0, tt = -1;

    for (int i = 1; i <= n; i++)
    {
        if (in[i] == 0)
        {
            qq[++tt] = i;
        }
    }

    while (tt >= hh)
    {
        auto x = qq[hh++];
    }
}