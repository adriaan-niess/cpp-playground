#include "cqueue/ConcurrentQueue.hpp"
#include "cqueue/BlockingQueue.hpp"
#include "cqueue/LockfreeQueue.hpp"

#include <iostream>
#include <cstdlib>
#include <thread>
#include <functional>
#include <chrono>
#include <fstream>

using namespace cqueue;

#define ITERATIONS 100
#define PRODUCE_INTERVAL 2ms
#define PRODUCER_LOGFILE "producer.csv"
#define CONSUMER_LOGFILE "consumer.csv"

inline std::chrono::nanoseconds now()
{
    auto time_point = std::chrono::system_clock::now();
    auto duration = time_point.time_since_epoch();
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    return nanoseconds;
}

void produce(ConcurrentQueue<int>& queue, const std::string& logfile, uint64_t iterations)
{
    using namespace std::chrono_literals;
    std::ofstream file;
    file.open(logfile);
    for (uint64_t i = 0; i < iterations; i++) {
        file << i << "," << now().count() << std::endl;
        queue.put(i);
        std::this_thread::sleep_for(PRODUCE_INTERVAL);
    }
    file.close();
}

void consume(ConcurrentQueue<int>& queue, const std::string& logfile, uint64_t iterations)
{
    using namespace std::chrono_literals;
    std::ofstream file;
    file.open(logfile);
    int value;
    for (uint64_t i = 0; i < iterations; i++) {
        queue.take(value);
        file << value << "," << now().count() << std::endl;
    }
    file.close();
}

void measureLatency(ConcurrentQueue<int>& queue, const std::string& prefix, uint64_t iterations)
{
    std::string prodLogfile = prefix + PRODUCER_LOGFILE;
    std::string consumerLogfile = prefix + CONSUMER_LOGFILE;
    std::thread producer(std::bind(&produce, std::ref(queue), std::ref(prodLogfile), iterations));
    std::thread consumer(std::bind(&consume, std::ref(queue), std::ref(consumerLogfile), iterations));
    producer.join();
    consumer.join();
}

int main(int argc, char** argv)
{
    uint64_t iterations = ITERATIONS;
    if (argc > 1) {
        iterations = std::atoi(argv[1]);
    }
    LockfreeQueue<int> lockfreeQueue;
    measureLatency(lockfreeQueue, "results/lockfree_", iterations);
    
    BlockingQueue<int> blockingQueue;
    measureLatency(blockingQueue, "results/blocking_", iterations);

    return EXIT_SUCCESS;
}
