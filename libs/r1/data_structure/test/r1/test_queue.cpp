#include "r1/queue.hpp"
#include <cassert>
#include <utility>

namespace r1_test_queue
{
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
}

bool const test_queue()
{
    // test default ctor
    {
        r1::queue<int> q;
        assert(q.empty() == true);
        assert(q.size() == 0);
    }

    //test copy ctor empty
    {
    r1::queue<int> q1;
    assert(q1.empty());
    assert(q1.size() == 0);
    r1::queue<int> q2(q1);
    assert(q2.empty());
    assert(q2.size() == 0);
}

    // test copy ctor full
    {
        r1::queue<int> q1;
        q1.push_back(1);
        q1.push_back(2);
        assert(!q1.empty());
        assert(q1.size() == 2);
        r1::queue<int> q2(q1);
        assert(!q1.empty());
        assert(q1.size() == 2);
        assert(!q2.empty());
        assert(q2.size() == 2);
    }

    // test move ctor empty
    {
        r1::queue<int> q1;
        assert(q1.empty());
        assert(q1.size() == 0);
        r1::queue<int> q2(std::move(q1));
        assert(q1.empty());
        assert(q1.size() == 0);
        assert(q2.empty());
        assert(q2.size() == 0);
    }

    // test move ctor full
    {
        r1::queue<int> q1;
        q1.push_back(1);
        q1.push_back(2);
        assert(!q1.empty());
        assert(q1.size() == 2);
        r1::queue<int> q2(std::move(q1));
        assert(q1.empty());
        assert(!q2.empty());
        assert(q2.size() == 2);
    }

    // test initialzie list empty
    {
        r1::queue<int> q = {};
        assert(q.empty());
        assert(q.size() == 0);
    }

    // test initialzie list full
    {
        r1::queue<int> q = {1, 2, 3};
        assert(!q.empty());
        assert(q.size() == 3);
        assert(q.front() == 1);
        q.pop_front();
        assert(q.front() == 2);
        q.pop_front();
        assert(q.front() == 3);
        q.pop_front();
    }

    // test copy assignment empty
    {
        r1::queue<int> q1;
        assert(q1.empty());
        assert(q1.size() == 0);
        r1::queue<int> q2 = q1;
        assert(q2.empty());
        assert(q2.size() == 0);
    }

    // test copy assignment full
    {
        r1::queue<int> q1;
        q1.push_back(1);
        q1.push_back(2);
        assert(!q1.empty());
        assert(q1.size() == 2);
        r1::queue<int> q2 = q1;
        assert(!q1.empty());
        assert(q1.size() == 2);
        assert(!q2.empty());
        assert(q2.size() == 2);
    }

    // test move assignment empty
    {
        r1::queue<int> q1;
        assert(q1.empty());
        assert(q1.size() == 0);
        r1::queue<int> q2 = std::move(q1);
        assert(q1.empty());
        assert(q1.size() == 0);
        assert(q2.empty());
        assert(q2.size() == 0);
    }
    // test move assignment full
    {
        r1::queue<int> q1;
        q1.push_back(1);
        q1.push_back(2);
        assert(!q1.empty());
        assert(q1.size() == 2);
        r1::queue<int> q2 = std::move(q1);
        assert(q1.empty());
        assert(!q2.empty());
        assert(q2.size() == 2);
    }

    // test empty
    {
        r1::queue<int> q;
        assert(q.empty());

        q.push_back(1);
        assert(!q.empty());

        q.pop_front();
        assert(q.empty());
    }

    // test size
    {
        r1::queue<int> q;
        assert(q.size() == 0);

        q.push_back(1);
        assert(q.size() == 1);

        q.pop_front();
        assert(q.size() == 0);
    }

    // test push_back
    {
        r1::queue<int> q1;
        q1.push_back(1);
        assert(q1.front() == 1);
        assert(q1.back() == 1);
        assert(q1.size() == 1);
        assert(!q1.empty());

        q1.push_back(2);
        assert(q1.front() == 1);
        assert(q1.back() == 2);
        assert(q1.size() == 2);
        assert(!q1.empty());

        const int x = 1;
        const int y = 2;
        r1::queue<int> q2;
        q2.push_back(x);
        assert(q2.front() == x);
        assert(q2.back() == x);
        assert(q2.size() == 1);
        assert(!q2.empty());

        q2.push_back(y);
        assert(q2.front() == x);
        assert(q2.back() == y);
        assert(q2.size() == 2);
        assert(!q2.empty());

        r1::queue<r1_test_queue::NoDefaultNoCopyAssign> q3;
        q3.push_back(r1_test_queue::NoDefaultNoCopyAssign(7));
        assert(q3.front().m_Int == 7);
    }

    // test pop_front
    {
        r1::queue<int> q;
        q.push_back(1);
        q.push_back(2);
        q.pop_front();
        assert(!q.empty());
        assert(q.size() == 1);
        assert(q.front() == 2);
        assert(q.back() == 2);
        q.pop_front();
        assert(q.empty());
        assert(q.size() == 0);
    }

    // test front/back
    {
        r1::queue<int> q;
        q.push_back(1);
        assert(q.front() == 1);
        assert(q.back() == 1);
        q.push_back(2);
        assert(q.front() == 1);
        assert(q.back() == 2);
        q.pop_front();
        assert(q.front() == 2);
        assert(q.back() == 2);
    }

    // test front/back const
    {
        r1::queue<int> q1;
        q1.push_back(1);
        q1.push_back(2);
        const r1::queue<int> q2 = q1;
        assert(q2.front() == 1);
        assert(q2.back() == 2);
    }

    return true;
}