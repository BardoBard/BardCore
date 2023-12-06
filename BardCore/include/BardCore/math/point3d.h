#ifndef BARDCORE_POINT3D_H
#define BARDCORE_POINT3D_H

#include "../bardcore.h"
#include "vector3d.h"
#include "../interfaces/dimension3.h"


namespace bardcore
{
    /**
     * \brief 3D point
     * \note inherits from dimension3
     * \note this class is also constexpr
     */
    class point3d : public dimension3<point3d>
    {
    public:
        using dimension3::dimension3;

        /// \brief calculates the vector between two points
        /// \param point point
        /// \return vector between two points
        NODISCARD constexpr vector3d get_vector(const point3d& point) const noexcept
        {
            return vector3d(point - *this);
        }

        /// \brief calculates the distance between two points
        /// \note formula: sqrt(Σ (a_i - b_i)^2)
        /// \param point other point
        /// \return distance between two points
        NODISCARD constexpr float distance(const point3d& point) const noexcept
        {
            return math::sqrt(distance_squared(point));
        }

        /// \brief calculates the distance squared between two points
        /// \note formula: Σ (a_i - b_i)^2
        /// \param point other point
        /// \return distance squared between two points
        NODISCARD constexpr float distance_squared(const point3d& point) const noexcept
        {
            const float x_diff = point.x - x;
            const float y_diff = point.y - y;
            const float z_diff = point.z - z;
            return x_diff * x_diff + y_diff * y_diff + z_diff * z_diff;
        }
    };
} // namespace bardcore
#endif //BARDCORE_POINT3D_H
