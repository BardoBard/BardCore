#ifndef BARDCORE_ZERO_DIVISION_H
#define BARDCORE_ZERO_DIVISION_H
#include "BardCore/bardcore.h"

namespace bardcore
{
    namespace exception
    {
        class zero_exception : public bard_exception
        {
        public:
            using bard_exception::bard_exception;
        };
    } // namespace bardcore::exceptions
} // namespace bardcore

#endif //BARDCORE_ZERO_DIVISION_H
