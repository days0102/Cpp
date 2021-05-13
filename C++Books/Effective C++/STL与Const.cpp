#include<iostream>
#include<vector>
using namespace std;
int main()
{
	vector<int>v;
	v.push_back(2);
	v.push_back(5);
	vector<int>::iterator it=v.begin();//迭代器
	//用const约束it1的指向不能变，所指的变量的值可以变，相当于 *const 
	const vector<int>::iterator it1=v.begin();	 
	//用const_iterator约束所指的变量的值不可改变，相当于const* 
	vector<int>::const_iterator it2=v.begin();
	//it1=v.end();//报错
	//*it2=1; //报错 
	const vector<int>::const_iterator it3=v.begin();//指针的指向和指针所指向的值不能变 
} 
