#pragma once

#include<string>
#include<map>

namespace bear {
	namespace core {
		class Matrix4x4;
		struct Color;
		template<typename T>
		struct Vector2;
		struct Color;
	}
}

namespace bear { namespace graphics {

	class Shader {
	public:
		unsigned int m_Program;
		// Caching the uniform locations for faster lookup
		std::map<const char*, int> m_UniformMap;
		bool m_IsActive;
		std::string m_VertexSource;
		std::string m_FragmentSource;
		bool m_GeometryFlag = false;
		std::string m_GeometrySource;

	public:
		Shader();
		~Shader();

		void setSource(const std::string& a_VertexSource, const std::string& a_FragmentSource);
		void setSourceFromFile(std::string a_VertexPath, std::string a_FragmentPath);
		void setGeometrySourcePath(std::string a_GeometryPath);
		void setGeometrySource(const std::string &a_GeometrySource);
		void compile();
		void enable();
		void disable();

		const bool isActive() const;

		void setUniformVector2f(const char* a_UniformName, core::Vector2<float>& a_Vector);
		void setUniformColor3f(const char* a_UniformName, core::Color& a_Color);
		void setUniformMatrix4x4(const char* a_UniformName, core::Matrix4x4& a_Matrix);
		void setUniformInteger(const char* a_UniformName, int a_Integer);
		void setUniformIntegerArray(const char* a_UniformName, unsigned int a_Count, int* a_Integers);
		void setUniformVector4f(const char* a_UniformName, core::Color& a_Vector);

	private:
		bool didCompile(unsigned int a_ShaderID, std::string &a_ErrMsg);
		int getUniformLocation(const char* a_UniformName);
	};

} }