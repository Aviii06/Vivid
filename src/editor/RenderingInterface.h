#pragma once
#include "confs/DynamicExportingMacros.h"

class VIVAPI RenderingInterface
{
public:
	virtual void Setup() = 0;
	virtual void Draw() = 0;
	virtual void ImGuiRender() = 0;
	virtual void Input() = 0;
};