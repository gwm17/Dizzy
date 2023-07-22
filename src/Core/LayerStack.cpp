#include "LayerStack.h"

namespace Dizzy {

	LayerStack::LayerStack() :
		m_insertPosition(0)
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_stack)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_stack.emplace(m_stack.begin() + m_insertPosition, layer);
		m_insertPosition += 1;
	}

	void LayerStack::PushOverlay(Layer* layer)
	{
		m_stack.emplace_back(layer);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto iter = std::find(m_stack.begin(), m_stack.end(), layer);
		if (iter != m_stack.end())
		{
			m_stack.erase(iter);
			m_insertPosition--;
		}
	}

	void LayerStack::PopOverlay(Layer* layer)
	{
		auto iter = std::find(m_stack.begin(), m_stack.end(), layer);
		if (iter != m_stack.end())
			m_stack.erase(iter);
	}

}