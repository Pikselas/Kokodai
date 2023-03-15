#include<chrono>
#include<random>
#include<array>
#include"Label.h"
#include"Window.h"
#include"Canvas3D.h"
#include"Cube.h"
#include"Pyramid.h"
#include"RangeButton.h"
#include"DropDownSelect.h"
#include"KokodaiManager.h"
#include"VertexShader.h"

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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	KokodaiManager manager;	
	auto cube = Cube<Canvas3D::VertexType>{ manager.GetCanvas() };
	auto pyramid = Pyramid<Canvas3D::VertexType>{ manager.GetCanvas() };

	std::vector<InputElemDesc> ieds
	{ 
		{"POSITION" , InputElemDesc::INPUT_FORMAT::FLOAT3 , 0},
		{"COLOR" , InputElemDesc::INPUT_FORMAT::UINT4 , 12}
	};
	
	const auto vsPath = GetProgramDirectory() / "VertexShader.cso";
	VertexShader vs(manager.GetCanvas(), vsPath, ieds);

	cube.SetVShader(vs);
	pyramid.SetVShader(vs);

	std::mt19937 gen(std::random_device{}());
	auto start = std::chrono::system_clock::now();
	std::vector<Object> objs;
	objs.reserve(100);
	for (int i = 0; i < 100; i++)
	{
		Object obj;
		if (i % 2 == 0)
		{
			obj = cube;
		}
		else
		{
			obj = pyramid;
		}
		obj.SetPosition(std::uniform_real_distribution<float>{-10.0f, 10.0f}(gen), std::uniform_real_distribution<float>{-10.0f, 10.0f}(gen), std::uniform_real_distribution<float>{-10.0f, 10.0f}(gen));
		auto f = Factor{ std::uniform_real_distribution<float>{-1.0f, 1.0f}(gen), std::uniform_real_distribution<float>{-1.0f, 1.0f}(gen),std::uniform_real_distribution<float>{-1.0f, 1.0f}(gen) };
		obj.OnUpdate = [&,fact=f](Object& obj)
		{
			auto d = std::chrono::duration<float>(start - std::chrono::system_clock::now()).count();
			obj.RotatePositional(fact.x * d, fact.y * d, fact.z * d);
		};
		objs.emplace_back(obj);
	}
	manager.Run(objs);
	return 0;
}