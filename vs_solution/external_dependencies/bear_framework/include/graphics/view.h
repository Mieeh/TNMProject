#pragma once

#include"../core/vector2.h"
#include"../core/matrix4x4.h"

namespace bear { namespace graphics { 

	class View {
	private:
		core::Vector2f m_WorldPosition;
		core::Matrix4x4 m_ViewMatrix;

	public:
		/*
		Constructs view with world position (0,0)
		*/
		View();

		/*
		Constructs view with world position a_Position
		*/
		View(core::Vector2f a_Position);

		// Sets position 
		void setPosition(core::Vector2f a_Position);
		void translate(core::Vector2f a_Translation);

		// Matrix getter
		core::Matrix4x4& getViewMatrix();
		// Position getter
		core::Vector2f getPosition();

	private:
		// Called when matrix needs to be updated
		void _update_matrix();
	};

} } 