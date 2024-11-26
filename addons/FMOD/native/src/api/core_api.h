#ifndef CORE_API
#define CORE_API

#include "fmod_types.h"

namespace CoreApi
{

class Sound;
class Channel;
class ChannelGroup;
class DSP;

class CoreSystem : public RefCounted
{
    GDCLASS(CoreSystem, RefCounted);

protected:
    static void _bind_methods();

private:
    FMOD::System* core_system = nullptr;

public:
    void set_instance(FMOD::System* core_system);

    Ref<Sound> create_sound(const String& name_or_data, FMOD_MODE mode, const Ref<FmodTypes::FMOD_CREATESOUNDEXINFO>& exinfo) const;
    Dictionary get_record_num_drivers() const;
    // abstracting getRecordDriverInfo() into multiple functions thanks to it's rather intense use of out parameters
    String get_record_driver_name(int id) const;
    Dictionary get_record_driver_rate_and_channels(int id) const;
    bool record_start(int id, const Ref<Sound>& sound, bool loop) const;
    bool record_stop(int id) const;
};

class Sound
{
    GDCLASS(Sound, RefCounted);

protected:
    static void _bind_methods();

private:
    FMOD::Sound* sound = nullptr;

public:
    void set_instance(FMOD::Sound* sound);
    FMOD::Sound* get_instance() const;

    unsigned int get_length(FMOD_TIMEUNIT lengthtype) const;
    bool release() const;
};

class Channel
{
    GDCLASS(Channel, RefCounted);

protected:
    static void _bind_methods();

private:
    FMOD::Channel* channel = nullptr;

public:
    void set_instance(FMOD::Channel* channel);

    bool set_frequency(float frequency) const;
    bool set_paused(bool paused) const;
    Ref<DSP> get_dsp(int index) const;
};

class ChannelGroup
{
    GDCLASS(ChannelGroup, RefCounted);

protected:
    static void _bind_methods();

private:
    FMOD::ChannelGroup* channel_group = nullptr;

public:
    void set_instance(FMOD::ChannelGroup* channel_group);

    // note(aidan): i don't know c++ well enough to figure out how to port this ChannelControl abstraction over naturally
    //              so just be wary that you might have to fix some bugs twice.

    bool set_paused(bool paused) const;
    Ref<DSP> get_dsp(int index) const;
};

class DSP
{
    GDCLASS(DSP, RefCounted);

protected:
    static void _bind_methods();

private:
    FMOD::DSP* dsp = nullptr;

public:
    void set_instance(FMOD::DSP* dsp);

    Dictionary get_metering_info() const;
};

} // namespace CoreApi

#endif // CORE_API