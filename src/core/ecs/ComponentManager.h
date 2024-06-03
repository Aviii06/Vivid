#pragma once
#include "ComponentArray.h"
#include "ComponentType.h"

#include <common/types/Types.h>
#include <common/types/SmartPointers.h>

namespace Vivid
{
	class ComponentManager
	{
	private:
		Map<ComponentType, Ref<IComponentArray>> m_componentArrays;
		template<typename T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray()
		{
			return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[T::GetComponentType()]);
		}

	public:
		template <typename T>
		void AddComponent(Entity entity, T component)
		{
			GetComponentArray<T>()->InsertData(entity, component);
		}

		template <typename T>
		void RemoveComponent(Entity entity, T component)
		{
			GetComponentArray<T>()->RemoveData(entity);
		}

		template <typename T>
		T& GetComponent(Entity entity)
		{
			return GetComponentArray<T>()->Get(entity);
		}
	};
}

