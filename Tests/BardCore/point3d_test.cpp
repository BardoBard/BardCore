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

        ASSERT_EQ(3.f, result.x);
        ASSERT_EQ(3.f, result.y);
        ASSERT_EQ(3.f, result.z);
    }

    TEST(point3d_test, add_vector_test)
    {
        constexpr point3d point1 = {1, 2, 3};
        constexpr vector3d vector1 = {4, 5, 6};

        constexpr point3d result = point1 + vector1;

        ASSERT_EQ(5.f, result.x);
        ASSERT_EQ(7.f, result.y);
        ASSERT_EQ(9.f, result.z);
    }

    TEST(point3d_test, distance_test)
    {
        constexpr point3d point1 = {1, 2, 3};
        constexpr point3d point2 = {4, 5, 6};

        constexpr float result = point1.distance(point2);

        ASSERT_NEAR(5.196f, result, ROUND_THREE_DECIMALS);
    }

    TEST(point3d_test, distance_squared_test)
    {
        constexpr point3d point1 = {1, 2, 3};
        constexpr point3d point2 = {4, 5, 6};

        constexpr float result = point1.distance_squared(point2);

        ASSERT_EQ(27.f, result);
    }
} // namespace testing
