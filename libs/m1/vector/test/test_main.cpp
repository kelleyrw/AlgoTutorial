#include <cstdlib>

extern bool const test_vector();

bool const test_main()
{
    bool result = true;

    result &= test_vector();

    return result;
}

int main()
{
    return
        test_main()
        ? EXIT_SUCCESS
        : EXIT_FAILURE;
}
