//
// Created by developer on 09/12/2021.
//

#ifndef HEIRLOOM_OPENGLFRAMEBUFFER_H
#define HEIRLOOM_OPENGLFRAMEBUFFER_H

#include "Heirloom/Renderer/FrameBuffer.h"

namespace Heirloom
{
	class OpenGLFramebuffer final : public Framebuffer
	{
	public:
		explicit OpenGLFramebuffer(const FramebufferSpecification& spec);
		~OpenGLFramebuffer() override;

		void Invalidate();

		void Bind() override;
		void Unbind() override;

		void Resize(uint32_t width, uint32_t height) override;

		uint32_t GetColorAttachmentRendererID() const override;
		const FramebufferSpecification& GetSpecification() const override;

	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
		FramebufferSpecification m_Specification;
	};
}

#endif //HEIRLOOM_OPENGLFRAMEBUFFER_H
