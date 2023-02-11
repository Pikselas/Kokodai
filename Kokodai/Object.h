#pragma once
#include<vector>
#include<span>
#include<d3d11.h>
class Object
{
	friend class Canvas3D;
protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_IndexBuffer;
protected:
	size_t m_IndexCount = 0;
protected:
	auto GetVBuff() const noexcept { return m_VertexBuffer.Get(); }
	auto GetIBuff() const noexcept { return m_IndexBuffer.Get(); }
};