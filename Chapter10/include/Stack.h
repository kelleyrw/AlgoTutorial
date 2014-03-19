#ifndef RWK_STACK_H
#define RWK_STACK_H

namespace rwk
{
    template <typename T>
    class stack
    {
    public:
        // typedefs:
        typedef T value_type;

        // construct:
        stack();

        // methods:
        bool empty() const;
        int size() const;
        void push(T const &value);
        void push(T &&value);
        void pop();
        value_type& top();
        value_type const& top() const;

    private:
        // members:
        static const int s_ArraySize = 1024;
        T m_Array[s_ArraySize];
        int m_Size;
    };

} // namespace rwk

#pragma region Implementation

#include <cassert>

namespace rwk
{
    // construct:
    template <typename T>
    stack<T>::stack()
        : m_Array()
        , m_Size(0)
    {}

    // methods:
    template <typename T>
    bool stack<T>::empty() const
    {
        return (m_Size == 0);
    }

    template <typename T>
    int stack<T>::size() const
    {
        return m_Size;
    }

    template <typename T>
    void stack<T>::push(T const &value)
    {
        assert(m_Size + 1 < s_ArraySize);
        m_Array[m_Size++] = value;
    }

    template <typename T>
    void stack<T>::push(T &&value)
    {
        assert(m_Size + 1 < s_ArraySize);
        m_Array[m_Size++] = std::move(value);
    }

    template <typename T>
    void stack<T>::pop()
    {
        assert(!empty());
        m_Size--;
    }

    template <typename T>
    typename stack<T>::value_type& stack<T>::top()
    {
        return m_Array[m_Size - 1];
    }

    template <typename T>
    typename stack<T>::value_type const& stack<T>::top() const
    {
        return m_Array[m_Size - 1];
    }
}

#pragma endregion

#endif // #define RWK_STACK_H