#ifndef P_TSQUEUE
#define P_TSQUEUE

#include <deque>
#include <mutex>

namespace punkyoi_api {

    template<class T>
    class tsqueue {
    public:
        tsqueue() = default;
        tsqueue(const tsqueue& other) = delete;

        const T& back() {
            std::scoped_lock lock(m_mutex);
            return m_deque.back();
        }

        const T& front() {
            std::scoped_lock lock(m_mutex);
            return m_deque.front();
        }

        T get_front() {
            std::scoped_lock lock(m_mutex);
            T result = std::move(m_deque.front());
            return result;
        }

        T get_back() {
            std::scoped_lock lock(m_mutex);
            T result = std::move(m_deque.back());
            return result;
        }

        void push_front(const T& value) {
            std::scoped_lock lock(m_mutex);
            m_deque.push_front(value);
        }

        void push_back(const T& value) {
            std::scoped_lock lock(m_mutex);
            m_deque.push_back(value);
        }

        void pop_front() {
            std::scoped_lock lock(m_mutex);
            m_deque.pop_front();
        }

        void pop_back() {
            std::scoped_lock lock(m_mutex);
            m_deque.pop_back();
        }

        bool empty() {
            std::scoped_lock lock(m_mutex);
            return m_deque.empty();
        }

        size_t size() {
            std::scoped_lock lock(m_mutex);
            return m_deque.size();
        }

        void clear() {
            std::scoped_lock lock(m_mutex);
            m_deque.clear();
        }


    protected:
        std::mutex m_mutex;
        std::deque<T> m_deque;
    };
}

#endif
