#ifndef LOCKFREEQUEUE_HPP
#define LOCKFREEQUEUE_HPP

#include "ConcurrentQueue.hpp"

#include <boost/lockfree/queue.hpp>

template<typename T>
class LockfreeQueue : public ConcurrentQueue<T>
{
private:
    uint64_t mMaxSize;
    boost::lockfree::queue<T> mQueue;
public:
    LockfreeQueue(uint64_t maxSize = 100);
    LockfreeQueue(const LockfreeQueue&) = delete;
    LockfreeQueue& operator=(const LockfreeQueue&) = delete;
    virtual ~LockfreeQueue() {};
    virtual void pop(T& value) override;
    virtual void push(const T& value) override;
};

template<typename T>
LockfreeQueue<T>::LockfreeQueue(uint64_t maxSize)
    : mQueue(maxSize)
{
}

template<typename T>
void LockfreeQueue<T>::pop(T& value)
{
    while (!mQueue.pop(value)) {
        // Do nothing
    }
}

template<typename T>
void LockfreeQueue<T>::push(const T& value)
{
    while (!mQueue.push(value)) {
        // Do nothing
    }
}


#endif
