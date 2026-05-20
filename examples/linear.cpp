#include "linear_allocator.hpp"

#include <iostream>

int main()
{
    LinearAllocator<64> l;

    auto* i1 = l.allocate<int>();
    *i1 = 6;

    auto* d1 = l.allocate<double>();
    *d1 = 7.0;

    std::cout << "i1: " << *i1 << ", d1: " << *d1 << "\n";

    return 0;
}
