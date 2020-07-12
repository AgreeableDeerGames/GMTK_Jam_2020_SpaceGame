#include <ProjectTemplate/Core/DataPad.h>

using namespace PT;



DataPad::DataPad() :
	m_bindVec(),
	m_controls()
{

}

bool DataPad::handleEvent(sf::Int64 elapsedTime, const sf::Event& event)
{
	return m_controls.handleEvent(elapsedTime, event);
}

void DataPad::AddBind(NumberGestureBind bind)
{
	m_bindVec.emplace_back(std::move(bind));
	RegenerateControls();
}

void DataPad::ReplaceBind(std::string name, NumberGestureBind bind)
{
	bind.setName(name);
	auto found = std::find_if(
		std::begin(m_bindVec),
		std::end(m_bindVec),
		[&](const NumberGestureBind& value) {return value.getName() == name; });

	if (found != std::end(m_bindVec))
	{
		*found = bind;
		RegenerateControls();
	}
	else
	{
		throw std::runtime_error("could not find bind to replace");
	}
}

const NumberGestureBind* DataPad::GetBindWithName(const std::string& name)
{
	auto found = std::find_if(
		std::begin(m_bindVec),
		std::end(m_bindVec),
		[&](const NumberGestureBind& value) {return value.getName() == name; });
	if (found == std::end(m_bindVec))
	{
		return nullptr;
	}
	return &(*found);
}


void DataPad::RegenerateControls()
{
	NumberGestureHandler newControls;
	for (const auto& bind : m_bindVec)
	{
		newControls.addGesture(bind);
	}
	m_controls = std::move(newControls);
}