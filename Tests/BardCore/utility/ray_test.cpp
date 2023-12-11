#include "pch.h"
#include "BardCore/utility/ray.h"

namespace testing
{
    //test constructor
    TEST(ray_test, constructor_test)
    {
        constexpr point3d origin = {1, 2, 3};
        constexpr vector3d direction = {4, 5, 6};
        constexpr float distance = 7;

        constexpr utility::ray ray = {origin, direction, distance};

        ASSERT_EQ(1.f, ray.get_position().x);
        ASSERT_EQ(2.f, ray.get_position().y);
        ASSERT_EQ(3.f, ray.get_position().z);

        //normalize direction
        ASSERT_NEAR(0.456f, ray.get_direction().x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.570f, ray.get_direction().y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.684f, ray.get_direction().z, ROUND_THREE_DECIMALS);

        ASSERT_EQ(7.f, ray.get_distance());
    }

    //test constructor start point, end point
    TEST(ray_test, constructor2_test)
    {
        constexpr point3d origin = {1, -2, 3};
        constexpr point3d end = {-4, 5, -6};

        constexpr utility::ray ray = {origin, end};

        ASSERT_EQ(1.f, ray.get_position().x);
        ASSERT_EQ(-2.f, ray.get_position().y);
        ASSERT_EQ(3.f, ray.get_position().z);

        //normalize direction
        ASSERT_NEAR(-0.402f, ray.get_direction().x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.562f, ray.get_direction().y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(-0.723f, ray.get_direction().z, ROUND_THREE_DECIMALS);

        ASSERT_NEAR(12.45f, ray.get_distance(), ROUND_TWO_DECIMALS);
    }

    //test move constructor
    TEST(ray_test, move_constructor_test)
    {
        constexpr point3d origin = {1, 2, 3};
        constexpr vector3d direction = {4, 5, 6};
        constexpr float distance = 7;

        constexpr utility::ray ray = utility::ray(origin, direction, distance);

        constexpr utility::ray ray1 = std::move(ray);

        ASSERT_EQ(1.f, ray1.get_position().x);
        ASSERT_EQ(2.f, ray1.get_position().y);
        ASSERT_EQ(3.f, ray1.get_position().z);

        //normalize direction
        ASSERT_NEAR(0.456f, ray1.get_direction().x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.570f, ray1.get_direction().y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.684f, ray1.get_direction().z, ROUND_THREE_DECIMALS);

        ASSERT_EQ(7.f, ray1.get_distance());
    }

    //test copy constructor
    TEST(ray_test, copy_constructor_test)
    {
        constexpr point3d origin = {1, 2, 3};
        constexpr vector3d direction = {4, 5, 6};
        constexpr float distance = 7;

        constexpr utility::ray ray = utility::ray(origin, direction, distance);

        constexpr utility::ray ray1 = ray;

        ASSERT_EQ(1.f, ray1.get_position().x);
        ASSERT_EQ(2.f, ray1.get_position().y);
        ASSERT_EQ(3.f, ray1.get_position().z);

        //normalize direction
        ASSERT_NEAR(0.456f, ray1.get_direction().x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.570f, ray1.get_direction().y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.684f, ray1.get_direction().z, ROUND_THREE_DECIMALS);

        ASSERT_EQ(7.f, ray1.get_distance());
    }

    //test assignment operator
    TEST(ray_test, assignment_operator_test)
    {
        constexpr point3d origin = {1, 2, 3};
        constexpr vector3d direction = {4, 5, 6};
        constexpr float distance = 7;

        constexpr utility::ray ray = utility::ray(origin, direction, distance);

        utility::ray ray1 = utility::ray(vector3d::up());

        ray1 = ray;

        ASSERT_EQ(1.f, ray1.get_position().x);
        ASSERT_EQ(2.f, ray1.get_position().y);
        ASSERT_EQ(3.f, ray1.get_position().z);

        //normalize direction
        ASSERT_NEAR(0.456f, ray1.get_direction().x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.570f, ray1.get_direction().y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.684f, ray1.get_direction().z, ROUND_THREE_DECIMALS);

        ASSERT_EQ(7.f, ray1.get_distance());
    }

    //test move assignment operator
    TEST(ray_test, move_assignment_operator_test)
    {
        constexpr point3d origin = {1, 2, 3};
        constexpr vector3d direction = {4, 5, 6};
        constexpr float distance = 7;

        utility::ray ray = utility::ray(origin, direction, distance);

        utility::ray ray1 = utility::ray(vector3d::up());

        std::swap(ray1, ray);

        ASSERT_EQ(1.f, ray1.get_position().x);
        ASSERT_EQ(2.f, ray1.get_position().y);
        ASSERT_EQ(3.f, ray1.get_position().z);

        //normalize direction
        ASSERT_NEAR(0.456f, ray1.get_direction().x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.570f, ray1.get_direction().y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.684f, ray1.get_direction().z, ROUND_THREE_DECIMALS);

        ASSERT_EQ(7.f, ray1.get_distance());
    }


    TEST(ray_test, constructor_throw_test)
    {
        constexpr point3d origin = {1, 2, 3};
        constexpr vector3d direction = {4, 5, 6};
        constexpr float distance = -7;

        //negative distance
        ASSERT_THROW(utility::ray(origin, direction, distance), exceptions::negative_exception);


        //same points, which causes zero direction vector
        constexpr point3d end = {1, 2, 3};

        ASSERT_THROW(utility::ray(origin, end), exceptions::zero_exception);


        //zero direction vector
        constexpr vector3d zero_direction = vector3d::zero();

        ASSERT_THROW(utility::ray(origin, zero_direction, 0), exceptions::zero_exception);
    }

    //test setters
    TEST(ray_test, setters_test)
    {
        constexpr point3d origin = {1, 2, 3};
        constexpr vector3d direction = {4, 5, 6};
        constexpr float distance = 7;

        utility::ray ray = utility::ray(vector3d::up());

        ray.set_position(origin);
        ray.set_direction(direction);
        ray.set_distance(distance);

        ASSERT_EQ(1.f, ray.get_position().x);
        ASSERT_EQ(2.f, ray.get_position().y);
        ASSERT_EQ(3.f, ray.get_position().z);

        //normalize direction
        ASSERT_NEAR(0.456f, ray.get_direction().x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.570f, ray.get_direction().y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.684f, ray.get_direction().z, ROUND_THREE_DECIMALS);

        ASSERT_EQ(7.f, ray.get_distance());
    }

    //test setter throw
    TEST(ray_test, setters_throw_test)
    {
        constexpr float distance = -1;
        constexpr float distance1 = -9;
        constexpr float distance2 = -2;

        utility::ray ray = utility::ray(vector3d::up());

        ASSERT_THROW(ray.set_distance(distance), exceptions::negative_exception);
        ASSERT_THROW(ray.set_distance(distance1), exceptions::negative_exception);
        ASSERT_THROW(ray.set_distance(distance2), exceptions::negative_exception);
    }

    //test within range
    TEST(ray_test, within_range_test)
    {
        constexpr point3d origin = {1, 2, 3};
        constexpr vector3d direction = {4, 5, 6};
        constexpr float distance = 7;

        constexpr utility::ray ray = {origin, direction, distance};

        //within range

        constexpr point3d within_range = {1, 2, 3};
        constexpr point3d within_range1 = {0, 0, 0};

        ASSERT_TRUE(ray.within_range(within_range));
        ASSERT_TRUE(ray.within_range(within_range1));

        //not within range

        constexpr point3d not_within_range = {8, 8, 8};
        constexpr point3d not_within_range1 = {5, 7, 9};

        ASSERT_FALSE(ray.within_range(not_within_range1));
        ASSERT_FALSE(ray.within_range(not_within_range));
    }

    //test within range throws
    TEST(ray_test, within_range_throw_test)
    {
        constexpr point3d origin = {1, 2, 3};
        constexpr vector3d direction = {4, 5, 6};
        constexpr float distance = 50;

        constexpr utility::ray ray = {origin, direction, distance};

        ASSERT_THROW(ray.within_range(-1), exceptions::negative_exception);
        ASSERT_THROW(ray.within_range(-10), exceptions::negative_exception);
    }

    //test get point
    TEST(ray_test, get_point_test)
    {
        constexpr point3d origin = {1, 2, 3};
        constexpr vector3d direction = {4, 5, 6};
        constexpr float distance = 7;

        constexpr utility::ray ray = {origin, direction, distance};

        //get point
#ifdef CXX17 // C++17 or higher (using optional instead of unique_ptr)
        const std::optional<point3d> point = ray.get_point(0);
        const std::optional<point3d> point1 = ray.get_point(1);
        const std::optional<point3d> point2 = ray.get_point(2);
        const std::optional<point3d> point3 = ray.get_point(10);

        ASSERT_TRUE(point.has_value());
        ASSERT_TRUE(point1.has_value());
        ASSERT_TRUE(point2.has_value());

        ASSERT_FALSE(point3.has_value());
        
#else // smaller than C++17 (using unique_ptr instead of optional)
        const std::unique_ptr<point3d> point = ray.get_point(0);
        const std::unique_ptr<point3d> point1 = ray.get_point(1);
        const std::unique_ptr<point3d> point2 = ray.get_point(2);
        const std::unique_ptr<point3d> point3 = ray.get_point(10);

        ASSERT_TRUE(point != nullptr);
        ASSERT_TRUE(point1 != nullptr);
        ASSERT_TRUE(point2 != nullptr);
        
        ASSERT_TRUE(point3 == nullptr);
#endif // CXX17


        ASSERT_NEAR(1.f, point->x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(2.f, point->y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(3.f, point->z, ROUND_THREE_DECIMALS);

        ASSERT_NEAR(1.456f, point1->x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(2.570f, point1->y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(3.684f, point1->z, ROUND_THREE_DECIMALS);

        ASSERT_NEAR(1.912f, point2->x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(3.140f, point2->y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(4.368f, point2->z, ROUND_THREE_DECIMALS);
    }

    //test get point throws
    TEST(ray_test, get_point_throw_test)
    {
        constexpr point3d origin = {1, 2, 3};
        constexpr vector3d direction = {4, 5, 6};
        constexpr float distance = 7;

        constexpr utility::ray ray = {origin, direction, distance};

        ASSERT_THROW(ray.get_point(-1), exceptions::negative_exception);
        ASSERT_THROW(ray.get_point(-10), exceptions::negative_exception);
    }
} // namespace testing
