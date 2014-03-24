#ifndef R1_LIST_HPP
#define R1_LIST_HPP

#include <initializer_list>
#include <iterator>

namespace r1
{
    template <typename T>
    class list
    {
    public:
        // member types:
        class iterator;
        class const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef T value_type;
        typedef int size_type;
        typedef int difference_type;
        typedef T& reference;
        typedef T const& const_reference;
        typedef T* pointer_type;
        typedef T const* const_pointer_type;

        // construct:
        explicit list();
        list(list &&rhs);
        list(list const &rhs);
        list(std::initializer_list<T> il);

        // assign:
        list& operator = (list &&rhs);
        list& operator = (list const &rhs);
        list& operator = (std::initializer_list<value_type> il);

        // element access:
        reference front();
        const_reference front() const;
        reference back();
        const_reference back() const;

        // iterators:
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const;
        reverse_iterator rend();
        const_reverse_iterator rend() const;

        // capacity:
        bool empty() const;
        size_type size() const;

        // modifiers:
        void clear();
        iterator insert(const_iterator position, value_type &&value);
        iterator insert(const_iterator position, value_type const &value);
        iterator insert(const_iterator position, std::initializer_list<value_type> il);
        template <typename InputIterator>
        iterator insert(const_iterator position, InputIterator first, InputIterator last);
        iterator erase(const_iterator position);
        iterator erase(const_iterator first, const_iterator last);
        void push_front(value_type &&value);
        void push_front(value_type const &value);
        void push_back(value_type &&value);
        void push_back(value_type const &value);

        // operations:
        void splice(list &l);
        void splice(list &&l);
        template <typename Compare>
        void splice(list &l, Compare comp);
        template <typename Compare>
        void splice(list &&l, Compare comp);
        void merge(list &l);
        void merge(list &&l);
        template <typename Compare>
        void merge(list &l, Compare comp);
        template <typename Compare>
        void merge(list &&l, Compare comp);

    private:
        // members:
        struct node_base;
        struct node;
        node_base m_Sentinel;
    };

    // iterator:
    template <typename T>
    class list<T>::iterator 
        : public std::iterator
            <
                std::bidirectional_iterator_tag,
                typename list::value_type,
                typename list::difference_type,
                typename list::pointer_type,
                typename list::reference
            >
    {
    public:
        // construct:
        iterator() = default;
        iterator(iterator &&rhs) = default;
        iterator(iterator const &rhs) = default;

        // destroy:
        ~iterator() = default;

        // assign:
        iterator& operator = (iterator &&rhs) = default;
        iterator& operator = (iterator const &rhs) = default;

        // members:
        typename list<T>::reference operator * ();
        typename list<T>::const_reference operator * () const;
        typename list<T>::pointer_type operator -> ();
        typename list<T>::const_pointer_type operator -> () const;
        iterator& operator ++ ();    // prefix
        iterator& operator ++ (int); // postfix
        iterator& operator -- ();    // prefix
        iterator& operator -- (int); // postfix

    private:
        // members:
        node_base *m_Node;
    };

    // non-member overloads:
    template <typename T>
    bool operator == (typename list<T>::iterator const &lhs, typename list<T>::iterator const &rhs);

    template <typename T>
    bool operator != (typename list<T>::iterator const &lhs, typename list<T>::iterator const &rhs);

    // const iterator:
    template <typename T>
    class list<T>::const_iterator
        : public std::iterator
            <
                std::bidirectional_iterator_tag,
                typename list::value_type,
                typename list::difference_type,
                typename list::pointer_type,
                typename list::reference
            >
    {
    public:
        // construct:
        const_iterator() = default;
        const_iterator(const_iterator &&rhs) = default;
        const_iterator(const_iterator const &rhs) = default;

        // destroy:
        ~const_iterator() = default;

        // assign:
        const_iterator& operator = (const_iterator &&rhs) = default;
        const_iterator& operator = (const_iterator const &rhs) = default;

        // members:
        typename list<T>::const_reference operator * () const;
        typename list<T>::const_pointer_type operator -> () const;
        const_iterator& operator ++ ();    // prefix
        const_iterator& operator ++ (int); // postfix
        const_iterator& operator -- ();    // prefix
        const_iterator& operator -- (int); // postfix

    private:
        // members:
        node_base *m_Node;
    };

    // non-member overloads:
    template <typename T>
    bool operator == (typename list<T>::const_iterator const &lhs, typename list<T>::const_iterator const &rhs);

    template <typename T>
    bool operator != (typename list<T>::const_iterator const &lhs, typename list<T>::const_iterator const &rhs);

}// namespace r1

#pragma region implementation

#include <memory>

namespace r1
{
    // iterator members:
    template <typename T>
    typename list<T>::reference list<T>::iterator::operator * ()
    {
        assert(*this != end());
        return dynamic_cast<node>(m_Node)->value;
    }

    template <typename T>
    typename list<T>::const_reference list<T>::iterator::operator * () const
    {
        assert(*this != end());
        return dynamic_cast<node>(m_Node)->value;
    }

    template <typename T>
    typename list<T>::pointer_type list<T>::iterator::operator -> ()
    {
        assert(*this != end())
        return &(m_Node->value);
    }

    template <typename T>
    typename list<T>::const_pointer_type list<T>::iterator::operator -> () const
    {
        assert(*this != end())
        return &(m_Node->value);
    }

    template <typename T>
    typename list<T>::iterator& list<T>::iterator::operator ++ () // prefix
    {
        m_Node = m_Node->next;
        return *this;
    }

    template <typename T>
    typename list<T>::iterator& list<T>::iterator::operator ++ (int) // postfix
    {
        iterator temp(*this);
        m_Node = m_Node->next;
        return temp;
    }

    template <typename T>
    typename list<T>::iterator& list<T>::iterator::operator -- () // prefix
    {
        m_Node = m_Node->prev;
        return *this;
    }

    template <typename T>
    typename list<T>::iterator& list<T>::iterator::operator -- (int) // postfix
    {
        iterator temp(*this);
        m_Node = m_Node->prev;
        return temp;
    }

    // iterator non-member overloads:
    template <typename T>
    bool operator == (typename list<T>::iterator const &lhs, typename list<T>::iterator const &rhs)
    {
        return (lhs.m_Node == rhs.m_Node);
    }

    template <typename T>
    bool operator != (typename list<T>::iterator const &lhs, typename list<T>::iterator const &rhs)
    {
        return !(lhs == rhs);
    }

    // const_iterator members:
    template <typename T>
    typename list<T>::const_reference list<T>::const_iterator::operator * () const
    {
        assert(*this != end());
        return m_Node->value;
    }

    template <typename T>
    typename list<T>::const_pointer_type list<T>::const_iterator::operator -> () const
    {
        assert(*this != end());
        return &(m_Node->value);
    }

    template <typename T>
    typename list<T>::const_iterator& list<T>::const_iterator::operator ++ () // prefix
    {
        m_Node = m_Node->next;
        return *this;
    }

    template <typename T>
    typename list<T>::const_iterator& list<T>::const_iterator::operator ++ (int) // postfix
    {
        const_iterator temp(*this);
        m_Node = m_Node->next;
        return temp;
    }

    template <typename T>
    typename list<T>::const_iterator& list<T>::const_iterator::operator -- () // prefix
    {
        m_Node = m_Node->prev;
        return *this;
    }

    template <typename T>
    typename list<T>::const_iterator& list<T>::const_iterator::operator -- (int) // postfix
    {
        const_iterator temp(*this);
        m_Node = m_Node->prev;
        return temp;
    }

    // const_iterator non-member overloads:
    template <typename T>
    bool operator == (typename list<T>::const_iterator const &lhs, typename list<T>::const_iterator const &rhs)
    {
        return (lhs.m_Node == rhs.m_Node);
    }

    template <typename T>
    bool operator != (typename list<T>::const_iterator const &lhs, typename list<T>::const_iterator const &rhs)
    {
        return !(lhs == rhs);
    }

    // members:
    template <typename T>
    struct list<T>::node_base
    {
        std::unique_ptr<node_base> next;
        node_base *pref;
    };

    template <typename T>
    struct list<T>::node : public node_base
    {
        value_type value;
    };

    // construct:
    template <typename T>
    /*explicit*/ list<T>::list()
        : m_Sentinel(nullptr, nullptr)
    {
        m_Sentinel.next = m_Sentinel.prev;
        m_Sentinel.prev = m_Sentinel.next;
    }

    // assign:

    // members:

}

#pragma endregion

#endif // R1_LIST_HPP