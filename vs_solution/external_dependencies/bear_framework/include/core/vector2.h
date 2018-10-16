#pragma once

#include<iostream>
#include<math.h>

#include<string>

namespace bear { namespace core {

	template<typename T>
	struct Vector2 {
		T x;
		T y;

		Vector2(T a_x, T a_y) : x(a_x), y(a_y) { }
		Vector2() : x(0), y(0) { }

		T magnitude() {
			return std::sqrt(std::pow<T, int>(x, 2) + std::pow<T, int>(y, 2));
		}
		Vector2<T> normalize() {
			return Vector2<T>(x / this->magnitude(), y / this->magnitude());
		}
		void scale(T factor) {
			x = x * factor;
			y = y * factor;
		}
		void moveTowards(core::Vector2<T> target, float speed) {
				Vector2<T> dir = Vector2<T>(target.x - this->x, target.y - this->y);
				Vector2<T> norm_dir = dir.normalize();
				*this = (*this) + (norm_dir*speed);
		}
		void lerp(core::Vector2<T> target, float t) {
			//*this = (*this) * t + target*(1.f - t);
			this->x = (1.0f - t) * this->x + t * target.x;
			this->y = (1.0f - t) * this->y + t * target.y;
		}

		static T distance(Vector2<T> &a_V1, Vector2<T> &a_V2) {
			return std::sqrt(std::pow<T, int>(a_V2.x - a_V1.x, 2) + std::pow<T, int>(a_V2.y - a_V1.y, 2));
		}

		// Operator overloading
		friend std::ostream & operator<<(std::ostream &os, const Vector2<T> &right) {
			os << "(" << right.x << ", " << right.y << ")";
			return os;
		}
		// == Operator
		bool operator==(const Vector2<T> right) {
			return this->x == right.x && this->y == right.y;
		}
		Vector2<T> operator-(const Vector2<T> right) {
			return Vector2<T>(this->x - right.x, this->y - right.y);
		}
		Vector2<T> operator+(const Vector2<T> right) {
			return Vector2<T>(this->x + right.x, this->y + right.y);
		}
		Vector2<T> operator*(const Vector2<T> right) {
			return Vector2<T>(this->x * right.x, this->y * right.y);
		}
		Vector2<T> operator*(const T right) {
			return Vector2<T>(this->x * right, this->y * right);
		}
		Vector2<T> operator/(const T right) {
			return Vector2<T>(this->x / right, this->y / right);
		}
		Vector2<T>& operator+=(const Vector2<T>& right) {
			this->x += right.x;
			this->y += right.y;
			return *this;
		}
		Vector2<T>& operator-=(const Vector2<T>& right) {
			this->x -= right.x;
			this->y -= right.y;
			return *this;
		}
		Vector2<T>& operator*=(const Vector2<T>& right) {
			this->x *= right.x;
			this->y *= right.y;
			return *this;
		}

		// Conversions
		explicit operator Vector2<int>() { return Vector2<int>((int)this->x, (int)this->y); }
		explicit operator Vector2<float>() { return Vector2<float>((float)this->x, (float)this->y); }
		explicit operator std::string() { return ( std::to_string(this->x) + std::to_string(this->y) ); } // Whoever wrote this is stupid
	};
	
	// Define some default templates
	typedef Vector2<int> Vector2i;
	static bool operator<(const Vector2i& left, const Vector2i& right) {
		if (right.x > left.x)
			return true;
	}
	typedef Vector2<float> Vector2f;
	typedef Vector2<unsigned int> Vector2ui;
	typedef Vector2<double> Vector2d;

	static void moveTowards2i(Vector2i& v1, Vector2i v2, float speed) {
		Vector2f dir_norm = core::Vector2f(v2.x - v1.x, v2.y - v1.y).normalize();
		core::Vector2i newPos = (core::Vector2i(v1.x, v1.y) + core::Vector2i(dir_norm.x * speed, dir_norm.y * speed));

		if(!(v1 == v2))
			v1 = newPos;
	}
}
}