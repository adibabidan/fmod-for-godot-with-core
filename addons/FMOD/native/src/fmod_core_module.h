#ifndef FMOD_CORE_MODULE_H
#define FMOD_CORE_MODULE_H

#include "api/core_api.h"

class FMODCoreModule : public Object
{
    GDCLASS(FMODCoreModule, Object);

protected:
    static void _bind_methods();

public:
    using FMOD_SOUND_FORMAT = ::FMOD_SOUND_FORMAT;
    using FMOD_SOUND_TYPE = ::FMOD_SOUND_TYPE;
    using FMOD_CHANNELCONTROL_DSP_INDEX = ::FMOD_CHANNELCONTROL_DSP_INDEX;
};

VARIANT_ENUM_CAST(FMODCoreModule::FMOD_SOUND_FORMAT);
VARIANT_ENUM_CAST(FMODCoreModule::FMOD_SOUND_TYPE);
VARIANT_ENUM_CAST(FMODCoreModule::FMOD_CHANNELCONTROL_DSP_INDEX);

#endif // FMOD_CORE_MODULE_H