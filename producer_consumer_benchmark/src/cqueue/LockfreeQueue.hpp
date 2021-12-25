#ifndef LOCKFREEQUEUE_HPP
#define LOCKFREEQUEUE_HPP

#include "cqueue/ConcurrentQueue.hpp"

#include <boost/lockfree/queue.hpp>

namespace cqueue {

template<typename T>
class LockfreeQueue : public ConcurrentQueue<T>
{
private:
    uint64_t mCapacitiy;
    boost::lockfree::queue<T> mQueue;
public:
    LockfreeQueue(uint64_t maxSize = 100);
    LockfreeQueue(const LockfreeQueue&) = delete;
    LockfreeQueue& operator=(const LockfreeQueue&) = delete;
    virtual ~LockfreeQueue() {};
    virtual void take(T& value) override;
    virtual void put(const T& value) override;
    virtual bool remove(T& value) override;
    virtual bool add(const T& value) override;
};

template<typename T>
LockfreeQueue<T>::LockfreeQueue(uint64_t capacitiy)
    : mQueue(capacitiy)
{
}

template<typename T>
void LockfreeQueue<T>::take(T& value)
{
    while (!mQueue.pop(value)) {
        // Do nothing
    }
}

template<typename T>
void LockfreeQueue<T>::put(const T& value)
{
    while (!mQueue.push(value)) {
        // Do nothing
    }
}

template<typename T>
bool LockfreeQueue<T>::remove(T& value)
{
    return mQueue.pop(value);
}

template<typename T>
bool LockfreeQueue<T>::add(const T& value)
{
    return mQueue.push(value);
}

} // namespace cqueue

#endif
