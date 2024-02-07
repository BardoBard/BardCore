#pragma once

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
        NODISCARD constexpr static double helper_sqrt_newton_raphson(
            const double value, const double curr,
            const double prev)
        {
            return curr == prev
                       ? curr
                       : helper_sqrt_newton_raphson(value, 0.5 * (curr + value / curr), curr);
        }

    public:
        /**
         * \brief epsilon value for double comparison
         */
        INLINE static constexpr double epsilon = 0.00001;

        /**
         * \brief 180 / pi constant, used for converting radians to degrees
         */
        INLINE static constexpr double _180_div_pi = 57.295779513082323;

        /**
         * \brief pi / 180 constant, used for converting degrees to radians
         */
        INLINE static constexpr double pi_div_180 = 0.017453292519943295;

        /**
         * \brief 2 * pi constant
         */
        INLINE static constexpr double _2pi = 6.28318530717958647692;

        /**
         * \brief pi constant
         */
        INLINE static constexpr double pi = 3.14159265358979323846;

        /**
         * \brief pi / 2 constant
         */
        INLINE static constexpr double pi_2 = 1.57079632679489661923;

        /**
         * \brief pi / 4 constant
         */
        INLINE static constexpr double pi_4 = 0.785398163397448309616;

        /**
         * \brief sqrt(2) constant
         */
        INLINE static constexpr double sqrt_2 = 1.41421356237309504880;

        /**
         * \brief sqrt(3) constant
         */
        INLINE static constexpr double sqrt_3 = 1.73205080756887729352;

        /**
         * \brief pi / 4 constant
         */
        INLINE static constexpr double inf = std::numeric_limits<double>::infinity();

        /**
         * \brief calculates the degrees from radians
         * \param radians radians
         * \return degrees
         */
        NODISCARD constexpr static double radians_to_degrees(const double radians) noexcept
        {
            return radians * math::_180_div_pi;
        }

        /**
         * \brief calculates the radians from degrees
         * \param degrees degrees
         * \return radians
         */
        NODISCARD constexpr static double degrees_to_radians(const double degrees) noexcept
        {
            return degrees * math::pi_div_180;
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
        NODISCARD constexpr static double sqrt(const double value)
        {
            if (value < 0)
                throw exception::negative_exception("sqrt(value) can not be negative");

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
        NODISCARD constexpr static double factorial(const unsigned int value) noexcept
        {
            if (value == 0)
                return 1;

            if (!std::_Is_constant_evaluated()) // use std if runtime
                return std::tgamma(static_cast<double>(value) + 1);

            return static_cast<double>(value) * factorial(value - 1);
        }

        /**
         * \brief calculates the power of a number, it uses std at runtime
         * \note read more at: https://en.wikipedia.org/wiki/Exponentiation
         * \param base base, the value to calculate the power from
         * \param exponent exponent
         * \return double(base)^exponent
         */
        NODISCARD constexpr static double pow(const double base, const int exponent) noexcept
        {
            if (!std::_Is_constant_evaluated()) // use std if runtime
                return std::pow(base, static_cast<double>(exponent));

            if (std::_Is_nan(base) || std::_Is_inf(base)) // base is inf
                return NAN;

            if (exponent == 0 || equals(base, 1.)) // base is 1 or exponent is 0
                return 1;

            return exponent > 0
                       ? base * pow(base, exponent - 1)
                       : 1 / (base * pow(base, -exponent - 1));
        }

        /**
         * \brief calculates the cosine of a number, it uses std at runtime
         * \note read more at: https://blogs.ubc.ca/infiniteseriesmodule/units/unit-3-power-series/taylor-series/the-maclaurin-expansion-of-cosx/
         * \note using the Maclaurin Expansion
         * \param value value to calculate the cosine from in radians
         * \return cosine of value
         */
        NODISCARD constexpr static double cos(const double value) noexcept
        {
            if (!std::_Is_constant_evaluated()) // use std if runtime
                return std::cos(value);

            if (std::_Is_nan(value) || std::_Is_inf(value)) // value is inf
                return NAN;

            return sin(value + pi_2);
        }

        /**
         * \brief calculates the sine of a number, it uses std at runtime
         * \note read more at: https://blogs.ubc.ca/infiniteseriesmodule/units/unit-3-power-series/taylor-series/maclaurin-expansion-of-sinx/
         * \note using the Maclaurin Expansion
         * \param value value to calculate the sine from in radians
         * \return sine of value
         */
        NODISCARD constexpr static double sin(double value) noexcept
        {
            if (!std::_Is_constant_evaluated()) // use std if runtime
                return std::sin(value);

            if (std::_Is_nan(value) || std::_Is_inf(value)) // value is inf
                return NAN;

            value = mod(value, 2 * pi); // make value between 0 and 2pi

            double result = 0;
            for (int index = 0; index < 1'000; ++index) // 1 thousand iterations as hard limit
            {
                //formula: Σ (-1)^n * x^(2n) / (2n)!
                const double r = pow(-1, index) * pow(value, 2 * index + 1) / factorial(2 * index + 1);

                // r is near zero, adding it to the result will not change the result
                // r is not a number or inf, stop calculating
                if (equals(r, 0) || (std::_Is_nan(r) || std::_Is_inf(r)))
                    break;

                result += r;
            }

            return result;
        }

        /**
         * \brief calculates the tangent of a number, it uses std at runtime
         * \note read more at: https://en.wikipedia.org/wiki/Trigonometric_functions
         * \note using the Maclaurin Expansion
         * \note compile time might be slightly inaccurate when close to the limit, e.g: somewhere close to pi
         * \param value value to calculate the tangent from in radians
         * \return tangent of value
         */
        NODISCARD constexpr static double tan(const double value) noexcept
        {
            if (std::_Is_nan(value) || std::_Is_inf(value)) // value is inf
                return NAN;

            if (equals(mod(value, pi), 0)) // value is a multiple of pi
                return 0;

            if (!equals(value, 0) && equals(mod(value, pi_2), 0)) // value is a multiple of pi/2
                return NAN;

            if (!std::_Is_constant_evaluated()) // use std if runtime
                return std::tan(value);

            return sin(value) / cos(value);
        }

        /**
         * \brief calculates the arcsine of a number, it uses std at runtime
         *
         * it's pretty accurate compile time, ~0.001 error margin,
         * When approaching 1 or -1 it will be less accurate, ~0.02 error margin
         * \note read more at: https://proofwiki.org/wiki/Power_Series_Expansion_for_Real_Arcsine_Function
         * \note using the power series expansion
         * \throws out_of_range_exception if value is not between -1 and 1
         * \param value value to calculate the arcsin from
         * \return arcsine of value
         */
        NODISCARD constexpr static double arcsin(const double value)
        {
            if (math::greater_than(math::abs(value), 1.) || std::_Is_nan(value) || std::_Is_inf(value))
                throw exception::out_of_range_exception("arcsin(x) must be between -1 and 1");

            if (!std::_Is_constant_evaluated()) // use std if runtime
                return std::asin(value);

            if (equals(math::abs(value), 1))
                return pi_2 * sign(value);

            double result = 0;
            for (int index = 0; index < 1'000; ++index) // 1 thousand iterations as hard limit
            {
                //formula: Σ ((2n)! / (2^(2n) * (n!)^2)) * (x^(2n+1) / (2n+1))
                const double r = factorial(2 * index) / (pow(2, 2 * index) * pow(factorial(index), 2)) * pow(
                    value, 2 * index + 1) / (2 * index + 1);

                // r is near zero, adding it to the result will not change the result
                // r is not a number or inf, stop calculating
                if (equals(r, 0) || (std::_Is_nan(r) || std::_Is_inf(r)))
                    break;

                result += r;
            }

            return result;
        }

        /**
         * \brief calculates the arccos of a number, it uses std at runtime
         * 
         * it's pretty accurate compile time, ~0.001 error margin,
         * When approaching 1 or -1 it will be less accurate, ~0.02 error margin
         * \note read more at: https://proofwiki.org/wiki/Power_Series_Expansion_for_Real_Arccosine_Function
         * \note using the power series expansion
         * \throws out_of_range_exception if value is not between -1 and 1
         * \param value value to calculate the arccos from
         * \return arccosine of value
         */
        NODISCARD constexpr static double arccos(const double value)
        {
            if (math::greater_than(math::abs(value), 1.) || std::_Is_nan(value) || std::_Is_inf(value))
                throw exception::out_of_range_exception("arccos(x) must be between -1 and 1");

            if (!std::_Is_constant_evaluated()) // use std if runtime
                return std::acos(value);

            return pi_2 - arcsin(value);
        }

        /**
         * \brief calculates the arctan of a number, it uses std at runtime
         * \note read more at: https://socratic.org/questions/what-is-the-taylor-series-of-f-x-arctan-x
         * \note using the Taylor Series
         * \note returns [-pi/2, pi/2] if value is inf
         * \param value value to calculate the arctan from
         * \return arccosine of value
         */
        NODISCARD constexpr static double arctan(const double value) noexcept
        {
            if (!std::_Is_constant_evaluated()) // use std if runtime
                return std::atan(value);

            if (std::_Is_nan(value))
                return NAN;

            if (std::_Is_inf(value)) // value is inf
                return pi_2 * sign(value); //https://en.cppreference.com/w/cpp/numeric/math/atan

            if (equals(value, 0)) // value is zero
                return 0;

            if (equals(math::abs(value), 1)) // value is 1 or -1
                return pi_4 * sign(value);

            // if value is greater than 1, use the formula: arctan(x) = pi/2 - arctan(1/x), which doesn't produce a limit
            if (math::greater_than(math::abs(value), 1.))
                return pi_2 * sign(value) - arctan(1 / value);

            double result = 0;
            for (int index = 0; index < 100; ++index) // 1 hundred iterations as hard limit
            {
                //formula: Σ (-1)^n * (x^(2n+1) / (2n+1))
                const double r = pow(-1, index) * pow(value, 2 * index + 1) / (2 * index + 1);

                // r is near zero, adding it to the result will not change the result
                // r is not a number or inf, stop calculating
                if (equals(r, 0) || (std::_Is_nan(r) || std::_Is_inf(r)))
                    break;

                result += r;
            }

            return result;
        }

        /**
         * \brief calculates the mod of a number, with a divisor
         * \note read more at: https://en.wikipedia.org/wiki/Modulo_operation
         * \note reference: https://cplusplus.com/reference/cmath/fmod/
         * \note example: mod(5.3, 2) = 1.3
         * \throws zero_exception if divisor is zero
         * \param value number to calculate the modulo from
         * \param divisor divisor, can not be zero
         * \return 
         */
        NODISCARD constexpr static double mod(const double value, const double divisor)
        {
            if (equals(divisor, 0))
                throw exception::zero_exception("mod divisor can not be zero");

            if (!std::_Is_constant_evaluated()) // use std if runtime
            {
                const double mod = std::fmod(value, divisor);
                return equals(abs(mod), abs(divisor))
                           ? 0
                           : mod;
            }

            if (equals(value, 0))
                return 0;

            const int multiplier = static_cast<int>(value / divisor + epsilon * sign(value / divisor)); // floor
            return value - static_cast<double>(multiplier) * divisor + DBL_EPSILON * sign(value);
        }

        /**
         * \brief calculates the sign value of a double value
         * \note read more at: https://en.wikipedia.org/wiki/Sign_(mathematics)
         * \param value double value
         * \return sign int value (-1, 0, 1), special case: 0
         */
        NODISCARD constexpr static int sign(const double value) noexcept
        {
            return equals(value, 0)
                       ? 0
                       : (value < 0
                              ? -1
                              : 1);
        }

        /**
         * \brief calculates the absolute value of a double value
         * \note read more at: https://en.wikipedia.org/wiki/Absolute_value
         * \param value double value
         * \return absolute double value
         */
        NODISCARD constexpr static double abs(const double value) noexcept
        {
            return value < 0
                       ? -value
                       : value;
        }

        /**
         * \brief checks if two double values are equal, using an epsilon
         * \note thanks to https://stackoverflow.com/questions/17333/how-do-you-compare-double-and-double-while-accounting-for-precision-loss
         * \note it uses an epsilon which means with big numbers it will be inaccurate
         * \note if the value is INF or NAN it will return false
         * \param value1 value 1 to compare
         * \param value2 value 2 to compare
         * \return a == b with epsilon
         */
        NODISCARD constexpr bool static equals(const double value1,
                                               const double value2) noexcept
        {
            return abs(value1 - value2) <= epsilon;
        }

        /**
         * \brief checks if left double value is greater than right double value, using an epsilon
         * \note thanks to https://stackoverflow.com/questions/17333/how-do-you-compare-double-and-double-while-accounting-for-precision-loss
         * \note it uses an epsilon which means with big numbers it will be inaccurate
         * \note if the value is INF or NAN it will return false
         * \param value1 value 1to compare
         * \param value2 value 2 to compare
         * \return a > b with epsilon
         */
        NODISCARD constexpr bool static greater_than(const double value1,
                                                     const double value2) noexcept
        {
            return value1 - value2 > epsilon;
        }

        /**
         * \brief checks if left double value is greater than or equal to right double value, using an epsilon
         * \note thanks to https://stackoverflow.com/questions/17333/how-do-you-compare-double-and-double-while-accounting-for-precision-loss
         * \note it uses an epsilon which means with big numbers it will be inaccurate
         * \note if the value is INF or NAN it will return false
         * \param value1 value 1to compare
         * \param value2 value 2 to compare
         * \return a >= b with epsilon
         */
        NODISCARD constexpr bool static greater_than_or_equals(const double value1,
                                                               const double value2) noexcept
        {
            return greater_than(value1, value2) || equals(value1, value2);
        }

        /**
         * \brief checks if left double value is less than right double value, using an epsilon
         * \note thanks to https://stackoverflow.com/questions/17333/how-do-you-compare-double-and-double-while-accounting-for-precision-loss
         * \note it uses an epsilon which means with big numbers it will be inaccurate
         * \note if the value is inf or NAN it will return false
         * \param value1 value 1to compare
         * \param value2 value 2 to compare
         * \return a < b with epsilon
         */
        NODISCARD constexpr bool static less_than(const double value1,
                                                  const double value2) noexcept
        {
            return value2 - value1 > epsilon;
        }

        /**
         * \brief checks if left double value is less than or equal to right double value, using an epsilon
         * \note thanks to https://stackoverflow.com/questions/17333/how-do-you-compare-double-and-double-while-accounting-for-precision-loss
         * \note it uses an epsilon which means with big numbers it will be inaccurate
         * \note if the value is inf or NAN it will return false
         * \param value1 value 1to compare
         * \param value2 value 2 to compare
         * \return a <= b with epsilon
         */
        NODISCARD constexpr bool static less_than_or_equals(const double value1,
                                                            const double value2) noexcept
        {
            return less_than(value1, value2) || equals(value1, value2);
        }

        /**
         * \brief calculates the greatest common divisor of two numbers, using the euclidean algorithm
         * \note read more at: https://en.wikipedia.org/wiki/Euclidean_algorithm#Procedure
         * \note this algorithm is not fast but it was fun to make, it's quite fast for small numbers
         * \throws negative_exception if a or b is negative
         * \throws negative_exception if a or b is negative
         * \param value1 number 1
         * \param value2 value 2
         * \return greatest common divisor of a and b
         */
        NODISCARD constexpr static unsigned int euclidean_gcd(const unsigned int value1, const unsigned int value2)
        {
            if (value1 == 0 || value2 == 0)
                throw exception::zero_exception("a and b must not be zero");
            if (value1 < value2)
                //TODO: make different exception
                throw exception::negative_exception("a must be greater than b");

            const unsigned int mod = value1 % value2;

            if (mod == 0) //stop condition
                return value2;

            return euclidean_gcd(value2, mod);
        }
    };
} // namespace bardcore
