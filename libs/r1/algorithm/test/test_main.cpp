#include <cstdlib>

extern bool const test_insert_sort();

bool const test_main()
{
    bool result = true;

    result &= test_insert_sort();

    return result;
}

int main()
{
    return
        test_main()
        ? EXIT_SUCCESS
        : EXIT_FAILURE;
}
