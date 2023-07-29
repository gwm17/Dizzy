#pragma once

#include "Renderer/RendererAPI.h"

namespace Dizzy {

	class OpenGLAPI : public RendererAPI
	{
	public:
		OpenGLAPI() :
			RendererAPI(RendererAPI::API::OpenGL)
		{
		}
		virtual void Clear() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual float GetFrameTime() override;
	};
}