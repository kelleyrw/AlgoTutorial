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
        static const unsigned int s_ArraySize = 1024;
        T m_Array[s_ArraySize];
        T* m_TopPtr;
        int m_Size;
    };

} // namespace rwk

// implementation

namespace rwk
{
    // construct:
    template <typename T>
    stack<T>::stack()
        : m_Array()
        , m_TopPtr(NULL)
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
        if (!empty())
        {
            assert(m_Size + 1 < s_ArraySize);
            *(m_TopPtr++) = value;
        }
        else
        {
            m_TopPtr = &m_Array[0];
            *m_TopPtr = value;
        }
        m_Size++;
    }

    template <typename T>
    void stack<T>::push(T &&value)
    {
        if (!empty())
        {
            assert(m_Size + 1 < s_ArraySize);
            *(m_TopPtr++) = std::move(value);
        }
        else
        {
            m_TopPtr = &m_Array[0];
            *m_TopPtr = std::move(value);
        }
        m_Size++;
    }

    template <typename T>
    void stack<T>::pop()
    {
        assert(!empty());
        m_TopPtr--;
    }

    template <typename T>
    T& stack<T>::top()
    {
        return *m_TopPtr;
    }

    template <typename T>
    T const& stack<T>::top() const
    {
        return *m_TopPtr;
    }
}

#endif // #define RWK_STACK_H