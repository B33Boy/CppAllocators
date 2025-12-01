#include "linear.hpp"

#include <vector>

int main()
{
    std::vector<int, LinearAllocator<int>> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    for ( int x : v )
    {
        std::cout << x << " ";
    }
    std::cout << "\n";

    return 0;
}
