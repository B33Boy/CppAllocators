#include "system_allocator.hpp"

#include <gtest/gtest.h>

TEST(SystemAllocator, AllocatedMemoryIsWritableAndReadable)
{
    SystemAllocator a;
    auto* i = a.allocate<int>();
    ASSERT_NE(i, nullptr);
    *i = 99;
    EXPECT_EQ(*i, 99);
    a.deallocate(i);
}

TEST(SystemAllocator, MultipleTypesWritableAndReadable)
{
    SystemAllocator a;

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

TEST(SystemAllocator, ReturnedPointerIsCorrectlyAligned)
{
    SystemAllocator a;
    void* p8 = a.allocate(8, 8);
    void* p16 = a.allocate(8, 16);
    void* p32 = a.allocate(8, 32);

    ASSERT_NE(p8, nullptr);
    ASSERT_NE(p16, nullptr);
    ASSERT_NE(p32, nullptr);
    EXPECT_EQ(reinterpret_cast<uintptr_t>(p8) % 8, 0u);
    EXPECT_EQ(reinterpret_cast<uintptr_t>(p16) % 16, 0u);
    EXPECT_EQ(reinterpret_cast<uintptr_t>(p32) % 32, 0u);

    a.deallocate(p8, 8);
    a.deallocate(p16, 8);
    a.deallocate(p32, 8);
}

TEST(SystemAllocator, SequentialAllocationsAreIndependent)
{
    SystemAllocator a;
    auto* i1 = a.allocate<int>();
    auto* i2 = a.allocate<int>();
    ASSERT_NE(i1, nullptr);
    ASSERT_NE(i2, nullptr);

    // Each allocation should be a distinct address
    EXPECT_NE(i1, i2);

    // Writing to one should not affect the other
    *i1 = 1;
    *i2 = 2;
    EXPECT_EQ(*i1, 1);
    EXPECT_EQ(*i2, 2);

    a.deallocate(i1);
    a.deallocate(i2);
}

TEST(SystemAllocator, ResetIsNoOp)
{
    SystemAllocator a;
    auto* p = a.allocate<int>();
    ASSERT_NE(p, nullptr);

    // Should not crash, and allocator should still work afterwards
    EXPECT_NO_THROW(a.reset());
    auto* p2 = a.allocate<int>();

    EXPECT_NE(p2, nullptr);

    a.deallocate(p);
    a.deallocate(p2);
}