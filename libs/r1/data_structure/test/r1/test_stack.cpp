#include "r1/stack.hpp"
#include <cassert>

bool const test_stack()
{
    // test default ctor
    {
        r1::stack<int> s0;
        assert(s0.empty() == true);
        assert(s0.size() == 0);
    }

    // test copy ctor empty
    {
        r1::stack<int> s1;
        r1::stack<int> s2(s1);
        assert(s1.size() == s2.size());
        assert(s1.empty() == s2.empty());
    }

    // test copy ctor full
    {
        r1::stack<int> s1;
        s1.push(1);
        s1.push(2);
        s1.push(3);
        r1::stack<int> s2(s1);
        assert(s1.size() == s2.size());
        assert(s1.empty() == s2.empty());
        while (!s1.empty())
        {
            assert(s1.top() == s2.top());
            assert(s1.size() == s2.size());
            assert(s1.empty() == s2.empty());
            s1.pop();
            s2.pop();
        }
    }

    // test move ctor
    // test copy assignment
    // test move assignment
    // test empty
    // test size
    // test push
    // test pop
    // test top
    // test top const

    return true;
}