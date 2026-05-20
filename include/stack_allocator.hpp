#pragma once

#include "allocator_base.hpp"

#include <memory>

template <size_t N> class StackAllocator : public AllocatorBase<StackAllocator<N>>
{
public:
    explicit StackAllocator() : remain(N), ptr(buffer)
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
        // no-op
    }

    void reset_impl() noexcept
    {
        ptr = buffer;
        remain = N;
    }

    size_t save() noexcept
    {
        return ptr - buffer;
    }

    void restore(size_t marker) noexcept
    {
        ptr = buffer + marker;
        remain = N - marker;
    }

private:
    alignas(std::max_align_t) std::byte buffer[N];
    size_t remain;
    std::byte* ptr;
};

template <size_t N> class StackGuard
{
public:
    StackGuard(StackAllocator<N>& s) : sa(s), marker(s.save())
    {
    }

    ~StackGuard()
    {
        sa.restore(marker);
    }

private:
    StackAllocator<N>& sa;
    size_t marker;
};
