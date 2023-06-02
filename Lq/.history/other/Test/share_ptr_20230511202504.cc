#include <iostream>

template <class T>
class share_ptr
{
private:
    int* ref_;
    T* ptr_;

public:
    share_ptr(T*);
    share_ptr(share_ptr& _ptr);
    share_ptr(share_ptr&& _ptr);

    T operator*();

    ~share_ptr();
};
template <class T>
T share_ptr<T>::operator*()
{
    return *ptr;
}

template <class T>
share_ptr<T>::share_ptr(T* ptr) : ptr_(ptr), ref(new int)
{
}
template <class T>
share_ptr<T>::share_ptr(share_ptr<T>& _ptr)
{
    ref_ = _ptr.ref_;
    ptr_ = _ptr.ptr_;
    *ref_++;
}
template <class T>
share_ptr<T>::share_ptr(share_ptr&& _ptr)
{
    ref_ = std::move(_ptr.ref_);
    ptr_ = std::move(_ptr.ptr_);
}

template <class T>
share_ptr<T>::~share_ptr()
{
    if (--(*ref_) == 0)
    {
        delete ptr_;
        ptr_ = nullptr;
    }
}

int main() { auto ptr = share_ptr<int>(new int); }