#pragma once
#include<span>
#include<wrl.h>
#include<vector>
#include<d3d11.h>
#include<d3dcompiler.h>
#include<DirectXMath.h>
#include<filesystem>
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")

#include"Window.h"

class Canvas3D
{
	template<typename t>
	using PtrManager = Microsoft::WRL::ComPtr<t>;
private:
	PtrManager<ID3D11Device> Device;
	PtrManager<IDXGISwapChain> SwapChain;
	PtrManager<ID3D11DeviceContext> ImmediateContext;
	PtrManager<ID3D11RenderTargetView> RenderTarget;
	PtrManager<ID3D11DepthStencilView> DepthStencilView;
	PtrManager<ID3D11Buffer> ConstBuffer;
public:
	struct VertexType
	{
		float x, y, z;
		unsigned char r, g, b, a;
	};
public:
	enum class PrimitiveTopology
	{
		Point	 = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,
		Line	 = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,
		Triangle = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
	};
private:
	std::function<void()> DrawFunc = []() {};
public:
	class Camera
	{
	private:
		DirectX::XMMATRIX transform_matrix;
	private:
		float rot_x = 0.0f, rot_y = 0.0f;
		float roll = 0.0f, pitch = 0.0f, yaw = 0.0f;
		float pos_z = 1.5f;
	private:
		void Transform();
	public:
		Camera();
	public:
		void Zoom(const float z);
		void RotateOrientation(const int x, const int y);
		void RotatePosition(const int x, const int y, const int z);
		DirectX::XMMATRIX GetTransformMatrix() const;
	};
	Camera camera;
private:
	const float Halfheight;
	const float Halfwidth;
private:
	void UpdateCbuff(DirectX::XMMATRIX transform_matrix) const;
public:
	Canvas3D(Window& wnd);
public:
	std::pair<float, float> GetNormalizedWindowPos(int x, int y) const;
	void ClearCanvas() const;
	void PresentOnScreen() const;
	void SetPrimitiveTopology(const PrimitiveTopology primitive) const;
	void DrawObject(std::span<VertexType> Vertices);
	void DrawObject(std::span<VertexType> Vertices, std::span<unsigned int> indices);
};