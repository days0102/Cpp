//#include<iostream>
//#include<algorithm>
//#include<iomanip>
//#include<cmath>//cbrt()函数返回n的三次方根 
//using namespace std;
//int main()
//{
//	double n;
//	cin>>n;
//	cout<<setprecision(6)<<fixed<<cbrt(n)<<endl;
//	return 0;
//} 


#include<iostream>
#include<algorithm>
#include<iomanip>
#include<cmath>//cbrt()函数返回n的三次方根 
using namespace std;

double q(double x)
{
	return x*x*x;
}
int main()
{
	double n;
	cin>>n;
	double l=-10000,r=10000;
	double mid;
	while(r-l>1e-7)//此处应为10的-7次方
	{
		mid=(l+r)/2;
		if(q(mid)>n)
			r=mid;
		else
			l=mid;
	}
	cout<<setprecision(6)<<fixed<<mid<<endl;
	return 0;
} 
