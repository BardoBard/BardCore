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
        INLINE static constexpr float epsilon = 0.0001f;

        /**
         * \brief pi constant
         */
        INLINE static constexpr float pi = 3.14159265358979323846f;

        /**
         * \brief pi constant
         */
        INLINE static constexpr float pi_2 = 1.57079632679489661923f;

        /**
         * \brief pi constant
         */
        INLINE static constexpr float pi_4 = 0.785398163397448309616f;

        /**
         * \brief calculates the degrees from radians
         * \param radians radians
         * \return degrees
         */
        NODISCARD constexpr static float radians_to_degrees(const float radians) noexcept
        {
            return radians * 180.0f / math::pi;
        }

        /**
         * \brief calculates the radians from degrees
         * \param degrees degrees
         * \return radians
         */
        NODISCARD constexpr static float degrees_to_radians(const float degrees) noexcept
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

            if (!std::_Is_constant_evaluated())
                return std::sqrt(value);

            // use std at runtime
            // use constexpr at compile time
            return helper_sqrt_newton_raphson(value, value, 0);
        }

        /**
         * \brief calculates the factorial of a number, it uses std at runtime
         * \note read more at: https://en.wikipedia.org/wiki/Factorial
         * \param value value to calculate the factorial from
         * \return factorial of value, e.g: value!
         */
        NODISCARD constexpr static float factorial(const unsigned int value) noexcept
        {
            if (value == 0)
                return 1;

            if (!std::_Is_constant_evaluated()) // use std if runtime
                return std::tgammaf(static_cast<float>(value) + 1);
            
            return static_cast<float>(value) * factorial(value - 1);
        }

        /**
         * \brief calculates the power of a number, it uses std at runtime
         * \note read more at: https://en.wikipedia.org/wiki/Exponentiation
         * \param base base, the value to calculate the power from
         * \param exponent exponent
         * \return float(base)^exponent
         */
        NODISCARD constexpr static float pow(const float base, const int exponent) noexcept
        {
            if (!std::_Is_constant_evaluated()) // use std if runtime
                return std::powf(base, static_cast<float>(exponent));

            if (std::_Is_nan(base) || base == INFINITY || base == -INFINITY) // base is infinity
                return NAN;

            if (exponent == 0 || fequals(base, 1.f)) // base is 1 or exponent is 0
                return 1;

            return exponent > 0
                       ? base * pow(base, exponent - 1)
                       : 1 / (base * pow(base, -exponent - 1));
        }

        /**
         * \brief calculates the exponential function of a number, it uses std at runtime
         * \note read more at: https://en.wikipedia.org/wiki/Exponential_function#Formal_definition
         * \note the algorithm is not accurate for a value above 12
         * \param value exponent, the value to calculate the exponential function from (can be negative)
         * \return exponential function of value
         */
        NODISCARD constexpr static float fexp(const float value) noexcept
        {
            // the algorithm is not accurate for a value above 12
            if (!std::_Is_constant_evaluated() || fgreater_than(fabs(value), 12))
                return std::exp(value);

            if (std::_Is_nan(value) || value == INFINITY || value == -INFINITY) // value is infinity
                return NAN;

            float result = 1.0f;

            for (int index = 1; index < 1'000; ++index) // 1 thousand iterations as hard limit
            {
                const float r = pow(fabs(value), index) / factorial(index);

                // r is near zero, adding it to the result will not change the result
                // r is not a number or infinity, stop calculating
                if (fequals(r, 0.f) || (std::_Is_nan(r) || r == INFINITY || r == -INFINITY))
                    break;

                result += r;
            }

            return fsign(value) == 1
                       ? result
                       : 1.0f / result;
        }

        /**
         * \brief calculates the cosine of a number, it uses std at runtime
         * \note read more at: https://blogs.ubc.ca/infiniteseriesmodule/units/unit-3-power-series/taylor-series/the-maclaurin-expansion-of-cosx/
         * \note using the Maclaurin Expansion
         * \param value value to calculate the cosine from
         * \return cosine of value
         */
        NODISCARD constexpr static float fcos(const float value) noexcept
        {
            if (!std::_Is_constant_evaluated()) // use std if runtime
                return std::cosf(value);

            if (std::_Is_nan(value) || value == INFINITY || value == -INFINITY) // value is infinity
                return NAN;

            float result = 0.0f;
            for (int index = 0; index < 1'000; ++index) // 1 thousand iterations as hard limit
            {
                //formula: Σ (-1)^n * x^(2n) / (2n)!
                const float r = pow(-1, index) * pow(value, 2 * index) / factorial(2 * index);

                // r is near zero, adding it to the result will not change the result
                // r is not a number or infinity, stop calculating
                if (fequals(r, 0.f) || (std::_Is_nan(r) || r == INFINITY || r == -INFINITY))
                    break;

                result += r;
            }

            return result;
        }

        /**
         * \brief calculates the sine of a number, it uses std at runtime
         * \note read more at: https://blogs.ubc.ca/infiniteseriesmodule/units/unit-3-power-series/taylor-series/maclaurin-expansion-of-sinx/
         * \note using the Maclaurin Expansion
         * \param value value to calculate the sine from
         * \return sine of value
         */
        NODISCARD constexpr static float fsin(const float value) noexcept
        {
            if (!std::_Is_constant_evaluated()) // use std if runtime
                return std::sinf(value);

            if (std::_Is_nan(value) || value == INFINITY || value == -INFINITY) // value is infinity
                return NAN;

            return fcos(value - pi_2);
        }

        /**
         * \brief calculates the tangent of a number, it uses std at runtime
         * \note read more at: https://en.wikipedia.org/wiki/Trigonometric_functions
         * \note using the Maclaurin Expansion
         * \note compile time might be slightly inaccurate when close to the limit, e.g: somewhere close to pi
         * \param value value to calculate the tangent from
         * \return tangent of value
         */
        NODISCARD constexpr static float ftan(const float value) noexcept
        {
            if (std::_Is_nan(value) || value == INFINITY || value == -INFINITY) // value is infinity
                return NAN;
            
            if (fequals(fmod(value, pi), 0.f)) // value is a multiple of pi
                return 0;

            if (!fequals(value, 0.f) && fequals(fmod(value, pi_2), 0.f)) // value is a multiple of pi/2
                return NAN;
            
            if (!std::_Is_constant_evaluated()) // use std if runtime
                return std::tanf(value);
            
            return fsin(value) / fcos(value);
        }

        /**
         * \brief calculates the mod of a number, with a divisor
         * \note read more at: https://en.wikipedia.org/wiki/Modulo_operation
         * \note reference: https://cplusplus.com/reference/cmath/fmod/
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
        NODISCARD constexpr static int fsign(const float value) noexcept
        {
            return fequals(value, 0)
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
        NODISCARD constexpr static float fabs(const float value) noexcept
        {
            return fless_than(value, 0)
                       ? -value
                       : value;
        }

        /**
         * \brief checks if two float values are equal, using an epsilon
         * \note thanks to https://stackoverflow.com/questions/17333/how-do-you-compare-float-and-double-while-accounting-for-precision-loss
         * \note it uses an epsilon which means with big numbers it will be inaccurate
         * \note if the value is INFINITY or NAN it will return false
         * \param number1 number 1 to compare
         * \param number2 number 2 to compare
         * \return a == b with epsilon
         */
        NODISCARD constexpr bool static fequals(const float number1, const float number2) noexcept
        {
            return fabs(number1 - number2) <= epsilon;
        }

        /**
         * \brief checks if left float value is greater than right float value, using an epsilon
         * \note thanks to https://stackoverflow.com/questions/17333/how-do-you-compare-float-and-double-while-accounting-for-precision-loss
         * \note it uses an epsilon which means with big numbers it will be inaccurate
         * \note if the value is INFINITY or NAN it will return false
         * \param number1 number 1 to compare
         * \param number2 number 2 to compare
         * \return a > b with epsilon
         */
        NODISCARD constexpr bool static fgreater_than(const float number1, const float number2) noexcept
        {
            return number1 - number2 > epsilon;
        }

        /**
         * \brief checks if left float value is less than right float value, using an epsilon
         * \note thanks to https://stackoverflow.com/questions/17333/how-do-you-compare-float-and-double-while-accounting-for-precision-loss
         * \note it uses an epsilon which means with big numbers it will be inaccurate
         * \note if the value is INFINITY or NAN it will return false
         * \param number1 number 1 to compare
         * \param number2 number 2 to compare
         * \return a < b with epsilon
         */
        NODISCARD constexpr bool static fless_than(const float number1, const float number2) noexcept
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
