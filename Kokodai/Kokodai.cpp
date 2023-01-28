#include"Label.h"
#include"Window.h"
#include"Canvas3D.h"
#include"RangeButton.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window window("Kokodai");
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
	
	Window ui("Kokodai - control panel", 400, 400);
	
	Label(ui, "rot-X", 10, 10,30,20);
	Label(ui, "rot-Y",10, 40, 30, 20);
	Label(ui, "rot-Z", 10, 70, 30, 20);
	
	Label(ui, "zoom", 10, 100, 35, 20);

	RangeButton x_rot(ui, 0, 360, 50, 10, 300, 20);
	RangeButton y_rot(ui, 0, 360, 50, 40, 300, 20);
	RangeButton z_rot(ui, 0, 360, 50, 70, 300, 20);
	
	RangeButton zoom(ui, 2, 40, 50, 100, 300, 20);

	x_rot.OnSlide = [&](RangeButton& rb)
	{
		canvas.Rotate(rb.GetCurrentPos(), y_rot.GetCurrentPos(), z_rot.GetCurrentPos());
	};
	
	y_rot.OnSlide = [&](RangeButton& rb)
	{
		canvas.Rotate(x_rot.GetCurrentPos(), rb.GetCurrentPos(), z_rot.GetCurrentPos());
	};

	z_rot.OnSlide = [&](RangeButton& rb)
	{
		canvas.Rotate(x_rot.GetCurrentPos(), y_rot.GetCurrentPos(), rb.GetCurrentPos());
	};

	zoom.OnSlide = [&](RangeButton& rb)
	{
		canvas.Zoom(rb.GetMaxPos() -  rb.GetCurrentPos());
	};
	
	while (window.IsOpen() && ui.IsOpen())
	{
		canvas.ClearCanvas();
		canvas.PresentOnScreen();
		Window::ProcessWindowEvents();
	}
	return 0;
}