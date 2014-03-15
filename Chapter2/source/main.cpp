#include <iostream>

// ------------------------------------------------------------ //
// helper functions
// ------------------------------------------------------------ //

template <typename T, unsigned int N>
void PrintArray(std::ostream& out, const T(&array)[N])
{
    if (N == 0) { out << "{}"; }
    for (std::size_t i = 0; i != N; i++)
    {
        if (i == 0) { out << "{"; }
        out << array[i];
        if (i != (N - 1)) { out << ", "; }
        if (i == (N - 1)) { out << "}"; }
    }
    return;
}

template <typename T, unsigned int N>
std::ostream& operator << (std::ostream& out, const T(&array)[N])
{
    if (N == 0) { out << "{}"; }
    for (std::size_t i = 0; i != N; i++)
    {
        if (i == 0) { out << "{"; }
        out << array[i];
        if (i != (N - 1)) { out << ", "; }
        if (i == (N - 1)) { out << "}"; }
    }
    return out;
}

// ------------------------------------------------------------ //
// Section 2.1 -- Insertion Sort
// ------------------------------------------------------------ //

void TestInsertionSort()
{
    const int v[] = { 5, 2, 4, 6, 1, 3 };
    const std::size_t N = sizeof(v) / sizeof(v[0]);
    PrintArray(std::cout, v);
    std::cout << std::endl;
    //std::cout << v << "\n";
}

int main()
{
    TestInsertionSort();
    return 0;
}
