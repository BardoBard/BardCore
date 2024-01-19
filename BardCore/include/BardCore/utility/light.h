#pragma once

#include "BardCore/math/point3d.h"

namespace bardcore
{
    namespace utility
    {
        /**
         * \brief light class, used for lighting, e.g. in raytracing
         */
        class light
        {
        public:
            /**
             * \brief position of the light
             */
            point3d position;

            /**
             * \brief intensity of the light
             */
            double intensity;

        public:
            /**
             * \brief constructor for light
             * \param position origin of the light
             * \param intensity intensity of the light
             */
            constexpr light(const point3d& position, const double intensity) : position(position), intensity(intensity)
            {
            }

            /**
             * \brief copy constructor
             * \param light light to copy
             */
            constexpr light(const light& light) noexcept : position(light.position), intensity(light.intensity)
            {
            }

            /**
             * \brief move constructor
             * \note intensity is copied instead of moved, because it is a primitive type
             * \param light light to move
             */
            constexpr light(light&& light) noexcept : position(std::move(light.position)), intensity(light.intensity)
            {
            }

            ~light() = default;

        private:
            /**
             * \brief this is a helper function for calculating the inverse square law
             * \note read more at: https://en.wikipedia.org/wiki/Inverse-square_law
             * \throws zero_exception if length is zero
             * \param length_squared length squared, e.g. length * length
             * \return intensity across distance
             */
            NODISCARD constexpr double inverse_square_law_squared(const double length_squared) const
            {
                if (length_squared <= 0)
                    throw exception::zero_exception("length must not be zero");

                return intensity / length_squared;
            }

        public:
            /**
             * \brief inverse square law
             * \note read more at: https://en.wikipedia.org/wiki/Inverse-square_law
             * \throws zero_exception if distance between point and light_position is zero
             * \param point point to calculate
             * \return intensity across distance
             */
            NODISCARD constexpr double inverse_square_law(const point3d& point) const
            {
                return inverse_square_law_squared(position.distance_squared(point));
            }

            /**
             * \brief inverse square law
             * \note read more at: https://en.wikipedia.org/wiki/Inverse-square_law
             * \throws zero_exception if length is zero
             * \param length length to calculate
             * \return intensity across distance
             */
            NODISCARD constexpr double inverse_square_law(const double length) const
            {
                return inverse_square_law_squared(length * length);
            }

            ///////////////////////////////////////////////////////
            ///                    operators                    ///
            ///////////////////////////////////////////////////////

            // operators like (+,-,*,/,<,>, etc) are not implemented because they don't make sense for a light

            /**
             * \brief output operator, prints "{position: (x, y, z), intensity: i}"
             * \param os output stream
             * \param light light to output
             * \return output stream "{position: (x, y, z), intensity: i}"
             */
            friend std::ostream& operator<<(std::ostream& os, const light& light)
            {
                return os << "{position: " << light.position << ", intensity: " << light.intensity << "}";
            }

            /**
             * \brief copy assignment
             * \param light light to copy
             * \return reference to this
             */
            light& operator=(const light& light) noexcept = default;

            /**
             * \brief move assignment
             * \param light light to move
             * \return reference to this
             */
            light& operator=(light&& light) noexcept = default;


            /**
             * \brief equal operator (position, intensity are equal)
             * \param left left light
             * \param right right light
             * \return true if left == right (position, intensity are equal)
             */
            NODISCARD constexpr friend bool operator==(const light& left, const light& right) noexcept
            {
                return left.position == right.position
                    && math::equals(left.intensity, right.intensity);
            }

            /**
             * \brief not equal operator (position or intensity are not equal)
             * \param left left light
             * \param right right light
             * \return true if left != right (position or intensity are not equal)
             */
            NODISCARD constexpr friend bool operator!=(const light& left, const light& right) noexcept
            {
                return !(left == right);
            }
        };
    } // namespace bardcore::utility
} // namespace bardcore
