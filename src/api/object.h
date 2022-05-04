#pragma once

#include <unordered_map>

namespace punkyoi_api {

    template<class T>
    class object {
        using counter_type = size_t;
    public:
        object() {
        }

        object(const object& x) {
            *this = x;
        }

        ~object() {
            release();
        }

        object& operator=(const object& x) {
            release();
            m_object = x.m_object;
            m_counter = x.m_counter;
            if (m_object) {
                ++(*m_counter);
            }
            return *this;
        }

        T* operator->() const {
            return m_object;
        }

        operator T* () const {
            return m_object;
        }

        template<class X>
        operator object<X>() {
            static_assert(std::is_base_of<X, T>::value, "Implicit cast is only for upcasting!");
            return as<X>();
        }

        template<class X>
        object<X> as() {
            return object<X>(static_cast<X*>(m_object), m_counter);
        }

        template<class... Args>
        static object new_instance(Args&&... args) {
            return object<T>(new T(args...));
        }

        void release() {
            if (m_counter) {
                --(*m_counter);
                if ((*m_counter) == 0) {
                    delete m_object;
                    delete m_counter;
                    m_object = nullptr;
                    m_counter = nullptr;
                }
            }
        }

        typedef T value_type;

        template<class X>
        friend class object;

    private:
        object(T* ptr) {
            m_object = ptr;
            m_counter = new counter_type();
            ++(*m_counter);
        }

        object(T* ptr, counter_type* counter) {
            m_object = ptr;
            m_counter = counter;
            if (m_counter) {
                ++(*m_counter);
            }
        }

        T* m_object = nullptr;
        counter_type* m_counter = nullptr;
    };

    template<class T, class... Args>
    inline object<T> new_instance(Args&&... args) {
        return object<T>::new_instance(args...);
    }
}