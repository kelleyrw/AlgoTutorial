// ------------------------------------------------------------ //
// helper functions
// ------------------------------------------------------------ //

#include <string>
#include <sstream>
#include <cassert>

template <typename T>
std::string ArrayString(const T* const array, const unsigned int N)
{
    // test boundary conditions
    assert(!(array == NULL && N > 0));

    std::stringstream os;
    os << "{";
    for (std::size_t i = 0; i != N; ++i)
    {
        os << array[i];
        if (i != (N - 1)) { os << ", "; }
    }
    os << "}";
    return os.str();
}

template <typename T, unsigned int N>
std::string ArrayString(const T(&array)[N])
{
    return ArrayString(array, N);
}

// ------------------------------------------------------------ //
// Section 2.1 -- Insertion Sort
// ------------------------------------------------------------ //

#include <iostream>
#include <functional>

namespace ch2
{
    // sort in place
    template <typename Compare = std::less<int> >
    void sort(int* const v, const std::size_t N, Compare compare = Compare())
    {
        // check for 0 or 1 elements
        if (N <= 1) 
        {
            return;
        }

        // test boundary conditions
        assert(!(v == NULL && N > 0));

        // do the sort
        for (std::size_t j = 1; j != N; ++j)
        {
            const int key = v[j];
            int i = j - 1;
            for ( ; i > -1 && compare(key, v[i]); --i)
            {
                v[i + 1] = v[i];
            }
            v[i + 1] = key;
        }
        return;
    }

    template <typename Compare = std::less<int> >
    bool is_sorted(const int* const v, const std::size_t N, Compare compare = Compare())
    {
        // check for 0 or 1 elements -- trivially sorted
        if (N <= 1)
        {
            return true;
        }

        // test boundary conditions
        assert(!(v == NULL && N > 0));

        // test if element j > element i
        for (std::size_t i = 0, j = 1; j < N; ++i, ++j)
        {
            if (compare(v[j], v[i]))
            {
                return false;
            }
        }
        return true;
    }

    // test the sort in place
    void TestInsertionSort()
    {
        // test array of size 0
        std::cout << "testing zero size array:\n";
        int* v0 = NULL;
        const std::size_t N0 = 0;
        std::cout << "before sorted = " << ArrayString(v0, N0) << "\n";
        ch2::sort(v0, N0);
        assert(ch2::is_sorted(v0, N0));
        std::cout << "after sorted = " << ArrayString(v0, N0) << "\n" << std::endl;

        // test array of size 1
        std::cout << "testing one size array:\n";
        int v1[] = { 7 };
        const std::size_t N1 = sizeof(v1) / sizeof(v1[0]);
        std::cout << "before sorted = " << ArrayString(v1, N1) << "\n";
        ch2::sort(v1, N1);
        assert(ch2::is_sorted(v1, N1));
        std::cout << "after sorted = " << ArrayString(v1, N1) << "\n" << std::endl;

        // test unsorted array
        std::cout << "testing unsorted array:\n";
        int const v2[] = { 4, 8, 3, 9 };
        const std::size_t N2 = sizeof(v2) / sizeof(v2[0]);
        std::cout << "v2 = " << ArrayString(v2, N2) << "\n" << std::endl;
        assert(!is_sorted(v2, N2));


        std::cout << "test example (page 20):\n";
        int v[] = { 5, 2, 4, 6, 1, 3 };
        const std::size_t N = sizeof(v) / sizeof(v[0]);
        std::cout << "before sorted = " << ArrayString(v) << "\n";
        ch2::sort(v, N);
        assert(ch2::is_sorted(v, N));
        std::cout << "after sorted = " << ArrayString(v) << "\n" << std::endl;
    }

    // problem 2.1-1
    void Problem2p1p1()
    {
        std::cout << "problem 2.1-1 (page 22):\n";
        int v[] = { 31, 41, 59, 26, 41, 58 };
        const std::size_t N = sizeof(v) / sizeof(v[0]);
        std::cout << "before sorted = " << ArrayString(v) << "\n";
        ch2::sort(v, N, std::less<int>());
        assert(ch2::is_sorted(v, N, std::less<int>()));
        std::cout << "after sorted  = " << ArrayString(v) << "\n" << std::endl;
    }

    // problem 2.1-2
    void Problem2p1p2()
    {
        std::cout << "problem 2.1-2 (page 22):\n";
        int v[] = { 5, 2, 4, 6, 1, 3 };
        const std::size_t N = sizeof(v) / sizeof(v[0]);
        std::cout << "before sorted = " << ArrayString(v) << "\n";
        ch2::sort(v, N, std::greater<int>());
        assert(ch2::is_sorted(v, N, std::greater<int>()));
        std::cout << "after sorted  = " << ArrayString(v) << "\n" << std::endl;
    }

} // namespace ch2


// ------------------------------------------------------------ //
// main
// ------------------------------------------------------------ //

int main()
try
{
    // section 2.1 -- insertion sort
    ch2::TestInsertionSort();

    // problem 2.1-1
    ch2::Problem2p1p1();

    // problem 2.1-2
    ch2::Problem2p1p2();

    return 0;
}
catch(std::exception& e)
{
    std::cerr << e.what() << std::endl;
}
