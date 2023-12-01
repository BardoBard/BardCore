#include "pch.h"

namespace testing
{
    //test 90 degrees
    TEST(math_test, get_degrees_from_radians_test)
    {
        constexpr float degrees = math::get_degrees_from_radians(1.570f);

        ASSERT_NEAR(90.f, degrees, ROUND_ONE_DECIMALS);
    }

    //test zero
    TEST(math_test, get_degrees_from_radians_zero_test)
    {
        constexpr float radians = math::get_radians_from_degrees(0.f);

        ASSERT_NEAR(0.0f, radians, ROUND_ONE_DECIMALS);
    }

    //test negative theta
    TEST(math_test, get_degrees_from_radians_negative_test)
    {
        constexpr float degrees = math::get_degrees_from_radians(-1.570f);

        ASSERT_NEAR(-90.0f, degrees, ROUND_ONE_DECIMALS);
    }

    //test 450 degrees
    TEST(math_test, get_degrees_from_radians_450_test)
    {
        constexpr float degrees = math::get_degrees_from_radians(7.854f);

        ASSERT_NEAR(450.0f, degrees, ROUND_ONE_DECIMALS);
    }

    //test 90 degrees
    TEST(math_test, get_radians_from_degrees_test)
    {
        constexpr float radians = math::get_radians_from_degrees(90.f);

        ASSERT_NEAR(1.57f, radians, ROUND_TWO_DECIMALS);
    }

    //test zero
    TEST(math_test, get_radians_from_degrees_zero_test)
    {
        constexpr float radians = math::get_radians_from_degrees(0.f);

        ASSERT_NEAR(0.0f, radians, ROUND_ONE_DECIMALS);
    }

    //test negative theta
    TEST(math_test, get_radians_from_degrees_negative_test)
    {
        constexpr float radians = math::get_radians_from_degrees(-90.f);

        ASSERT_NEAR(-1.57f, radians, ROUND_TWO_DECIMALS);
    }

    //test 450 degrees
    TEST(math_test, get_radians_from_degrees_450_test)
    {
        constexpr float radians = math::get_radians_from_degrees(450.f);

        ASSERT_NEAR(7.85f, radians, ROUND_TWO_DECIMALS);
    }

    //test sqrt constexpr
    TEST(math_test, sqrt_test)
    {
        constexpr float result = math::sqrt(100);
        constexpr float result2 = math::sqrt(52);
        constexpr float result3 = math::sqrt(100000000000);

        ASSERT_NEAR(10, result, ROUND_ZERO);
        ASSERT_NEAR(7.21, result2, ROUND_TWO_DECIMALS);
        ASSERT_NEAR(316228, result3, ROUND_ONE);
    }
} // namespace testing
