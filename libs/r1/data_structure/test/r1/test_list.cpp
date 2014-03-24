#include "r1/list.hpp"
#include <cassert>
#include <utility>

namespace r1_test_list
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

bool const test_list()
{
    
    return true;
}