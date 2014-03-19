#include "Stack.h"
#include <iostream>
#include <sstream>
#include <string>

template <typename T>
std::string PopString(rwk::stack<T> &s)
{
    std::stringstream os;
    os << "{";
    while (!s.empty())
    {
        os << s.top();
        s.pop();
        if (!s.empty()) os << ", ";
    }
    os << "}";
    return os.str();
}

int main()
{
    rwk::stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);
    std::cout << "s: " << PopString(s) << '\n';
    return 0;
}