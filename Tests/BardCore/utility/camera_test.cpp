#include "pch.h"
#include "BardCore/utility/camera.h"

namespace testing
{
    TEST(camera_test, constructor)
    {
        constexpr point3d position{0, 0, 0};
        constexpr vector3d direction{1, 0, 0};
        constexpr unsigned int screen_width = 100;
        constexpr unsigned int screen_height = 100;

        constexpr utility::camera cam{position, direction, screen_width, screen_height};

        EXPECT_EQ(cam.get_position(), position);
        EXPECT_EQ(cam.get_direction(), direction);
        EXPECT_EQ(cam.get_screen_width(), screen_width);
        EXPECT_EQ(cam.get_screen_height(), screen_height);
        EXPECT_EQ(cam.get_fov(), 90);
    }

    TEST(camera_test, constructor_exceptions)
    {
        EXPECT_THROW(utility::camera({0, 0, 0}, {1,1,1}, 1, 0), exception::zero_exception);
        EXPECT_THROW(utility::camera({0, 0, 0}, {1,1,1}, 0, 1), exception::zero_exception);
        EXPECT_THROW(utility::camera({0, 0, 0}, {0,0,0}, 1, 1), exception::zero_exception);
        EXPECT_THROW(utility::camera({0, 0, 0}, {1,1,1}, 1, 1, 0), exception::zero_exception);
        EXPECT_THROW(utility::camera({0, 0, 0}, {1,1,1}, 1, 1, 180), exception::out_of_range_exception);
    }

    TEST(camera_test, setters)
    {
        constexpr point3d position{0, 0, 0};
        constexpr vector3d direction{1, 0, 0};
        constexpr unsigned int screen_width = 100;
        constexpr unsigned int screen_height = 100;
        constexpr unsigned int fov = 90;

        utility::camera cam{position, direction, screen_width, screen_height, fov};

        constexpr point3d new_position{1, 1, 1};
        cam.set_position(new_position);

        constexpr vector3d new_direction = vector3d(1, 1, 1).normalize();
        cam.set_direction(new_direction);

        constexpr unsigned int new_screen_width = 200;
        cam.set_width(new_screen_width);

        constexpr unsigned int new_screen_height = 200;
        cam.set_height(new_screen_height);

        constexpr unsigned int new_fov = 45;
        cam.set_fov(new_fov);

        EXPECT_EQ(cam.get_position(), new_position);
        EXPECT_EQ(cam.get_direction(), new_direction);
        EXPECT_EQ(cam.get_screen_width(), new_screen_width);
        EXPECT_EQ(cam.get_screen_height(), new_screen_height);
        EXPECT_EQ(cam.get_fov(), new_fov);
    }

    TEST(camera_test, setters_exceptions)
    {
        constexpr point3d position{0, 0, 0};
        constexpr vector3d direction{1, 0, 0};
        constexpr unsigned int screen_width = 100;
        constexpr unsigned int screen_height = 100;

        utility::camera cam{position, direction, screen_width, screen_height};

        constexpr vector3d new_direction{0, 0, 0};
        EXPECT_THROW(cam.set_direction(new_direction), exception::zero_exception);

        constexpr unsigned int new_screen_width = 0;
        EXPECT_THROW(cam.set_width(new_screen_width), exception::zero_exception);

        constexpr unsigned int new_screen_height = 0;
        EXPECT_THROW(cam.set_height(new_screen_height), exception::zero_exception);
    }

    TEST(camera_test, shoot_ray)
    {
        constexpr point3d position{-1, 2, 0};
        constexpr vector3d direction{9, 65, 24};
        constexpr unsigned int screen_width = 100;
        constexpr unsigned int screen_height = 100;
        constexpr double distance = 7;
        constexpr unsigned int fov = 120;

        constexpr utility::camera cam = utility::camera(position, direction, screen_width, screen_height, fov);

        constexpr utility::ray ray = cam.shoot_ray(screen_width / 2, screen_height / 2, distance);

        constexpr utility::ray ray2_expected = utility::ray(position, vector3d(-0.261844, 0.66309, 0.701249), 73);
        constexpr utility::ray ray2 = cam.shoot_ray(63, 65, 73);


        EXPECT_EQ(ray, utility::ray(position, direction, distance));
        EXPECT_EQ(ray2, ray2_expected);
    }

    TEST(camera_test, shoot_ray2)
    {
        constexpr point3d position{-1, -2, 5};
        constexpr vector3d direction{7, 23, 7};
        constexpr unsigned int screen_width = 20;
        constexpr unsigned int screen_height = 80;
        constexpr double distance = 50;
        constexpr unsigned int fov = 90;

        constexpr utility::camera cam = utility::camera(position, direction, screen_width, screen_height, fov);

        constexpr auto ray_expected = utility::ray(position, vector3d(0.746306, 0.38265, 0.544615), 50);
        constexpr utility::ray ray = cam.shoot_ray(2, 63, distance);

        EXPECT_EQ(ray, ray_expected);
    }

    TEST(camera_test, shoot_ray_exceptions)
    {
        constexpr point3d position{0, 0, 0};
        constexpr vector3d direction{0, 2, 3};
        constexpr unsigned int screen_width = 100;
        constexpr unsigned int screen_height = 100;
        constexpr double distance = 56;

        constexpr utility::camera cam = utility::camera(position, direction, screen_width, screen_height);

        EXPECT_THROW(cam.shoot_ray(screen_width + 1, screen_height + 1, distance), exception::out_of_range_exception);
        EXPECT_THROW(cam.shoot_ray(screen_width, screen_height, distance), exception::out_of_range_exception);
        EXPECT_NO_THROW(cam.shoot_ray(0, 0, distance));
        EXPECT_NO_THROW(cam.shoot_ray(screen_width - 1, screen_height - 1, distance));
    }
} // namespace testing
