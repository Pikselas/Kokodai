#include"Window.h"
#include"Canvas3D.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window window;
	Canvas3D canvas(window);
	
	std::vector<Canvas3D::VertexType> ObjectBuffer;
	
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

	window.keyboard.EnableKeyRepeat();
	
	window.keyboard.OnKeyPress = [& , x = 0 , y = 0 , z = 0](Window::KeyBoard::EventT e) mutable
	{
		switch (e.KEY_CODE)
		{
		case 'W':
			x += 1;
			break;
		case 'S':
			x -= 1;
			break;
		case 'A':
			y += 1;
			break;
		case 'D':
			y -= 1;
			break;
		case 'Q':
			z += 1;
			break;
		case 'E':
			z -= 1;
			break;
		}
		canvas.Rotate(x, y, z);
	};
	
	window.mouse.OnWheel = [&](Window& wnd)
	{
		auto delta = window.mouse.GetWheelDelta();
		canvas.Zoom(delta);
	};
	
	while (window.IsOpen())
	{
		canvas.ClearCanvas();
		canvas.PresentOnScreen();
		window.ProcessEvents();
	}
	return 0;
}