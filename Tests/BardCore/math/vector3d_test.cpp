#include "pch.h"
#include "BardCore/math/vector3d.h"

#include "BardCore/math/imaginary/quaternion.h"

namespace testing
{
    //test angle
    TEST(vector3d_test, angle_test)
    {
        constexpr vector3d vector1 = {1, 2, 3};
        constexpr vector3d vector2 = {4, 5, 6};

        const double result_degrees = vector1.angle_degrees(vector2);
        const double result_radians = vector1.angle_radians(vector2);
        constexpr double result_dot = vector1.angle_dot(vector2);

        ASSERT_NEAR(12.94, result_degrees, ROUND_TWO_DECIMALS);
        ASSERT_NEAR(0.226, result_radians, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.974, result_dot, ROUND_THREE_DECIMALS);
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

        constexpr double result = vector1.dot(vector2);

        ASSERT_EQ(32.0, result);
    }

    //test dot with negative result
    TEST(vector3d_test, dot_negative_test)
    {
        constexpr vector3d vector1 = {1, 2, 3};
        constexpr vector3d vector2 = {-4, -5, -6};

        constexpr double result = vector2.dot(vector1);

        ASSERT_EQ(-32.0, result);
    }

    //test dot with zero
    TEST(vector3d_test, dot_zero_test)
    {
        constexpr vector3d vector1 = {1, 2, 3};
        constexpr vector3d vector2 = {0, 0, 0};

        constexpr double result = vector1.dot(vector2);

        ASSERT_EQ(0.0, result);
    }

    //lenght test
    TEST(vector3d_test, length_test)
    {
        constexpr vector3d vector1 = {1, 2, 3};

        constexpr double result = vector1.length();

        ASSERT_NEAR(3.742, result, ROUND_THREE_DECIMALS);
    }

    //test length with negative input
    TEST(vector3d_test, length_negative_test)
    {
        constexpr vector3d vector1 = {-1, -2, -3};

        constexpr double result = vector1.length();

        ASSERT_NEAR(3.742, result, ROUND_THREE_DECIMALS);
    }

    //test length with zero
    TEST(vector3d_test, length_zero_test)
    {
        constexpr vector3d vector1 = {0, 0, 0};

        constexpr double result = vector1.length();

        ASSERT_EQ(0.0, result);
    }


    //normalize test 1
    TEST(vector3d_test, normalize_test)
    {
        constexpr vector3d vector1 = {3, 2, -1};

        constexpr vector3d result = vector1.normalize();

        ASSERT_NEAR(0.802, result.x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.535, result.y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(-0.267, result.z, ROUND_THREE_DECIMALS);
    }

    //normalize test with negative input
    TEST(vector3d_test, normalize_negative_test)
    {
        constexpr vector3d vector1 = {-3, -2, 1};

        constexpr vector3d result = vector1.normalize();

        ASSERT_NEAR(-0.802, result.x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(-0.535, result.y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.267, result.z, ROUND_THREE_DECIMALS);
    }

    //normalize test 2
    TEST(vector3d_test, normalize2_test)
    {
        constexpr vector3d vector1 = {-0.834, -0.653, -0.127};

        constexpr vector3d result = vector1.normalize();

        ASSERT_NEAR(-0.782, result.x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(-0.612, result.y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(-0.119, result.z, ROUND_THREE_DECIMALS);
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
        double result = vector1.angle_degrees(vector2);
        ASSERT_NEAR(15.09, result, ROUND_TWO_DECIMALS);

        result = vector1.angle_radians(vector2);
        ASSERT_NEAR(0.263, result, ROUND_THREE_DECIMALS);

        result = vector1.angle_dot(vector2);
        ASSERT_NEAR(0.966, result, ROUND_THREE_DECIMALS);

        //dot
        result = vector1.dot(vector3);
        ASSERT_EQ(6950.0, result);

        //length
        result = vector1.length();
        ASSERT_NEAR(95.567, result, ROUND_THREE_DECIMALS);

        //length
        result = vector3.length();
        ASSERT_NEAR(92.309, result, ROUND_THREE_DECIMALS);

        //normalize
        constexpr vector3d result_normalize = vector1.normalize();

        ASSERT_NEAR(0.471, result_normalize.x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.335, result_normalize.y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(0.816, result_normalize.z, ROUND_THREE_DECIMALS);
    }

    //reflection
    TEST(vector3d_test, reflection_test)
    {
        constexpr vector3d vector1 = {1, 2, 3};
        constexpr vector3d vector2 = {0, 0, 1};

        const auto result = vector1.reflection(vector2);

        ASSERT_NEAR(-1.0, result->x, ROUND_ONE_DECIMALS);
        ASSERT_NEAR(-2.0, result->y, ROUND_ONE_DECIMALS);
        ASSERT_NEAR(3.0, result->z, ROUND_ONE_DECIMALS);
    }

    //reflection with negative input
    TEST(vector3d_test, reflection_negative_test)
    {
        constexpr vector3d vector1 = {-1, 2, -3};
        constexpr vector3d vector2 = {-4, -5, 6};

        const auto result = vector1.reflection(vector2);

        ASSERT_FALSE(result);
    }

    TEST(vector3d_test, refraction_test)
    {
        constexpr vector3d l = {0.707107, -0.707107, 0.0};
        constexpr vector3d n = {0.0, 1.0, 0.0};
        constexpr double refractive_ratio = 0.9;
        const auto result = l.refraction(n, refractive_ratio);

        ASSERT_EQ(vector3d(0.636396, -0.771363, 0.0), *result);
        ASSERT_EQ(vector3d(0.636396, -0.771363, 0.0), *l.refraction(n, refractive_ratio));
    }

    TEST(vector3d_test, refraction_internal_reflection_test)
    {
        constexpr vector3d l = {1.191752, 1, 0}; // 50 degrees
        constexpr vector3d n = {0.0, 1.0, 0.0};
        constexpr double refractive_ratio = 1.333; // ratio for internal reflection
        constexpr double refractive_ratio_2 = 1.2; // ratio for refraction

        ASSERT_FALSE(l.refraction(n, refractive_ratio));

        ASSERT_TRUE(math::equals(l.refraction(n, refractive_ratio_2)->length(), 1));
        ASSERT_EQ(vector3d(0.919253, -0.393668, 0), *l.refraction(n, refractive_ratio_2));
    }

    TEST(vector3d_test, refraction_exception_test)
    {
        constexpr vector3d l = {1, 2, 3};
        constexpr vector3d n = {0.0, 1.0, 0.0};

        constexpr vector3d zero_n = {0.0, 0.0, 0.0};
        constexpr double negative_refractive_ratio = -0.9;
        constexpr double zero_refractive_ratio = 0;

        ASSERT_THROW(l.refraction(n, negative_refractive_ratio), exception::negative_exception);
        ASSERT_THROW(l.refraction(n, zero_refractive_ratio), exception::zero_exception);
        ASSERT_THROW(l.refraction(zero_n, 0.9), exception::zero_exception);
    }
} // namespace testing
