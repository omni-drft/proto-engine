#pragma once

namespace ProtoEngine
{

	class Vertex
	{
	public:
		Vertex(float x, float y) : x(x), y(y) {}
		float GetX() const { return x; }
		float GetY() const { return y; }
		void SetX(float x) { this->x = x; }
		void SetY(float y) { this->y = y; }
		void ModX(float x) { this->x += x; }
		void ModY(float y) { this->y += y; }
	private:
		float x, y;
	};

	inline Vertex addVertices(const Vertex v1, const Vertex v2)
	{
		return Vertex(v1.GetX() + v2.GetX(), v1.GetY() + v2.GetY());
	}

	inline Vertex multiplyVertices(const Vertex v1, const Vertex v2)
	{
		return Vertex(v1.GetX() * v2.GetX(), v1.GetY() * v2.GetY());
	}

}
