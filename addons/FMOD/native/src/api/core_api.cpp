#include "core_api.h"

using namespace CoreApi;

void CoreSystem::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("create_sound", "name_or_data", "mode", "exinfo"), &CoreSystem::create_sound);
    ClassDB::bind_method(D_METHOD("get_record_driver_name", "id", "namelen"), &CoreSystem::get_record_driver_name);
    ClassDB::bind_method(D_METHOD("get_record_driver_rate_and_channels", "id"), &CoreSystem::get_record_driver_rate_and_channels);
    ClassDB::bind_method(D_METHOD("record_start", "id", "sound", "loop"), &CoreSystem::record_start);
    ClassDB::bind_method(D_METHOD("record_stop", "id"), &CoreSystem::record_stop);
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
        ref->set_instance(sound);
    }

    return ref;
}

Dictionary CoreSystem::get_record_num_drivers()
{
    Dictionary record_num_drivers;

    int available{}, connected{};
    ERROR_CHECK(core_system->getRecordNumDrivers(&available, &connected));
    record_num_drivers["available"] = available;
    record_num_drivers["connected"] = connected;

    return record_num_drivers;
}

String CoreSystem::get_record_driver_name(int id, int namelen)
{
    String name;
    char buffer[namelen];
    if(ERROR_CHECK(core_system->getRecordDriverInfo(id, &buffer, namelen, NULL, NULL, NULL, NULL, NULL)))
    {
        name.assign(buffer, namelen);
    }

    return name;
}

Dictionary CoreSystem::get_record_driver_rate_and_channels(int id)
{
    Dictionary record_driver_info;
    int native_rate;
    int native_channels;
    if(ERROR_CHECK(core_system->getRecordDriverInfo(id, NULL, 0, NULL, &native_rate, NULL, &native_channels, NULL)))
    {
        record_driver_info["rate"] = native_rate;
        record_driver_info["channels"] = native_channels;
    }

    return record_driver_info;
}

bool CoreSystem::record_start(int id, const Ref<Sound>& sound, bool loop) const
{
    return ERROR_CHECK(core_system->recordStart(id, sound->get_instance(), loop));
}

bool CoreSystem::record_stop(int id) const
{
    return ERROR_CHECK(core_system->recordStop(id));
}

void Sound::_bind_methods()
{

}

void Sound::set_instance(FMOD::Sound* sound)
{
    this->sound = sound;
}

FMOD::Sound* Sound::get_instance()
{
    return sound;
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