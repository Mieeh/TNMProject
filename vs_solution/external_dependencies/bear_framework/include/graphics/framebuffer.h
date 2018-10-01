#pragma once

#include<string>

typedef unsigned int GLenum;
#define GL_COLOR_ATTACHMENT0 0x8CE0

namespace bear { namespace graphics {

	class Shader;

	class Framebuffer {
	private:
		unsigned int m_FBO;
		unsigned int m_TBO;
		GLenum m_DrawBuffer[1] = { GL_COLOR_ATTACHMENT0 };
		unsigned int m_QuadVBO, m_QuadVAO;
		Shader* m_FramebufferShader;

		unsigned int m_TargetFBO = 0;

	public:            
		Framebuffer(unsigned int a_Width, unsigned int a_Height);
		~Framebuffer();

		void setShader(std::string a_ShaderName);
		void setFramebufferRenderTarget(unsigned int a_FBO);
		void windowResize(unsigned int a_Width, unsigned int a_Height);

		void clearFBO();               // binds and clears the framebuffer color buffer
		void bind();				   // bind the framebuffer to be rendered
		void unbind();				   // unbind the framebuffer
		static void FBOunbind();	   // Dummy method for unbding and drawing to the screen
		void drawFramebufferTextureToScreen(); // Draw the framebuffer texture
		unsigned int getFBO();
	};

} }