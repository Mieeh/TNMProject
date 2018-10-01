#pragma once

namespace bear { namespace graphics {

	typedef unsigned int GLenum; 

	struct VertexAttribute {
		// glVertexAttribPointer(index, count, type, normalize, stride, starting_offset)
		unsigned int index;
		unsigned int count;
		GLenum type;
		bool normalize;
		size_t stride;
		void* starting_offset;
	};
	struct Vertex;

	class UnlitBatcher {
	private:
		unsigned int m_VBO;
		unsigned int m_VAO;

		const size_t c_BatchSize;
		size_t m_ByteSizeOffset;

	public:
		// Constructor 
		// param 1: max size for batch in bytes
		UnlitBatcher(size_t a_BatchSize, VertexAttribute* a_VertexAttributes, size_t a_AttributeCount);

		// Destructor
		~UnlitBatcher();

		// Method for clearing the batch 
		void clearBatch();

		// Method for adding to the batch
		bool updateBatch(void *a_Data, size_t a_Size);

		// Binds the batch 
		// Binds to: OpenGL VertexArray & GL_ARRAY_BUFFER
		void bindBatch();
	};

} }