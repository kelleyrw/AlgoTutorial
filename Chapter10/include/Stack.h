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
        // members:
        struct Node;
        Node *m_Head;
        int m_Size;

        // private methods:
        void push(Node * const node);
    };

} // namespace rwk

#pragma region Implementation

#include <cassert>

namespace rwk
{
    // construct:
    template <typename T>
    stack<T>::stack()
        : m_Head(nullptr)
        , m_Size(0)
    {}

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

    // members:
    template <typename T>
    struct stack<T>::Node
    {
        T value;
        Node *next;
    };
}

#pragma endregion

#endif // #define RWK_STACK_H