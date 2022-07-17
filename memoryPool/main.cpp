#include <iostream>
#include <ctime>

#include "TestStack.h"
#include "MemoryPool.h"

// 插入元素个数
#define ELEMS 25000
// 重复次数
#define REPS 50

int main()
{
    clock_t start;

    // 使用默认分配器
//    TestStack<int, std::allocator<int> > stackDefault;
//    start = clock();
//    for (int j = 0; j < REPS; j++) {
//        for (int i = 0; i < ELEMS; i++)
//            stackDefault.push(i);
//        for (int i = 0; i < ELEMS; i++)
//            stackDefault.pop();
//    }
//    std::cout << "Default Allocator Time: ";
//    std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";

     //使用内存池
     TestStack<int, MemoryPool<int>> stackPool;
     start = clock();
     for (int j = 0; j < REPS; j++) {
         for (int i = 0; i < ELEMS; i++)
           stackPool.push(i);
         for (int i = 0; i < ELEMS; i++)
           stackPool.pop();
     }
     std::cout << "MemoryPool Allocator Time: ";
     std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";

    return 0;
}