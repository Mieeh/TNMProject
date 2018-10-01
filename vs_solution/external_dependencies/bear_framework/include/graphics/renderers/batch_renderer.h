#pragma once

#include<vector>
#include<deque>

#include"../vertex.h"
#include"unlit_batch.h"

#include"../framebuffer.h"

namespace bear { namespace core {
	class Matrix4x4;
} }

typedef unsigned int GLenum;

namespace bear { namespace graphics {

#define VERTEX_SIZE sizeof(Vertex)
#define QUAD_SIZE VERTEX_SIZE * 6 // 6 indices
#define QUAD_MAX_COUNT 40963 // 64*64
#define UNLIT_BUFFER_SIZE QUAD_SIZE * QUAD_MAX_COUNT

	/*
	* This renderer batches data into one big buffer (for unlit-primitives)
	* When dealing with rendering textures, we render them after dealing with the unlit-primitives
	* REASON: I don't know how to batch triangle + quads + sprites so this renderer renders sprites seperate from triangle + quads
	*/

	class Shader;
	class Renderable;
	class View;

	class BatchRenderer {
	private:
		UnlitBatcher *m_UnlitBatch;
		unsigned int m_IndicesCount = 0;
		std::vector<Renderable*> m_RenderableList;
		std::vector<unsigned int> textureSlots;

		// Used by default if none is submitted by the flush caller	
		static View& defaultView;
		
	public:
		BatchRenderer();
		~BatchRenderer();
	
		/*
		* call init or the renderer won't work
		*/
		void init();

		/*
		* Render routines, use submit between begin&flush
		* begin prepares the renderer for new data through submit
		* flush renders the submitted data
		*/
		void begin();
		void submit(Renderable* a_Renderable);
		void fill_buffer();
		void flush(View& a_View = defaultView);

	private:
		static bool _layer_compare(Renderable* a_R1, Renderable* a_R2);
	};

} }