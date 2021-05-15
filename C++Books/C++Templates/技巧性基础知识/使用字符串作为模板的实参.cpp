
//#include<iostream>
//using namespace std;
//
//template<typename T>
//inline T const& max(T const& a, T const& b)
//{
//	return a < b ? b : a;
//}
//
//
//int main()
//{
//	std::string s;
//	
//	//在函数max前加::说明是在顶层命名空间（相当于全局变量）中调用
//	//如果没有加::,因为使用了std会出现调用二义性编译错误
//	std::cout << ::max("apple", "peach") << std::endl;
//
//	//"apple"类型为char const[6],"tomata"类型为char const[7]
//	//::max("apple", "tomato");  //错误，不同类型的实参
//	//::max("apple", s);         //错误，不同类型的实参
//}
//
//#include<iostream>
//using namespace std;
//
////非引用参数
//template<typename T>
//inline T max(T a, T b)
//{
//	return a < b ? b : a;
//}
//int main()
//{
//	string s;
//
//	::max("apple", "peach");
//
//	//对于非引用类型的参数，在实参演绎的过程中，会出现数组到指针的类型转换(decay)  
//	::max("apple", "tomato");//通过，但会退化(decay)为相同的类型 
//	//::max("apple",s);//错误，不同的类型 
//}

#include<iostream>
#include<typeinfo>

template<typename T>
void ref(T const& x)
{
	std::cout << "x in ref(T const&): " << typeid(x).name() << std::endl;
}

template<typename T>
void nonref(T x)
{
	std::cout << "x in nonref(T x): " << typeid(x).name() << std::endl;
}

int main()
{
	ref("hello");
	nonref("hello");
	std::cout << typeid(2).name() << std::endl;//查看数据类型
}
