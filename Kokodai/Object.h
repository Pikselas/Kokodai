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
	float FixedPointRotationX = 0.0f;
	float FixedPointRotationY = 0.0f;
	float FixedPointRotationZ = 0.0f;
protected:
	float PositionalRotateX = 0.0f;
	float PositionalRotateY = 0.0f;
	float PositionalRotateZ = 0.0f;
protected:
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
		return DirectX::XMMatrixRotationRollPitchYaw(FixedPointRotationX, FixedPointRotationY, FixedPointRotationZ) *
			DirectX::XMMatrixTranslation(m_PositionX, m_PositionY, m_PositionZ) * DirectX::XMMatrixRotationRollPitchYaw(PositionalRotateX, PositionalRotateY, PositionalRotateZ);
	}
public:
	void RotateFixedPoint(const float x, const float y, const float z) noexcept
	{
		FixedPointRotationX = x;
		FixedPointRotationY = y;
		FixedPointRotationZ = z;
	}
	void RotatePositional(const float x, const float y, const float z)
	{
		PositionalRotateX = x;
		PositionalRotateY = y;
		PositionalRotateZ = z;
	}
	void RotateFixedPoint(const unsigned short x, const unsigned short y, const unsigned short z) noexcept
	{
		FixedPointRotationX = x * DirectX::XM_PI / 180;
		FixedPointRotationY = y * DirectX::XM_PI / 180;
		FixedPointRotationZ = z * DirectX::XM_PI / 180;
	}
	void RotatePositional(const unsigned short x, const unsigned short y, const unsigned short z)
	{
		PositionalRotateX = x * DirectX::XM_PI / 180;
		PositionalRotateY = y * DirectX::XM_PI / 180;
		PositionalRotateZ = z * DirectX::XM_PI / 180;
	}
	void SetPosition(const float x, const float y, const float z) noexcept
	{
		m_PositionX = x;
		m_PositionY = y;
		m_PositionZ = z;
	}
};