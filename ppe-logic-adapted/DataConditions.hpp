#ifndef HEADER_GUARD_QKIFSNLROZOXGSUJ
#define HEADER_GUARD_QKIFSNLROZOXGSUJ

#include "Data.hpp"

inline bool isGearPositionParking(InputData const& data)
{
    return data.parking_position;
}

inline bool isIgnitionOn(InputData const& data)
{
    return data.ignition_on;
}

#endif // HEADER_GUARD_QKIFSNLROZOXGSUJ
