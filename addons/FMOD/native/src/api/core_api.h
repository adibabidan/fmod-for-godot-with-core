#ifndef CORE_API
#define CORE_API

#include "fmod_types.h"

namespace CoreApi
{

class Sound;
// note(aidan): i don't know c++ well enough to figure out how to port this ChannelControl abstraction over naturally
//              so just be wary that you might have to fix some bugs twice.
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
};

} // namespace CoreApi

#endif // CORE_API