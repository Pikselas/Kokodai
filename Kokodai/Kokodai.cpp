#include<chrono>
#include"Label.h"
#include"Window.h"
#include"Canvas3D.h"
#include"Cube.h"
#include"Pyramid.h"
#include"RangeButton.h"
#include"DropDownSelect.h"
#include"KokodaiManager.h"
#include<random>

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


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	KokodaiManager manager;	
	//Label(manager.GetWindow(), "TEXT WA KOKO DESU", 325 , 290, 150, 20);
	//Label(manager.GetWindow(), "Konnichiwa , Kokodai Desu. Watashi wa Annimationo UI desu.Kore systemo wa kakkoi desu", 300, 275, 200, 50);
	auto cube = Cube<Canvas3D::VertexType>{ manager.GetCanvas() };
	auto pyramid = Pyramid<Canvas3D::VertexType>{ manager.GetCanvas() };
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