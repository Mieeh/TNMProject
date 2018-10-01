#pragma once

#include"..\core\vector2.h"

namespace bear { namespace graphics { 

	struct Transform
	{
		core::Vector2f m_Position;
		core::Vector2f m_Size;

		void move(core::Vector2f& a_Vector) {
			m_Position += a_Vector;
		}
	};

} } 