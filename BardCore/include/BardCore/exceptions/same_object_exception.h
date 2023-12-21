#ifndef BARDCORE_SAME_OBJECT_EXCEPTION_H
#define BARDCORE_SAME_OBJECT_EXCEPTION_H
#include "BardCore/bardcore.h"

namespace bardcore
{
    namespace exceptions
    {
        class same_object_exception : public bard_exception
        {
        public:
            using bard_exception::bard_exception;
        };
    } // namespace bardcore::exceptions
} // namespace bardcore

#endif //BARDCORE_SAME_OBJECT_EXCEPTION_H
