#ifndef CONCURRENT_QUEUE_HPP
#define CONCURRENT_QUEUE_HPP

template<typename T>
class ConcurrentQueue
{
public:
    virtual ~ConcurrentQueue() {};
    virtual void pop(T& value) = 0;
    virtual void push(const T& value) = 0;
};

#endif
