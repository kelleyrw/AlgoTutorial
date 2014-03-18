// ------------------------------------------------------------ //
// helper functions
// ------------------------------------------------------------ //

#include <string>
#include <sstream>

template <typename T, unsigned int N>
std::string ArrayString(const T(&array)[N])
{
    std::stringstream os;
    os << "{";
    for (std::size_t i = 0; i != N; i++)
    {
        os << array[i];
        if (i != (N - 1)) { os << ", "; }
    }
    os << "}";
    return os.str();
}

// ------------------------------------------------------------ //
// Section 2.1 -- Insertion Sort
// ------------------------------------------------------------ //

#include <iostream>
#include <functional>

namespace ch2
{
    // sort in place
    template <typename Compare>
    void sort(int* const v, const std::size_t N, Compare compare)
    {
        for (std::size_t j = 1; j != N; j++)
        {
            const int key = v[j];
            int i = j - 1;
            for ( ; i > -1 && compare(key, v[i]); i--)
            {
                v[i + 1] = v[i];
            }
            v[i + 1] = key;
        }
        return;
    }
    
    // test the sort in place
    void TestInsertionSort()
    {
        std::cout << "test example (page 20):\n";
        int v[] = { 5, 2, 4, 6, 1, 3 };
        const std::size_t N = sizeof(v) / sizeof(v[0]);
        std::cout << "before sorted = " << ArrayString(v) << "\n";
        ch2::sort(v, N, std::less<int>());
        std::cout << "after sorted  = " << ArrayString(v) << "\n" << std::endl;
    }

    // problem 2.1-1
    void Problem2p1p1()
    {
        std::cout << "problem 2.1-1 (page 22):\n";
        int v[] = { 31, 41, 59, 26, 41, 58 };
        const std::size_t N = sizeof(v) / sizeof(v[0]);
        std::cout << "before sorted = " << ArrayString(v) << "\n";
        ch2::sort(v, N, std::less<int>());
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
