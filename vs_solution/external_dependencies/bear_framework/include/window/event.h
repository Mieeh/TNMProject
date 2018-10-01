#pragma once

#include"../core/vector2.h"

namespace bear {

	/*
	Enumeration table for the type of each event registered
	Same regardless of underlying framework (GLFW/SFML/SDL)
	*/
	enum EventType {
		KeyPressed,
		KeyReleased,
		MousePressed,
		MouseReleased,
		WindowReiszed,
		Closed
	};

	/* Struct for actual event */
	/* Same regardless of underlying framework (GLFW/SFML/SDL) */
	struct Event {
		EventType type;
		int key; // keyboard
		int button; // mouse
		core::Vector2f size; // example use: window resize 
	};

}