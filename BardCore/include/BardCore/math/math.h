#ifndef BARDCORE_MATH_H
#define BARDCORE_MATH_H

#include "../bardcore.h"

namespace bardcore
{
    class math
    {
    private:
        /// \brief helper function for calculating the square root via Newton-Raphson 
        /// \note credit: Alex Shtoff - https://stackoverflow.com/questions/8622256/in-c11-is-sqrt-defined-as-constexpr
        /// \param value value to calculate the square root from
        /// \param curr current value
        /// \param prev previous value
        /// \return square root of value
        constexpr NODISCARD static float sqrt_newton_raphson(const float value, const float curr, const float prev)
        {
            return curr == prev
                       ? curr
                       : sqrt_newton_raphson(value, 0.5f * (curr + value / curr), curr);
        }

    public:
        INLINE static constexpr float pi = 3.14159265358979323846f;

        constexpr NODISCARD static float get_degrees_from_radians(const float radians)
        {
            return radians * 180.0f / math::pi;
        }

        constexpr NODISCARD static float get_radians_from_degrees(const float degrees)
        {
            return degrees * math::pi / 180.0f;
        }

    public:
        /// \brief calculates the square root via Newton-Raphson
        /// \param value value to calculate the square root from
        /// \throws negative_exception if value is negative
        /// \return square root of value
        constexpr NODISCARD static float sqrt(const float value)
        {
            if (value < 0)
                throw negative_exception("value can not be negative");

            return sqrt_newton_raphson(value, value, 0);
        }
    };
} // namespace bardcore
#endif //BARDCORE_MATH_H
