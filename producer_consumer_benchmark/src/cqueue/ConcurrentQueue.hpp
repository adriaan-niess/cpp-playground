#ifndef CONCURRENT_QUEUE_HPP
#define CONCURRENT_QUEUE_HPP

namespace cqueue {

template<typename T>
class ConcurrentQueue
{
public:
    virtual ~ConcurrentQueue() {};

    /**
     * Retrieves and removes an element from queue's head and blocks if necessary.
     *
     * @param value Reference used to store the element.
     */
    virtual void take(T& value) = 0;
    
    /**
     * Adds a specified element to the queue's tail and waits if necessary for space to become available.
     *
     * @param value The element to add.
     */
    virtual void put(const T& value) = 0;

    /**
     * Removes an element from the front of the queue if present.
     *
     * @param value Reference used to store the element.
     * @return True if an element was removed, false otherwise.
     */
    virtual bool remove(T& value) = 0;

    /**
     * Adds an element to back of the if enough space is available.
     *
     * @param value The element to add.
     * @return True if the element was added, false otherwise.
     */
    virtual bool add(const T& value) = 0;
};

} // namespace cqueue

#endif
