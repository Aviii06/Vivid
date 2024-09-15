#pragma once
#include <common/types/Types.h>

namespace Vivid
{
	enum class ComponentType
	{
		TransformComponent = 1,
		ModelComponent = 2,
		// PointLightComponent,
		DirectionalLightComponent = 3,
		_size = 4,
	};
	constexpr size_t MAX_COMPONENTS = 32;

	using Signature = std::bitset<MAX_COMPONENTS>;


}