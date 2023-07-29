#pragma once

#include "Core/Layer.h"

namespace Dizzy {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		virtual ~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;

		void OnImGuiRender() override;

		void Begin();
		void End();

	private:

	};
}