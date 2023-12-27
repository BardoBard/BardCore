#include "pch.h"
#include "BardCore/math/vector3d.h"

namespace testing
{
    //test angle
    TEST(vector3d_test, angle_test)
    {
        constexpr vector3d vector1 = {1, 2, 3};
        constexpr vector3d vector2 = {4, 5, 6};

        const float result_degrees = vector1.angle_degrees(vector2);
        const float result_radians = vector1.angle_radians(vector2);
        constexpr float result_dot = vector1.angle_dot(vector2);

        ASSERT_NEAR(12.94f, result_degrees, ROUND_TWO_DECIMALS);
        ASSERT_NEAR(0.226f, result_radians, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.974f, result_dot, ROUND_THREE_DECIMALS);
    }

    //test angle with zero
    TEST(vector3d_test, angle_zero_test)
    {
        constexpr vector3d vector1 = {1, 2, 3};
        constexpr vector3d vector2 = {0, 0, 0};

        ASSERT_THROW(vector1.angle_degrees(vector2), exception::bard_exception);
        ASSERT_THROW(vector1.angle_radians(vector2), exception::bard_exception);
        ASSERT_THROW(vector1.angle_dot(vector2), exception::bard_exception);
    }

    //test angle with same vector
    TEST(vector3d_test, angle_same_vector_test)
    {
        constexpr vector3d vector1 = {1, 2, 3};
        constexpr vector3d vector2 = {1, 2, 3};
        ASSERT_NO_THROW(vector1.angle_degrees(vector2));
        ASSERT_NO_THROW(vector1.angle_radians(vector2));
        ASSERT_NO_THROW(vector1.angle_dot(vector2));
    }

    //test angle with same object
    TEST(vector3d_test, angle_same_object_test)
    {
        constexpr vector3d vector1 = {1, 2, 3};

        ASSERT_THROW(vector1.angle_degrees(vector1), exception::bard_exception);
        ASSERT_THROW(vector1.angle_radians(vector1), exception::bard_exception);
        ASSERT_THROW(vector1.angle_dot(vector1), exception::bard_exception);
    }

    //test dot
    TEST(vector3d_test, dot_test)
    {
        constexpr vector3d vector1 = {1, 2, 3};
        constexpr vector3d vector2 = {4, 5, 6};

        constexpr float result = vector1.dot(vector2);

        ASSERT_EQ(32.f, result);
    }

    //test dot with negative result
    TEST(vector3d_test, dot_negative_test)
    {
        constexpr vector3d vector1 = {1, 2, 3};
        constexpr vector3d vector2 = {-4, -5, -6};

        constexpr float result = vector2.dot(vector1);

        ASSERT_EQ(-32.f, result);
    }

    //test dot with zero
    TEST(vector3d_test, dot_zero_test)
    {
        constexpr vector3d vector1 = {1, 2, 3};
        constexpr vector3d vector2 = {0, 0, 0};

        constexpr float result = vector1.dot(vector2);

        ASSERT_EQ(0.f, result);
    }

    //lenght test
    TEST(vector3d_test, length_test)
    {
        constexpr vector3d vector1 = {1, 2, 3};

        constexpr float result = vector1.length();

        ASSERT_NEAR(3.742f, result, ROUND_THREE_DECIMALS);
    }

    //test length with negative input
    TEST(vector3d_test, length_negative_test)
    {
        constexpr vector3d vector1 = {-1, -2, -3};

        constexpr float result = vector1.length();

        ASSERT_NEAR(3.742f, result, ROUND_THREE_DECIMALS);
    }

    //test length with zero
    TEST(vector3d_test, length_zero_test)
    {
        constexpr vector3d vector1 = {0, 0, 0};

        constexpr float result = vector1.length();

        ASSERT_EQ(0.f, result);
    }


    //normalize test 1
    TEST(vector3d_test, normalize_test)
    {
        constexpr vector3d vector1 = {3, 2, -1};

        constexpr vector3d result = vector1.normalize();

        ASSERT_NEAR(0.802f, result.x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.535f, result.y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(-0.267f, result.z, ROUND_THREE_DECIMALS);
    }

    //normalize test with negative input
    TEST(vector3d_test, normalize_negative_test)
    {
        constexpr vector3d vector1 = {-3, -2, 1};

        constexpr vector3d result = vector1.normalize();

        ASSERT_NEAR(-0.802f, result.x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(-0.535f, result.y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.267f, result.z, ROUND_THREE_DECIMALS);
    }

    //normalize test 2
    TEST(vector3d_test, normalize2_test)
    {
        constexpr vector3d vector1 = {-0.834f, -0.653f, -0.127f};

        constexpr vector3d result = vector1.normalize();

        ASSERT_NEAR(-0.782f, result.x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(-0.612f, result.y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(-0.119f, result.z, ROUND_THREE_DECIMALS);
    }

    //normalize test with zero
    TEST(vector3d_test, normalize_zero_test)
    {
        constexpr vector3d vector1 = {0, 0, 0};
        ASSERT_ANY_THROW(vector1.normalize());
    }

    //all tests
    TEST(vector3d_test, all_test)
    {
        constexpr vector3d vector1 = {45, 32, 78}; //original vector 
        constexpr vector3d vector2 = {14, 26, 52}; //used for angle calculations
        constexpr vector3d vector3 = {12, 76, 51}; //used for dot product

        //angle
        float result = vector1.angle_degrees(vector2);
        ASSERT_NEAR(15.09f, result, ROUND_TWO_DECIMALS);

        result = vector1.angle_radians(vector2);
        ASSERT_NEAR(0.263f, result, ROUND_THREE_DECIMALS);

        result = vector1.angle_dot(vector2);
        ASSERT_NEAR(0.966f, result, ROUND_THREE_DECIMALS);

        //dot
        result = vector1.dot(vector3);
        ASSERT_EQ(6950.f, result);

        //length
        result = vector1.length();
        ASSERT_NEAR(95.567f, result, ROUND_THREE_DECIMALS);

        //length
        result = vector3.length();
        ASSERT_NEAR(92.309f, result, ROUND_THREE_DECIMALS);

        //normalize
        constexpr vector3d result_normalize = vector1.normalize();

        ASSERT_NEAR(0.471f, result_normalize.x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.335f, result_normalize.y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.816f, result_normalize.z, ROUND_THREE_DECIMALS);
    }

    //reflection
    TEST(vector3d_test, reflection_test)
    {
        constexpr vector3d vector1 = {1, 2, 3};
        constexpr vector3d vector2 = {0, 0, 1};

        const auto result = vector1.reflection(vector2);

        ASSERT_NEAR(-1.f, result->x, ROUND_ONE_DECIMALS);
        ASSERT_NEAR(-2.f, result->y, ROUND_ONE_DECIMALS);
        ASSERT_NEAR(3.f, result->z, ROUND_ONE_DECIMALS);
    }

    //reflection with negative input
    TEST(vector3d_test, reflection_negative_test)
    {
        constexpr vector3d vector1 = {-1, 2, -3};
        constexpr vector3d vector2 = {-4, -5, 6};

        const auto result = vector1.reflection(vector2);

#if defined(CXX17)
        ASSERT_FALSE(result.has_value());
#elif defined(CXX14)
        ASSERT_EQ(nullptr, result);
#endif
    }
} // namespace testing
