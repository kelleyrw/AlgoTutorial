#ifndef R1_STACK_HPP
#define R1_STACK_HPP

#include <memory>

namespace r1
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
        void push(std::unique_ptr<Node> &node);

        // members:
        std::unique_ptr<Node> m_Head;
        int m_Size;
    };

} // namespace r1

#pragma region Implementation

#include <cassert>
#include <algorithm>

namespace r1
{
    // members:
    template <typename T>
    struct stack<T>::Node
    {
        Node(T const &v, Node * const n) : value(v), next(n) {}
        Node(T &&v, Node * const n) : value(std::move(v)), next(n) {}
        T value;
        std::unique_ptr<Node> next;
    };

    // construct:
    template <typename T>
    stack<T>::stack()
        : m_Head(nullptr)
        , m_Size(0)
    {}

    template <typename T>
    stack<T>::stack(stack &&rhs)
        : m_Head(std::move(rhs.m_Head))
        , m_Size(rhs.m_Size)
    {
        // reset rhs to blank values
        rhs.m_Head.reset(nullptr);
        rhs.m_Size = 0;
    }

    template <typename T>
    stack<T>::stack(stack const &rhs)
        : m_Head(nullptr)
        , m_Size(0)
    {
        if (rhs.empty()) return;
        
        // initial node
        m_Head.reset(new Node(rhs.m_Head->value, nullptr));
        Node * tail = m_Head.get();
        ++m_Size;
        
        // subsequent nodes
        Node * node = rhs.m_Head->next.get();
        while (node != nullptr)
        {
            tail->next.reset(new Node(node->value, nullptr));
            tail = tail->next.get();
            ++m_Size;
            node = node->next.get();
        }
    }

    // assign:
    template <typename T>
    typename stack<T>& stack<T>::operator = (stack &&rhs)
    {
        assert(this != &rhs);
        stack temp(std::move(*this));

        // copy object's data
        m_Head.reset(rhs.m_Head);
        m_Size = rhs.m_Size;

        // reset rhs to blank values
        rhs.m_Head.reset(nullptr);
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
        while (!empty()) pop();
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
    void stack<T>::push(std::unique_ptr<Node> &node)
    {
        if (empty())
        {
            m_Head = std::move(node);
        }
        else
        {
            node->next = std::move(m_Head);
            m_Head = std::move(node);
        }
        ++m_Size;
    }

    template <typename T>
    void stack<T>::push(T const &value)
    {
        std::unique_ptr<Node> new_node = std::make_unique<Node>(value, nullptr);
        push(new_node);
    }

    template <typename T>
    void stack<T>::push(T &&value)
    {
        std::unique_ptr<Node> new_node = std::make_unique<Node>(std::move(value), nullptr);
        push(new_node);
    }

    template <typename T>
    void stack<T>::pop()
    {
        assert(!empty());
        if (m_Size == 1)
        {
            m_Head.reset(nullptr);
        }
        else
        {
            m_Head = std::move(m_Head->next);
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

} // namespace r1

#pragma endregion

#endif // #define R1_STACK_HPP