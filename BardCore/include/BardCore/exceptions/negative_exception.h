#ifndef BARDCORE_NEGATIVE_EXCEPTION_H
#define BARDCORE_NEGATIVE_EXCEPTION_H
#include "../bardcore.h"

namespace bardcore::exceptions
{
    class negative_exception : public bard_exception
    {
    public:
        using bard_exception::bard_exception;
    };
} // namespace bardcore::exceptions

#endif //BARDCORE_NEGATIVE_EXCEPTION_H
