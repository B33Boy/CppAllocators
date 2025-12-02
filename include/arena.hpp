
#pragma once

#include <cstdlib> // size_t
#include <iostream>
#include <memory>

class LinearArena
{
public:
    constexpr LinearArena(size_t size) : start_ptr_(nullptr), capacity_(size), offset_(0)
    {
        start_ptr_ = ::operator new(size);
        std::cout << "(Arena) Allocated " << size << " bytes\n";
    }

    ~LinearArena()
    {
        ::operator delete(start_ptr_);
    }

    // Disable copy construction and copy assignment
    LinearArena(LinearArena const& other) = delete;
    LinearArena& operator=(LinearArena const& other) = delete;

    // Allow move construction and move assignment
    constexpr LinearArena(LinearArena&& other) noexcept = default;
    LinearArena& operator=(LinearArena&& other) noexcept = default;

    [[nodiscard]] constexpr void* allocate(size_t const req_size, size_t const req_alignment)
    {
        size_t remaining_space = capacity_ - offset_;
        void* new_start = static_cast<char*>(start_ptr_) + offset_;
        void* old_start = new_start;

        if ( std::align(req_alignment, req_size, new_start, remaining_space) )
        {
            size_t padding = static_cast<char*>(new_start) - static_cast<char*>(old_start);

            offset_ += req_size + padding;
            std::cout << "(Arena) Allocating " << req_size << " bytes (Used: " << offset_ << "/" << capacity_ << ")\n";

            return new_start;
        }
        return nullptr;
    }

private:
    void* start_ptr_;
    size_t capacity_;
    size_t offset_;
};