#pragma once

#include "arena.hpp"

#include <cstdlib> // size_t
#include <iostream>

template <typename T> class LinearAllocator
{
public:
    using value_type = T;

    // =============== Constructors  ===============
    constexpr LinearAllocator(LinearArena& arena) noexcept : arena_(&arena)
    {
        std::cout << "(LinearAllocator) Created\n";
    }

    // =============== Defaulted Special Functions ===============
    LinearAllocator(LinearAllocator const& other) = default;
    LinearAllocator(LinearAllocator&& other) noexcept = default;
    LinearAllocator& operator=(LinearAllocator const& other) = default;
    LinearAllocator& operator=(LinearAllocator&& other) noexcept = default;

    // =============== Templated Special Functions  ===============

    /**
     * Templated Rebinding Constructor
     * Copy constructor is needed when using STL containers that internally convert the allocator<T> to an allocator<U>
     * For example, if you construct a linked list as std::list<int, LinearAllocator<int>>, then internally it holds
     * Nodes that contain data, next ptr, etc. The std::list will internally rebind the allocator<int> to
     * allocator<Node<int>> with the copy constructor.
     *
     * When this happens, we want to ensure that the underlying pointer to the arena is the same.
     */
    template <class U> constexpr LinearAllocator(LinearAllocator<U> const& other) noexcept : arena_(other.arena_)
    {
        std::cout << "(LinearAllocator) Copy Constructed\n";
    }

    template <class U> constexpr LinearAllocator& operator=(LinearAllocator<U> const& other) noexcept
    {
        std::cout << "(LinearAllocator) Copy Assigned\n";
        arena_ = other.arena_;
        return *this;
    }

    template <class U> constexpr LinearAllocator& operator=(LinearAllocator<U> const&& other) noexcept
    {
        std::cout << "(LinearAllocator) Move Assigned\n";
        arena_ = std::move(other.arena_);
        other.arena_ = nullptr;
        return *this;
    }

    // =============== Allocate/Deallocate ===============
    [[nodiscard]]
    constexpr T* allocate(size_t req_elements)
    {
        return static_cast<T*>(arena_->allocate(req_elements * sizeof(T), alignof(T)));
    }

    template <class U> constexpr U* allocate(size_t req_elements)
    {
        return static_cast<U*>(arena_->allocate(req_elements * sizeof(U), alignof(U)));
    }

    constexpr void deallocate([[maybe_unused]] T* p, [[maybe_unused]] size_t n)
    {
        std::cout << "(LinearAllocator) deallocate called for " << n << " elements (ignored)\n";
    }

private:
    LinearArena* arena_; // non-owning
};

// If two allocators point to the same arena, they are considered equal
template <class T, class U> bool operator==(LinearAllocator<T> const& a, LinearAllocator<U> const& b)
{
    return a.arena_ == b.arena_;
}

template <class T, class U> bool operator!=(LinearAllocator<T> const& a, LinearAllocator<U> const& b)
{
    return a.arena_ != b.arena_;
}
