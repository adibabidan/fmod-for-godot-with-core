#include "core_api.h"

using namespace CoreApi;

void CoreSystem::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("create_sound", "name_or_data", "mode", "exinfo"), &CoreSystem::create_sound);
    ClassDB::bind_method(D_METHOD("play_sound", "sound", "channel_group", "paused"), &CoreSystem::play_sound);
    ClassDB::bind_method(D_METHOD("get_record_num_drivers"), &CoreSystem::get_record_num_drivers);
    ClassDB::bind_method(D_METHOD("get_record_driver_name", "id", "namelen"), &CoreSystem::get_record_driver_name);
    ClassDB::bind_method(D_METHOD("get_record_driver_rate_and_channels", "id"), &CoreSystem::get_record_driver_rate_and_channels);
    ClassDB::bind_method(D_METHOD("get_record_position", "id"), &CoreSystem::get_record_position);
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

Ref<Channel> CoreSystem::play_sound(const Ref<Sound>& sound, const Ref<ChannelGroup>& channel_group, bool paused) const
{
    FMOD::Channel* channel = nullptr;
    Ref<Channel> ref = create_ref<Channel>();

    if(ERROR_CHECK(core_system->playSound(sound->get_instance(), 0, paused, &channel)))
    {
        ref->set_instance(channel);
    }

    return ref;
}

Dictionary CoreSystem::get_record_num_drivers() const
{
    Dictionary record_num_drivers;

    int available{}, connected{};
    ERROR_CHECK(core_system->getRecordNumDrivers(&available, &connected));
    record_num_drivers["available"] = available;
    record_num_drivers["connected"] = connected;

    return record_num_drivers;
}

String CoreSystem::get_record_driver_name(int id, int namelen) const
{
	auto raw_buffer = std::string(namelen, ' ');
    raw_buffer.resize(namelen);

    if(ERROR_CHECK(core_system->getRecordDriverInfo(id, &raw_buffer[0], namelen, NULL, NULL, NULL, NULL, NULL)))
    {
        return String(raw_buffer.c_str());
    }

    return String();
}

Dictionary CoreSystem::get_record_driver_rate_and_channels(int id) const
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

unsigned int CoreSystem::get_record_position(int id) const
{
    unsigned int position = 0;
    if(ERROR_CHECK(core_system->getRecordPosition(id, &position)))
    {
        return position;
    }
    return position;
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
    ClassDB::bind_method(D_METHOD("get_length", "lengthtype"), &Sound::get_length);
    ClassDB::bind_method(D_METHOD("release"), &Sound::release);
}

void Sound::set_instance(FMOD::Sound* sound)
{
    this->sound = sound;
}

FMOD::Sound* Sound::get_instance() const
{
    return sound;
}

unsigned int Sound::get_length(FMOD_TIMEUNIT lengthtype) const
{
    unsigned int length{};

    if(ERROR_CHECK(sound->getLength(&length, lengthtype)))
    {
        return length;
    }

    return length;
}

bool Sound::release() const
{
    return ERROR_CHECK(sound->release());
}

void Channel::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_frequency", "frequency"), &Channel::set_frequency);
    ClassDB::bind_method(D_METHOD("set_paused", "paused"), &Channel::set_paused);
    ClassDB::bind_method(D_METHOD("get_dsp", "index"), &Channel::get_dsp);
}

void Channel::set_instance(FMOD::Channel* channel)
{
    this->channel = channel;
}

bool Channel::set_frequency(float frequency) const
{
    return ERROR_CHECK(channel->setFrequency(frequency));
}

bool Channel::set_paused(bool paused) const
{
    return ERROR_CHECK(channel->setPaused(paused));
}

Ref<DSP> Channel::get_dsp(int index) const
{
    FMOD::DSP* dsp = nullptr;
    Ref<DSP> ref = create_ref<DSP>();

    if(ERROR_CHECK(channel->getDSP(index, &dsp)))
    {
        ref->set_instance(dsp);
    }

    return ref;
}

void ChannelGroup::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_paused", "paused"), &ChannelGroup::set_paused);
    ClassDB::bind_method(D_METHOD("get_dsp", "index"), &ChannelGroup::get_dsp);
}

void ChannelGroup::set_instance(FMOD::ChannelGroup* channel_group)
{
    this->channel_group = channel_group;
}

FMOD::ChannelGroup* ChannelGroup::get_instance() const
{
    return channel_group;
}

bool ChannelGroup::set_paused(bool paused) const
{
    return ERROR_CHECK(channel_group->setPaused(paused));
}

Ref<DSP> ChannelGroup::get_dsp(int index) const
{
    FMOD::DSP* dsp = nullptr;
    Ref<DSP> ref = create_ref<DSP>();

    if(ERROR_CHECK(channel_group->getDSP(index, &dsp)))
    {
        ref->set_instance(dsp);
    }

    return ref;
}

void DSP::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_dsp"), &DSP::get_metering_info);
}

void DSP::set_instance(FMOD::DSP* dsp)
{
    this->dsp = dsp;
}

Dictionary DSP::get_metering_info() const
{
    Dictionary metering_info;

    Ref<FmodTypes::FMOD_DSP_METERING_INFO> inputRef = create_ref<FmodTypes::FMOD_DSP_METERING_INFO>();
    Ref<FmodTypes::FMOD_DSP_METERING_INFO> outputRef = create_ref<FmodTypes::FMOD_DSP_METERING_INFO>();

    FMOD_DSP_METERING_INFO input{}, output{};
    
    if(ERROR_CHECK(dsp->getMeteringInfo(&input, &output)))
    {
        inputRef->set_fmod_dsp_metering_info(input);
        outputRef->set_fmod_dsp_metering_info(output);

        metering_info["input"] = inputRef;
        metering_info["output"] = outputRef;
    }

    return metering_info;
}