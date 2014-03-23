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
        void push_back(value_type &&value);
        void push_back(value_type const &value);
        void pop_front();
        value_type& front();
        value_type& front() const;
        value_type& back();
        value_type& back() const;

    private:
        // methods:
        class Node;
        void push_back(Node * const node);

        // members:
        Node *m_Front;
        Node *m_Back;
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
        : m_Front(nullptr)
        , m_Back(nullptr)
        , m_Size(0)
    {}

    template <typename T>
    queue<T>::queue(queue &&rhs)
        : m_Front(std::move(rhs.m_Front))
        , m_Back(std::move(rhs.m_Back))
        , m_Size(rhs.m_Size)
    {
        // empty but valid state
        rhs.m_Front = nullptr;
        rhs.m_Back = nullptr;
        rhs.m_Size = 0;
    }

    template <typename T>
    queue<T>::queue(queue const &rhs)
        : m_Front(nullptr)
        , m_Back(nullptr)
        , m_Size(0)
    {
        for (Node *node = rhs.m_Front; node != nullptr; node = node->next)
        {
            push_back(node->value);
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
        m_Front = std::move(rhs.m_Front);
        m_Back = std::move(rhs.m_Back);
        m_Size = rhs.m_Size;

        // leave rhs in empty but valid state
        rhs.m_Front = nullptr;
        rhs.m_Back = nullptr;
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
        while (!empty()) pop_front();
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
    void queue<T>::push_back(Node * const node)
    {
        node->next = nullptr;
        if (empty())
        {
            m_Front = node;
        }
        else
        {
            m_Back->next = node;
        }
        m_Back = node;
        ++m_Size;
    }

    template <typename T>
    void queue<T>::push_back(value_type &&value)
    {
        Node * const new_node = new Node{ std::move(value), nullptr };
        push_back(new_node);
    }

    template <typename T>
    void queue<T>::push_back(value_type const &value)
    {
        Node * const new_node = new Node{ value, nullptr };
        push_back(new_node);
    }

    template <typename T>
    void queue<T>::pop_front()
    {
        assert(!empty());
        if (m_Size == 1)
        {
            delete m_Front;
            m_Front = nullptr;
            m_Back = nullptr;
        }
        else
        {
            Node * const old_head = m_Front;
            m_Front = old_head->next;
            delete old_head;
        }
        --m_Size;
    }

    template <typename T>
    typename queue<T>::value_type& queue<T>::front()
    {
        assert(!empty());
        return m_Front->value;
    }

    template <typename T>
    typename queue<T>::value_type& queue<T>::front() const
    {
        assert(!empty());
        return m_Front->value;
    }

    template <typename T>
    typename queue<T>::value_type& queue<T>::back()
    {
        assert(!empty());
        return m_Back->value;
    }

    template <typename T>
    typename queue<T>::value_type& queue<T>::back() const
    {
        assert(!empty());
        return m_Back->value;
    }

} // namespace r1
#pragma endregion

#endif  // R1_QUEUE_HPP