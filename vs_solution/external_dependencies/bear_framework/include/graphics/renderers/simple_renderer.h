#pragma once

#include"../renderable.h"

namespace bear { namespace graphics { 

	class SimpleRenderer {
	private:
		unsigned int VBO;
		unsigned int VAO;
		unsigned int TBO;

	public:
		// Constructor
		SimpleRenderer();

		// 
		void draw(Renderable& renderable);

	private:
		void GL_draw_call();
	};

} }