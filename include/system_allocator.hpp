#pragma once

#include "allocator_base.hpp"

#include <cstddef>

class SystemAllocator : public AllocatorBase<SystemAllocator>
{
public:
    void* allocate_impl(size_t bytes, size_t align)
    {
        return ::operator new(bytes, std::align_val_t(align));
    }

    void deallocate_impl(void* ptr, [[maybe_unused]] size_t bytes)
    {
        ::operator delete(ptr);
    }

    void reset_impl()
    {
        // no-op
    }
};