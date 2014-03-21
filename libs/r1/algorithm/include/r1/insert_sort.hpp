#ifndef R1_INSERT_SORT_HPP
#define R1_INSERT_SORT_HPP

namespace r1
{
    // sort in place
    template <typename Compare = std::less<int>>
    void insert_sort_int(int* const v, int const N, Compare compare = Compare());

    template <int N, typename Compare = std::less<int>>
    void insert_sort_int(int(&array)[N], Compare compare = Compare());

    // sort in place using iterators
    template <typename BidirectionalIterator, typename Compare = std::less<int>>
    void insert_sort(BidirectionalIterator first, BidirectionalIterator last, Compare compare = Compare());

    template <typename Compare = std::less<int> >
    bool is_sorted(int const * const v, int const N, Compare compare = Compare());

    template <int N, typename Compare = std::less<int>>
    bool is_sorted(const int(&array)[N], Compare compare = Compare());

} // namespace r1

#pragma region Implementation

#include <functional>
#include <list>
#include <cassert>

namespace r1
{
    // sort in place
    template <typename Compare>
    void insert_sort_int(int* const v, int const N, Compare compare)
    {
        // check for 0 or 1 elements
        if (N <= 1) return;

        // test boundary conditions
        assert(!(v == NULL && N > 0));

        // do the sort
        for (int j = 1; j < N; ++j)
        {
            int const key = v[j];
            int i = j - 1;
            for (; i > -1 && compare(key, v[i]); --i)
            {
                v[i + 1] = v[i];
            }
            v[i + 1] = key;
        }
        return;
    }

    template <int N, typename Compare>
    void insert_sort_int(int(&array)[N], Compare compare)
    {
        insert_sort_int(array, N, compare);
    }

    // sort in place using iterators
    template <typename BidirectionalIterator, typename Compare>
    void insert_sort(BidirectionalIterator first, BidirectionalIterator last, Compare compare)
    {
        BidirectionalIterator j = first;
        for (++j; j != last; ++j)
        {
            int const key = *j;
            BidirectionalIterator current = j;
            BidirectionalIterator adjacent = current;
            for (--current; adjacent != first && compare(key, *current); --adjacent)
            {
                *adjacent = *current;
                if (current != first) --current;
            }
            *adjacent = key;
        }
        return;
    }

    template <typename Compare>
    bool is_sorted(int const * const v, int const N, Compare compare)
    {
        // check for 0 or 1 elements -- trivially sorted
        if (N <= 1) return true;

        // test boundary conditions
        assert(!(v == NULL && N > 0));

        // test if element j > element i
        for (int i = 0, j = 1; j < N; ++i, ++j)
        {
            if (compare(v[j], v[i]))
            {
                return false;
            }
        }
        return true;
    }

    template <int N, typename Compare>
    bool is_sorted(const int(&array)[N], Compare compare)
    {
        return is_sorted(array, N, compare);
    }

} // namespace r1

#pragma endregion

#endif // #define R1_INSERT_SORT_HPP