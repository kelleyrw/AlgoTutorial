#ifndef R1_LIST_HPP
#define R1_LIST_HPP

#include <memory>

namespace r1
{
    template <typename T>
    class list
    {
    public:
        // iterators
        class iterator;
        class const_iterator;
        class reverse_iterator;
        class const_reverse_iterator;
        
        // typdefs:
        typedef T value_type;
        typedef int size_type;
        typedef ptrdiff_t difference_type;

        // construct:
        explicit list();
        explicit list(size_type n, value_type const &value);
        list(list const &rhs);
        list(list &&rhs);
        list(std::initializer_list<T> il);

        // assign:
        list& operator = (list const &rhs);
        list& operator = (list &&rhs);
        list& operator = (std::initializer_list<value_type> il);

        // methods:
        iterator begin();
        const_iterator begin() const;

        iterator end();
        const_iterator end() const;
        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const;
        reverse_iterator rend();
        const_reverse_iterator rend() const;
        value_type& front();
        value_type const& front() const;
        value_type& back();
        value_type const& back() const;
        void push_front(value_type const &value);
        void push_front(value_type &&value);
        void push_back(value_type const &value);
        void push_back(value_type &&value);
        iterator insert(const_iterator position, value_type const &value);
        iterator insert(const_iterator position, size_type n, value_type const &value);
        iterator insert(const_iterator position, value_type &&value);
        iterator insert(const_iterator position, std::initializer_list<value_type> il);
        template <typename InputIterator>
        iterator insert(const_iterator position, InputIterator first, InputIterator last);
        iterator erase(const_iterator position);
        iterator erase(const_iterator first, const_iterator last);
        void clear();
        const bool empty() const;
        const size_type size() const;

        // shall i do these?
        void merge(list &l);
        void merge(list &&l);
        template <typename Compare>
        void merge(list &l, Compare comp);
        template <typename Compare>
        void merge(list &&l, Compare comp);
        void sort();
        template <typename Compare>
        void sort(Compare comp);
        void reverse();

        // const methods:



        
    private:
        // members:
        class Node;
        std::unique_ptr<Node> sentinel;
    };

    // non-member function overloads:

}// namespace r1

#endif // R1_LIST_HPP