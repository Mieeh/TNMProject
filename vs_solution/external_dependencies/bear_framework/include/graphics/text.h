#pragma once

#define DEFAULT_FONT_SIZE

#include<map>

#include"../core/vector2.h"
#include"../core/color.h"

typedef struct FT_FaceRec_*  FT_Face;
typedef struct FT_LibraryRec_  *FT_Library;

namespace bear { namespace graphics { 

	class Shader;
	class View;

	struct _text_buffer_objects {
		unsigned int VAO, VBO;
	};

	struct glyph_character {
		unsigned int m_TexID;
		core::Vector2f m_Size;
		core::Vector2f m_Bearings;
		unsigned int m_Offset;
	};

	class Font {
	public:
		// Methods
		Font(const char* a_Path, const int a_FontSize);

		FT_Face *m_Face;
		FT_Library *m_Lib;
		std::map<char, glyph_character> m_Characters;
		unsigned int m_FontSize;
	};

	class TextLabel {
	public:
		// Requires a font from the creator side
		TextLabel(std::string a_Text, Font& a_FontPath, core::Vector2f a_Position, core::Color a_Color);

		// Destructor 
		~TextLabel();

		// Draw this text label
		void draw(View& a_View = defaultView);

		// Change text label font pointer
		void setFont(Font& a_Font);

		// Change string literal
		void setStringLiteral(const std::string& a_StringLiteral);

		// Sets position
		void setPosition(core::Vector2f a_Position);

	private:
		std::string m_StringLiteral;
		core::Vector2f m_Position;
		core::Color m_Color;
		_text_buffer_objects m_Buffer;
		Font &m_Font;
		static View &defaultView;
	};

} }