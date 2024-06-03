#pragma once
#include <common/types/Types.h>
#include <iostream>
#include "Entity.h"


namespace Vivid
{
	class IComponentArray
	{

	};
	template <typename T>
	class ComponentArray : public IComponentArray
	{
	private:
		Vector<T> m_components;
		Map<EntityID, size_t> m_entityToIndex;
		Map<size_t, EntityID> m_indexToEntity;
		size_t m_size;

	public:
		ComponentArray()
		{
			m_components.reserve(MAX_ENTITIES);
			m_size = 0;
		}

		void Insert(Entity entity, T component)
		{
			if (m_entityToIndex.find(entity.GetID()) == m_entityToIndex.end())
			{
				std::cerr << "Cannot add the same component to the same entity. EntityID: " << entity.GetID() << std::endl;
				return;
			}

			m_components[entity.GetID()] = component;
			m_entityToIndex[entity.GetID()] = m_size;
			m_indexToEntity[m_size] = entity.GetID();
			m_size++;
		}

		void Remove(Entity entity)
		{
			if (m_entityToIndex.find(entity.GetID()) != m_entityToIndex.end())
			{
				std::cerr << "The entity with EntityID: " << entity.GetID() << " doesn't contain the component" << std::endl;
				return;
			}

			size_t removedEntityIndex = m_entityToIndex[entity.GetID()];
			size_t lastElementIndex = m_size - 1;

			m_components[removedEntityIndex] = m_components[lastElementIndex];

			EntityID last_entity_id = m_indexToEntity[lastElementIndex];
			m_entityToIndex[last_entity_id] = removedEntityIndex;
			m_indexToEntity[removedEntityIndex] = last_entity_id;

			// m_components.pop_back();
			m_entityToIndex.erase(entity.GetID());
			m_indexToEntity.erase(lastElementIndex);

			--m_size;
		}

		T& Get(Entity entity)
		{
			if (m_entityToIndex.find(entity.GetID()) != m_entityToIndex.end())
			{
				std::cerr << "Couldn't get the component of the entity with EntityID: " << entity.GetID() << std::endl;
			}

			return m_components[m_entityToIndex[entity.GetID()]];
		}

	};

}
