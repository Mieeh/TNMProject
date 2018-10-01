#pragma once

#include<iostream>

namespace bear { namespace core {

	template<typename T>
	struct Vector3 {
		T x;
		T y;
		T z;

		Vector3(T a_x, T a_y, T a_z) : x(a_x), y(a_y), z(a_z) { }
		Vector3() : x(0), y(0), z(0) { }

		// Operator overloading
		friend std::ostream & operator<<(std::ostream &os, const Vector3<T> &right) {
			os << "(" << right.x << ", " << right.y << ", " << right.z << ")";
			return os;
		}
		Vector3<T> operator-(const Vector3<T> right) {
			return Vector3<T>(this->x - right.x, this->y - right.y, this->z - right.z);
		}
		Vector3<T> operator+(const Vector3<T> right) {
			return Vector3<T>(this->x + right.x, this->y + right.y, this->z + right.z);
		}
		Vector3<T> operator*(const Vector3<T> right) {
			return Vector3<T>(this->x * right.x, this->y * right.y, this->z * right.z);
		}
		Vector3<T>& operator+=(const Vector3<T>& right) {
			this->x += right.x;
			this->y += right.y;
			this->z += right.z
			return *this;
		}
		Vector3<T>& operator-=(const Vector3<T>& right) {
			this->x -= right.x;
			this->y -= right.y;
			this->z -= right.z;
			return *this;
		}
		Vector3<T>& operator*=(const Vector3<T>& right) {
			this->x *= right.x;
			this->y *= right.y;
			this->z *= right.z;
			return *this;
		}
	};

	// Define some default templates
	typedef Vector3<int> Vector3i;
	typedef Vector3<float> Vector3f;
	typedef Vector3<unsigned int> Vector3ui;
	
} }