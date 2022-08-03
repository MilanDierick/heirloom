// Author: Milan Dierick
// Solution: Heirloom

#ifndef HEIRLOOM_LAYERSTACK_H
#define HEIRLOOM_LAYERSTACK_H

#include "Layer.h"

namespace Heirloom
{
	/**
	 * \brief Manages the different layers
	 */
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		LayerStack(const LayerStack& other)                = delete;
		LayerStack(LayerStack&& other) noexcept            = delete;
		LayerStack& operator=(const LayerStack& other)     = delete;
		LayerStack& operator=(LayerStack&& other) noexcept = delete;

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		// ReSharper disable CppInconsistentNaming
		std::vector<Layer*>::iterator begin();
		std::vector<Layer*>::iterator end();
		std::vector<Layer*>::const_iterator cbegin() const;
		std::vector<Layer*>::const_iterator cend() const;
		// ReSharper restore CppInconsistentNaming

	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex;
	};
}

#endif //HEIRLOOM_LAYERSTACK_H
