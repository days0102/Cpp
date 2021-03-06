/*
 * @Author: Outsider
 * @Date: 2022-03-04 20:09:21
 * @LastEditors: Outsider
 * @LastEditTime: 2022-03-11 15:21:43
 * @Description: In User Settings Edit
 * @FilePath: \C++\Luogu\P3371.cpp
 */
// /*
//  * @Author: Outsider
//  * @Date: 2022-03-04 20:09:21
//  * @LastEditors: Outsider
//  * @LastEditTime: 2022-03-11 14:14:47
//  * @Description: In User Settings Edit
//  * @FilePath: \C++\Luogu\P3371.cpp
//  */

// #include<iostream>

// using namespace std;

// int n,m,s;

// const int c=10005;

// int arr[c][c];
// int dist[c];

// void dijkstra(int k)
// {
//     int* cnt=new int[n+1];
//     for(int i=1;i<=n;i++){
//         dist[i]=arr[k][i];
//         cnt[i]=0;
//     }
//     dist[k]=0;
//     cnt[k]=1;

//     for(int i=1;i<=n;i++){
//         int minn=0x7fffffff;
//         int node=k;
//         for(int j=1;j<=n;j++){
//             if((dist[j]<minn)&&(cnt[j]==0)){
//                 minn=dist[j];
//                 node=j;
//             }
//         }
//         cnt[node]=1;
//         for(int j=1;j<=n;j++){
//             if((dist[j]>dist[node]+arr[node][j])&&(cnt[j]==0)){
//                 if(dist[node]+arr[node][j]>0){
//                    dist[j]=dist[node]+arr[node][j];
//                 }
//             }
//         }
//     }
//     delete []cnt;
// }

// int main()
// {
//     cin>>n>>m>>s;

//     for(int i=1;i<=n;i++)
//     {
//         for(int j=1;j<=n;j++){
//             arr[i][j]=0x7fffffff;
//             if(i==j){
//                 arr[i][j]=0;
//             }
//         }
//     }

//     for(int i=0;i<m;i++){
//         int u,v,w;
//         cin>>u>>v>>w;
//         arr[u][v]=w;
//     }

//     // for(int i=1;i<=n;i++)
//     // {
//     //     for(int j=1;j<=n;j++){
//     //         cout<<arr[i][j]<<" ";

//     //     }
//     //     cout<<endl;
//     // }

//     dijkstra(s);
//     for(int i=1;i<=n;i++){
//         cout<<dist[i]<<" ";
//     }
//     cout<<endl;

//     system("pause");
// }

#include<iostream>
#include<queue>
using namespace std;
const int c=500005;
struct Edge{
    int from;
    int to;
    int w;
    int next;
}edge[c];
int head[10005];
int cnt=0;
void addEdge(int from,int to,int w)
{
    edge[cnt].to=to;
    edge[cnt].next=head[from];
    edge[cnt].w=w;
    head[from]=cnt++;
}
int dist[10005];
int vis[10005]={0};
int main()
{
    int n,m,s;
    cin>>n>>m>>s;
    for(int i=1;i<=n;i++)
    {
        dist[i]=0x7fffffff;
        head[i]=-1;
    }
    for(int i=0;i<m;i++)
    {
        int x,y,z;
        cin>>x>>y>>z;
        addEdge(x,y,z);
    }
    dist[s]=0;
    int cur=s;
    while(vis[cur]==0){
        vis[cur]=1;
        for(int i=head[cur];i!=-1;i=edge[i].next)
        {
            if(vis[edge[i].to]==0&&dist[edge[i].to]>dist[cur]+edge[i].w){
                dist[edge[i].to]=dist[cur]+edge[i].w;
            }
        }
        int minn=0x7fffffff;
        for(int i=1;i<=n;i++)
        {
            if(vis[i]==0&&dist[i]<minn){
                minn=dist[i];
                cur=i;
            }
        }
    }
    for(int i=1;i<=n;i++){
        cout<<dist[i]<<" ";
    }
    cout<<endl;
    system("pause");
}