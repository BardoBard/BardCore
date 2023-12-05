#ifndef BARDCORE_SAME_OBJECT_EXCEPTION_H
#define BARDCORE_SAME_OBJECT_EXCEPTION_H
#include "../bardcore.h"

namespace bardcore::exceptions
{
    class same_object_exception : public bard_exception
    {
    public:
        using bard_exception::bard_exception;
    };
} // namespace bardcore::exceptions

#endif //BARDCORE_SAME_OBJECT_EXCEPTION_H
