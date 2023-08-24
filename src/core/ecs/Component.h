#pragma once
#include "editor/camera/Camera.h"

namespace Vivid
{
	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;
		virtual void Draw(Camera* camera) = 0;
		virtual void ImGuiRender() = 0;
	};
}
