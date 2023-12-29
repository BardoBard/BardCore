#ifndef BARDCORE_CAMERA_H
#define BARDCORE_CAMERA_H

#include <BardCore/bardcore.h>
#include <BardCore/math/vector3d.h>
#include <BardCore/math/point3d.h>
#include <BardCore/utility/ray.h>

namespace bardcore
{
    namespace utility
    {
        /**
         * \brief camera class, used for creating rays through a screen
         */
        class camera
        {
        protected:
            point3d position_; // position of the camera
            vector3d direction_; // normalized direction of the camera

            point3d top_left_;
            vector3d half_horizontal_, half_vertical_; // half of the horizontal and vertical vector

            unsigned int screen_width_{}, screen_height_{}; // screen width and height

        private:
            /**
             * \brief this is a helper function to calculate the screen topleft and horizontal and vertical vectors
             * \note this function is called in the constructor
             */
            constexpr void calculate_screen() noexcept
            {
                vector3d arbitrary_vector = {1, 0, 0}; //random vector
                if (direction_ == arbitrary_vector)
                    arbitrary_vector = {0, 1, 0};
                //other random vector, if direction is the same as the first random vector

                const vector3d cross_factor = direction_.cross(arbitrary_vector).normalize();

                //get center of screen
                const auto center = position_ + direction_;

                //get horizontal and vertical vector
                half_horizontal_ = direction_.cross(cross_factor).normalize();
                half_vertical_ = half_horizontal_.cross(direction_).normalize();

                //get top left corner
                top_left_ = center - half_horizontal_ + half_vertical_;
            }

        public:
            /**
             * \brief constructor for camera (position, direction, width, height)
             * \throws zero_exception if width or height is zero
             * \throws zero_exception if length of direction is zero, e.g if direction is {0, 0, 0}
             * \param position position of the camera
             * \param direction direction of the camera (it will be normalized for you)
             * \param screen_width width of the camera
             * \param screen_height height of the camera
             */
            constexpr camera(const point3d& position, const vector3d& direction, const unsigned int screen_width,
                             const unsigned int screen_height) : position_(position), direction_(direction.normalize()),
                                                                 screen_width_(screen_width),
                                                                 screen_height_(screen_height)
            {
                set_width(screen_width);
                set_height(screen_height);
                calculate_screen();
            }

            /**
             * \brief copy constructor
             * \param other camera to copy
             */
            constexpr camera(const camera& other) : position_(other.position_), direction_(other.direction_),
                                                    top_left_(other.top_left_),
                                                    half_horizontal_(other.half_horizontal_),
                                                    half_vertical_(other.half_vertical_),
                                                    screen_width_(other.screen_width_),
                                                    screen_height_(other.screen_height_)
            {
            }

            /**
             * \brief move constructor
             * \param other camera to move
             */
            constexpr camera(camera&& other) noexcept : position_(std::move(other.position_)),
                                                        direction_(std::move(other.direction_)),
                                                        top_left_(std::move(other.top_left_)),
                                                        half_horizontal_(std::move(other.half_horizontal_)),
                                                        half_vertical_(std::move(other.half_vertical_)),
                                                        screen_width_(std::move(other.screen_width_)),
                                                        screen_height_(std::move(other.screen_height_))
            {
            }

            ~camera() = default;

            /**
             * \brief shoot a ray from the camera through a pixel on the screen
             * \throws out_of_range_exception if x or y is greater than screen width or height
             * \param x x position on the screen
             * \param y y position on the screen
             * \param distance distance of the ray
             */
            NODISCARD constexpr ray shoot_ray(const unsigned int x, const unsigned int y, const float distance) const
            {
                if (x > screen_width_ || y > screen_height_)
                    throw bardcore::exception::out_of_range_exception(
                        "x and y must be smaller or equal to screen width and height");

                //calculate the position on the screen
                const float ratio_width = static_cast<float>(x) / static_cast<float>(screen_width_);
                const float ratio_height = static_cast<float>(y) / static_cast<float>(screen_height_);

                //calculate the position on the screen
                const vector3d horizontal = half_horizontal_ * 2 * ratio_width;
                const vector3d vertical = half_vertical_ * 2 * ratio_height;

                // return ray
                return {position_, position_.get_vector(top_left_ + horizontal - vertical), distance};
            }

            ///////////////////////////////////////////////////////
            ///                 getters/setters                 ///
            ///////////////////////////////////////////////////////

        public:
            NODISCARD constexpr unsigned int get_screen_width() const noexcept { return screen_width_; }
            NODISCARD constexpr unsigned int get_screen_height() const noexcept { return screen_height_; }
            NODISCARD constexpr const point3d& get_position() const noexcept { return position_; }
            NODISCARD constexpr const vector3d& get_direction() const noexcept { return direction_; }

            /**
             * \brief sets the position of the camera
             * \param position new position
             */
            constexpr void set_position(const point3d& position) noexcept
            {
                position_ = position;
                calculate_screen();
            }

            /**
             * \brief sets the direction of the camera
             * \throws zero_exception if length of direction is zero, e.g if direction is {0, 0, 0}
             * \param direction new direction
             */
            constexpr void set_direction(const vector3d& direction)
            {
                direction_ = direction.normalize();
                calculate_screen();
            }

            /**
             * \brief sets the width of the camera
             * \throws zero_exception if width is zero
             * \param width new width
             */
            constexpr void set_width(const unsigned int width)
            {
                if (width == 0)
                    throw exception::zero_exception("width and height must be greater than 0");

                screen_width_ = width;
                calculate_screen();
            }

            /**
             * \brief sets the height of the camera
             * \throws zero_exception if height is zero
             * \param new_height new height
             */
            constexpr void set_height(const unsigned int new_height)
            {
                if (new_height == 0)
                    throw exception::zero_exception("width and height must be greater than 0");

                screen_height_ = new_height;
                calculate_screen();
            }

            ///////////////////////////////////////////////////////
            ///                    operators                    ///
            ///////////////////////////////////////////////////////

            // operators like (+,-,*,/,<,>, etc) are not implemented because they don't make sense for a camera

            /**
             * \brief output operator, prints "{position: (x, y, z), direction: (x, y, z), screen_width: w, screen_height: h}"
             * \param os output stream
             * \param camera camera to output
             * \return output stream "{position: (x, y, z), direction: (x, y, z), screen_width: w, screen_height: h}"
             */
            friend std::ostream& operator<<(std::ostream& os, const camera& camera)
            {
                return os << "{position: " << camera.position_ << ", direction: " << camera.direction_ <<
                    ", screen_width: "
                    << camera.screen_width_ << ", screen_height: " << camera.screen_height_ << "}";
            }

            /**
             * \brief copy assignment operator
             * \param other camera to copy
             * \return this
             */
            camera& operator=(const camera&) = default;

            /**
             * \brief move assignment operator
             * \param other camera to move
             * \return this
             */
            camera& operator=(camera&&) noexcept = default;

            /**
             * \brief equal operator (position, direction, screen width and height are equal)
             * \param left left camera
             * \param right right camera
             * \return true if left == right (position, direction, screen width and height are equal)
             */
            NODISCARD constexpr friend bool operator==(const camera& left, const camera& right) noexcept
            {
                return left.position_ == right.position_
                    && left.direction_ == right.direction_
                    && left.screen_width_ == right.screen_width_
                    && left.screen_height_ == right.screen_height_;
            }

            /**
             * \brief not equal operator (position, direction, screen width or height are not equal)
             * \param left left camera
             * \param right right camera
             * \return true if left != right (position, direction, screen width or height are not equal)
             */
            NODISCARD constexpr friend bool operator!=(const camera& left, const camera& right) noexcept
            {
                return !(left == right);
            }
        };
    } // namespace utility
} // namespace bardcore


#endif //BARDCORE_CAMERA_H
