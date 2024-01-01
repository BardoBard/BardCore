#include "pch.h"
#include "BardCore/math/point3d.h"
#include "BardCore/math/vector3d.h"

namespace testing
{
    TEST(point3d_test, get_vector_test)
    {
        constexpr point3d point1 = {1, 2, 3};
        constexpr point3d point2 = {4, 5, 6};

        constexpr vector3d result = point1.get_vector(point2);

        ASSERT_EQ(3.0, result.x);
        ASSERT_EQ(3.0, result.y);
        ASSERT_EQ(3.0, result.z);
    }

    TEST(point3d_test, add_vector_test)
    {
        constexpr point3d point1 = {1, 2, 3};
        constexpr vector3d vector1 = {4, 5, 6};

        constexpr point3d result = point1 + vector1;

        ASSERT_EQ(5.0, result.x);
        ASSERT_EQ(7.0, result.y);
        ASSERT_EQ(9.0, result.z);
    }

    TEST(point3d_test, distance_test)
    {
        constexpr point3d point1 = {1, 2, 3};
        constexpr point3d point2 = {4, 5, 6};

        constexpr double result = point1.distance(point2);

        ASSERT_NEAR(5.196, result, ROUND_THREE_DECIMALS);
        ASSERT_NO_THROW(point1.distance(point1));
    }

    TEST(point3d_test, distance_test_neg)
    {
        constexpr point3d point1 = {-5, 3, 2};
        constexpr point3d point2 = {7, 9, -25};

        constexpr double result = point1.distance(point2);

        ASSERT_NEAR(result, 30.1, ROUND_ONE_DECIMALS);
    }
    
    TEST(point3d_test, distance_squared_test)
    {
        constexpr point3d point1 = {1, 2, 3};
        constexpr point3d point2 = {4, 5, 6};

        constexpr double result = point1.distance_squared(point2);

        ASSERT_EQ(27.0, result);
    }

    TEST(point3d_test, distance_squared_test_neg)
    {
        constexpr point3d point1 = {-5, 3, 2};
        constexpr point3d point2 = {7, 9, -25};

        constexpr double result = point1.distance_squared(point2);

        ASSERT_NEAR(result, 909.0, ROUND_ONE_DECIMALS);
    }

    //center test
    TEST(point3d_test, center_test)
    {
        constexpr point3d point1 = {1, 2, 3};
        constexpr point3d point2 = {4, 5, 6};

        constexpr point3d result = point1.center(point2);

        ASSERT_EQ(2.5, result.x);
        ASSERT_EQ(3.5, result.y);
        ASSERT_EQ(4.5, result.z);
    }
} // namespace testing
