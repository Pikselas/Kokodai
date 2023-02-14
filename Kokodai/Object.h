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
	float m_RotationX = 0.0f;
	float m_RotationY = 0.0f;
	float m_RotationZ = 0.0f;
	float m_PositionX = 0.0f;
	float m_PositionY = 0.0f;
	float m_PositionZ = 0.0f;
protected:
	size_t m_IndexCount = 0;
protected:
	auto GetVBuff() const noexcept { return m_VertexBuffer; }
	auto GetIBuff() const noexcept { return m_IndexBuffer; }
	auto GetTansformMatrix() const noexcept
	{
		return DirectX::XMMatrixRotationRollPitchYaw(m_RotationX, m_RotationY, m_RotationZ) *
			DirectX::XMMatrixTranslation(m_PositionX, m_PositionY, m_PositionZ);
	}
public:
	void SetRotation(const float x, const float y, const float z) noexcept
	{
		m_RotationX = x;
		m_RotationY = y;
		m_RotationZ = z;
	}
	void SetRotation(const unsigned short x, const unsigned short y, const unsigned short z) noexcept 
	{ 
		m_RotationX = x * DirectX::XM_PI / 180; 
		m_RotationY = y * DirectX::XM_PI / 180;
		m_RotationZ = z * DirectX::XM_PI / 180;
	}
	void SetPosition(const float x, const float y, const float z) noexcept
	{
		m_PositionX = x;
		m_PositionY = y;
		m_PositionZ = z;
	}
};