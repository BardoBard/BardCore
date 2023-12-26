#ifndef BARDCORE_NEGATIVE_EXCEPTION_H
#define BARDCORE_NEGATIVE_EXCEPTION_H
#include "BardCore/bardcore.h"

namespace bardcore
{
    namespace exception
    {
        class negative_exception : public bard_exception
        {
        public:
            using bard_exception::bard_exception;
        };
    } // namespace bardcore::exceptions
} // namespace bardcore

#endif //BARDCORE_NEGATIVE_EXCEPTION_H
