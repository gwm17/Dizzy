#pragma once

#include "Core/DZCore.h"
#include "RendererAPI.h"
#include "glm/glm.hpp"

namespace Dizzy {

	class RenderCommand
	{
	public:
		static void SetClearColor(const glm::vec4& color) { s_rendererAPI->SetClearColor(color); }
		static void Clear() { s_rendererAPI->Clear(); }
		static float GetFrameTime() { s_rendererAPI->GetFrameTime(); }

	private:
		static RendererAPI* s_rendererAPI;
	};
}