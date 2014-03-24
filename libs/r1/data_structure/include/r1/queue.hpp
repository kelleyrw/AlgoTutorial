#ifndef R1_QUEUE_HPP
#define R1_QUEUE_HPP

#include <initializer_list>
#include <memory>

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
        queue(std::initializer_list<value_type> list);

        // assign:
        queue& operator = (queue &&rhs);
        queue& operator = (queue const &rhs);

        // destroy:
        ~queue() = default;

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
        void push_back(std::unique_ptr<Node> &node);

        // members:
        std::unique_ptr<Node> m_Front;
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
        // construct:
        Node(value_type const &v, Node * const n);
        Node(value_type &&v, Node * const n);

        // members:
        value_type value;
        std::unique_ptr<Node> next;
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
        for (Node const * node = rhs.m_Front.get(); node != nullptr; node = node->next.get())
        {
            push_back(node->value);
        }
    }

    template <typename T>
    queue<T>::queue(std::initializer_list<value_type> list)
        : m_Front(nullptr)
        , m_Back(nullptr)
        , m_Size(0)
    {
        for (auto &&value : list) push_back(value);
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
    void queue<T>::push_back(std::unique_ptr<Node> &node)
    {
        if (empty())
        {
            m_Back = node.get();
            m_Front = std::move(node);
        }
        else
        {
            m_Back->next = std::move(node);
            m_Back = m_Back->next.get();
        }
        ++m_Size;
    }

    template <typename T>
    void queue<T>::push_back(value_type &&value)
    {
        std::unique_ptr<Node> new_node = std::make_unique<Node>(std::move(value), nullptr);
        push_back(new_node);
    }

    template <typename T>
    void queue<T>::push_back(value_type const &value)
    {
        std::unique_ptr<Node> new_node = std::make_unique<Node>(value, nullptr);
        push_back(new_node);
    }

    template <typename T>
    void queue<T>::pop_front()
    {
        assert(!empty());
        if (m_Size == 1)
        {
            m_Front = nullptr;
            m_Back = nullptr;
        }
        else
        {
            m_Front = std::move(m_Front->next);
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