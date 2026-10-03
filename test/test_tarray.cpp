#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicArray, can_create_empty_array)
{
    TDynamicArray<int> arr;

    EXPECT_EQ(0, arr.size());
    EXPECT_EQ(0, arr.get_capacity());
    EXPECT_TRUE(arr.empty());
}

TEST(TDynamicArray, can_create_array_with_given_size)
{
    TDynamicArray<int> arr(5);

    EXPECT_EQ(5, arr.size());
    EXPECT_EQ(10, arr.get_capacity());
    for (size_t i = 0; i < arr.size(); i++) EXPECT_EQ(0, arr[i]);
}

TEST(TDynamicArray, can_create_array_with_zero_size)
{
    TDynamicArray<int> arr(0);

    EXPECT_EQ(0, arr.size());
    EXPECT_EQ(0, arr.get_capacity());
}

TEST(TDynamicArray, can_copy_array)
{
    TDynamicArray<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    TDynamicArray<int> arr1(arr);

    EXPECT_EQ(arr.size(), arr1.size());
    for (size_t i = 0; i < arr.size(); ++i) EXPECT_EQ(arr[i], arr1[i]);
}

TEST(TDynamicArray, copied_array_has_its_own_memory)
{
    TDynamicArray<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    TDynamicArray<int> arr1(arr);
    arr1[0] = 100;

    EXPECT_EQ(1, arr[0]);
    EXPECT_EQ(100, arr1[0]);
}

TEST(TDynamicArray, can_assign_array)
{
    TDynamicArray<int> arr1;
    arr1.push_back(1);
    arr1.push_back(2);
    TDynamicArray<int> arr2;
    arr2.push_back(10);
    arr2.push_back(20);
    arr2.push_back(30);
    arr1 = arr2;

    ASSERT_EQ(3, arr1.size());
    EXPECT_EQ(10, arr1[0]);
    EXPECT_EQ(20, arr1[1]);
    EXPECT_EQ(30, arr1[2]);
}

TEST(TDynamicArray, can_assign_array_to_itself)
{
    TDynamicArray<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr = arr;

    ASSERT_EQ(2, arr.size());
    EXPECT_EQ(1, arr[0]);
    EXPECT_EQ(2, arr[1]);
}

TEST(TDynamicArray, can_move_array)
{
    TDynamicArray<int> arr1;
    arr1.push_back(1);
    TDynamicArray<int> arr2;
    arr2.push_back(2);
    arr2.push_back(3);
    arr1 = std::move(arr2);

    ASSERT_EQ(2, arr1.size());
    EXPECT_EQ(2, arr1[0]);
    EXPECT_EQ(3, arr1[1]);

    EXPECT_TRUE(arr2.empty());
}

TEST(TDynamicArray, can_access_element_using_square_brackets)
{
    TDynamicArray<int> arr(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    EXPECT_EQ(1, arr[0]);
    EXPECT_EQ(2, arr[1]);
    EXPECT_EQ(3, arr[2]);
}

TEST(TDynamicArray, can_access_element_using_at)
{
    TDynamicArray<int> arr(1);
    arr.at(0) = 42;

    EXPECT_EQ(42, arr.at(0));
}

TEST(TDynamicArray, at_throws_for_out_of_range_index)
{
    TDynamicArray<int> arr(3);

    EXPECT_THROW(arr.at(3), std::out_of_range);
}

TEST(TDynamicArray, can_push_back_element)
{
    TDynamicArray<int> arr;
    arr.push_back(1);

    ASSERT_EQ(1, arr.size());
    EXPECT_EQ(1, arr[0]);
}

TEST(TDynamicArray, push_back_increases_size_by_one)
{
    TDynamicArray<int> arr;
    arr.push_back(1);
    arr.push_back(1);
    arr.push_back(1);

    EXPECT_EQ(3, arr.size());
}

TEST(TDynamicArray, push_back_preserves_existing_elements)
{
    TDynamicArray<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);

    EXPECT_EQ(1, arr[0]);
    EXPECT_EQ(2, arr[1]);
    EXPECT_EQ(3, arr[2]);
}

TEST(TDynamicArray, reserve_increases_capacity)
{
    TDynamicArray<int> arr;
    arr.push_back(1);
    arr.reserve(20);

    EXPECT_EQ(20, arr.get_capacity());
    EXPECT_EQ(1, arr.size());
    EXPECT_EQ(1, arr[0]);
}

TEST(TDynamicArray, reserve_does_not_change_size)
{
    TDynamicArray<int> arr(3);
    arr.reserve(10);

    EXPECT_EQ(3, arr.size());
}

TEST(TDynamicArray, resize_increases_size)
{
    TDynamicArray<int> arr(2);
    arr[0] = 1;
    arr[1] = 2;
    arr.resize(5);

    ASSERT_EQ(5, arr.size());
    EXPECT_EQ(1, arr[0]);
    EXPECT_EQ(2, arr[1]);
    EXPECT_EQ(0, arr[2]);
    EXPECT_EQ(0, arr[3]);
    EXPECT_EQ(0, arr[4]);
}

TEST(TDynamicArray, resize_to_zero_makes_array_empty)
{
    TDynamicArray<int> arr(5);
    arr.resize(0);

    EXPECT_EQ(0, arr.size());
}

TEST(TDynamicArray, can_pop_back_element)
{
    TDynamicArray<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.pop_back();

    ASSERT_EQ(1, arr.size());
    EXPECT_EQ(1, arr[0]);
}

TEST(TDynamicArray, pop_back_on_empty_array_throws)
{
    TDynamicArray<int> arr;

    EXPECT_THROW(arr.pop_back(), std::out_of_range);
}

TEST(TDynamicArray, clear_removes_all_elements)
{
    TDynamicArray<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.clear();

    EXPECT_EQ(0, arr.size());
}

TEST(TDynamicArray, clear_preserves_capacity)
{
    TDynamicArray<int> arr;
    arr.reserve(20);
    arr.push_back(1);
    arr.push_back(2);
    size_t cap = arr.get_capacity();
    arr.clear();

    EXPECT_EQ(0, arr.size());
    EXPECT_EQ(cap, arr.get_capacity());
}

TEST(TDynamicArray, can_swap_arrays)
{
    TDynamicArray<int> arr1;
    arr1.push_back(1);
    arr1.push_back(2);
    TDynamicArray<int> arr2;
    arr2.push_back(3);

    arr1.swap(arr2);

    ASSERT_EQ(1, arr1.size());
    EXPECT_EQ(3, arr1[0]);

    ASSERT_EQ(2, arr2.size());
    EXPECT_EQ(1, arr2[0]);
    EXPECT_EQ(2, arr2[1]);
}