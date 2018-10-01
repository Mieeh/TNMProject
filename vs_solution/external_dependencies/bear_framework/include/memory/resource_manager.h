#pragma once

#include<unordered_map>
#include<iostream>
#include"../graphics/image.h"

namespace bear {

	/*
	Singleton class, used internally by the framework to load and get resources
	*/

	namespace graphics {
		class Texture;
		class Shader;
	}
	
	class ResourceManager {
	private:
		ResourceManager() { }  // Singleton related
		static ResourceManager* s_Instance; // Singleton related
		
		std::unordered_map<std::string, graphics::Texture*> m_TextureMap;
		std::unordered_map<std::string, graphics::Shader*> m_ShaderMap;

	public:
		static ResourceManager* Instance(); // Singleton related
	
		void Init();
		void Exit();

		/*
		\param2 Path to the image file
		\param3 Format for said image file (RGBA ~ .png | RGB ~ .jpg)
		*/
		void CreateTexture(std::string a_Name, std::string a_File, graphics::image_format a_Format);
		/*
		\param2 Path to the vertex shader source
		\param3 Path to the fragment shader source
		\param4 Path to the geometry shader source (optional) leave empty for no geometry shader
		*/
		graphics::Shader* CreateShaderFromFile(std::string a_Name, std::string a_File1, std::string a_File2, std::string a_File3);
		graphics::Shader* CreateShaderFromSource(std::string a_Name, std::string a_Source1, std::string a_Source2, std::string a_Source3);

		/* Resource getters */
		graphics::Shader* GetShader(std::string a_Name);
		graphics::Texture* GetTexture(std::string a_Name);
	};

}