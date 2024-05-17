#include "core/ecs/Component.h"
#include "core/ecs/ECS.h"

Vivid::Component::Component()
	 :m_ID(ECS::s_EntityID++)
{
}
