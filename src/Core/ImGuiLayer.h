#pragma once

#include "Platform/OpenGL/ImGuiLayerOGL.h"

namespace Dizzy {

	static ImGuiLayer* CreateImGuiLayer()
	{
		return new ImGuiLayer();
	}
}