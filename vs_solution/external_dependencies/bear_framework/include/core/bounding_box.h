#pragma once

#include"../core/vector2.h"

namespace bear { namespace core { 

	template<typename T>
	class BoundingBox {
	private:
		Vector2<T> m_Position;
		Vector2<T> m_Size;

	public:
		// Assume T is compatible for the standard math operators 
		BoundingBox() : m_Position(0, 0), m_Size(0, 0) { }
		BoundingBox(Vector2<T> a_Position, Vector2<T> a_Size) : m_Position(a_Position), m_Size(a_Size) { }
		BoundingBox(const BoundingBox<T>& a_Other) : m_Position(a_Other.m_Position), m_Size(a_Other.m_Size) { }

		bool collidesPoint(T a_X, T a_Y) {
			T x1 = this->m_Position.x;
			T x2 = this->m_Position.x + this->m_Size.x;
			T y1 = this->m_Position.y;
			T y2 = this->m_Position.y + this->m_Size.y;

			return ((a_X >= x1 && a_X <= x2) && (y1 >= y1 && y2 <= y2));
		}

		bool intersects(BoundingBox<T>& a_Box2) {
			
			T b1x1 = this->m_Position.x;
			T b1x2 = this->m_Position.x + this->m_Size.x;
			T b1y1 = this->m_Position.y;
			T b1y2 = this->m_Position.y + this->m_Size.y;

			T b2x1 = a_Box2.m_Position.x;
			T b2x2 = a_Box2.m_Position.x + a_Box2.m_Size.x;
			T b2y1 = a_Box2.m_Position.y;
			T b2y2 = a_Box2.m_Position.y + a_Box2.m_Size.y;

			/*
			if (b1x1 < b2x2 && b1x2 > b2x1 && b1y1 < b2y2 && b1y2 > b2y1)
				return true;
			*/
			// Proof by contradiction
			if (b1x2 < b2x1 || b1x1 > b2x2)
				return false;
			else if (b1y2 < b2y1 || b1y1 > b2y2)
				return false;
			else
				return true;

			return false;
		}
	};

	typedef BoundingBox<float> BoundingBoxF;
	typedef BoundingBox<double> BoundingBoxD;

} } 