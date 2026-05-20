#include "stack_allocator.hpp"

#include <iostream>

int main()
{
    StackAllocator<64> s;

    auto* i1 = s.allocate<int>();
    *i1 = 6;

    auto* d1 = s.allocate<double>();
    *d1 = 7.0;

    std::cout << "before scope - i1: " << *i1 << ", d1: " << *d1 << "\n";

    {
        StackGuard sg(s);
        auto* d2 = s.allocate<double>();
        *d2 = 99.0;
        std::cout << "inside scope - d2: " << *d2 << "\n";
    } // sg destructs here, restores ptr to before d2 was allocated

    auto* d3 = s.allocate<double>();
    *d3 = 42.0;
    std::cout << "after scope - d3: " << *d3 << "\n";

    return 0;
}
