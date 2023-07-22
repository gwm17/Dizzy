#pragma once

#include "Layer.h"

namespace Dizzy {

	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		std::vector<Layer*>::iterator begin() { return m_stack.begin(); }
		std::vector<Layer*>::iterator end() { return m_stack.end(); }

	private:
		std::vector<Layer*> m_stack;
		std::size_t m_insertPosition;
	};
}