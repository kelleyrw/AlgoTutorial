#ifndef R1_QUEUE_HPP
#define R1_QUEUE_HPP

namespace r1
{
    template <typename T>
    class queue
    {
    public:
        // typdefs:
        typedef T value_type;

        // construct:
        queue();
        queue(queue &&rhs);
        queue(queue const &rhs);

        // assign:
        queue& operator = (queue &&rhs);
        queue& operator = (queue const &rhs);

        // destroy:
        ~queue();

        // methods:
        bool empty() const;
        int size() const;
        void push(value_type &&value);
        void push(value_type const &value);
        void pop();
        value_type& front();
        value_type& front() const;
        value_type& back();
        value_type& back() const;

    private:
        // methods:
        class Node;
        void push(Node * const node);

        // members:
        Node * m_Head;
        Node * m_Tail;
        int m_Size;
    };

} // namespace r1

#pragma region implementation

#include <cassert>

namespace r1
{
    // members:
    template <typename T>
    class queue<T>::Node
    {
    public:
        Node(value_type const &v, Node * const n);
        Node(value_type &&v, Node * const n);
        value_type value;
        Node *next;
    };

    template <typename T>
    queue<T>::Node::Node(value_type const &v, Node * const n)
        : value(v)
        , next(n)
    {}

    template <typename T>
    queue<T>::Node::Node(value_type &&v, Node * const n)
        : value(std::move(v))
        , next(n)
    {}

    // construct:
    template <typename T>
    queue<T>::queue()
        : m_Head(nullptr)
        , m_Tail(nullptr)
        , m_Size(0)
    {}

    template <typename T>
    queue<T>::queue(queue &&rhs)
        : m_Head(std::move(rhs.m_Head))
        , m_Tail(std::move(rhs.m_Tail))
        , m_Size(rhs.m_Size)
    {
        // empty but valid state
        rhs.m_Head = nullptr;
        rhs.m_Tail = nullptr;
        rhs.m_Size = 0;
    }

    template <typename T>
    queue<T>::queue(queue const &rhs)
        : m_Head(nullptr)
        , m_Tail(nullptr)
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
    typename queue<T>& queue<T>::operator = (queue &&rhs)
    {
        // no self assignment
        assert(this != &rhs);

        // move original contents to temp
        // to get cleaned up
        stack temp(std::move(*this));

        // move object's data
        m_Head = std::move(rhs.m_Head);
        m_Tail = std::move(rhs.m_Tail);
        m_Size = rhs.m_Size;

        // leave rhs in empty but valid state
        rhs.m_Head = nullptr;
        rhs.m_Tail = nullptr;
        rhs.m_Size = 0;

        return *this;
    }

    template <typename T>
    typename queue<T>& queue<T>::operator = (queue const &rhs)
    {
        queue temp(rhs);
        std::swap(*this, temp);
        return *this;
    }

    // destroy:
    template <typename T>
    queue<T>::~queue()
    {
        while (!empty()) pop();
    }

    // methods:
    template <typename T>
    bool queue<T>::empty() const
    {
        return (m_Size == 0);
    }

    template <typename T>
    int queue<T>::size() const
    {
        return m_Size;
    }

    template <typename T>
    void queue<T>::push(Node * const node)
    {
        node->next = nullptr;
        if (empty())
        {
            m_Head = node;
        }
        else
        {
            m_Tail->next = node;
        }
        m_Tail = node;
        ++m_Size;
    }

    template <typename T>
    void queue<T>::push(value_type &&value)
    {
        Node * const new_node = new Node{ std::move(value), nullptr };
        push(new_node);
    }

    template <typename T>
    void queue<T>::push(value_type const &value)
    {
        Node * const new_node = new Node{ value, nullptr };
        push(new_node);
    }

    template <typename T>
    void queue<T>::pop()
    {
        assert(!empty());
        if (m_Size == 1)
        {
            delete m_Head;
            m_Head = nullptr;
            m_Tail = nullptr;
        }
        else
        {
            Node * const old_head = m_Head;
            m_Head = old_head->next;
            delete old_head;
        }
        --m_Size;
    }

    template <typename T>
    typename queue<T>::value_type& queue<T>::front()
    {
        assert(!empty());
        return m_Head->value;
    }

    template <typename T>
    typename queue<T>::value_type& queue<T>::front() const
    {
        assert(!empty());
        return m_Head->value;
    }

    template <typename T>
    typename queue<T>::value_type& queue<T>::back()
    {
        assert(!empty());
        return m_Tail->value;
    }

    template <typename T>
    typename queue<T>::value_type& queue<T>::back() const
    {
        assert(!empty());
        return m_Tail->value;
    }

} // namespace r1
#pragma endregion

#endif  // R1_QUEUE_HPP