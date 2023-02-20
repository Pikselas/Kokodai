#pragma once
#include"Object.h"
template<typename VertexType>
class Pyramid : public Object
{
private:
	static constexpr VertexType Vertices[] =
	{
		{0.0f , 1.0f , 0.0f , 100 , 200 , 150},
		{-1.0f , -1.0f , -1.0f ,200 , 100 , 50},
		{1.0f , -1.0f , -1.0f , 50 , 60 , 40},
		{-1.0f , -1.0f , 1.0f ,90 , 12 , 64},
		{1.0f , -1.0f , 1.0f , 123 , 67 , 100}
	};
	static constexpr unsigned int Indices[] =
	{
		0 , 2 , 1,
		0 , 1 , 3,
		0 , 4 , 2,
		0 , 3 , 4,
		1 , 2 , 3,
		3 , 2 , 4
	};
public:
	Pyramid(auto canvas)
	{
		m_VertexBuffer = canvas.CreateVertexBuffer(Vertices);
		m_IndexBuffer = canvas.CreateIndexBuffer(Indices);
		m_IndexCount = std::size(Indices);
	}
};