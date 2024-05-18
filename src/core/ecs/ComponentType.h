#pragma once


namespace Vivid
{
	/*!
	 * @enum ComponentType
	 * @brief Contains the types of components.
	 * @details ComponentType is an enum class that contains the types of components that can be added to an entity.
	 */
	enum class ComponentType
	{
		TransformComponent,
		ModelComponent,
		PointLightComponent,
		DirectionalLightComponent,
		_size,
	};

}