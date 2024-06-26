#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <condition_variable>
#include <mutex>
#include <queue>

template <typename T>

// Queue class, it is responsible for ensuring continuaity in the Network and "shepherding" the clients into playing at roughly the same pace.
// In a five philosophers example, it is a 6th "waiter" that determines who gets to go first in gaining the chopsticks necessary to eat.
class Queue
{
    public:
        T pop() // Blocking pop
        {
            std::unique_lock<std::mutex> mlock(m_mutex);
            m_cond.wait(mlock, [this]{return !m_queue.empty();});
            auto val = m_queue.front();
            m_queue.pop();
            return val;
        }

        void pop(T& item) // pop will not wait with an empty queue
        {
            std::unique_lock<std::mutex> mlock(m_mutex);
            if (m_queue.empty())
            {
                return;
            }
            item = m_queue.front();
            m_queue.pop();
        }

        void push(const T& item)
        {
            std::unique_lock<std::mutex> mlock(m_mutex);
            m_queue.push(item);
            m_cond.notify_one();
        }
        Queue()=default;
        Queue(const Queue&) = delete;            // disable copying
        Queue& operator=(const Queue&) = delete; // disable assignment

    private:
        std::queue<T> m_queue;
        std::mutex m_mutex;
        std::condition_variable m_cond;
};

#endif
