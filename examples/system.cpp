#include "system_allocator.hpp"

#include <iostream>

int main()
{

    SystemAllocator s;

    int* i1 = static_cast<int*>(s.allocate(sizeof(int)));
    *i1 = 5;

    double* d1 = static_cast<double*>(s.allocate(sizeof(double)));
    *d1 = 6.0;

    std::cout << "i1: " << *i1 << ", d1: " << *d1 << "\n";

    s.deallocate(d1, sizeof(*d1));
    s.deallocate(i1, sizeof(*i1));

    return 0;
}