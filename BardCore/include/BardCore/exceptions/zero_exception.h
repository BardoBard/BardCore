#ifndef BARDCORE_ZERO_DIVISION_H
#define BARDCORE_ZERO_DIVISION_H
#include "../bardcore.h"

namespace bardcore::exceptions
{
    class zero_exception : public bard_exception
    {
    public:
        using bard_exception::bard_exception;
    };
} // namespace bardcore::exceptions

#endif //BARDCORE_ZERO_DIVISION_H
