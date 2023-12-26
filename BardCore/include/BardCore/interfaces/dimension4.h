#ifndef BARDCORE_dimension4_H
#define BARDCORE_dimension4_H
#include "BardCore/bardcore.h"

namespace bardcore
{
    /**
     * \brief abstract class for 4D
     * \note quaternion : public dimension4<quaternion>
     * \note this class is also constexpr 
     * \tparam T implementation of the operator
     */
    template <typename T>
    class dimension4
    {
    public:
        float x{}, y{}, z{}, w{};

    public:
        NODISCARD constexpr INLINE static T zero() noexcept { return T(0, 0, 0, 0); }
        NODISCARD constexpr INLINE static T one() noexcept { return T(1, 1, 1, 1); }

    public:
        ~dimension4() = default;

        /**
         * \brief copy constructor
         * \param other other dimension4
         */
        constexpr dimension4(const dimension4& other)
            : x{other.x},
              y{other.y},
              z{other.z},
              w{other.w}
        {
        }

        /**
         * \brief move constructor
         * \param other other dimension4
         */
        constexpr dimension4(dimension4&& other) noexcept
            : x{other.x},
              y{other.y},
              z{other.z},
              w{other.w}
        {
        }

        /**
         * \brief default constructor with 0, 0, 0
         */
        constexpr dimension4(): dimension4(0, 0, 0, 0)
        {
        }

        /**
         * \brief copy constructor
         * \tparam Derived a derived class of dimension4, e.g. quaternion
         * \param other other dimension4
         */
        template <typename Derived>
        constexpr explicit dimension4(const dimension4<Derived>& other) : dimension4(other.x, other.y, other.z, other.w)
        {
        }

        /**
         * \brief constructor with x, y, z in 4D
         * \param x x
         * \param y y
         * \param z z
         * \param w w
         */
        constexpr dimension4(const float x, const float y, const float z, const float w): x(x), y(y), z(z), w(w)
        {
        }

        ///////////////////////////////////////////////////////
        ///                    operators                    ///
        ///////////////////////////////////////////////////////

        /**
         * \brief output operator, prints "(x, y, z, w)"
         * \param os output stream
         * \param dimension4 dimension4 to output
         * \return output stream "(x, y, z, w)"
         */
        friend std::ostream& operator<<(std::ostream& os, const dimension4& dimension4)
        {
            return os
                << "("
                << dimension4.x << ", "
                << dimension4.y << ", "
                << dimension4.z << ", "
                << dimension4.w
                << ")";
        }

        /**
         * \brief subtracts a dimension4 from another dimension4 and stores the result in a new dimension4
         * \tparam Derived a derived class of dimension4, e.g. quaternion
         * \param other other dimension4
        */
        template <typename Derived, ENABLE_IF_DERIVED(dimension4, Derived)>
        NODISCARD constexpr T operator-(const Derived& other) const noexcept
        {
            return {x - other.x, y - other.y, z - other.z, w - other.w};
        }

        /**
         * \brief subtract a float from this dimension4 and stores the result in a new dimension4
         * \param n float to subtract with
         * \return new dimension4
         */
        NODISCARD constexpr T operator-(const float n) const noexcept
        {
            return {x - n, y - n, z - n, w - n};
        }

        /**
         * \brief adds a dimension4 from another dimension4 and stores the result in a new dimension4
         * \tparam Derived a derived class of dimension4, e.g. quaternion
         * \param other other dimension4
        */
        template <typename Derived, ENABLE_IF_DERIVED(dimension4, Derived)>
        NODISCARD constexpr T operator+(const Derived& other) const noexcept
        {
            return {x + other.x, y + other.y, z + other.z, w + other.w};
        }

        /**
         * \brief adds a float from this dimension4 and stores the result in a new dimension4
         * \param n float to add with
         * \return new dimension4
         */
        NODISCARD constexpr T operator+(const float n) const noexcept
        {
            return {x + n, y + n, z + n, w + n};
        }

        /**
         * \brief multiplies a dimension4 with n and stores the result in a new dimension4
         * \param n float to multiply with
        */
        NODISCARD constexpr T operator*(const float n) const noexcept
        {
            return {x * n, y * n, z * n, w * n};
        }

        /**
         * \brief divides a dimension4 with n and stores the result in a new dimension4
         * \throws std::invalid_argument if n is 0
         * \param n float to divide with
        */
        NODISCARD constexpr T operator/(const float n) const
        {
            if (n == 0.f)
                throw exception::zero_exception("division by zero");

            return {x / n, y / n, z / n, w / n};
        }

        /**
         * \brief adds a dimension4 to this dimension4
         * \tparam Derived a derived class of dimension4, e.g. quaternion
         * \param other other dimension4
        */
        template <typename Derived, ENABLE_IF_DERIVED(dimension4, Derived)>
        void operator+=(const Derived& other) noexcept
        {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;
        }

        /**
         * \brief add a float from this dimension4
         * \param n float to add with
         */
        void operator+=(const float n) noexcept
        {
            x += n;
            y += n;
            z += n;
            w += n;
        }

        /**
         * \brief subtracts this dimension4 from this dimension4
         * \tparam Derived a derived class of dimension4, e.g. quaternion
         * \param other other dimension4
        */
        template <typename Derived, ENABLE_IF_DERIVED(dimension4, Derived)>
        void operator-=(const Derived& other) noexcept
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            w -= other.w;
        }

        /**
         * \brief subtracts a float from this dimension4
         * \param n float to subtract with
         */
        void operator-=(const float n) noexcept
        {
            x -= n;
            y -= n;
            z -= n;
            w -= n;
        }

        /**
         * \brief multiplies this dimension4 with n
         * \param n float to multiply with
        */
        void operator*=(const float n) noexcept
        {
            x *= n;
            y *= n;
            z *= n;
            w *= n;
        }

        /**
         * \brief divides this dimension4 with n
         * \throws zero_exception if n is 0
         * \param n float to divide with
        */
        void operator/=(const float n)
        {
            if (n == 0.f)
                throw exception::zero_exception("division by zero");

            x /= n;
            y /= n;
            z /= n;
            w /= n;
        }

        /**
         * \brief copy assignment operator
         * \param other other dimension4
         * \return this
         */
        dimension4& operator=(const dimension4& other) noexcept = default;

        /**
         * \brief move assignment operator
         * \param other other dimension4
         * \return this
         */
        dimension4& operator=(dimension4&& other) noexcept = default;

        /**
         * \brief less than operator
         * \param left left dimension4
         * \param right right dimension4
         * \return true if left < right
         */
        NODISCARD constexpr friend bool operator<(const dimension4& left, const dimension4& right) noexcept
        {
            return left.x < right.x
                && left.y < right.y
                && left.z < right.z
                && left.w < right.w;
        }

        /**
         * \brief less than or equal operator
         * \param left left dimension4
         * \param right right dimension4
         * \return true if left <= right
         */
        NODISCARD constexpr friend bool operator<=(const dimension4& left, const dimension4& right) noexcept
        {
            return !(right < left);
        }

        /**
         * \brief greater than operator
         * \param left left dimension4
         * \param right right dimension4
         * \return true if left > right
         */
        NODISCARD constexpr friend bool operator>(const dimension4& left, const dimension4& right) noexcept
        {
            return right < left;
        }

        /**
         * \brief greater than or equal operator
         * \param left left dimension4
         * \param right right dimension4
         * \return true if left >= right
         */
        NODISCARD constexpr friend bool operator>=(const dimension4& left, const dimension4& right) noexcept
        {
            return !(left < right);
        }

        /**
         * \brief equal operator
         * \param left left dimension4
         * \param right right dimension4
         * \return true if left == right
         */
        NODISCARD constexpr friend bool operator==(const dimension4& left, const dimension4& right) noexcept
        {
            return left.x == right.x
                && left.y == right.y
                && left.z == right.z
                && left.w == right.w;
        }

        /**
         * \brief not equal operator
         * \param left left dimension4
         * \param right right dimension4
         * \return true if left != right
         */
        NODISCARD constexpr friend bool operator!=(const dimension4& left, const dimension4& right) noexcept
        {
            return !(left == right);
        }
    };
} // namespace bardcore
#endif //BARDCORE_dimension4_H
