#include<chrono>
#include<random>
#include<typeindex>
#include<map>
#include"Cube.h"
#include"Pyramid.h"
#include"Texture.h"
#include"PaperTex.h"
#include"TexturedCube.h"
#include"PixelShader.h"
#include"VertexShader.h"
#include"ConstantBuffer.h"
#include"KokodaiManager.h"

/*
	TODO: 
	 2.When a new object is added it is added to the canvas and the UI (a control section with the name of the object is added to the UI)
*/

struct Factor
{
	float x;
	float y;
	float z;
};

auto GetProgramDirectory()
{
	char buffer[MAX_PATH];
	GetModuleFileName(nullptr, buffer, 100);
	std::filesystem::path path = buffer;
	return path.parent_path();
}

template<typename T>
concept ObjectT = std::is_base_of_v<Object,T>;

template<ObjectT ObjT>
Object BuildObject(Canvas3D& cnv)
{
	static std::map<std::pair<Canvas3D*,std::type_index>,Object> objects;
	auto ObjComb = std::make_pair(&cnv, std::type_index(typeid(ObjT)));
	if (objects.find(ObjComb) == objects.end())
	{
		if constexpr (std::is_same_v<ObjT, Cube<Canvas3D::VertexType>>)
		{
			Cube<Canvas3D::VertexType> cube{ cnv };
			std::vector<InputElemDesc> ieds
			{
				{"POSITION" , InputElemDesc::INPUT_FORMAT::FLOAT3 , 0},
				{"COLOR" , InputElemDesc::INPUT_FORMAT::UINT4 , 12}
			};
			const auto programDir = GetProgramDirectory();
			const auto vsPath = programDir / "VertexShader.cso";
			const auto psPath = programDir / "PixelShader.cso";
			VertexShader vs(cnv, vsPath, ieds);
			PixelShader ps(cnv, psPath);
			ConstantBuffer cb(cnv, sizeof(DirectX::XMMATRIX));
			cube.SetVShader(vs);
			cube.SetPShader(ps);
			cube.SetCBuffer(cb);
			objects[ObjComb] = cube;
			return cube;
		}
		else if constexpr (std::is_same_v<ObjT, TexturedCube>)
		{
			TexturedCube cube{ cnv };
			std::vector<InputElemDesc> ieds
			{
				{"POSITION" , InputElemDesc::INPUT_FORMAT::FLOAT3 , 0},
				{"TEXCOORD" , InputElemDesc::INPUT_FORMAT::FLOAT2 , 12}
			};
			const auto programDir = GetProgramDirectory();
			const auto vsPath = programDir / "TextureVS.cso";
			const auto psPath = programDir / "TexturePS.cso";
			VertexShader vs(cnv, vsPath, ieds);
			PixelShader ps(cnv, psPath);
			ConstantBuffer cb(cnv, sizeof(DirectX::XMMATRIX));
			Image img("D:/wallpaperflare-cropped.jpg");
			Texture tex(cnv, img);
			cube.SetVShader(vs);
			cube.SetPShader(ps);
			cube.SetCBuffer(cb);
			cube.SetTexture(tex);
			objects[ObjComb] = cube;
			return cube;
		}
	}
	return objects[ObjComb];
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	KokodaiManager manager;
	std::mt19937 gen(std::random_device{}());
	auto start = std::chrono::system_clock::now();
	std::vector<Object> objs;
	objs.reserve(100);
	auto count = 0u;

	for (int i = 0; i < 100; i++)
	{
		Object obj;
		if (i % 2 == 0)
		{
			obj = BuildObject<Cube<Canvas3D::VertexType>>(manager.GetCanvas());
		}
		else
		{
			obj = BuildObject<TexturedCube>(manager.GetCanvas());
		}
		obj.SetPosition(std::uniform_real_distribution<float>{-10.0f, 10.0f}(gen), std::uniform_real_distribution<float>{-10.0f, 10.0f}(gen), std::uniform_real_distribution<float>{-10.0f, 10.0f}(gen));
		auto f = Factor{ std::uniform_real_distribution<float>{-1.0f, 1.0f}(gen), std::uniform_real_distribution<float>{-1.0f, 1.0f}(gen),std::uniform_real_distribution<float>{-1.0f, 1.0f}(gen) };
		obj.OnUpdate = [&,fact=f](Object& obj)
		{
			//auto d = std::chrono::duration<float>(start - std::chrono::system_clock::now()).count();
			//obj.RotatePositional(fact.x * d, fact.y * d, fact.z * d);
			//obj.RotateFixedPoint(fact.x * d, fact.y * d, fact.z * d);
		};
		objs.emplace_back(obj);
	}

	manager.Run(objs);
	return 0;
}