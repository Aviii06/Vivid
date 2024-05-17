#include "common/types/Types.h"
#include "core/ecs/components/TransformComponent.h"
#include "core/ecs/components/light/PointLightComponent.h"
#include "core/ecs/components/model/ModelComponent.h"
#include "core/ecs/components/light/DirectionalLightComponent.h"

#include "core/ecs/ComponentType.h"

namespace Vivid
{
	const Map<ComponentType, String> g_AllComponentStrings = {
		{ComponentType::TransformComponent, "Transform Component"},
		{ComponentType::ModelComponent, "Model Component"},
		{ComponentType::PointLightComponent, "Point Light Component"},
		{ComponentType::DirectionalLightComponent, "Directional Light Component"},
	};

}
