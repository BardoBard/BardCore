#ifndef BARDCORE_MATH_H
#define BARDCORE_MATH_H

#include "BardCore/bardcore.h"

namespace bardcore
{
    class math
    {
    private:
        /**
         * \brief helper function for calculating the square root via Newton-Raphson 
         * \note credit: Alex Shtoff - https://stackoverflow.com/questions/8622256/in-c11-is-sqrt-defined-as-constexpr
         * \param value value to calculate the square root from
         * \param curr current value
         * \param prev previous value
         * \return square root of value
         */
        NODISCARD constexpr static float helper_sqrt_newton_raphson(const float value, const float curr,
                                                                    const float prev)
        {
            return curr == prev
                       ? curr
                       : helper_sqrt_newton_raphson(value, 0.5f * (curr + value / curr), curr);
        }

    public:
        /**
         * \brief epsilon value for float comparison
         */
        INLINE static constexpr float epsilon = 0.00015f;
        
        /**
         * \brief pi constant
         */
        INLINE static constexpr float pi = 3.14159265358979323846f;

        /**
         * \brief calculates the degrees from radians
         * \param radians radians
         * \return degrees
         */
        NODISCARD constexpr static float radians_to_degrees(const float radians)
        {
            return radians * 180.0f / math::pi;
        }

        /**
         * \brief calculates the radians from degrees
         * \param degrees degrees
         * \return radians
         */
        NODISCARD constexpr static float degrees_to_radians(const float degrees)
        {
            return degrees * math::pi / 180.0f;
        }

    public:
        /**
         * \brief calculates sqrt at compile time if possible, otherwise it uses std::sqrt
         * \note calculates the square root via Newton-Raphson, during compile time
         * \note sqrt(0) = 0, e.g : 0^(1/2) = 0
         * \param value value to calculate the square root from
         * \throws negative_exception if value is negative
         * \return square root of value
         */
        NODISCARD constexpr static float sqrt(const float value)
        {
            if (value < 0)
                throw exception::negative_exception("value can not be negative");

            // use std at runtime
            // use constexpr at compile time
            return std::_Is_constant_evaluated()
                       ? helper_sqrt_newton_raphson(value, value, 0)
                       : std::sqrt(value);
        }

        /**
         * \brief calculates the mod of a number, with a divisor
         * \note read more at: https://en.wikipedia.org/wiki/Modulo_operation
         * \note example: fmod(5.3, 2) = 1.3
         * \throws zero_exception if divisor is zero
         * \param number number to calculate the modulo from
         * \param divisor divisor, can not be zero
         * \return 
         */
        NODISCARD constexpr static float fmod(float number, const float divisor)
        {
            if (fequals(divisor, 0))
                throw exception::zero_exception("divisor can not be zero");
            
            if (!std::_Is_constant_evaluated()) // use std if runtime
                return std::fmod(number, divisor);

            // for constexpr we don't care that much about performance


            if (fequals(number, 0.f))
                return 0;

            number = fabs(number); // make number positive, it doesn't make a difference

            while (fgreater_than(number, fabs(divisor)) || fequals(number, fabs(divisor)))
                number -= fabs(divisor);

            return number * static_cast<float>(fsign(divisor));
        }

        /**
         * \brief calculates the sign value of a float value
         * \note read more at: https://en.wikipedia.org/wiki/Sign_(mathematics)
         * \param value float value
         * \return sign int value (-1, 0, 1), special case: 0
         */
        NODISCARD constexpr static int fsign(const float value)
        {
            return value == 0
                       ? 0
                       : (value < 0
                              ? -1
                              : 1);
        }

        /**
         * \brief calculates the absolute value of a float value
         * \note read more at: https://en.wikipedia.org/wiki/Absolute_value
         * \param value float value
         * \return absolute float value
         */
        NODISCARD constexpr static float fabs(const float value)
        {
            return fless_than(value, 0)
                       ? -value
                       : value;
        }

        /**
         * \brief checks if two float values are equal, using an epsilon
         * \note thanks to https://stackoverflow.com/questions/17333/how-do-you-compare-float-and-double-while-accounting-for-precision-loss
         * \note it uses an epsilon which means with big numbers it will be inaccurate
         * \param number1 number 1 to compare
         * \param number2 number 2 to compare
         * \return a == b with epsilon
         */
        NODISCARD constexpr bool static fequals(const float number1, const float number2)
        {
            return fabs(number1 - number2) <= epsilon;
        }

        /**
         * \brief checks if left float value is greater than right float value, using an epsilon
         * \note thanks to https://stackoverflow.com/questions/17333/how-do-you-compare-float-and-double-while-accounting-for-precision-loss
         * \note it uses an epsilon which means with big numbers it will be inaccurate
         * \param number1 number 1 to compare
         * \param number2 number 2 to compare
         * \return a > b with epsilon
         */
        NODISCARD constexpr bool static fgreater_than(const float number1, const float number2)
        {
            return number1 - number2 > epsilon;
        }

        /**
         * \brief checks if left float value is less than right float value, using an epsilon
         * \note thanks to https://stackoverflow.com/questions/17333/how-do-you-compare-float-and-double-while-accounting-for-precision-loss
         * \note it uses an epsilon which means with big numbers it will be inaccurate
         * \param number1 number 1 to compare
         * \param number2 number 2 to compare
         * \return a < b with epsilon
         */
        NODISCARD constexpr bool static fless_than(const float number1, const float number2)
        {
            return number2 - number1 > epsilon;
        }

        /**
         * \brief calculates the greatest common divisor of two numbers, using the euclidean algorithm
         * \note read more at: https://en.wikipedia.org/wiki/Euclidean_algorithm#Procedure
         * \note this algorithm is not fast but it was fun to make, it's quite fast for small numbers
         * \throws negative_exception if a or b is negative
         * \throws negative_exception if a or b is negative
         * \param number1 number 1
         * \param number2 number 2
         * \return greatest common divisor of a and b
         */
        NODISCARD constexpr static unsigned int euclidean_gcd(const unsigned int number1, const unsigned int number2)
        {
            if (number1 == 0 || number2 == 0)
                throw exception::zero_exception("a and b must not be zero");
            if (number1 < number2)
                //TODO: make different exception
                throw exception::negative_exception("a must be greater than b");

            const unsigned int mod = number1 % number2;

            if (mod == 0) //stop condition
                return number2;

            return euclidean_gcd(number2, mod);
        }
    };
} // namespace bardcore
#endif //BARDCORE_MATH_H
