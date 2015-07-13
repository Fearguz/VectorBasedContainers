#pragma once

#include <vector>
#include <memory>

namespace VectorBasedContainers
{

template <typename T, class Alloc = std::allocator<T>>
class Stack
{
    private:
        std::vector<T, Alloc> m_data;

        size_t m_size;

    public:
        Stack() : m_data(), m_size(0) { }

        Stack(size_t capacity) : m_data(), m_size(0)
        {
            m_data.reserve(capacity);
        }

        Stack(const Stack &oth) : m_data(oth.m_data), m_size(oth.m_size) { }

        Stack(Stack &&oth) : m_data(std::move(oth.m_data)), m_size(std::move(m_size)) { }

        ~Stack()
        {
            clear();
        }

        void clear()
        {
            m_data.clear();
            m_size = 0;
        }

        bool empty() const throw()
        {
            return (m_size == 0);
        }

        size_t size() const throw()
        {
            return m_size;
        }

        const T& top() const
        {
            return m_data[m_size - 1];
        }

        void push(const T &val)
        {
            m_data.push_back(val);
            ++m_size;
        }

        void push(T &&val)
        {
            m_data.push_back(std::move(val));
            ++m_size;
        }

        void pop()
        {
            m_data.pop_back();
            --m_size;
        }
};

}
