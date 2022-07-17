//
// Created by Wanxi on 2022/2/13.
//

#ifndef MEMORYPOOL_TESTSTACK_H
#define MEMORYPOOL_TESTSTACK_H

#include <memory>

template<typename T, typename alloc = std::allocator<T>>
class TestStack
{
private:
    // 定义结构体
    template<typename U>
    struct stackNode
    {
        U data;
        stackNode* prev = nullptr;
        stackNode(U element)
        {
            data = element;
        }
    };
    // 定义分配器
    typedef typename alloc::template rebind<stackNode<T>>::other allocator_;

    allocator_ allocator;
    stackNode<T>* top_;
public:
    TestStack();
    ~TestStack();

    void pop(); // pop满足stl，不返回只弹出
    void push(T element);
    void clear();
    T top();
};

template<typename T, typename alloc>
TestStack<T, alloc>::TestStack(): top_(nullptr)
{
}

template<typename T, typename alloc>
TestStack<T, alloc>::~TestStack()
{
    clear();
}

template<typename T, typename alloc>
void TestStack<T, alloc>::clear()
{
    while (top_ != nullptr)
        this->pop();
}

template<typename T, typename alloc>
void TestStack<T, alloc>::push(T element)
{
    stackNode<T>* temp = allocator.allocate(1);
    allocator.construct(temp, stackNode<T>(element));
    temp->prev = top_;
    top_ = temp;
}

template<typename T, typename alloc>
void TestStack<T, alloc>::pop()
{
    stackNode<T>* temp = top_->prev;
    allocator.destroy(top_);
    allocator.deallocate(top_, 1);
    top_ = temp;
}

template<typename T, typename alloc>
T TestStack<T, alloc>::top()
{
    if (!top_)
        return top_->data;
}

#endif //MEMORYPOOL_TESTSTACK_H