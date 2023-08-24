#pragma once

namespace Vivid
{
	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;
		virtual void Draw() = 0;
		virtual void ImGuiRender() = 0;
	};
}
