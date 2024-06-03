#pragma once
#include <common/types/Types.h>

namespace Vivid
{
	enum class ComponentType
	{
		TransformComponent,
		ModelComponent,
		// PointLightComponent,
		DirectionalLightComponent,
		_size
	};
	constexpr size_t MAX_COMPONENTS = 32;

	using Signature = std::bitset<MAX_COMPONENTS>;


}