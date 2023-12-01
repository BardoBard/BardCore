#ifndef BARDCORE_NEGATIVE_EXCEPTION_H
#define BARDCORE_NEGATIVE_EXCEPTION_H
#include "../bardcore.h"

namespace bardcore
{
    class negative_exception : public bard_exception
    {
    public:
        using bard_exception::bard_exception;
    };
} // namespace bardcore

#endif //BARDCORE_NEGATIVE_EXCEPTION_H
