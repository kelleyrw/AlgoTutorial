#include "r1/stack.hpp"
#include <cassert>

class NoDefaultNoCopyAssign
{
public:
    int m_Int;
    NoDefaultNoCopyAssign(const int value) : m_Int(value) {}
    NoDefaultNoCopyAssign() = delete;
    NoDefaultNoCopyAssign(NoDefaultNoCopyAssign && rhs) : m_Int(std::move(rhs.m_Int)) {}
    NoDefaultNoCopyAssign(NoDefaultNoCopyAssign const & rhs) : m_Int(rhs.m_Int) {}
    NoDefaultNoCopyAssign& operator = (NoDefaultNoCopyAssign && rhs) { m_Int = std::move(rhs.m_Int); }
    NoDefaultNoCopyAssign& operator = (NoDefaultNoCopyAssign const&) = delete;
    ~NoDefaultNoCopyAssign() {}
};

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

    // test move ctor empty
    {
        r1::stack<int> s1;
        r1::stack<int> s2(std::move(s1));
        assert(s1.size() == s2.size());
        assert(s1.empty() == s2.empty());
    }

    // test move ctor full
    {
        r1::stack<int> s1;
        s1.push(1);
        s1.push(2);
        s1.push(3);
        r1::stack<int> s2(std::move(s1));
        assert(s1.empty());
        assert(s2.size() == 3);
        assert(s2.top() == 3); s2.pop();
        assert(s2.top() == 2); s2.pop();
        assert(s2.top() == 1); s2.pop();
    }

    // test copy assignment full
    {
        r1::stack<int> s1;
        r1::stack<int> s2 = s1;
        assert(s1.size() == s2.size());
        assert(s1.empty() == s2.empty());
    }

    // test copy assignment full
    {
        r1::stack<int> s1;
        s1.push(1);
        s1.push(2);
        s1.push(3);
        r1::stack<int> s2 = s1;
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

    // test move assignment empty
    {
        r1::stack<int> s1;
        r1::stack<int> s2 = std::move(s1);
        assert(s1.size() == s2.size());
        assert(s1.empty() == s2.empty());
    }

    // test move assignment full
    {
        r1::stack<int> s1;
        s1.push(1);
        s1.push(2);
        s1.push(3);
        r1::stack<int> s2 = std::move(s1);
        assert(s1.empty());
        assert(s2.size() == 3);
        assert(s2.top() == 3); s2.pop();
        assert(s2.top() == 2); s2.pop();
        assert(s2.top() == 1); s2.pop();
    }

    // test empty
    {
        r1::stack<int> s1;
        assert(s1.empty());

        s1.push(1);
        assert(!s1.empty());

        s1.pop();
        assert(s1.empty());
    }

    // test size
    {
        r1::stack<int> s1;
        assert(s1.size() == 0);

        s1.push(1);
        s1.push(2);
        s1.push(3);
        assert(s1.size() == 3);

        s1.pop();
        assert(s1.size() == 2);
    }

    // test push
    {
        r1::stack<int> s1;
        s1.push(1);
        assert(s1.top() == 1);
        assert(s1.size() == 1);
        assert(!s1.empty());

        s1.push(2);
        assert(s1.top() == 2);
        assert(s1.size() == 2);
        assert(!s1.empty());

        int x = 1;
        int y = 2;
        r1::stack<int> s2;
        s2.push(x);
        assert(s2.top() == 1);
        assert(s2.size() == 1);
        assert(!s2.empty());

        s2.push(y);
        assert(s2.top() == 2);
        assert(s2.size() == 2);
        assert(!s2.empty());

        r1::stack<NoDefaultNoCopyAssign> s3;
        s3.push(NoDefaultNoCopyAssign(7));
        assert(s3.top().m_Int == 7);
    }

    // test pop
    {
        r1::stack<int> s1;
        s1.push(1);
        s1.push(2);
        s1.pop();
        assert(!s1.empty());
        assert(s1.size() == 1);
        assert(s1.top() == 1);
        s1.pop();
        assert(s1.empty());
        assert(s1.size() == 0);
    }

    // test top
    {
        r1::stack<int> s1;
        s1.push(1);
        assert(s1.top() == 1);
        s1.push(2);
        assert(s1.top() == 2);
        s1.pop();
        assert(s1.top() == 1);
    }

    // test top const
    {
        r1::stack<int> s1;
        s1.push(1);
        s1.push(2);
        const r1::stack<int> s2 = s1;
        assert(s2.top() == 2);
    }

    return true;
}