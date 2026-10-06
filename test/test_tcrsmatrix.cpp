#include "tmatrix.h"

#include <gtest.h>

TEST(TCRSMatrix, can_create_matrix)
{
    TCRSMatrix<int> m(3, 4);

    EXPECT_EQ(3, m.get_rows());
    EXPECT_EQ(4, m.get_cols());
    EXPECT_EQ(0, m.get_DataSize());
}

TEST(TCRSMatrix, can_create_matrix_with_zero_size)
{
    TCRSMatrix<int> m(0, 0);

    EXPECT_EQ(0, m.get_rows());
    EXPECT_EQ(0, m.get_cols());
    EXPECT_EQ(0, m.get_DataSize());
}

TEST(TCRSMatrix, can_get_zero_from_empty_matrix)
{
    TCRSMatrix<int> m(3, 4);

    EXPECT_EQ(0, m.get(0, 0));
    EXPECT_EQ(0, m.get(1, 2));
    EXPECT_EQ(0, m.get(2, 3));
}

TEST(TCRSMatrix, can_set_and_get_element)
{
    TCRSMatrix<int> m(3, 4);

    m.set(1, 2, 5);

    EXPECT_EQ(5, m.get(1, 2));
    EXPECT_EQ(1, m.get_DataSize());
}

TEST(TCRSMatrix, can_set_several_elements)
{
    TCRSMatrix<int> m(3, 4);

    m.set(0, 1, 5);
    m.set(1, 2, 10);
    m.set(2, 3, 15);

    EXPECT_EQ(5, m.get(0, 1));
    EXPECT_EQ(10, m.get(1, 2));
    EXPECT_EQ(15, m.get(2, 3));
}

TEST(TCRSMatrix, can_change_existing_element)
{
    TCRSMatrix<int> m(3, 3);

    m.set(1, 1, 5);
    m.set(1, 1, 10);

    EXPECT_EQ(10, m.get(1, 1));
}

TEST(TCRSMatrix, can_set_zero_to_element)
{
    TCRSMatrix<int> m(3, 3);

    m.set(1, 1, 5);
    m.set(1, 1, 0);

    EXPECT_EQ(0, m.get(1, 1));
    EXPECT_EQ(0, m.get_DataSize());
}

TEST(TCRSMatrix, can_get_zero_from_unset_element)
{
    TCRSMatrix<int> m(3, 3);

    m.set(1, 1, 5);

    EXPECT_EQ(0, m.get(0, 0));
    EXPECT_EQ(0, m.get(0, 1));
    EXPECT_EQ(0, m.get(1, 0));
    EXPECT_EQ(0, m.get(1, 2));
    EXPECT_EQ(0, m.get(2, 2));
}

TEST(TCRSMatrix, throws_when_get_row_is_out_of_range)
{
    TCRSMatrix<int> m(3, 4);

    EXPECT_THROW(m.get(3, 0), std::out_of_range);
}

TEST(TCRSMatrix, throws_when_get_column_is_out_of_range)
{
    TCRSMatrix<int> m(3, 4);

    EXPECT_THROW(m.get(0, 4), std::out_of_range);
}

TEST(TCRSMatrix, throws_when_set_row_is_out_of_range)
{
    TCRSMatrix<int> m(3, 4);

    EXPECT_THROW(m.set(3, 0, 10), std::out_of_range);
}

TEST(TCRSMatrix, throws_when_set_column_is_out_of_range)
{
    TCRSMatrix<int> m(3, 4);

    EXPECT_THROW(m.set(0, 4, 10), std::out_of_range);
}

TEST(TCRSMatrix, can_multiply_by_scalar)
{
    TCRSMatrix<int> m(2, 3);
    m.set(0, 0, 1);
    m.set(1, 2, 2);
    m.set(1, 1, 3);
    TCRSMatrix<int> m1 = m * 5;

    EXPECT_EQ(5, m1.get(0, 0));
    EXPECT_EQ(10, m1.get(1, 2));
    EXPECT_EQ(15, m1.get(1, 1));
    EXPECT_EQ(0, m1.get(0, 1));
    EXPECT_EQ(0, m1.get(1, 0));
    EXPECT_EQ(3, m1.get_DataSize());
}

TEST(TCRSMatrix, can_multiply_by_zero)
{
    TCRSMatrix<int> m(2, 3);
    m.set(0, 0, 1);
    m.set(1, 2, 2);
    m.set(1, 1, 3);
    TCRSMatrix<int> m1 = m * 0;

    EXPECT_EQ(0, m1.get(0, 0));
    EXPECT_EQ(0, m1.get(1, 2));
    EXPECT_EQ(0, m1.get(1, 1));
    EXPECT_EQ(0, m1.get(0, 1));
    EXPECT_EQ(0, m1.get(1, 0));
    EXPECT_EQ(0, m1.get_DataSize());
}

TEST(TCRSMatrix, can_multiply_by_vector)
{
    TCRSMatrix<int> m(2, 3);
    m.set(0, 0, 2);
    m.set(0, 2, 3);
    m.set(1, 1, 4);
    TDynamicArray<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    TDynamicArray<int> m1 = m * v;

    EXPECT_EQ(2, m1.size());
    EXPECT_EQ(11, m1[0]);
    EXPECT_EQ(8, m1[1]);
}

TEST(TCRSMatrix, throws_when_vector_size_is_wrong)
{
    TCRSMatrix<int> m(2, 3);
    TDynamicArray<int> v;
    v.push_back(1);
    v.push_back(2);

    EXPECT_THROW(m * v, std::invalid_argument);
}

TEST(TCRSMatrix, can_add_matrices)
{
    TCRSMatrix<int> m1(2, 3);
    m1.set(0, 0, 2);
    m1.set(0, 2, 3);
    m1.set(1, 1, 4);
    TCRSMatrix<int> m2(2, 3);
    m2.set(0, 0, 5);
    m2.set(0, 1, 6);
    m2.set(1, 1, 1);
    TCRSMatrix<int> m = m1 + m2;

    EXPECT_EQ(7, m.get(0, 0));
    EXPECT_EQ(6, m.get(0, 1));
    EXPECT_EQ(3, m.get(0, 2));
    EXPECT_EQ(5, m.get(1, 1));
}

TEST(TCRSMatrix, throws_when_adding_matrices_with_different_sizes)
{
    TCRSMatrix<int> m1(2, 3);
    TCRSMatrix<int> m2(3, 2);

    EXPECT_THROW(m1 + m2, std::invalid_argument);
}

TEST(TCRSMatrix, can_subtract_matrices)
{
    TCRSMatrix<int> m1(2, 3);
    m1.set(0, 0, 7);
    m1.set(0, 2, 5);
    m1.set(1, 1, 4);
    TCRSMatrix<int> m2(2, 3);
    m2.set(0, 0, 2);
    m2.set(0, 1, 3);
    m2.set(1, 1, 1);
    TCRSMatrix<int> m = m1 - m2;

    EXPECT_EQ(5, m.get(0, 0));
    EXPECT_EQ(-3, m.get(0, 1));
    EXPECT_EQ(5, m.get(0, 2));
    EXPECT_EQ(3, m.get(1, 1));
}

TEST(TCRSMatrix, throws_when_subtracting_matrices_with_different_sizes)
{
    TCRSMatrix<int> m1(2, 3);
    TCRSMatrix<int> m2(3, 2);

    EXPECT_THROW(m1 - m2, std::invalid_argument);
}

TEST(TCRSMatrix, can_multiply_matrices)
{
    TCRSMatrix<int> m1(2, 3);
    m1.set(0, 0, 1);
    m1.set(0, 2, 2);
    m1.set(1, 1, 3);

    TCRSMatrix<int> m2(3, 2);
    m2.set(0, 0, 4);
    m2.set(1, 1, 5);
    m2.set(2, 0, 6);

    TCRSMatrix<int> m = m1 * m2;

    EXPECT_EQ(16, m.get(0, 0));
    EXPECT_EQ(0, m.get(0, 1));
    EXPECT_EQ(0, m.get(1, 0));
    EXPECT_EQ(15, m.get(1, 1));
}

TEST(TCRSMatrix, throws_when_multiplying_matrices_with_wrong_sizes)
{
    TCRSMatrix<int> m1(2, 3);
    TCRSMatrix<int> m2(2, 2);

    EXPECT_THROW(m1 * m2, std::invalid_argument);
}

TEST(TCRSMatrix, can_multiply_by_zero_matrix)
{
    TCRSMatrix<int> m1(2, 3);
    m1.set(0, 0, 2);
    m1.set(0, 2, 3);
    m1.set(1, 1, 4);
    TCRSMatrix<int> m2(3, 2);
    TCRSMatrix<int> m = m1 * m2;

    EXPECT_EQ(0, m.get(0, 0));
    EXPECT_EQ(0, m.get(0, 1));
    EXPECT_EQ(0, m.get(1, 0));
    EXPECT_EQ(0, m.get(1, 1));
    EXPECT_EQ(0, m.get_DataSize());
}

TEST(TCRSMatrix, can_multiply_matrices_with_empty_rows)
{
    TCRSMatrix<int> m1(3, 3);
    m1.set(0, 0, 2);
    m1.set(2, 2, 3);
    TCRSMatrix<int> m2(3, 2);
    m2.set(0, 1, 4);
    m2.set(2, 0, 5);
    TCRSMatrix<int> m = m1 * m2;

    EXPECT_EQ(8, m.get(0, 1));
    EXPECT_EQ(0, m.get(0, 0));
    EXPECT_EQ(0, m.get(1, 0));
    EXPECT_EQ(0, m.get(1, 1));
    EXPECT_EQ(15, m.get(2, 0));
    EXPECT_EQ(0, m.get(2, 1));
}

TEST(TCRSMatrix, does_not_store_zero_after_matrix_multiplication)
{
    TCRSMatrix<int> m1(1, 2);
    m1.set(0, 0, 2);
    m1.set(0, 1, -2);
    TCRSMatrix<int> m2(2, 1);
    m2.set(0, 0, 3);
    m2.set(1, 0, 3);
    TCRSMatrix<int> m = m1 * m2;

    EXPECT_EQ(0, m.get(0, 0));
    EXPECT_EQ(0, m.get_DataSize());
}