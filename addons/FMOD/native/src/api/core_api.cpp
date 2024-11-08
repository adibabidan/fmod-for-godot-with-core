#include "studio_api.h"

using namespace CoreApi;

void CoreSystem::_bind_methods()
{

}

void CoreSystem::set_instance(FMOD::System* core_system)
{
    this->core_system = core_system;
}