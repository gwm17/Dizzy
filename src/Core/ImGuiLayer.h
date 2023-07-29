#pragma once

//Ehh
#ifdef DZ_WINDOWS
#include "Platform/OpenGL/ImGuiLayerOGL.h"
#endif

//Eventually replace with metal
#ifdef DZ_APPLE
#include "Platform/OpenGL/ImGuiLayerOGL.h"
#endif

//OpenGL is appropriate here
#ifdef DZ_LINUX
#include "Platform/OpenGL/ImGuiLayerOGL.h"
#endif

namespace Dizzy {

	static ImGuiLayer* CreateImGuiLayer()
	{
		return new ImGuiLayer();
	}
}