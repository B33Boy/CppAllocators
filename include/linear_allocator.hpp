#pragma once

#include "allocator_base.hpp"

#include <memory>

template <size_t N> 
class LinearAllocator : public AllocatorBase<LinearAllocator<N>>
{
public:
    explicit LinearAllocator() : remain(N), ptr(buffer)
    {
    }

    void* allocate_impl(size_t bytes, size_t align) noexcept
    {
        void* pos = ptr;
        if ( std::align(align, bytes, pos, remain) == nullptr )
            return nullptr;

        ptr = static_cast<std::byte*>(pos) + bytes;
        remain -= bytes;
        return pos;
    }

    void deallocate_impl(void* ptr, size_t bytes) noexcept
    {
        // no-op
    }

    void reset_impl() noexcept
    {
        ptr = buffer;
        remain = N;
    }

    size_t capacity() noexcept
    {
        return N;
    }

    size_t size() noexcept
    {
        return N - remain;
    }

private:
    std::byte buffer[N];
    size_t remain;
    void* ptr;
};