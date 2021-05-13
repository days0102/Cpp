#include<iostream>
using namespace std;
int main()
{
	//const出现在*左边表示被指物是常量
	int a=5;
	const int*p=&a;//等价于int const*p=&a; 
	cout<<*p<<endl;
	a=2;//可以修改a的值 
	//*p=1;//报错 
	cout<<*p<<endl;
	
	//const出现在*右边表示指针自身是常量
	int b=10;
	int *const q=&b;
	cout<<*q<<endl; 
	//q=&a; //报错
} 
