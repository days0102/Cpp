/*
 * @Author: Outsider
 * @Date: 2023-02-15 12:30:59
 * @LastEditors: Outsider
 * @LastEditTime: 2023-02-15 13:17:47
 * @Description: In User Settings Edit
 * @FilePath: \Lq\Luogu\BinarySearch\P1024-bs.cc
 */
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
double a, b, c, d;
double fun(double x)
{
    return a * x * x * x + b * x * x + c * x + d;
}
int main()
{
    cin >> a >> b >> c >> d;
    for (double i = -100; i <= 100; i++)
    {
        if (fun(i) == 0)
        {
            cout << fixed << setprecision(2) << i << " ";
        }
        else if (fun(i) * fun(i + 1) < 0)
        {
            double ll = i, rr = i + 1;
            while (rr - ll > 1e-5)
            {
                double mm = ll + ((rr - ll) / 2);
                if (fun(mm) * fun(rr) < 0)
                {
                    ll = mm;
                }
                else
                {
                    rr = mm;
                }
            }
            cout << fixed << setprecision(2) << ll << " ";
        }
    }
}