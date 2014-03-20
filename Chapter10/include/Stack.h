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
        stack(stack &&rhs);
        stack(stack const &rhs);

        // assign:
        stack& operator = (stack &&rhs);
        stack& operator = (stack const &rhs);

        // destroy:
        ~stack();

        // methods:
        bool empty() const;
        int size() const;
        void push(T const &value);
        void push(T &&value);
        void pop();
        value_type& top();
        value_type const& top() const;

    private:
        // methods:
        struct Node;
        void push(Node * const node);

        // members:
        Node *m_Head;
        int m_Size;
    };

} // namespace rwk

#pragma region Implementation

#include <cassert>
#include <algorithm>

namespace rwk
{
    // members:
    template <typename T>
    struct stack<T>::Node
    {
        T value;
        Node *next;
    };

    // construct:
    template <typename T>
    stack<T>::stack()
        : m_Head(nullptr)
        , m_Size(0)
    {}

    template <typename T>
    stack<T>::stack(stack &&rhs)
        : m_Head(rhs.m_Head)
        , m_Size(rhs.m_Size)
    {
        // reset rhs to blank values
        rhs.m_Head = nullptr;
        rhs.m_Size = 0;
    }

    template <typename T>
    stack<T>::stack(stack const &rhs)
        : m_Head(nullptr)
        , m_Size(0)
    {
        if (rhs.empty()) return;
        Node * node = rhs.m_Head;
        while (node != nullptr)
        {
            push(node->value);
            node = node->next;
        }
    }

    // assign:
    template <typename T>
    typename stack<T>& stack<T>::operator = (stack &&rhs)
    {
        assert(this != &rhs);
        stack temp(std::move(*this));

        // copy object's data
        m_Head = rhs.m_Head;
        m_Size = rhs.m_Size;

        // reset rhs to blank values
        rhs.m_Head = nullptr;
        rhs.m_Size = 0;
        
        return *this;
    }

    template <typename T>
    typename stack<T>& stack<T>::operator = (stack const &rhs)
    {
        stack tmp(rhs);
        std::swap(*this, tmp);
        return *this;
    }

    // destroy:
    template <typename T>
    stack<T>::~stack()
    {
        while (!empty())
        {
            pop();
        }
    }

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
    void stack<T>::push(Node * const node)
    {
        if (empty())
        {
            m_Head = node;
            node->next = nullptr;
        }
        else
        {
            node->next = m_Head;
            m_Head = node;
        }
        ++m_Size;
    }

    template <typename T>
    void stack<T>::push(T const &value)
    {
        Node * const new_node = new Node;
        new_node->value = value;
        push(new_node);
    }

    template <typename T>
    void stack<T>::push(T &&value)
    {
        Node * const new_node = new Node;
        new_node->value = std::move(value);
        push(new_node);
    }

    template <typename T>
    void stack<T>::pop()
    {
        assert(!empty());
        if (m_Size == 1)
        {
            delete m_Head;
            m_Head = nullptr;
        }
        else
        {
            Node * const old_head = m_Head;
            m_Head = m_Head->next;
            delete old_head;
        }
        --m_Size;
    }

    template <typename T>
    typename stack<T>::value_type& stack<T>::top()
    {
        return m_Head->value;
    }

    template <typename T>
    typename stack<T>::value_type const& stack<T>::top() const
    {
        return m_Head->value;
    }

} // namespace rwk

#pragma endregion

#endif // #define RWK_STACK_H