#include "pch.h"

namespace testing
{
    TEST(point3d_test, get_vector_test)
    {
        const point3d point1 = {1, 2, 3};
        const point3d point2 = {4, 5, 6};

        const vector3d result = point1.get_vector(point2);

        ASSERT_EQ(3.f, result.x);
        ASSERT_EQ(3.f, result.y);
        ASSERT_EQ(3.f, result.z);
    }

    TEST(point3d_test, add_vector_test)
    {
        const point3d point1 = {1, 2, 3};
        const vector3d vector1 = {4, 5, 6};

        const point3d result = point1 + vector1;

        ASSERT_EQ(5.f, result.x);
        ASSERT_EQ(7.f, result.y);
        ASSERT_EQ(9.f, result.z);
    }

    TEST(point3d_test, distance_test)
    {
        const point3d point1 = {1, 2, 3};
        const point3d point2 = {4, 5, 6};

        const float result = point1.distance(point2);

        ASSERT_NEAR(5.196f, result, ROUND_THREE_DECIMALS);
    }

    TEST(point3d_test, distance_squared_test)
    {
        const point3d point1 = {1, 2, 3};
        const point3d point2 = {4, 5, 6};

        const float result = point1.distance_squared(point2);

        ASSERT_EQ(27.f, result);
    }
}
