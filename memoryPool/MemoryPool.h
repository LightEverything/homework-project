//
// Created by Wanxi on 2022/2/14.
//

#ifndef MEMORYPOOL_MEMORYPOOL_H
#define MEMORYPOOL_MEMORYPOOL_H


template<typename T, size_t blockSize = 4096>
class MemoryPool
{
private:
    union slot_
    {
        T data;
        slot_* prev;
    };

    slot_* currentBlock;
    slot_* currentSlot;
    slot_* freeBlock;
    slot_* lastBlock;
public:
    template <typename U>
    struct rebind
    {
        typedef MemoryPool<U> other;
    };

    MemoryPool() noexcept;
    ~MemoryPool() noexcept;

    template<typename U, typename ...argv>
    void construct(U* pointer, argv&&... argvs);

    template<typename U>
    void destroy(U* pointer);
    T* allocate(size_t n = 1, T* hint = 0);
    void deallocate(T* pointer, size_t n = 1);
};

template<typename T, size_t blockSize>
MemoryPool<T, blockSize>::MemoryPool() noexcept:
        currentBlock(nullptr),
        currentSlot(nullptr),
        freeBlock(nullptr),
        lastBlock(nullptr)
{

}
template<typename T, size_t blockSize>
    template<typename U, typename... argv>
void MemoryPool<T, blockSize>::construct(U *pointer, argv &&...argvs)
{
    new(pointer) U (std::forward<argv>(argvs)...);
}

template<typename T, size_t blockSize>
void MemoryPool<T, blockSize>::deallocate(T *pointer, size_t n)
{
    reinterpret_cast<slot_*>(pointer)->prev = freeBlock;
    freeBlock = reinterpret_cast<slot_*>(pointer);
}

template<typename T, size_t blockSize>
MemoryPool<T, blockSize>::~MemoryPool<T, blockSize>() noexcept
{
    while (currentBlock) {
        slot_* temp = currentBlock->prev;
        void* temptemp = reinterpret_cast<void*>(currentBlock);
        operator delete(temptemp);
        currentBlock= temp;
    }
}

template<typename T, size_t blockSize>
T *MemoryPool<T, blockSize>::allocate(size_t n, T *hint)
{
    if (freeBlock)
    {
        T* rePoint = reinterpret_cast<T*>(freeBlock);
        freeBlock = freeBlock->prev;
        return rePoint;
    }
    else
    {
        if (currentSlot >= lastBlock)
        {
            char* newBlock = reinterpret_cast<char*>(operator new(blockSize));
            reinterpret_cast<slot_*>(newBlock)->prev = currentBlock;
            currentBlock = reinterpret_cast<slot_*>(newBlock);

            // 对齐
            char* addBody = newBlock + sizeof(slot_*);
            size_t bodyPadding = ((newBlock + blockSize) - addBody) % alignof(slot_);
            currentSlot = reinterpret_cast<slot_*>(addBody + bodyPadding);
            lastBlock = reinterpret_cast<slot_*>(newBlock + blockSize - sizeof(slot_) );
        }
        return reinterpret_cast<T*>(currentSlot++);
    }
}

template<typename T, size_t blockSize>
    template<typename U>
void MemoryPool<T, blockSize>::destroy(U *pointer)
{
    pointer->~U();
}

#endif //MEMORYPOOL_MEMORYPOOL_H