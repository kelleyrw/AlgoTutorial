#include <cstdlib>

extern bool const test_stack();

bool const test_main()
{
    bool result = true;

    result &= test_stack();

    return result;
}

int main()
{
    return
        test_main()
        ? EXIT_SUCCESS
        : EXIT_FAILURE;
}
