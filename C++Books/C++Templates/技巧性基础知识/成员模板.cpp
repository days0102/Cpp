#include<iostream>
#include<deque>
using namespace std;
template<typename T>
class Stack{
private:
    std::deque<T> elems;
public:
    //缺省的赋值运算符要求两边要有相同的类型
    template<typename T2>//使用元素类型为T2的栈进行赋值
    Stack<T>& operator=(Stack<T2>const&)
};
//实现部分
template<typename T>
template<typename T2>
Stack<T>& Stack<T>::operator=(const Stack<T2> &) {
    /*
     * 模板赋值运算符并没有取代缺省赋值运算符，对于相同栈类型之间的赋值仍然回调用缺省的赋值运算符
     */
    return *this;
}

//内部容器类型实现为一个模板参数
template<typename T,typename CONT=std::deque<T>>
class Stack
{
private:
    CONT elems;
public:
    template<typename T2,typename CONT2>//把元素类型为T2的栈赋值给原栈
    Stack<T,CONT>& operator=(Stack<T2,CONT2>const&);
};
template<typename T,typename CONT>
template<typename T2,typename CONT2>
Stack<T,CONT>& Stack<T,CONT>::operator=(Stack<T2,CONT2>const&t2)
{
    //对于类模板而言，只有那些被调用的成员函数才会被实例化
}
int main()
{
	
} 
