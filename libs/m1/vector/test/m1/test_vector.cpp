#include "m1/vector.hpp"
#include <cassert>

bool const test_vector()
{
    static_assert(sizeof(m1::vector3f) == sizeof(float[3]), "unexpected size");
    m1::vector3f const zero = {};
    assert(zero[0] == 0.0f);
    assert(zero[1] == 0.0f);
    assert(zero[2] == 0.0f);
    return true;
}
