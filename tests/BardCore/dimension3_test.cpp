#include "pch.h"

namespace testing
{
    TEST(dimension3_test, point_add_test)
    {
        constexpr point3d point1 = {1, 2, 3};
        constexpr point3d point2 = {7, 8, 9};

        constexpr point3d result = point1 + point2;

        ASSERT_EQ(8.f, result.x);
        ASSERT_EQ(10.f, result.y);
        ASSERT_EQ(12.f, result.z);
    }

    //addition with negative result
    TEST(dimension3_test, point_add_negative_test)
    {
        constexpr point3d point1 = {1, 2, 3};
        constexpr point3d point2 = {7, 8, 9};

        constexpr point3d result = point2 + point1;

        ASSERT_NEAR(8.f, result.x, ROUND_EPSILON);
        ASSERT_NEAR(10.f, result.y, ROUND_EPSILON);
        ASSERT_NEAR(12.f, result.z, ROUND_EPSILON);
    }

    //add zero
    TEST(dimension3_test, point_add_zero_test)
    {
        constexpr point3d point1 = {1, 2, 3};
        constexpr point3d point2 = {0, 0, 0};

        constexpr point3d result = point1 + (point2);

        //assert near
        ASSERT_NEAR(1.f, result.x, ROUND_EPSILON);
        ASSERT_NEAR(2.f, result.y, ROUND_EPSILON);
        ASSERT_NEAR(3.f, result.z, ROUND_EPSILON);
    }

    TEST(dimension3_test, point_sub_test)
    {
        constexpr point3d point1 = {1, 2, 3};
        constexpr point3d point2 = {9, 8, 7};

        constexpr point3d result = point1 - (point2);

        ASSERT_EQ(-8.f, result.x);
        ASSERT_EQ(-6.f, result.y);
        ASSERT_EQ(-4.f, result.z);
    }

    //subtraction with negative result
    TEST(dimension3_test, point_sub_negative_test)
    {
        constexpr point3d point1 = {1, 2, 3};
        constexpr point3d point2 = {9, 8, 7};

        constexpr point3d result = point2 - (point1);

        //assert near
        ASSERT_EQ(8.f, result.x);
        ASSERT_EQ(6.f, result.y);
        ASSERT_EQ(4.f, result.z);
    }

    TEST(dimension3_test, point_multiply_test)
    {
        constexpr point3d point1 = {1, 2, 3};

        constexpr point3d result = point1 * (5);

        ASSERT_EQ(5.f, result.x);
        ASSERT_EQ(10.f, result.y);
        ASSERT_EQ(15.f, result.z);
    }

    //multiply by zero
    TEST(dimension3_test, point_multiply_zero_test)
    {
        constexpr point3d point1 = {1, 2, 3};

        constexpr point3d result = point1 * (0);

        ASSERT_EQ(0.f, result.x);
        ASSERT_EQ(0.f, result.y);
        ASSERT_EQ(0.f, result.z);
    }

    TEST(dimension3_test, point_divide_test)
    {
        constexpr point3d point1 = {10, 20, 30};

        constexpr point3d result = point1 / (5);

        ASSERT_EQ(2.f, result.x);
        ASSERT_EQ(4.f, result.y);
        ASSERT_EQ(6.f, result.z);
    }

    //test divide by zero
    TEST(dimension3_test, point_divide_zero_test)
    {
        constexpr point3d point1 = {10, 20, 30};

        ASSERT_ANY_THROW(point1 / (0));
    }

    TEST(dimension3_test, point_all_test)
    {
        constexpr point3d point1 = {10, 20, 30}; //original point
        constexpr point3d point2 = {54, 32, 21}; //used for addition
        constexpr point3d point3 = {45, 23, 12}; //used for subtraction
        constexpr float n1 = 7; //used for multiplication
        constexpr float n2 = 2; //used for division

        point3d result = point1 + (point2);
        result = result - (point3);
        result = result * (n1);
        result = result / (n2);

        ASSERT_NEAR(66.5f, result.x, ROUND_ONE_DECIMALS);
        ASSERT_NEAR(101.5f, result.y, ROUND_ONE_DECIMALS);
        ASSERT_NEAR(136.5f, result.z, ROUND_ONE_DECIMALS);
    }
};
