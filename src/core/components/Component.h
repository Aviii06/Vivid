#pragma once

namespace Vivid
{
	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;
		virtual void OnUpdate() = 0;
		virtual void OnRender() = 0;
		virtual void OnImGuiRender() = 0;
	};
}
