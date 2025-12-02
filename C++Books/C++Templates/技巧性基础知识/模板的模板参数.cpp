#include<iostream>
#include<vector>
#include<deque>

//如果要使用一个和缺省值不同的内部容器，必须两次指定元素类型
//即为了指定内部容器的类型，需要同时传递容器的类型和它所含有元素的类型，如下：
Stack<int,std::vector<int> >vStack;

//然而，借助模板的模板参数，可以只指定容器的类型而不需要指定所含元素的类型
Stack<int,std::vector>vStack;
//为了获得这个特性，必须把第2个模板参数指定为模板的模板参数，声明如下：
template<typename T, template<typename ELEM>class CONT=std::deque>//ELEM为模板参数，可省略
//上面的class不能改为typename
class Stack{
private:
    CONT<T>elems;//使用第1个模板参数作为的2个模板参数的实例化类型(一般地，可以使用类模板中地任意类型来实例化模板的模板参数)
public:

};

//零初始化（初始化模板类型的变量）
template<typename T>
void foo()
{
    T x;//如果T是内奸类型，那么x本身是一个不确定值
    //显式的调用内建类型的缺省构造函数，把缺省值设为0或false
    T y=T();
    //对于类成员可使用构造函数
}