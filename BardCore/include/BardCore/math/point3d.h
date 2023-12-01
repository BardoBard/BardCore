#ifndef BARDCORE_POINT3D_H
#define BARDCORE_POINT3D_H

#include "../bardcore.h"
#include "vector3d.h"
#include "dimension3.h"


namespace bardcore
{
    class point3d : public dimension3<point3d>
    {
    public:
        using dimension3::dimension3;

        constexpr point3d operator+(const vector3d& vector) const noexcept
        {
            return {x + vector.x, y + vector.y, z + vector.z};
        }

        constexpr point3d operator+(const point3d& point) const noexcept
        {
            return {x + point.x, y + point.y, z + point.z};
        }

        constexpr point3d operator-(const vector3d& vector) const noexcept
        {
            return {x - vector.x, y - vector.y, z - vector.z};
        }

        constexpr point3d operator-(const point3d& point) const noexcept
        {
            return {x - point.x, y - point.y, z - point.z};
        }

        /// \brief calculates the vector between two points
        /// \param point point
        /// \return vector between two points
        constexpr NODISCARD vector3d get_vector(const point3d& point) const noexcept
        {
            return vector3d(point - *this);
        }

        /// \brief calculates the distance between two points
        /// \note formula: sqrt(Σ (a_i - b_i)^2)
        /// \param point other point
        /// \return distance between two points
        constexpr NODISCARD float distance(const point3d& point) const noexcept
        {
            return math::sqrt(distance_squared(point));
        }

        /// \brief calculates the distance squared between two points
        /// \note formula: Σ (a_i - b_i)^2
        /// \param point other point
        /// \return distance squared between two points
        constexpr NODISCARD float distance_squared(const point3d& point) const noexcept
        {
            const float x_diff = point.x - x;
            const float y_diff = point.y - y;
            const float z_diff = point.z - z;
            return x_diff * x_diff + y_diff * y_diff + z_diff * z_diff;
        }
    };
} // namespace bardcore
#endif //BARDCORE_POINT3D_H
