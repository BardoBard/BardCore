#include "pch.h"
#include "BardCore/utility/light.h"
#include "BardCore/math/point3d.h"
#include "BardCore/math/vector3d.h"


namespace testing
{
    TEST(light_test, constructor)
    {
        constexpr bardcore::point3d position(1, 2, 3);
        constexpr double intensity = 100;

        constexpr bardcore::utility::light light(position, intensity);

        EXPECT_EQ(light.position, position); // uses operator== from point3d
        EXPECT_EQ(light.intensity, intensity);
    }

    TEST(light_test, copy_constructor)
    {
        constexpr bardcore::point3d position(1, 2, 3);
        constexpr double intensity = 100;
        constexpr bardcore::utility::light light(position, intensity);

        constexpr bardcore::utility::light light2(light);

        EXPECT_EQ(light2.position, position); // uses operator== from point3d
        EXPECT_EQ(light2.intensity, intensity);
    }

    TEST(light_test, move_constructor)
    {
        constexpr bardcore::point3d position(1, 2, 3);
        constexpr double intensity = 100;
        constexpr bardcore::utility::light light(position, intensity);

        constexpr bardcore::utility::light light2(std::move(light));

        EXPECT_EQ(light2.position, position); // uses operator== from point3d
        EXPECT_EQ(light2.intensity, intensity);
    }

    TEST(light_test, inverse_square_law_point)
    {
        constexpr bardcore::utility::light light(bardcore::point3d(0, 0, 0), 1);
        constexpr bardcore::point3d point(1, 1, 1);

        constexpr double result = light.inverse_square_law(point);

        EXPECT_NEAR(result, 1.0 / 3.0, ROUND_THREE_DECIMALS);
    }

    TEST(light_test, inverse_square_law_length2)
    {
        constexpr bardcore::utility::light light(bardcore::point3d(0, 0, 0), 100);
        constexpr double length = 25;

        constexpr double result = light.inverse_square_law(length);

        EXPECT_NEAR(result, 100.0 / 625.0, ROUND_THREE_DECIMALS);
    }

    TEST(light_test, inverse_square_law_length)
    {
        constexpr bardcore::utility::light light(bardcore::point3d(0, 0, 0), 1);
        constexpr double length = 1;

        constexpr double result = light.inverse_square_law(length);

        EXPECT_NEAR(result, 1.0, ROUND_THREE_DECIMALS);
    }

    TEST(light_test, inverse_square_law_point2)
    {
        constexpr bardcore::utility::light light(bardcore::point3d(-5, 3, 2), 100);
        constexpr bardcore::point3d point(7, 9, -25);

        constexpr double result = light.inverse_square_law(point);

        EXPECT_NEAR(result, 100.0 / 909.0, ROUND_THREE_DECIMALS);
    }

    //exception tests

    TEST(light_test, inverse_square_law_point_exception)
    {
        constexpr bardcore::utility::light light(bardcore::point3d(0, 0, 0), 1);
        constexpr bardcore::point3d point(0, 0, 0);
        constexpr bardcore::point3d point2(1, 1, 1);

        EXPECT_THROW(light.inverse_square_law(point), bardcore::exception::zero_exception);
        EXPECT_NO_THROW(light.inverse_square_law(point2));
    }

    TEST(light_test, inverse_square_law_length_exception)
    {
        constexpr bardcore::utility::light light(bardcore::point3d(0, 0, 0), 1);
        constexpr double length = 0;
        constexpr double length2 = 10;

        EXPECT_THROW(light.inverse_square_law(length), bardcore::exception::zero_exception);
        EXPECT_NO_THROW(light.inverse_square_law(length2));
    }
} // namespace testing
