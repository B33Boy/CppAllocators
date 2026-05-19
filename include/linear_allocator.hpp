#pragma once

#include "allocator_base.hpp"

#include <memory>

template <size_t N> class LinearAllocator : public AllocatorBase<LinearAllocator<N>>
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

    void deallocate_impl([[maybe_unused]] void* ptr, [[maybe_unused]] size_t bytes,
                         [[maybe_unused]] size_t align) noexcept
    {
    }

    void reset_impl() noexcept
    {
        ptr = buffer;
        remain = N;
    }

private:
    alignas(std::max_align_t) std::byte buffer[N];
    size_t remain;
    void* ptr;
};