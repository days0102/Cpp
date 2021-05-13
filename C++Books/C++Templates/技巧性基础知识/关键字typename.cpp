#include<iostream>
using namespace std;
template<typename T>
class MyClass
{
    typename T::SubType *ptr;//说明SubType是定义于类T中的一种类型，即ptr是一个指向T::SubType类型的指针
    //如果不使用typename,SubType会被认为是一个静态成员，即被看成是T::SubType与ptr的乘积
};

//.template构造
template<int N>
void printBitset(std::bitset<N> const&bs)
{
    //如果没有.template编译器将不知道bs.template后面的小于号<并不是数学中的小于号，而是模板实参列表的起始符号
    std::cout<<bs.template to_string<char,char_traits<char>,allocator<char> >();
}

//使用this->
//对于具有基类的类模板，自身使用名称x并不一定等同于this->x,即使该x是从基类继承获得的
template<typename T>
class Base
{
public:
    void exit();
};
template<typename T>
class Derived:Base<T>
{
public:
    void foo()
    {
        //foo()内部决定要调用哪一个exit()时，并不会考虑基类Base中定义的exit()
        exit();//调用外部的exit()或者出现错误
        //限定成员的访问this->或Base<T>::
    }
};

int main()
{

}
