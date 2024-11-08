#ifndef CORE_API
#define CORE_API

#include "fmod_types.h"

namespace CoreApi
{

class CoreSystem : public RefCounted
{
    GDCLASS(CoreSystem, RefCounted)

protected:
    static void _bind_methods();

private:
    FMOD::System* core_system = nullptr;

public:
    void set_instance(FMOD::System* core_system);
};

}