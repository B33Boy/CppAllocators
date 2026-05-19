#include "system_allocator.hpp"

#include <iostream>

int main()
{

    SystemAllocator s;

    int* i1 = s.allocate<int>();
    *i1 = 5;

    double* d1 = s.allocate<double>();
    *d1 = 6.0;

    std::cout << "i1: " << *i1 << ", d1: " << *d1 << "\n";

    s.deallocate(d1);
    s.deallocate(i1);

    return 0;
}