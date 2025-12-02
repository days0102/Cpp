/*注意: 
1)对于单纯常量，最好以const对象或enums代替#defines。
2)对于形似函数的宏(macros),最好改用inline函数替换#defines。 
*/

#include<iostream>
using namespace std;
class Gameplay
{
	public:
		const int num=5;//const约束可以在声明式初始化
		static const int cnt=2;
		/*也可以用初始式对num初始化 
		const int num;
		Gameplay(int x):num(x){}  
		*/ 
		static const int ans;//在类外赋值 
};
//cnt的定义式 
const int Gameplay::cnt; 
const int Gameplay::ans=10; //定义时只用去除static 
int main()
{
	Gameplay one;
	cout<<one.num<<endl;
	cout<<&(one.num)<<endl; 
	cout<<one.cnt<<endl;//没有对cnt地址操作，没有定义式是正确的 
	cout<<&(one.cnt)<<endl;//如果没有cnt的定义式，会报错
	cout<<one.ans<<endl; 
}
