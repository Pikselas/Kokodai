#include<chrono>
#include"Label.h"
#include"Window.h"
#include"Canvas3D.h"
#include"Cube.h"
#include"RangeButton.h"
#include"DropDownSelect.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window window("Kokodai");
	Canvas3D canvas(window);
	
	Window ui("Kokodai - control panel", 400, 400);
	
	Label(ui, "rot-X", 10, 10,30,20);
	Label(ui, "rot-Y",10, 40, 30, 20);

	Label(ui, "zoom", 10, 70, 35, 20);
	
	Label(ui, "Roll", 10, 100, 30, 20);
	Label(ui, "Pitch", 10, 130, 30, 20);
	Label(ui, "Yaw", 10, 160, 30, 20);
	
	Label(ui, "Primitive", 10, 190, 70, 20);

	RangeButton x_rot(ui, 0, 360, 50, 10, 300, 20);
	RangeButton y_rot(ui, 0, 360, 50, 40, 300, 20);
	
	RangeButton zoom(ui, 1, 10, 50, 70, 300, 20);

	RangeButton roll(ui, 0, 360, 50, 100, 300, 20);
	RangeButton pitch(ui, 0, 360, 50, 130, 300, 20);
	RangeButton yaw(ui, 0, 360, 50, 160, 300, 20);

	DropDownSelect primitive(ui, 80, 190, 100, 100);
	primitive.AddItem("Triangle");
	primitive.AddItem("Line");
	primitive.AddItem("Point");

	primitive.OnSelect = [&](DropDownSelect& dd)
	{
		if (const auto selected = dd.GetSelection(); selected == "Triangle")
			canvas.SetPrimitiveTopology(Canvas3D::PrimitiveTopology::Triangle);
		else if (selected == "Line")
			canvas.SetPrimitiveTopology(Canvas3D::PrimitiveTopology::Line);
		else if (selected == "Point")
			canvas.SetPrimitiveTopology(Canvas3D::PrimitiveTopology::Point);
	};
	
	float z = 1.5f;
	
	x_rot.OnSlide = [&](RangeButton& rb)
	{
		canvas.camera.RotateOrientation(rb.GetCurrentPos(), y_rot.GetCurrentPos());
	};
	y_rot.OnSlide = [&](RangeButton& rb)
	{
		canvas.camera.RotateOrientation(x_rot.GetCurrentPos(), rb.GetCurrentPos());
	};
	zoom.OnSlide  = [&](RangeButton& rb)
	{
		canvas.camera.Zoom(rb.GetMaxPos() - rb.GetCurrentPos() + 1);
	};
	roll.OnSlide  = [&](RangeButton& rb)
	{
		canvas.camera.RotatePosition(rb.GetCurrentPos(), pitch.GetCurrentPos(), yaw.GetCurrentPos());
	};
	pitch.OnSlide = [&](RangeButton& rb)
	{
		canvas.camera.RotatePosition(roll.GetCurrentPos(), rb.GetCurrentPos(), yaw.GetCurrentPos());
	};
	yaw.OnSlide	  = [&](RangeButton& rb)
	{
		canvas.camera.RotatePosition(roll.GetCurrentPos(), pitch.GetCurrentPos(), rb.GetCurrentPos());
	};

	Cube<Canvas3D::VertexType> cube(canvas);
	cube.SetPosition(0.0f, 0.0f, 0.0f );
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	
	RangeButton Speed(ui, 1, 100, 50, 220, 300, 20);
	
	while (window.IsOpen() && ui.IsOpen())
	{
		canvas.ClearCanvas();
		auto d = std::chrono::duration<float>(start - std::chrono::system_clock::now()).count() * (float)Speed.GetCurrentPos() / 10;
		cube.SetRotation(d, 0.0f,0.0f);
		canvas.DrawObject(cube);
		canvas.PresentOnScreen();
		Window::ProcessWindowEventsNonBlocking();
	}
	return 0;
}