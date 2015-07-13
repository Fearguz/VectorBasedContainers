#pragma once

#include <vector>
#include <memory>

namespace VectorBasedContainers
{

template <typename T, size_t C = 10, class Alloc = std::allocator<T>>
class Queue
{
    private:
        std::vector<T, Alloc> m_data;

        size_t m_front;
        size_t m_size;
        size_t m_capacity;

        int validate()
        {
            if ((m_size + 1) > m_capacity)
            {
                return -1;
            }
            else if (m_data.size() + 1 > m_data.capacity())
            {
                m_data.erase(m_data.begin(), m_data.begin() + m_front);
                m_front = 0;
                m_size = m_data.size();
            }

            return 0;
        }

    public:
        Queue() : m_data(), m_front(0), m_size(0), m_capacity(C)
        {
            m_data.reserve(m_capacity);
        }

        Queue(const Queue& other) : m_data(other.m_data), m_front(other.m_front), m_size(other.m_size), m_capacity(C)
        {
            m_data.reserve(m_capacity);
        }

        Queue(Queue &&other) : m_data(std::move(other.m_data)), m_front(std::move(other.m_front)), m_size(std::move(other.m_size)), m_capacity(C)
        {
            m_data.reserve(m_capacity);
        }

        Queue& operator=(const Queue& other)
        {
            if (&(*this) == &other)
            {
                return *this;
            }

            m_data = other.m_data;
            m_front = other.m_front;
            m_size = other.m_size;
            return *this;
        }

        ~Queue()
        {
            clear();
        }

        bool empty() const throw()
        {
            return (m_size == 0);
        }

        size_t size() const throw()
        {
            return m_size;
        }

        void clear()
        {
            m_data.clear();
            m_size = m_front = 0;
        }

        const T& front() const
        {
            return m_data[m_front];
        }

        const T& back() const
        {
            return m_data[m_size - 1];
        }

        int push_back(const T &val)
        {
            if (validate() != 0)
            {
                return -1;
            }
            m_data.push_back(val);
            ++m_size;
            return 0;
        }

        int push_back(T &&val)
        {
            if (validate() != 0)
            {
                return -1;
            }
            m_data.push_back(std::move(val));
            ++m_size;
            return 0;
        }

        void pop()
        {
            ++m_front;
            --m_size;
        }
};

}
