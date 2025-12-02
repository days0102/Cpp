#include<iostream>
using namespace std;
//两个成员函数如果只是常量性不同，可以被重载 
class TextBlock 
{
	public:
		//size_t是一个与机器相关的unsigned类型
		//sizeof返回的就是size_t类型，数组下标也是size_t类型 
		const char& operator[](std::size_t position) const
		{
			return text[position];
		}
		char& operator[](std::size_t position)
		{
			return text[position];
		}
		//参数不能是char*,无法从char*转换为string
		TextBlock(string s):text(s){
		}
		private:
			std::string text;
}; 
int main()
{
	TextBlock tb("Hello");
	std::cout<<tb[0]<<endl;//调用non-const 
	const TextBlock ctb("World");
	std::cout<<ctb[0]<<endl;//调用const 
} 
