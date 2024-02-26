/* ============================== FILE PURPOSE ==============================
* 
* This file contains the Vertex class that is used to represent 2D vertices.
* It also contains two functions that are used to add and multiply vertices.
* 
=========================================================================== */


#pragma once

namespace ProtoEngine
{
	/// <summary>
	/// This class represents a 2D vertex and is being used for better readability of object coordinates.
	/// </summary>
	class Vertex
	{
	public:
		/// <summary>
		/// Constructor for the Vertex class.
		/// </summary>
		/// <param name="x">- x coordinate</param>
		/// <param name="y">- y coordinate</param>
		Vertex(float x, float y) : x(x), y(y) {}

		/// <summary>
		/// X getter
		/// </summary>
		/// <returns>x coordinate</returns>
		float GetX() const { return x; }
		
		/// <summary>
		/// Y getter
		/// </summary>
		/// <returns>y coordinate</returns>
		float GetY() const { return y; }

		/// <summary>
		/// X setter
		/// </summary>
		/// <param name="x">new value for x</param>
		void SetX(float x) { this->x = x; }

		/// <summary>
		/// Y setter
		/// </summary>
		/// <param name="y">new value for y</param>
		void SetY(float y) { this->y = y; }

		/// <summary>
		/// X modifier
		/// </summary>
		/// <param name="x">value that will be added to x coordinate</param>
		void ModX(float x) { this->x += x; }

		/// <summary>
		/// Y modifier
		/// </summary>
		/// <param name="y">value that will be added to y coordinate</param>
		void ModY(float y) { this->y += y; }
	private:
		/// <summary>
		/// Coordinates of the vertex
		/// </summary>
		float x, y;
	};

	/// <summary>
	/// Function that adds two vertices together and returns the result.
	/// </summary>
	/// <param name="v1">- first vertex</param>
	/// <param name="v2">- second vertex</param>
	/// <returns>sum of 2 vertices</returns>
	inline Vertex addVertices(const Vertex v1, const Vertex v2)
	{
		return Vertex(v1.GetX() + v2.GetX(), v1.GetY() + v2.GetY());
	}

	/// <summary>
	/// Function that multiplies two vertices together and returns the result.
	/// </summary>
	/// <param name="v1">- first vertex</param>
	/// <param name="v2">- second vertex</param>
	/// <returns>multiplication result of given vertices</returns>
	inline Vertex multiplyVertices(const Vertex v1, const Vertex v2)
	{
		return Vertex(v1.GetX() * v2.GetX(), v1.GetY() * v2.GetY());
	}

}
