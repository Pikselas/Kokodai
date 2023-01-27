#pragma once
#include<span>
#include<wrl.h>
#include<vector>
#include<d3d11.h>
#include<d3dcompiler.h>
#include<DirectXMath.h>
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
private:
	DirectX::XMMATRIX transform_matrix;
public:
	struct VertexType
	{
		float x, y, z;
		unsigned char r, g, b, a;
	};
	size_t vertices;
private:
	const float Halfheight;
	const float Halfwidth;
private:
	float rot_x, rot_y, rot_z;
	float pos_Z = 2.0f;
private:
	void UpdateCbuff();
public:
	void Rotate(const int x, const int y, const int z);
	void Zoom(const float z);
public:
	Canvas3D(Window& wnd);
public:
	std::pair<float, float> GetNormalizedWindowPos(int x, int y) const;
	void ClearCanvas() const;
	void PresentOnScreen() const;
	void DrawObjects(std::span<VertexType> ObjectBuffer);
};