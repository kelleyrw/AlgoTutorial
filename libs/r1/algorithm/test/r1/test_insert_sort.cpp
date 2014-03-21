#include "r1/insert_sort.hpp"
#include <cassert>

// ------------------------------------------------------------ //
// helper functions
// ------------------------------------------------------------ //

#include <string>
#include <sstream>
#include <iostream>

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
// helper functions
// ------------------------------------------------------------ //

// test the sort in place
const bool TestInsertionSort()
{
    // test array of size 0
    std::cout << "testing zero size array:\n";
    int* v0 = NULL;
    int const N0 = 0;
    std::cout << "before sorted = " << ArrayString(v0, N0) << "\n";
    r1::insert_sort_int(v0, N0);
    assert(r1::is_sorted(v0, N0));
    std::cout << "after sorted = " << ArrayString(v0, N0) << "\n" << std::endl;

    // test array of size 1
    std::cout << "testing one size array:\n";
    int v1[] = { 7 };
    std::cout << "before sorted = " << ArrayString(v1) << "\n";
    r1::insert_sort_int(v1);
    assert(r1::is_sorted(v1));
    std::cout << "after sorted = " << ArrayString(v1) << "\n" << std::endl;

    // test unsorted array
    std::cout << "testing unsorted array:\n";
    int const v2[] = { 4, 8, 3, 9 };
    std::cout << "v2 = " << ArrayString(v2) << "\n" << std::endl;
    assert(!r1::is_sorted(v2));
    
    // test example from page 20
    std::cout << "test example (page 20):\n";
    int v[] = { 5, 2, 4, 6, 1, 3 };
    std::cout << "before sorted = " << ArrayString(v) << "\n";
    r1::insert_sort_int(v);
    assert(r1::is_sorted(v));
    std::cout << "after sorted = " << ArrayString(v) << "\n" << std::endl;

    // test example from page 20 using iterators
    std::cout << "test example (page 20) using templates:\n";
    int v3[] = { 5, 2, 4, 6, 1, 3 };
    const int N3 = sizeof(v3)/sizeof(v3[0]);
    std::cout << "before sorted = " << ArrayString(v3) << "\n";
    r1::insert_sort(v3, v3+N3);
    assert(r1::is_sorted(v3));
    std::cout << "after sorted = " << ArrayString(v3) << "\n" << std::endl;

    // now try it with an std::list
    std::cout << "test example (page 20) using tempates and std::list:\n";
    int v4[] = { 5, 2, 4, 6, 1, 3 };
    const int N4 = sizeof(v4) / sizeof(v4[0]);
    std::list<int> l1(v4, v4+N4);
    std::cout << "before sorted = " << ArrayString(v4) << "\n";
    r1::insert_sort(l1.begin(), l1.end());
    std::copy(l1.begin(), l1.end(), v4);
    assert(r1::is_sorted(v4));
    std::cout << "after sorted = " << ArrayString(v4) << "\n" << std::endl;
    return true;
}

// problem 2.1-1
const bool Problem2p1p1()
{
    std::cout << "problem 2.1-1 (page 22):\n";
    int v[] = { 31, 41, 59, 26, 41, 58 };
    std::cout << "before sorted = " << ArrayString(v) << "\n";
    r1::insert_sort_int(v, std::less<int>());
    assert(r1::is_sorted(v, std::less<int>()));
    std::cout << "after sorted  = " << ArrayString(v) << "\n" << std::endl;
    return true;
}

// problem 2.1-2
const bool Problem2p1p2()
{
    std::cout << "problem 2.1-2 (page 22):\n";
    int v[] = { 5, 2, 4, 6, 1, 3 };
    std::cout << "before sorted = " << ArrayString(v) << "\n";
    r1::insert_sort_int(v, std::greater<int>());
    assert(r1::is_sorted(v, std::greater<int>()));
    std::cout << "after sorted  = " << ArrayString(v) << "\n" << std::endl;
    return true;
}

bool const test_insert_sort()
{
    bool result = true;

    // section 2.1 -- insertion sort
    result &= TestInsertionSort();

    // problem 2.1-1
    result &= Problem2p1p1();

    // problem 2.1-2
    result &= Problem2p1p2();

    return result;
}

