#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLAPI.h"

namespace Dizzy {

	//Future include metal
	RendererAPI* RenderCommand::s_rendererAPI = new OpenGLAPI();

}