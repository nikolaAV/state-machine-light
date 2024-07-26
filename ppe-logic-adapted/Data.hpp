#ifndef HEADER_GUARD_EPRBVSMSUEDPRILX
#define HEADER_GUARD_EPRBVSMSUEDPRILX

#include "FeatureState.hpp"

struct InputData
{
    bool ignition_on{false};      // m_KST_KL_15
    bool parking_position{false}; // m_DPM_StDispDrvPosn
};

struct OutputData
{
    EFeatureState feature_state{EFeatureState::Off};
};

#endif // HEADER_GUARD_EPRBVSMSUEDPRILX
