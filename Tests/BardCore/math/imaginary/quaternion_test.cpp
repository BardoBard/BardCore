#include "pch.h"
#include "BardCore/math/imaginary/quaternion.h"
#include "BardCore/math/point3d.h"

namespace testing
{
    TEST(quaternion_test, multiplication_test)
    {
        constexpr quaternion quaternion1 = {1, 2, 3, 4};
        constexpr quaternion quaternion2 = {5, 6, 7, 8};

        constexpr quaternion result = quaternion1.multiply(quaternion2);

        ASSERT_EQ(-60.0, result.get_real());
        ASSERT_EQ(12.0, result.get_i());
        ASSERT_EQ(30.0, result.get_j());
        ASSERT_EQ(24.0, result.get_k());
    }

    TEST(quaternion_test, multiplication2_test)
    {
        constexpr quaternion quaternion1 = {-56, 0, 2, 1};
        constexpr quaternion quaternion2 = {9, -3, 0, 9};

        constexpr quaternion result = quaternion1.multiply(quaternion2);

        ASSERT_EQ(-513.0, result.get_real());
        ASSERT_EQ(186.0, result.get_i());
        ASSERT_EQ(15.0, result.get_j());
        ASSERT_EQ(-489.0, result.get_k());
    }

    TEST(quaternion_test, rotation_point_vector_theta_test)
    {
        constexpr vector3d vector = {1, 2, 3};
        constexpr point3d point = {4, 5, 6};
        constexpr double theta = 90.0;

        const point3d result = quaternion::rotate_degrees(point, vector, theta);


        ASSERT_NEAR(3.087, result.x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(2.968, result.y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(7.659, result.z, ROUND_THREE_DECIMALS);
    }

    TEST(quaternion_test, rotation_point_vector_theta_test2)
    {
        constexpr vector3d vector = {1, 2, 3};
        constexpr point3d point = {4, 5, 6};
        constexpr double theta = 180.0;

        const point3d result = quaternion::rotate_degrees(point, vector, theta);

        ASSERT_NEAR(0.571, result.x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(4.143, result.y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(7.714, result.z, ROUND_THREE_DECIMALS);
    }

    TEST(quaternion_test, rotation_point_vector_zero_theta_test)
    {
        constexpr vector3d vector = {1, 2, 3};
        constexpr point3d point = {4, 5, 6};
        constexpr double theta = 0;

        constexpr point3d result = quaternion::rotate_degrees(point, vector, theta);


        ASSERT_NEAR(4, result.x, ROUND_EPSILON);
        ASSERT_NEAR(5, result.y, ROUND_EPSILON);
        ASSERT_NEAR(6, result.z, ROUND_EPSILON);
    }

    TEST(quaternion_test, rotation_vector_theta_test)
    {
        constexpr vector3d rotation_vector = {1, 2, 3};
        constexpr vector3d vector = {4, 5, 6};
        constexpr double theta = 270.0;

        constexpr vector3d result = quaternion::rotate_degrees(vector, rotation_vector, theta);

        ASSERT_NEAR(1.484, result.x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(6.175, result.y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(6.055, result.z, ROUND_THREE_DECIMALS);
    }

    TEST(quaternion_test, rotation_vector_theta_test2)
    {
        constexpr vector3d rotation_vector = {1, 2, 3};
        constexpr vector3d vector = {4, 5, 6};
        constexpr double theta = 360.0;

        constexpr vector3d result = quaternion::rotate_degrees(vector, rotation_vector, theta);

        ASSERT_NEAR(4, result.x, ROUND_ONE_DECIMALS);
        ASSERT_NEAR(5, result.y, ROUND_ONE_DECIMALS);
        ASSERT_NEAR(6, result.z, ROUND_ONE_DECIMALS);
    }

    //test zero theta
    TEST(quaternion_test, rotation_vector_zero_theta_test2)
    {
        constexpr vector3d rotation_vector = {1, 2, 3};
        constexpr vector3d vector = {4, 5, 6};
        constexpr double theta = 0;

        constexpr vector3d result = quaternion::rotate_degrees(vector, rotation_vector, theta);

        ASSERT_NEAR(4, result.x, ROUND_EPSILON);
        ASSERT_NEAR(5, result.y, ROUND_EPSILON);
        ASSERT_NEAR(6, result.z, ROUND_EPSILON);
    }

    //test negative theta
    TEST(quaternion_test, rotation_vector_negative_theta_test)
    {
        constexpr vector3d rotation_vector = {1, 2, 3};
        constexpr vector3d vector = {4, 5, 6};
        constexpr double theta = -90.0;

        constexpr vector3d result = quaternion::rotate_degrees(vector, rotation_vector, theta);

        ASSERT_NEAR(1.484, result.x, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(6.175, result.y, ROUND_THREE_DECIMALS);
        ASSERT_NEAR(6.055, result.z, ROUND_THREE_DECIMALS);
    }

    //test exception
    TEST(quaternion_test, rotation_exception_test)
    {
        constexpr vector3d rotation_vector = {0, 0, 0};
        constexpr vector3d vector = {4, 5, 6};
        constexpr double theta = 90.0;

        ASSERT_THROW(quaternion::rotate_degrees(vector, rotation_vector, theta), exception::zero_exception);
    }

    //test exception
    TEST(quaternion_test, rotation_exception_test2)
    {
        constexpr vector3d rotation_vector = {1, 2, 3};
        constexpr vector3d vector = {0, 0, 0};
        constexpr double theta = 90.0;

        ASSERT_THROW(quaternion::rotate_degrees(vector, rotation_vector, theta), exception::zero_exception);
    }
    
    //test conjugate
    TEST(quaternion_test, conjugate_test)
    {
        constexpr quaternion quaternion1 = {1, 2, 3, 4};

        constexpr quaternion result = quaternion1.conjugate();

        ASSERT_NEAR(1.0, result.get_real(), ROUND_EPSILON);
        ASSERT_NEAR(-2.0, result.get_i(), ROUND_EPSILON);
        ASSERT_NEAR(-3.0, result.get_j(), ROUND_EPSILON);
        ASSERT_NEAR(-4.0, result.get_k(), ROUND_EPSILON);
    }

    //test conjugate
    TEST(quaternion_test, conjugate_test2)
    {
        constexpr quaternion quaternion1 = {0, 0, 0, 0};

        constexpr quaternion result = quaternion1.conjugate();

        ASSERT_NEAR(0.0, result.get_real(), ROUND_EPSILON);
        ASSERT_NEAR(0.0, result.get_i(), ROUND_EPSILON);
        ASSERT_NEAR(0.0, result.get_j(), ROUND_EPSILON);
        ASSERT_NEAR(0.0, result.get_k(), ROUND_EPSILON);
    }

    //test mirror
    TEST(quaternion_test, mirror_test)
    {
        constexpr vector3d mirror_vector = {1, 2, 3};
        constexpr point3d point = {4, 5, 6};

        constexpr point3d result = quaternion::mirror(point, mirror_vector);

        ASSERT_NEAR(0.57, result.x, ROUND_TWO_DECIMALS);
        ASSERT_NEAR(4.14, result.y, ROUND_TWO_DECIMALS);
        ASSERT_NEAR(7.71, result.z, ROUND_TWO_DECIMALS);
    }

    //test mirror
    TEST(quaternion_test, mirror_test2)
    {
        constexpr vector3d mirror_vector = {0, -2, -1};
        constexpr point3d point = {-9, 8, -7};

        constexpr point3d result = quaternion::mirror(point, mirror_vector);

        ASSERT_NEAR(9.0, result.x, ROUND_EPSILON);
        ASSERT_NEAR(-0.8, result.y, ROUND_ONE_DECIMALS);
        ASSERT_NEAR(10.6, result.z, ROUND_ONE_DECIMALS);
    }

    //test mirror zero
    TEST(quaternion_test, mirror_zero_test)
    {
        constexpr vector3d mirror_vector = {0, 0, 0};
        constexpr point3d point = {4, 5, 6};

        ASSERT_THROW(quaternion::mirror(point, mirror_vector), exception::zero_exception);
    }

    //test mirror zero
    TEST(quaternion_test, mirror_zero_test2)
    {
        constexpr vector3d mirror_vector = {1, 2, 3};
        constexpr point3d point = {0, 0, 0};

        ASSERT_THROW(quaternion::mirror(point, mirror_vector), exception::zero_exception);
    }
} // namespace testing
