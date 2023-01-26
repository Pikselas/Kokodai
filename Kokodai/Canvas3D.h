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
	PtrManager<ID3D11DepthStencilView> DepthView;
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
	std::vector<VertexType> VERTEX_BUFFER;
private:
	float rot_X;
	float rot_Y;
	float rot_Z;
private:
	const float Halfheight;
	const float Halfwidth;
public:
	void DrawFunction(Window& wnd);
	void UpdateCbuff();
public:
	Canvas3D(Window& wnd);
public:
	std::pair<float, float> GetNormalizedWindowPos(int x, int y) const;
	void ClearCanvas() const;
	void PresentOnScreen() const;
	void DrawObjects(std::span<VertexType> ObjectBuffer);
};