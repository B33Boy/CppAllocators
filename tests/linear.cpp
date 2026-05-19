#include "linear_allocator.hpp"

#include <gtest/gtest.h>

TEST(LinearAllocator, AllocatedMemoryIsWritableAndReadable)
{
    LinearAllocator<16> a;
    auto* i = a.allocate<int>();
    ASSERT_NE(i, nullptr);
    *i = 42;
    EXPECT_EQ(*i, 42);
}

TEST(LinearAllocator, MultipleTypesWritableAndReadable)
{
    LinearAllocator<64> a;

    auto* i = a.allocate<int>();
    auto* d = a.allocate<double>();
    ASSERT_NE(i, nullptr);
    ASSERT_NE(d, nullptr);

    *i = 7;
    *d = 3.14;
    EXPECT_EQ(*i, 7);
    EXPECT_DOUBLE_EQ(*d, 3.14);

    a.deallocate(i);
    a.deallocate(d);
}

TEST(LinearAllocator, ReturnedPointerIsCorrectlyAligned)
{
    LinearAllocator<256> a;
    void* _ = a.allocate(1, 1); // misalign the bump pointer
    void* p8 = a.allocate(8, 8);
    void* p16 = a.allocate(16, 16);

    ASSERT_NE(p8, nullptr);
    ASSERT_NE(p16, nullptr);
    EXPECT_EQ(reinterpret_cast<uintptr_t>(p8) % 8, 0u);
    EXPECT_EQ(reinterpret_cast<uintptr_t>(p16) % 16, 0u);
}

TEST(LinearAllocator, ReturnsNullWhenFull)
{
    LinearAllocator<4> a;
    int* p1 = a.allocate<int>();
    int* p2 = a.allocate<int>();
    EXPECT_NE(p1, nullptr);
    EXPECT_EQ(p2, nullptr);
}

TEST(LinearAllocator, FailedAllocationDoesNotCorruptalloc)
{
    LinearAllocator<64> a;
    // Consume most of the alloc
    void* p1 = a.allocate(60, 1);
    ASSERT_NE(p1, nullptr);

    // This should fail — not enough room
    void* p2 = a.allocate(60, 1);
    EXPECT_EQ(p2, nullptr);

    // A small allocation should still succeed
    void* p3 = a.allocate(4, 1);
    EXPECT_NE(p3, nullptr);
}

TEST(LinearAllocator, ExactFitAllocation)
{
    LinearAllocator<sizeof(double)> a;
    auto* p = a.allocate<double>();
    EXPECT_NE(p, nullptr);

    // One more byte should fail
    auto* p2 = a.allocate<char>();
    EXPECT_EQ(p2, nullptr);
}

TEST(LinearAllocator, SequentialAllocationsDoNotOverlap)
{
    LinearAllocator<64> a;
    auto* p1 = a.allocate<int>();
    auto* p2 = a.allocate<int>();
    ASSERT_NE(p1, nullptr);
    ASSERT_NE(p2, nullptr);

    // p2 must start at or after the end of p1
    uintptr_t end_of_p1 = reinterpret_cast<uintptr_t>(p1) + sizeof(int);
    EXPECT_GE(reinterpret_cast<uintptr_t>(p2), end_of_p1);
}

TEST(LinearAllocator, ResetAllowsReuse)
{
    LinearAllocator<64> a;
    void* p1 = a.allocate(64, 1);
    ASSERT_NE(p1, nullptr);

    a.reset();

    void* p2 = a.allocate(64, 1);
    EXPECT_NE(p2, nullptr);
}

TEST(LinearAllocator, DeallocateIsNoOp)
{
    LinearAllocator<16> a;
    auto* p = a.allocate<int>();
    ASSERT_NE(p, nullptr);

    a.deallocate(p);
}