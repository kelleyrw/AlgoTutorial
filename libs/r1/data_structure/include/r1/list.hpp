#ifndef R1_LIST_HPP
#define R1_LIST_HPP

#include <initializer_list>

namespace r1
{
    template <typename T>
    class list
    {
    public:
        // member types:
        class iterator;
        class const_iterator;
        class reverse_iterator;
        class const_reverse_iterator;
        typedef T value_type;
        typedef int size_type;
        typedef int difference_type;

        // construct:
        explicit list();
        list(list const &rhs);
        list(list &&rhs);
        list(std::initializer_list<T> il);

        // assign:
        list& operator = (list const &rhs);
        list& operator = (list &&rhs);
        list& operator = (std::initializer_list<value_type> il);

        // element access:
        value_type& front();
        value_type const& front() const;
        value_type& back();
        value_type const& back() const;

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
        iterator insert(const_iterator position, value_type const &value);
        iterator insert(const_iterator position, value_type &&value);
        iterator insert(const_iterator position, std::initializer_list<value_type> il);
        template <typename InputIterator>
        iterator insert(const_iterator position, InputIterator first, InputIterator last);
        iterator erase(const_iterator position);
        iterator erase(const_iterator first, const_iterator last);
        void push_front(value_type const &value);
        void push_front(value_type &&value);
        void push_back(value_type const &value);
        void push_back(value_type &&value);

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

    // non-member function overloads:

}// namespace r1

#pragma region implementation

#include <memory>

#pragma endregion

namespace r1
{
    // iterators
    template <typename T>
    class list<T>::iterator
    {
    public:
        // construct:
        iterator();
        iterator(iterator const &rhs);
        iterator(iterator &&rhs);

        // destroy:
        ~iterator();

        // assign:
        iterator& operator = (iterator const &rhs);
        iterator& operator = (iterator &&rhs);

        // members:
        bool operator == (iterator const &rhs) const;
        bool operator == (iterator &&rhs) const;
        bool operator != (iterator const &rhs) const;
        bool operator != (iterator &&rhs) const;
        value_type& operator * ();
        value_type const & operator * () const;
        value_type * const operator -> ();
        value_type const * const operator -> () const;
        iterator& operator ++ (); // prefix
        iterator& operator ++ (int); // postfix
        iterator& operator -- (); // prefix
        iterator& operator -- (int); // postfix

    private:
        // members:
        list* m_List;
        node_base* m_Node;
    };

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

#endif // R1_LIST_HPP