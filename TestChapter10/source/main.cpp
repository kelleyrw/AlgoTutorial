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
    std::cout << "size of s = " << s.size() << "\n";
    std::cout << "s: " << PopString(s) << '\n';

    // test copy constructor
    s.push(1);
    s.push(2);
    s.push(3);
    rwk::stack<int> s2(s);
    std::cout << "size of s2 = " << s2.size() << "\n";
    std::cout << "s2: " << PopString(s2) << '\n';

    // test assignment
    rwk::stack<int> s3;
    s3 = s;
    std::cout << "size of s3 = " << s3.size() << "\n";
    std::cout << "s3: " << PopString(s3) << '\n';
    return 0;
}