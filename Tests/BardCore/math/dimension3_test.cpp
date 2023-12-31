#include "pch.h"

#include "BardCore/math/point3d.h"

namespace testing
{
    TEST(dimension3_test, point_add_test)
    {
        constexpr point3d point1 = {1, 2, 3};
        constexpr point3d point2 = {7, 8, 9};

        constexpr point3d result = point1 + point2;

        ASSERT_EQ(8.0, result.x);
        ASSERT_EQ(10.0, result.y);
        ASSERT_EQ(12.0, result.z);
    }

    //addition with negative result
    TEST(dimension3_test, point_add_negative_test)
    {
        constexpr point3d point1 = {1, 2, 3};
        constexpr point3d point2 = {7, 8, 9};

        constexpr point3d result = point2 + point1;

        ASSERT_NEAR(8.0, result.x, ROUND_EPSILON);
        ASSERT_NEAR(10.0, result.y, ROUND_EPSILON);
        ASSERT_NEAR(12.0, result.z, ROUND_EPSILON);
    }

    //add zero
    TEST(dimension3_test, point_add_zero_test)
    {
        constexpr point3d point1 = {1, 2, 3};
        constexpr point3d point2 = {0, 0, 0};

        constexpr point3d result = point1 + (point2);

        //assert near
        ASSERT_NEAR(1.0, result.x, ROUND_EPSILON);
        ASSERT_NEAR(2.0, result.y, ROUND_EPSILON);
        ASSERT_NEAR(3.0, result.z, ROUND_EPSILON);
    }

    TEST(dimension3_test, point_sub_test)
    {
        constexpr point3d point1 = {1, 2, 3};
        constexpr point3d point2 = {9, 8, 7};

        constexpr point3d result = point1 - (point2);

        ASSERT_EQ(-8.0, result.x);
        ASSERT_EQ(-6.0, result.y);
        ASSERT_EQ(-4.0, result.z);
    }

    //subtraction with negative result
    TEST(dimension3_test, point_sub_negative_test)
    {
        constexpr point3d point1 = {1, 2, 3};
        constexpr point3d point2 = {9, 8, 7};

        constexpr point3d result = point2 - (point1);

        //assert near
        ASSERT_EQ(8.0, result.x);
        ASSERT_EQ(6.0, result.y);
        ASSERT_EQ(4.0, result.z);
    }

    TEST(dimension3_test, point_multiply_test)
    {
        constexpr point3d point1 = {1, 2, 3};

        constexpr point3d result = point1 * (5);

        ASSERT_EQ(5.0, result.x);
        ASSERT_EQ(10.0, result.y);
        ASSERT_EQ(15.0, result.z);
    }

    //multiply by zero
    TEST(dimension3_test, point_multiply_zero_test)
    {
        constexpr point3d point1 = {1, 2, 3};

        constexpr point3d result = point1 * (0);

        ASSERT_EQ(0.0, result.x);
        ASSERT_EQ(0.0, result.y);
        ASSERT_EQ(0.0, result.z);
    }

    TEST(dimension3_test, point_divide_test)
    {
        constexpr point3d point1 = {10, 20, 30};

        constexpr point3d result = point1 / (5);

        ASSERT_EQ(2.0, result.x);
        ASSERT_EQ(4.0, result.y);
        ASSERT_EQ(6.0, result.z);
    }

    //test divide by zero
    TEST(dimension3_test, point_divide_zero_test)
    {
        constexpr point3d point1 = {10, 20, 30};

        ASSERT_THROW(point1 / 0, exception::zero_exception);
    }

    TEST(dimension3_test, point_all_test)
    {
        constexpr point3d point1 = {10, 20, 30}; //original point
        constexpr point3d point2 = {54, 32, 21}; //used for addition
        constexpr point3d point3 = {45, 23, 12}; //used for subtraction
        constexpr double n1 = 7; //used for multiplication
        constexpr double n2 = 2; //used for division

        point3d result = point1 + (point2);
        result = result - (point3);
        result = result * (n1);
        result = result / (n2);

        ASSERT_NEAR(66.5, result.x, ROUND_ONE_DECIMALS);
        ASSERT_NEAR(101.5, result.y, ROUND_ONE_DECIMALS);
        ASSERT_NEAR(136.5, result.z, ROUND_ONE_DECIMALS);
    }

    TEST(dimension3_test, operator_tests)
    {
        point3d point1 = {10, 20, 30}; //original point
        const point3d point2 = {54, 32, 21};
        const point3d point3 = {45, 23, 12};

        const vector3d vector1 = {45, 23, 12};

        ASSERT_EQ(point3d(64, 52, 51), point1 + point2);
        ASSERT_EQ(point3d(-35, -3, 18), point1 - point3);
        ASSERT_EQ(point3d(20, 40, 60), point1 * 2);
        ASSERT_EQ(point3d(5, 10, 15), point1 / 2);

        ASSERT_EQ(point3d(12, 22, 32), point1 += 2);
        ASSERT_EQ(point3d(10, 20, 30), point1 -= 2);
        ASSERT_EQ(point3d(20, 40, 60), point1 *= 2);
        ASSERT_EQ(point3d(10, 20, 30), point1 /= 2);

        ASSERT_EQ(point3d(55, 43, 42), point1 += vector1);
        ASSERT_EQ(point3d(10, 20, 30), point1 -= vector1);
    }
} // namespace testing
