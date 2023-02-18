#include<chrono>
#include"Label.h"
#include"Window.h"
#include"Canvas3D.h"
#include"Cube.h"
#include"RangeButton.h"
#include"DropDownSelect.h"
#include"KokodaiManager.h"

/*
	TODO: 
	 2.When a new object is added it is added to the canvas and the UI (a control section with the name of the object is added to the UI)
*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	KokodaiManager manager;	
	auto cube = Cube<Canvas3D::VertexType>{ manager.GetCanvas() };
	auto cube2 = cube;
	cube.SetPosition(0.0f, 0.0f, 5.0f);
	cube2.SetPosition(0.8f, 0.0f, 5.0f);
	manager.Add(cube);
	manager.Add(cube2);
	auto start = std::chrono::system_clock::now();
	manager.Run([&](Object& obj)
		{
			auto d = std::chrono::duration<float>(start - std::chrono::system_clock::now()).count();
			obj.RotatePositional(-d, d, -d);
			obj.RotateFixedPoint(d, -d, d);
		});
	return 0;
}