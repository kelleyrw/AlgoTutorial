// ------------------------------------------------------------ //
// helper functions
// ------------------------------------------------------------ //

#include <string>
#include <sstream>
#include <cassert>

template <typename T>
std::string ArrayString(T const * const array, const int N)
{
    // test boundary conditions
    assert(!(array == NULL && N > 0));

    std::stringstream os;
    os << "{";
    for (int i = 0; i < N; ++i)
    {
        os << array[i];
        if (i != (N - 1)) os << ", ";
    }
    os << "}";
    return os.str();
}

template <typename T, int N>
std::string ArrayString(T const(&array)[N])
{
    return ArrayString(array, N);
}

// ------------------------------------------------------------ //
// Section 2.1 -- Insertion Sort
// ------------------------------------------------------------ //

#include <iostream>
#include <functional>
#include <list>

namespace ch2
{
    // sort in place
    template <typename Compare = std::less<int>>
    void sort(int* const v, int const N, Compare compare = Compare())
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
            for ( ; i > -1 && compare(key, v[i]); --i)
            {
                v[i + 1] = v[i];
            }
            v[i + 1] = key;
        }
        return;
    }

    template <int N, typename Compare = std::less<int>>
    void sort(int (&array)[N], Compare compare = Compare())
    {
        sort(array, N, compare);
    }

    // sort in place using iterators
    template <typename BidirectionalIterator, typename Compare = std::less<int>>
    void sort_range(BidirectionalIterator first, BidirectionalIterator last, Compare compare = Compare())
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

    template <typename Compare = std::less<int> >
    bool is_sorted(int const * const v, int const N, Compare compare = Compare())
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

    template <int N, typename Compare = std::less<int>>
    bool is_sorted(const int (&array)[N], Compare compare = Compare())
    {
        return is_sorted(array, N, compare);
    }

    // test the sort in place
    void TestInsertionSort()
    {
        // test array of size 0
        std::cout << "testing zero size array:\n";
        int* v0 = NULL;
        int const N0 = 0;
        std::cout << "before sorted = " << ArrayString(v0, N0) << "\n";
        sort(v0, N0);
        assert(is_sorted(v0, N0));
        std::cout << "after sorted = " << ArrayString(v0, N0) << "\n" << std::endl;

        // test array of size 1
        std::cout << "testing one size array:\n";
        int v1[] = { 7 };
        std::cout << "before sorted = " << ArrayString(v1) << "\n";
        sort(v1);
        assert(is_sorted(v1));
        std::cout << "after sorted = " << ArrayString(v1) << "\n" << std::endl;

        // test unsorted array
        std::cout << "testing unsorted array:\n";
        int const v2[] = { 4, 8, 3, 9 };
        std::cout << "v2 = " << ArrayString(v2) << "\n" << std::endl;
        assert(!is_sorted(v2));
        
        // test example from page 20
        std::cout << "test example (page 20):\n";
        int v[] = { 5, 2, 4, 6, 1, 3 };
        std::cout << "before sorted = " << ArrayString(v) << "\n";
        sort(v);
        assert(is_sorted(v));
        std::cout << "after sorted = " << ArrayString(v) << "\n" << std::endl;

        // test example from page 20 using iterators
        std::cout << "test example (page 20) using templates:\n";
        int v3[] = { 5, 2, 4, 6, 1, 3 };
        const int N3 = sizeof(v3)/sizeof(v3[0]);
        std::cout << "before sorted = " << ArrayString(v3) << "\n";
        sort_range(v3, v3+N3);
        assert(is_sorted(v3));
        std::cout << "after sorted = " << ArrayString(v3) << "\n" << std::endl;

        // now try it with an std::list
        std::cout << "test example (page 20) using tempates and std::list:\n";
        int v4[] = { 5, 2, 4, 6, 1, 3 };
        const int N4 = sizeof(v4) / sizeof(v4[0]);
        std::list<int> l1(v4, v4+N4);
        std::cout << "before sorted = " << ArrayString(v4) << "\n";
        sort_range(l1.begin(), l1.end());
        std::copy(l1.begin(), l1.end(), v4);
        assert(is_sorted(v4));
        std::cout << "after sorted = " << ArrayString(v4) << "\n" << std::endl;
    }

    // problem 2.1-1
    void Problem2p1p1()
    {
        std::cout << "problem 2.1-1 (page 22):\n";
        int v[] = { 31, 41, 59, 26, 41, 58 };
        std::cout << "before sorted = " << ArrayString(v) << "\n";
        ch2::sort(v, std::less<int>());
        assert(ch2::is_sorted(v, std::less<int>()));
        std::cout << "after sorted  = " << ArrayString(v) << "\n" << std::endl;
    }

    // problem 2.1-2
    void Problem2p1p2()
    {
        std::cout << "problem 2.1-2 (page 22):\n";
        int v[] = { 5, 2, 4, 6, 1, 3 };
        std::cout << "before sorted = " << ArrayString(v) << "\n";
        ch2::sort(v, std::greater<int>());
        assert(ch2::is_sorted(v, std::greater<int>()));
        std::cout << "after sorted  = " << ArrayString(v) << "\n" << std::endl;
    }

} // namespace ch2

// ------------------------------------------------------------ //
// main
// ------------------------------------------------------------ //

int main()
{
    // section 2.1 -- insertion sort
    ch2::TestInsertionSort();

    // problem 2.1-1
    ch2::Problem2p1p1();

    // problem 2.1-2
    ch2::Problem2p1p2();

    return 0;
}