#pragma once

#include"../core/vector2.h"
#include"image.h"

namespace bear { namespace graphics { 

	class Texture {
	private:
		unsigned int m_TBO;
		core::Vector2i m_Size;

	public:
		Texture(Image& a_Image);
		Texture(void *a_Data, core::Vector2i a_Size, image_format a_Format);
		Texture();
		~Texture();

		core::Vector2i getTextureSize();
		void setData(Image& a_Image);
		void bind();
		void unbind();
		int getTextureID();
	};

} } 