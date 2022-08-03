// Author: Milan Dierick
// Solution: Heirloom

#include "hlpch.h"
#include "Layer.h"

namespace Heirloom
{
	Layer::Layer(const std::string& debugName)
			: m_DebugName(debugName)
	{
	}

	const std::string& Layer::GetName() const
	{
		return m_DebugName;
	}
}
