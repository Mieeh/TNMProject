#pragma once

namespace bear { namespace core {

	// This is based on the way GLSL takes in colors 0-1, 1 fully lit, 0 not lit
	struct Color {
		float r, g, b, a;

		Color() : r(0), g(0), b(0), a(1.0f) { }
		Color(float a_r, float a_g, float a_b, float a_a = 1.0f) : r(a_r), g(a_g), b(a_b), a(a_a) { }

		static Color Black() { return Color(0, 0, 0); }
		static Color White() { return Color(1, 1, 1); }
		static Color Red() { return Color(1, 0, 0); }
		static Color Green() { return Color(0, 1, 0); }
		static Color Blue() { return Color(0, 0, 1); }
		// Add more commonly used colors...
	};

} }