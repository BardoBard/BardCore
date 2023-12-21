#ifndef BARDCORE_LIGHT_H
#define BARDCORE_LIGHT_H

#include "BardCore/utility/ray.h"
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
            float intensity;

        public:
            /**
             * \brief constructor for light
             * \param position origin of the light
             * \param intensity intensity of the light
             */
            constexpr light(const point3d& position, const float intensity) : position(position), intensity(intensity)
            {
            }

        private:
            /**
             * \brief this is a helper function for calculating the inverse square law
             * \note read more at: https://en.wikipedia.org/wiki/Inverse-square_law
             * \throws zero_exception if length is zero
             * \param length_squared length squared, e.g. length * length
             * \return intensity across distance
             */
            NODISCARD constexpr float inverse_square_law_squared(const float length_squared) const
            {
                if (length_squared <= 0.f)
                    throw exceptions::zero_exception("length must not be zero");

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
            NODISCARD constexpr float inverse_square_law(const point3d& point) const
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
            NODISCARD constexpr float inverse_square_law(const float length) const
            {
                return inverse_square_law_squared(length * length);
            }
        };
    } // namespace bardcore::utility
} // namespace bardcore
#endif //BARDCORE_LIGHT_H
