// ------------------------------------------------------------ //
// helper functions
// ------------------------------------------------------------ //

#include <string>
#include <sstream>

template <typename T, unsigned int N>
std::string ArrayString(const T(&array)[N])
{
    std::stringstream os;
    if (N == 0) { os << "{}"; }
    for (std::size_t i = 0; i != N; i++)
    {
        if (i == 0) { os << "{"; }
        os << array[i];
        if (i != (N - 1)) { os << ", "; }
        if (i == (N - 1)) { os << "}"; }
    }
    return os.str();
}

// ------------------------------------------------------------ //
// Section 2.1 -- Insertion Sort
// ------------------------------------------------------------ //

#include <iostream>

namespace ch2
{
    // sort in place
    void sort(int v[], const std::size_t N)
    {
        for (std::size_t j = 1; j != N; j++)
        {
            const int key = v[j];
            int i = j - 1;
            while (i > -1 && v[i] > key)
            {
                v[i + 1] = v[i];
                i = i - 1;
            }
            v[i + 1] = key;
        }
        return;
    }
    
    void TestInsertionSort()
    {
        int v[] = { 5, 2, 4, 6, 1, 3 };
        const std::size_t N = sizeof(v) / sizeof(v[0]);
        std::cout << "before sorted = " << ArrayString(v) << std::endl;
        ch2::sort(v, N);
        std::cout << "after sorted  = " << ArrayString(v) << std::endl;
    }

} // namespace ch2


// ------------------------------------------------------------ //
// main
// ------------------------------------------------------------ //

int main()
{
    // section 2.1 -- insertion sort
    ch2::TestInsertionSort();
    return 0;
}
