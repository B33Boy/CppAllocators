#pragma once

#include <cstdlib> // size_t
#include <iostream>

template <typename T> class LinearAllocator
{
public:
    using value_type = T;

    constexpr LinearAllocator(size_t arena_size = 1024) noexcept : capacity_(arena_size), offset_(0)
    {
        arena_ = static_cast<T*>(::operator new(arena_size * sizeof(T)));

        std::cout << "Arena Allocated with " << arena_size * sizeof(T) << " bytes\n";
    }

    ~LinearAllocator()
    {
        ::operator delete(arena_);
    }

    /**
     * Copy constructor is needed when using STL containers that internally convert the allocator<T> to an allocator<U>
     * For example, if you construct a linked list as std::list<int, LinearAllocator<int>>, then internally it holds
     * Nodes that contain data, next ptr, etc. The std::list will internally rebind the allocator<int> to
     * allocator<Node<int>> with the copy constructor.
     */
    template <class U>
    constexpr LinearAllocator(LinearAllocator<U> const& other) noexcept
        : capacity_(other.capacity_), offset_(other.offset_), arena_(other.arena_)
    {
    }

    constexpr LinearAllocator(LinearAllocator&& other) noexcept = delete;            // move constructor
    constexpr LinearAllocator& operator=(LinearAllocator const& other) = delete;     // copy assignment operator
    constexpr LinearAllocator& operator=(LinearAllocator&& other) noexcept = delete; // move assignment operator

    [[nodiscard]] constexpr T* allocate(size_t n)
    {
        if ( offset_ + n > capacity_ )
            return nullptr;

        std::cout << "LinearAllocator: allocating " << n << " elements, offset now " << offset_ << "\n";
        offset_ += n;
        return static_cast<T*>(arena_ + offset_);
    }

    constexpr void deallocate([[maybe_unused]] T* p, [[maybe_unused]] size_t n)
    {
        std::cout << "LinearAllocator: deallocate called for " << n << " elements (ignored)\n";
    }

private:
    size_t capacity_;
    size_t offset_;
    T* arena_;
};