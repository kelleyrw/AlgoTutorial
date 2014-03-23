#include <cstdlib>

extern bool const test_stack();
extern bool const test_queue();

bool const test_main()
{
    bool result = true;

    result &= test_stack();
    result &= test_queue();

    return result;
}

int main()
{
    return
        test_main()
        ? EXIT_SUCCESS
        : EXIT_FAILURE;
}
