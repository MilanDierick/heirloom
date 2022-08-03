// Author: Milan Dierick
// Solution: Heirloom

#include "hlpch.h"
#include "LayerStack.h"

Heirloom::LayerStack::LayerStack()
		: m_LayerInsertIndex(0)
{
}

Heirloom::LayerStack::~LayerStack()
{
	HL_PROFILE_FUNCTION()

	for (Layer* layer : m_Layers)
	{
		layer->OnDetach();
		delete layer;
	}
}

void Heirloom::LayerStack::PushLayer(Layer* layer)
{
	HL_PROFILE_FUNCTION()

	m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
	++m_LayerInsertIndex;
}

void Heirloom::LayerStack::PushOverlay(Layer* overlay)
{
	HL_PROFILE_FUNCTION()

	m_Layers.emplace_back(overlay);
}

void Heirloom::LayerStack::PopLayer(Layer* layer)
{
	HL_PROFILE_FUNCTION()

	const auto it = std::ranges::find(m_Layers, layer);
	if (it != m_Layers.end())
	{
		m_Layers.erase(it);
		--m_LayerInsertIndex;
	}
}

void Heirloom::LayerStack::PopOverlay(Layer* overlay)
{
	HL_PROFILE_FUNCTION()

	const auto it = std::ranges::find(m_Layers, overlay);
	if (it != m_Layers.end())
	{
		m_Layers.erase(it);
	}
}

std::vector<Heirloom::Layer*>::iterator Heirloom::LayerStack::begin()
{
	return m_Layers.begin();
}

std::vector<Heirloom::Layer*>::iterator Heirloom::LayerStack::end()
{
	return m_Layers.end();
}

std::vector<Heirloom::Layer*>::const_iterator Heirloom::LayerStack::cbegin() const
{
	return m_Layers.cbegin();
}

std::vector<Heirloom::Layer*>::const_iterator Heirloom::LayerStack::cend() const
{
	return m_Layers.cend();
}
