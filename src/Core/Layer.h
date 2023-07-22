#pragma once

namespace Dizzy {

	class Layer
	{
	public:
		Layer(const std::string& name = "DefaultLayer");
		virtual ~Layer();

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnEvent() {};
		virtual void OnUpdate() {};

		const std::string& GetName() { return m_name; }

	private:
		std::string m_name;
	};
}