#include "RenderCommand.h"

//Ehh
#ifdef DZ_WINDOWS
#include "Platform/OpenGL/OpenGLAPI.h"

namespace Dizzy {

	//Future include metal
	RendererAPI* RenderCommand::s_rendererAPI = new OpenGLAPI();

}
#endif

//Eventually replace with Metal
#ifdef DZ_APPLE
#include "Platform/OpenGL/OpenGLAPI.h"

namespace Dizzy {

	//Future include metal
	RendererAPI* RenderCommand::s_rendererAPI = new OpenGLAPI();

}
#endif

//OpenGL is appropriate here
#ifdef DZ_LINUX
#include "Platform/OpenGL/OpenGLAPI.h"

namespace Dizzy {

	//Future include metal
	RendererAPI* RenderCommand::s_rendererAPI = new OpenGLAPI();

}
#endif