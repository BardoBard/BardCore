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

    TEST(dimension3_test, point_add_n_test)
    {
        constexpr point3d point1 = {1, 2, 3};
        constexpr double n = 5;

        ASSERT_EQ(point3d(6, 7, 8), point1 + n);
        ASSERT_EQ(point3d(6, 7, 8), n + point1);
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

    TEST(dimension3_test, point_subtract_n_test)
    {
        constexpr point3d point1 = {1, 2, 3};
        constexpr double n = 5;

        ASSERT_EQ(point3d(-4, -3, -2), point1 - n);
        ASSERT_EQ(point3d(4, 3, 2), n - point1);
    }

    //subtraction with negative result
    TEST(dimension3_test, point_sub_negative_test)
    {
        constexpr point3d point1 = {1, 2, 3};
        constexpr point3d point2 = {9, 8, 7};

        constexpr point3d result = point2 - point1;

        //assert near
        ASSERT_EQ(8.0, result.x);
        ASSERT_EQ(6.0, result.y);
        ASSERT_EQ(4.0, result.z);
    }

    TEST(dimension3_test, point_multiply_test)
    {
        constexpr point3d point1 = {1, 2, 3};

        constexpr point3d result = point1 * 5;

        ASSERT_EQ(5.0, result.x);
        ASSERT_EQ(10.0, result.y);
        ASSERT_EQ(15.0, result.z);
    }

    TEST(dimension3_test, point_multiply_n_test)
    {
        constexpr point3d point1 = {1, 2, 3};
        constexpr double n = 5;

        ASSERT_EQ(point3d(5, 10, 15), point1 * n);
        ASSERT_EQ(point3d(5, 10, 15), n * point1);
    }

    //multiply by zero
    TEST(dimension3_test, point_multiply_zero_test)
    {
        constexpr point3d point1 = {1, 2, 3};

        constexpr point3d result = point1 * 0;

        ASSERT_EQ(0.0, result.x);
        ASSERT_EQ(0.0, result.y);
        ASSERT_EQ(0.0, result.z);
    }

    TEST(dimension3_test, point_divide_test)
    {
        constexpr point3d point1 = {10, 20, 30};

        constexpr point3d result = point1 / 5;

        ASSERT_EQ(2.0, result.x);
        ASSERT_EQ(4.0, result.y);
        ASSERT_EQ(6.0, result.z);
    }

    TEST(dimension3_test, point_divide_n_test)
    {
        constexpr point3d point1 = {10, 20, 30};
        constexpr double n = 5;

        ASSERT_EQ(point3d(2, 4, 6), point1 / n);
    }

    TEST(dimension3_test, point_divide_exception_test)
    {
        ASSERT_THROW(5 / point3d(0, 1, 2), exception::zero_exception);
        ASSERT_THROW(5 / point3d(1, 0, 2), exception::zero_exception);
        ASSERT_THROW(5 / point3d(1, 2, 0), exception::zero_exception);
        ASSERT_THROW(5 / point3d(1, 2, 0.00001), exception::zero_exception);
        
        ASSERT_NO_THROW(5 / point3d(1, 2, 3));
        ASSERT_NO_THROW(5 / point3d(-1, -2, -3));
        ASSERT_NO_THROW(5 / point3d(0.1, -2, -3));
        ASSERT_NO_THROW(5 / point3d(1, -0.0001, -3));
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
        constexpr point3d point2 = {54, 32, 21};
        constexpr point3d point3 = {45, 23, 12};

        constexpr vector3d vector1 = {45, 23, 12};

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

    TEST(dimension3_test, operator_neg_pos_test)
    {
        point3d point1 = {10, 20, 30};
        point3d point2 = {-54, 32, 21};
        point3d point3 = {-45, 0, -12};

        ASSERT_EQ(-point1, point3d(-10, -20, -30));
        ASSERT_EQ(point1.abs(), point3d(10, 20, 30));

        ASSERT_EQ(-point2, point3d(54, -32, -21));
        ASSERT_EQ(point2.abs(), point3d(54, 32, 21));

        ASSERT_EQ(-point3, point3d(45, 0, 12));
        ASSERT_EQ(point3.abs(), point3d(45, 0, 12));
    }
} // namespace testing
