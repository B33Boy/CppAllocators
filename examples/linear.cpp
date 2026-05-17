#include "linear_allocator.hpp"

#include <vector>

int main()
{
    LinearAllocator<64> l;

    auto i1 = static_cast<int*>(l.allocate(sizeof(int)));
    *i1 = 6;

    auto* d1 = static_cast<double*>(l.allocate(sizeof(double)));
    *d1 = 7.0;

    return 0;
}
