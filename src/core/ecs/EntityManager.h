#pragma once
#include <common/types/Types.h>
#include "Entity.h"
#include "ComponentType.h"

namespace Vivid
{
	class EntityManager
	{
	private:
		Vector<Entity> m_entities;
		Vector<size_t> m_EntityIDToIndex;
		int m_totalEntities;

	public:
		EntityManager();

		Entity CreateEntity();
		bool DeleteEntity(EntityID id);

		Signature GetComponents(EntityID id);
	};

}
