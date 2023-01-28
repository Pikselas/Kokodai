#include"Label.h"
#include"Window.h"
#include"Canvas3D.h"
#include"RangeButton.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window window("Kokodai");
	Canvas3D canvas(window);
	
	std::vector<Canvas3D::VertexType> ObjectBuffer;

	ObjectBuffer.emplace_back(0.0f, 1.0f, 0.0f, 150, 155, 215);
	ObjectBuffer.emplace_back(1.0f, -1.0f, 0.0f, 205, 255, 215);
	ObjectBuffer.emplace_back(-1.0f, -1.0f, 0.0f, 155, 105, 201);

	canvas.DrawObjects(ObjectBuffer);
	
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
	
	window.mouse.OnWheel = [&](Window& wnd)
	{
		auto delta = window.mouse.GetWheelDelta();
		canvas.camera.Zoom(delta);
	};
	
	Window ui("Kokodai - control panel", 400, 400);
	
	Label(ui, "rot-X", 10, 10,30,20);
	Label(ui, "rot-Y",10, 40, 30, 20);
	Label(ui, "rot-Z", 10, 70, 30, 20);

	Label(ui, "Roll", 10, 100, 30, 20);
	Label(ui, "Pitch", 10, 130, 30, 20);
	Label(ui, "Yaw", 10, 160, 30, 20);
	
	//Label(ui, "zoom", 10, 100, 35, 20);

	RangeButton x_rot(ui, 0, 360, 50, 10, 300, 20);
	RangeButton y_rot(ui, 0, 360, 50, 40, 300, 20);
	
	RangeButton roll(ui, 0, 360, 50, 100, 300, 20);
	RangeButton pitch(ui, 0, 360, 50, 130, 300, 20);
	RangeButton yaw(ui, 0, 360, 50, 160, 300, 20);
	
	//RangeButton zoom(ui, 2, 40, 50, 100, 300, 20);

	x_rot.OnSlide = [&](RangeButton& rb)
	{
		canvas.camera.RotateOrientation(rb.GetCurrentPos(), y_rot.GetCurrentPos());
	};
	
	y_rot.OnSlide = [&](RangeButton& rb)
	{
		canvas.camera.RotateOrientation(x_rot.GetCurrentPos(), rb.GetCurrentPos());
	};

	//zoom.OnSlide = [&](RangeButton& rb)
	//{
		//canvas.Zoom(rb.GetMaxPos() -  rb.GetCurrentPos());
	//};

	roll.OnSlide = [&](RangeButton& rb)
	{
		canvas.camera.RotatePosition(rb.GetCurrentPos(), pitch.GetCurrentPos(), yaw.GetCurrentPos());
	};

	pitch.OnSlide = [&](RangeButton& rb)
	{
		canvas.camera.RotatePosition(roll.GetCurrentPos(), rb.GetCurrentPos(), yaw.GetCurrentPos());
	};

	yaw.OnSlide = [&](RangeButton& rb)
	{
		canvas.camera.RotatePosition(roll.GetCurrentPos(), pitch.GetCurrentPos(), rb.GetCurrentPos());
	};
	
	while (window.IsOpen() && ui.IsOpen())
	{
		canvas.ClearCanvas();
		canvas.PresentOnScreen();
		Window::ProcessWindowEvents();
	}
	return 0;
}