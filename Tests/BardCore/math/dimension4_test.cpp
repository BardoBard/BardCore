#include "pch.h"

#include "BardCore/math/point3d.h"
#include "BardCore/math/imaginary/quaternion.h"

namespace testing
{
    TEST(dimension4_test, point_add_test)
    {
        constexpr quaternion quaternion1 = {1, 2, 3, 4};
        constexpr quaternion quaternion2 = {7, 8, 9, 10};

        ASSERT_EQ(quaternion(8, 10, 12, 14), quaternion1 + quaternion2);
    }

    TEST(dimension4_test, point_add_n_test)
    {
        constexpr quaternion quaternion1 = {1, 2, 3, 4};
        constexpr double n = 5;

        ASSERT_EQ(quaternion(6, 7, 8, 9), quaternion1 + n);
        ASSERT_EQ(quaternion(6, 7, 8, 9), n + quaternion1);
    }

    TEST(dimension4_test, point_add_negative_test)
    {
        constexpr quaternion quaternion1 = {1, -2, 3, 4};
        constexpr quaternion quaternion2 = {-7, 8, -9, 10};

        ASSERT_EQ(quaternion(-6, 6, -6, 14), quaternion1 + quaternion2);
    }

    TEST(dimension4_test, point_add_zero_test)
    {
        constexpr quaternion quaternion1 = {1, 2, 3, 4};
        constexpr quaternion quaternion2 = {0, 0, 0, 0};

        ASSERT_EQ(quaternion(1, 2, 3, 4), quaternion1 + quaternion2);
    }

    TEST(quaternion_test, point_sub_test)
    {
        constexpr quaternion quaternion1 = {1, 2, 3, 4};
        constexpr quaternion quaternion2 = {9, 8, 7, 6};

        ASSERT_EQ(quaternion(-8, -6, -4, -2), quaternion1 - quaternion2);
    }

    TEST(dimension4_test, point_sub_n_test)
    {
        constexpr quaternion quaternion1 = {1, 2, 3, 4};
        constexpr double n = 5;

        ASSERT_EQ(quaternion(-4, -3, -2, -1), quaternion1 - n);
        ASSERT_EQ(quaternion(4, 3, 2, 1), n - quaternion1);
    }

    TEST(dimension4_test, point_sub_negative_test)
    {
        constexpr quaternion quaternion1 = {1, -2, 3, 4};
        constexpr quaternion quaternion2 = {-9, 8, -7, 6};

        ASSERT_EQ(quaternion(10, -10, 10, -2), quaternion1 - quaternion2);
    }

    TEST(dimension4_test, point_sub_zero_test)
    {
        constexpr quaternion quaternion1 = {1, 2, 3, 4};
        constexpr quaternion quaternion2 = {0, 0, 0, 0};

        ASSERT_EQ(quaternion(1, 2, 3, 4), quaternion1 - quaternion2);
    }

    TEST(dimension4_test, point_mul_test)
    {
        constexpr quaternion quaternion1 = {1, 2, 3, 4};

        ASSERT_EQ(quaternion(2, 4, 6, 8), quaternion1 * 2);
    }

    TEST(dimension4_test, point_mul_n_test)
    {
        constexpr quaternion quaternion1 = {1, 2, 3, 4};
        constexpr double n = 5;

        ASSERT_EQ(quaternion(5, 10, 15, 20), quaternion1 * n);
        ASSERT_EQ(quaternion(5, 10, 15, 20), n * quaternion1);
    }

    TEST(dimension4_test, point_mul_negative_test)
    {
        constexpr quaternion quaternion1 = {-1, 2, -3, 4};

        ASSERT_EQ(quaternion(-2, 4, -6, 8), quaternion1 * 2);
    }

    TEST(dimension4_test, point_mul_zero_test)
    {
        constexpr quaternion quaternion1 = {1, 2, 3, 4};

        ASSERT_EQ(quaternion(0, 0, 0, 0), quaternion1 * 0);
    }

    TEST(dimension4_test, point_div_test)
    {
        constexpr quaternion quaternion1 = {1, 2, 3, 4};

        ASSERT_EQ(quaternion(0.5, 1, 1.5, 2), quaternion1 / 2);
    }

    TEST(dimension4_test, point_div_n_test)
    {
        constexpr quaternion quaternion1 = {10, 20, 30, 40};
        constexpr double n = 5;

        ASSERT_EQ(quaternion(2, 4, 6, 8), quaternion1 / n);
    }

    TEST(dimension4_test, point_div_n_exception_test)
    {

        ASSERT_THROW(5 / quaternion(0, 1, 2, 3), bardcore::exception::zero_exception);
        ASSERT_THROW(5 / quaternion(1, 0, 2, 3), bardcore::exception::zero_exception);
        ASSERT_THROW(5 / quaternion(1, 2, 0, 3), bardcore::exception::zero_exception);
        ASSERT_THROW(5 / quaternion(1, 2, 3, 0), bardcore::exception::zero_exception);
        ASSERT_THROW(5 / quaternion(1, 2, 3, 0.00001), bardcore::exception::zero_exception);
        ASSERT_THROW(5 / quaternion(1, 2, -0.00001, 3), bardcore::exception::zero_exception);

        ASSERT_NO_THROW(5 / quaternion(1, 2, 3, 4));
        ASSERT_NO_THROW(5 / quaternion(-1, 2, -3, 4));
        ASSERT_NO_THROW(5 / quaternion(-1, 2, -3, 4));
        ASSERT_NO_THROW(5 / quaternion(-1, 0.0001, 3, 4));
        ASSERT_NO_THROW(5 / quaternion(-1, -0.0001, 3, 4));
    }

    TEST(dimension4_test, point_div_negative_test)
    {
        constexpr quaternion quaternion1 = {-1, 2, -3, 4};

        ASSERT_EQ(quaternion(-0.5, 1, -1.5, 2), quaternion1 / 2);
    }

    TEST(dimension4_test, point_div_zero_test)
    {
        constexpr quaternion quaternion1 = {1, 2, 3, 4};

        ASSERT_THROW(quaternion1 / 0, bardcore::exception::zero_exception);
    }

    TEST(dimension4_test, operator_test)
    {
        constexpr quaternion quaternion1 = {1, 2, 3, 4};
        constexpr quaternion quaternion2 = {1, 2, 3, 4};
        constexpr quaternion quaternion3 = {5, 6, 7, 8};

        ASSERT_TRUE(quaternion1 == quaternion2);
        ASSERT_FALSE(quaternion1 == quaternion3);
        ASSERT_FALSE(quaternion1 != quaternion2);
        ASSERT_TRUE(quaternion1 != quaternion3);
    }

    TEST(dimension4_test, operator2_test)
    {
        quaternion quaternion1 = {1, 2, 3, 4};
        constexpr quaternion quaternion2 = {1, 2, 3, 4};

        ASSERT_EQ(quaternion(1, 2, 3, 4), quaternion1 + 0);
        ASSERT_EQ(quaternion(0, 1, 2, 3), quaternion1 - 1);
        ASSERT_EQ(quaternion(2, 4, 6, 8), quaternion1 * 2);
        ASSERT_EQ(quaternion(0.5, 1, 1.5, 2), quaternion1 / 2);

        ASSERT_EQ(quaternion(2,4,6,8), quaternion1 + quaternion2);
        ASSERT_EQ(quaternion(0, 0, 0, 0), quaternion1 - quaternion2);

        ASSERT_EQ(quaternion(2, 4, 6, 8), quaternion1 += quaternion2);
        ASSERT_EQ(quaternion(1, 2, 3, 4), quaternion1 -= quaternion2);

        ASSERT_EQ(quaternion(2, 4, 6, 8), quaternion1 *= 2);
        ASSERT_EQ(quaternion(1, 2, 3, 4), quaternion1 /= 2);
    }

    TEST(dimension4_test, operator_neg_pos_test)
    {
        quaternion quaternion1 = {1, 2, 3, 4};
        quaternion quaternion2 = {-1, 2, -3, -4};
        quaternion quaternion3 = {0, 2, -3, -4};

        ASSERT_EQ(quaternion(-1, -2, -3, -4), -quaternion1);
        ASSERT_EQ(quaternion(1, 2, 3, 4), quaternion1.abs());

        ASSERT_EQ(quaternion(1, -2, 3, 4), -quaternion2);
        ASSERT_EQ(quaternion(1, 2, 3, 4), quaternion2.abs());

        ASSERT_EQ(quaternion(0, -2, 3, 4), -quaternion3);
        ASSERT_EQ(quaternion(0, 2, 3, 4), quaternion3.abs());
    }

    TEST(dimension4_test, assignment_test)
    {
        quaternion quaternion1 = {1, 2, 3, 4};
        constexpr quaternion quaternion2 = {1, 2, 3, 4};

        ASSERT_EQ(quaternion(1, 2, 3, 4), quaternion1);
        ASSERT_EQ(quaternion(1, 2, 3, 4), quaternion2);

        quaternion1 = quaternion2;

        ASSERT_EQ(quaternion(1, 2, 3, 4), quaternion1);
        ASSERT_EQ(quaternion(1, 2, 3, 4), quaternion2);

        constexpr quaternion quaternion3 = {5, 6, 7, 8};
        quaternion1 = std::move(quaternion3);

        ASSERT_EQ(quaternion(5, 6, 7, 8), quaternion1);
        ASSERT_EQ(quaternion(5, 6, 7, 8), quaternion3);
    }
} // namespace testing
