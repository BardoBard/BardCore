#ifndef BARDCORE_RAY_H
#define BARDCORE_RAY_H

#include "BardCore/math/point3d.h"
#include "BardCore/math/vector3d.h"

namespace bardcore
{
    namespace utility
    {
        /// \brief 
        class ray
        {
        protected:
            /// \brief position of the ray, e.g (1,2,3)
            point3d position_{};

            /// \brief normalized direction of the ray, e.g (1,0,0)
            vector3d direction_{};

            /// \brief distance from the position to the end of the ray, e.g 5
            float distance_{};

        public:
            /// \brief default constructor, only direction needs to be set
            /// \throws zero_exception if length of vector is zero
            /// \note position will be set to (0,0,0) and distance to the length of the direction
            explicit constexpr ray(const vector3d& direction) : ray(point3d(), direction, direction.length())
            {
            }

            /// \brief constructs a ray with start and end point
            /// \throws zero_exception if points are on the same position
            /// \param start starting point, position of the ray
            /// \param end ending point, distance will be calculated from the start to this point
            constexpr ray(const point3d& start, const point3d& end) : ray(
                start, start.get_vector(end), start.distance(end))
            {
            }

            /// \brief constructs a ray with a position, direction and distance
            /// \throws negative_exception if distance is negative
            /// \throws zero_exception if length of vector is zero
            /// \param position position of the ray
            /// \param direction direction of the ray
            /// \param distance distance of the ray
            constexpr ray(const point3d& position, const vector3d& direction, const float distance) :
                position_(position), direction_(direction.normalize()), distance_(distance)
            {
                if (distance < 0)
                    throw exceptions::negative_exception("distance can't be negative");
            }

            /// \brief copy constructor
            /// \param ray ray to copy
            constexpr ray(const ray& ray) noexcept : position_(ray.position_), direction_(ray.direction_),
                                                     distance_(ray.distance_)
            {
            }

            /// \brief move constructor
            /// \param ray ray to move
            constexpr ray(ray&& ray) noexcept : position_(std::move(ray.position_)),
                                                direction_(std::move(ray.direction_)),
                                                distance_(std::move(ray.distance_))
            {
            }

            ~ray() = default;

            /// \brief gets the position of the ray
            /// \return position of the ray
            NODISCARD constexpr const point3d& get_position() const noexcept { return position_; }

            /// \brief gets the direction of the ray
            /// \return direction of the ray
            NODISCARD constexpr const vector3d& get_direction() const noexcept { return direction_; }

            /// \brief gets distance from the position to the end of the ray
            /// \return distance of the ray
            NODISCARD constexpr float get_distance() const noexcept { return distance_; }

            /// \brief sets a new position of the ray
            /// \param position new position of the ray
            void set_position(const point3d& position) noexcept { this->position_ = position; }

            /// \brief sets the direction of the ray, the direction will be normalized
            /// \throws zero_exception if length of vector is zero
            /// \param direction direction of the ray
            void set_direction(const vector3d& direction) { this->direction_ = direction.normalize(); }

            /// \brief sets the distance of the ray
            /// \throws negative_exception if distance is negative
            /// \param distance distance of the ray
            void set_distance(const float distance)
            {
                if (distance < 0)
                    throw exceptions::negative_exception("distance can't be negative");

                this->distance_ = distance;
            }

            /// \brief sets the distance of the ray
            /// \param point second point, distance will be calculated from the position to this point
            void set_distance(const point3d& point) noexcept { set_distance(position_.distance(point)); }


            /// \brief calculates if length is within range of the ray, this could be useful for a quick check before calculating the intersection
            /// \throws negative_exception if length is negative
            /// \param length length to check
            /// \return true if length is within the range of the ray, otherwise false
            NODISCARD constexpr bool within_range(const float length) const
            {
                if (length < 0)
                    throw exceptions::negative_exception("length can't be negative");

                return length <= distance_;
            }

            /// \brief calculates if a point is within the range of the ray, this could be useful for a quick check before calculating the intersection
            /// \param point point to check
            /// \return true if point is within the range of the ray, otherwise false
            NODISCARD constexpr bool within_range(const point3d& point) const noexcept
            {
                return within_range(position_.distance(point));
            }

            /// \brief calculates the point on the ray at the given distance, if distance is out of range, std::nullopt will be returned
            /// \throws negative_exception if distance is negative
            /// \param distance distance from the position to the point
            /// \return point on the ray at the given distance, if distance is out of range, std::nullopt will be returned
            NODISCARD constexpr std::optional<point3d> get_point(const float distance) const
            {
                return within_range(distance) ? std::make_optional(position_ + direction_ * distance) : std::nullopt;
            }

            ///////////////////////////////////////////////////////
            ///                    operators                    ///
            ///////////////////////////////////////////////////////

            /// \brief copy assignment
            /// \param ray ray to copy
            /// \return reference to this
            ray& operator=(const ray& ray) noexcept = default;

            /// \brief move assignment
            /// \param ray ray to move
            /// \return reference to this
            ray& operator=(ray&& ray) noexcept = default;
        };
    } // namespace bardcore::utility
} // namespace bardcore
#endif //BARDCORE_RAY_H
