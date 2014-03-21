#include "r1/stack.hpp"
#include <cassert>

bool const test_stack()
{
    r1::stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);

    // test copy ctor
    r1::stack<int> s2(s1);
    assert(s1.size() == s2.size());

    // test assignement
    r1::stack<int> s3 = s1;
    assert(s1.size() == s3.size());
    return true;
}