#include"Window.h"
#include"Canvas3D.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window window;
	Canvas3D canvas(window);
	
	std::vector<Canvas3D::VertexType> ObjectBuffer;
	
	//To do implement depth stencil view

	window.mouse.OnMove = [&](Window& wnd)
	{
		if (window.mouse.IsLeftPressed())
		{
			auto [x, y] = window.mouse.GetXY();
			auto [nx, ny] = canvas.GetNormalizedWindowPos(x, y);
			ObjectBuffer.emplace_back(nx, ny, 0.0f, 255, 255, 255, 255);
			canvas.DrawObjects(ObjectBuffer);
		}
	};
	
	while (window.IsOpen())
	{
		canvas.ClearCanvas();
		canvas.PresentOnScreen();
		window.ProcessEvents();
	}
	return 0;
}