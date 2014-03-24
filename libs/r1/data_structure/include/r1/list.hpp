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

    // iterators
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
        iterator();
        iterator(iterator &&rhs);
        iterator(iterator const &rhs);

        // destroy:
        ~iterator();

        // assign:
        iterator& operator = (iterator &&rhs);
        iterator& operator = (iterator const &rhs);

        // members:
        bool operator == (iterator &&rhs) const;
        bool operator == (iterator const &rhs) const;
        bool operator != (iterator &&rhs) const;
        bool operator != (iterator const &rhs) const;
        reference operator * ();
        const_reference operator * () const;
        pointer_type operator -> ();
        const_pointer_type operator -> () const;
        iterator& operator ++ (); // prefix
        iterator& operator ++ (int); // postfix
        iterator& operator -- (); // prefix
        iterator& operator -- (int); // postfix

    private:
        // members:
        node_base *m_Node;
    };

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
        const_iterator();
        const_iterator(const_iterator &&rhs);
        const_iterator(const_iterator const &rhs);

        // destroy:
        ~const_iterator();

        // assign:
        const_iterator& operator = (const_iterator &&rhs);
        const_iterator& operator = (const_iterator const &rhs);

        // members:
        bool operator == (const_iterator &&rhs) const;
        bool operator == (const_iterator const &rhs) const;
        bool operator != (const_iterator &&rhs) const;
        bool operator != (const_iterator const &rhs) const;
        const_reference operator * () const;
        const_pointer_type operator -> () const;
        const_iterator& operator ++ (); // prefix
        const_iterator& operator ++ (int); // postfix
        const_iterator& operator -- (); // prefix
        const_iterator& operator -- (int); // postfix

    private:
        // members:
        node_base *m_Node;
    };

    // non-member function overloads:

}// namespace r1

#pragma region implementation

#include <memory>

namespace r1
{
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