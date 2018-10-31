#pragma once

#include<string>
#include<memory>

// Include files for the graphics module to work 
#include"vertex.h"
#include"shader.h"
#include"renderable.h"
#include"texture.h"
#include"image.h"
#include"text.h"
#include"view.h"
#include"framebuffer.h"
#include"renderers/slow_renderer.h"

#include"../core/file_utility.h"

namespace bear { namespace graphics {

	class Graphics {
		// Define some friendships between graphics classes
		friend class BatchRenderer;
		friend class TextLabel;
		friend class ParticleSource;
		friend class SlowRenderer;
	
	private:
		// Used by: BatchRenderer
		static Shader* s_DefaultShader;
		static Shader* s_DefaultShaderText;
		static Shader* s_DefaultParticleShader;
		
		static unsigned int m_ScreenWidth;
		static unsigned int m_ScreenHeight;

	public:
		/* 
		* Initalize GLEW OpenGL bindings 
		* Arguments: window width and height used for shaders
		*/
		static bool init(unsigned int a_Width, unsigned int a_Height);

		/* Deallocates shader objects */
		static bool exit();

		/*
		* Callback for when window size is changed
		*/
		static void window_resize_callback(unsigned int a_Width, unsigned int a_Height);
	};

	// Used by Graphics::s_DefaultShader
	static int default_shader_pos_location = 0;
	static int default_shader_col_location = 1;
	static int default_shader_uv_location = 2;
	static std::string default_vertex_shader_source[] = {
		"#version 330",

		"layout(location=0) in vec2 in_pos;",
		"layout(location=1) in vec4 in_color;",
		"layout(location=2) in vec2 in_uv;",
		"layout(location=3) in float texture_slot;",

		"uniform mat4 projection_matrix;",
		"uniform mat4 model_matrix = mat4(1.0);",
		"uniform mat4 view_matrix = mat4(1.0);",

		"out float ts;",
		"out vec4 out_color;",
		"out vec2 uv;",
		"out vec2 pos;",

		"void main() {",
		    "gl_Position = projection_matrix * model_matrix * view_matrix * vec4(in_pos.x, in_pos.y, 0, 1.0);",
		    "out_color = in_color;", 
			"uv = in_uv;", 
			"pos = in_pos;",
			//"ts = texture_slot;",
			"ts = -1;",
		"}" 
	};
	static std::string default_fragment_shader_source[] = {
		"#version 330",

		//"layout(location = 0) out vec3 color;", // This means that the variable color will write in the render target 0
		// Which happens to be our texture because DrawBuffers[0] is GL_COLOR_ATTATCHMENT, which is, renderedTexture

		"in vec4 out_color;",
		"in vec2 uv;",
		"in vec2 pos;",
		"in float ts;"

		"uniform sampler2D texture_sampler;",

		//"uniform sampler2D texture_samplers[14];",

		"void main() {",
			"if(uv.x > 0) { gl_FragColor = texture(texture_sampler, uv) * out_color; }",
			"else { gl_FragColor = out_color; }",
			//"gl_FragColor = out_color;",

			//"if(ts == -1) {",
			//    "gl_FragColor = out_color;", 
			//"}", 
			//"else {", 
		    //    "highp int _ts = int(ts);"
			//    "gl_FragColor = texture(texture_samplers[_ts], uv) * out_color;", 
			//	//"color = texture(texture_sampler, uv) * out_color;",
			//"}",  
		"}" 
	};

	// Used by Graphics::s_DefaultShaderText
	static std::string text_vertex_shader_source[] = {
		"#version 330 core",

		"layout(location = 0) in vec4 vertex;",

		"out vec2 TexCoords;",

		"uniform mat4 projection_matrix;",
		"uniform mat4 view_matrix = mat4(1.0f);",

		"void main() {",
		    "gl_Position = projection_matrix * view_matrix * vec4(vertex.xy, 0, 1);",
		    "TexCoords = vertex.zw;",
		"}" 
	};
	static std::string text_fragment_shader_source[] = {
		"#version 330 core",

		"in vec2 TexCoords;",

		"uniform sampler2D texture;",
		"uniform vec3 text_color;",

		"out vec4 color;",

		"void main() {",
		    "color = vec4(1,1,1,texture2D(texture, TexCoords).r) * vec4(text_color,1);",
		"}"
	};
	 
	// Stringify the shader arrays above
	static std::string default_vertex_shader_stringified = "";
	static std::string default_fragment_shader_stringified = "";
	static std::string text_vertex_shader_stringified = "";
	static std::string text_fragment_shader_stringified = "";
} }