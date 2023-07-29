#pragma once

#include "Core/DZCore.h"
#include "glm/glm.hpp"

namespace Dizzy {

	class RendererAPI
	{
	public:
		enum class API
		{
			OpenGL,
			None
		};
		RendererAPI(API api)
		{
			s_api = api;
		}

		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual float GetFrameTime() = 0;

		static API GetAPI() { return s_api; }

	private:
		static API s_api;
	};
}