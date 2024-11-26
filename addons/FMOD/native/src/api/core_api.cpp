#include "core_api.h"

using namespace CoreApi;

void CoreSystem::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("create_sound", "name_or_data", "mode", "exinfo"), &CoreSystem::create_sound);
}

void CoreSystem::set_instance(FMOD::System* core_system)
{
    this->core_system = core_system;
}

Ref<Sound> CoreSystem::create_sound(const String& name_or_data, FMOD_MODE mode, const Ref<FmodTypes::FMOD_CREATESOUNDEXINFO>& exinfo) const
{
    FMOD::Sound* sound = nullptr;
    Ref<Sound> ref = create_ref<Sound>();

    FMOD_CREATESOUNDEXINFO info{};
    exinfo->get_createsoundexinfo(info);

    if (ERROR_CHECK(core_system->createSound(name_or_data.utf8().get_data(), mode, &info, &sound)))
    {
        ref->set_instance(sound)
    }

    return ref;
}

void Sound::_bind_methods()
{

}

void Sound::set_instance(FMOD::Sound* sound)
{
    this->sound = sound;
}

void Channel::_bind_methods()
{

}

void Channel::set_instance(FMOD::Channel* channel)
{
    this->channel = channel;
}

void ChannelGroup::_bind_methods()
{

}

void ChannelGroup::set_instance(FMOD::ChannelGroup* channel_group)
{
    this->channel_group = channel_group;
}

void DSP::_bind_methods()
{

}

void DSP::set_instance(FMOD::DSP* dsp)
{
    this->dsp = dsp;
}