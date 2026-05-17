#pragma once

#include <cstddef>
#include <cstdlib>

template <typename Derived> class AllocatorBase
{
public:
    void* allocate(size_t bytes, size_t align = alignof(std::max_align_t))
    {
        return derived().allocate_impl(bytes, align);
    }

    void deallocate(void* ptr, size_t bytes)
    {
        derived().deallocate_impl(ptr, bytes);
    }

    void reset()
    {
        derived().reset_impl();
    }

private:
    AllocatorBase() = default;
    friend Derived;

    Derived& derived()
    {
        return static_cast<Derived&>(*this);
    }
};