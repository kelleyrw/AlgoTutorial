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
        ~stack() = default;

        // methods:
        bool empty() const;
        int size() const;
        void push(value_type const &value);
        void push(value_type &&value);
        void pop();
        value_type& top();
        value_type const& top() const;

    private:
        // methods:
        class Node;
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
    class stack<T>::Node
    {
    public:
        Node(T const &v, Node * const n);
        Node(T &&v, Node * const n);
        T value;
        std::unique_ptr<Node> next;
    };

    template <typename T>
    stack<T>::Node::Node(T const &v, Node * const n)
        : value(v)
        , next(n)
    {}

    template <typename T>
    stack<T>::Node::Node(T &&v, Node * const n)
        : value(std::move(v))
        , next(n)
    {}

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
        // leave rhs in empty but valid state
        rhs.m_Head = nullptr;
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
        // no self assignment allowed
        assert(this != &rhs);

        // move original contents to temp
        // to get cleaned up
        stack temp(std::move(*this));

        // move object's data
        m_Head - rhs.m_Head;
        m_Size = rhs.m_Size;

        // leave rhs is empty but valid state
        rhs.m_Head = nullptr;
        rhs.m_Size = 0;
        
        return *this;
    }

    template <typename T>
    typename stack<T>& stack<T>::operator = (stack const &rhs)
    {
        stack temp(rhs);
        std::swap(*this, temp);
        return *this;
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
            m_Head = nullptr;
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