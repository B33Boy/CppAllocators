#pragma once

#include <cstddef>
#include <cstdlib>

template <typename Derived> class AllocatorBase
{
public:
    [[nodiscard]] void* allocate(size_t bytes, size_t align = alignof(std::max_align_t))
    {
        return derived().allocate_impl(bytes, align);
    }

    // Overload allocate to directly return T* given a type rather than a void*
    template <typename T> T* allocate()
    {
        return static_cast<T*>(derived().allocate(sizeof(T), alignof(T)));
    }

    void deallocate(void* ptr, size_t bytes, size_t align = alignof(std::max_align_t))
    {
        derived().deallocate_impl(ptr, bytes, align);
    }

    // overload to handle deallocation of T*
    template <typename T> void deallocate(T* ptr)
    {
        derived().deallocate_impl(ptr, sizeof(T), alignof(T));
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