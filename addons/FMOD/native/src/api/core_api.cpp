#include "core_api.h"

using namespace CoreApi;

void CoreSystem::_bind_methods()
{

}

void CoreSystem::set_instance(FMOD::System* core_system)
{
    this->core_system = core_system;
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