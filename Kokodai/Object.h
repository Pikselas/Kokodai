#pragma once
#include<vector>
#include<span>
template<typename VertexType>
class Object
{
public:
	virtual std::span<const VertexType> GetVertices() const = 0;
	virtual std::span<const unsigned int> GetIndices() const = 0;
};