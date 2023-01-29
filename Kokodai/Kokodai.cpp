#include"Label.h"
#include"Window.h"
#include"Canvas3D.h"
#include"RangeButton.h"
#include"DropDownSelect.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window window("Kokodai");
	Canvas3D canvas(window);
	
	std::vector<Canvas3D::VertexType> ObjectBuffer = {
		
		//front
	{-1.0f , 1.0f , -1.0f , 100 , 200 , 150},
	{ 1.0f , 1.0f , -1.0f , 200 , 100 , 50},
	{-1.0f , -1.0f , -1.0f , 50 , 60 , 40},
	{ 1.0f , -1.0f , -1.0f , 100 , 120 , 130},

	//left
	{-1.0f ,1.0f , 1.0f , 200 , 0 , 10 },
	{-1.0f ,1.0f , -1.0f , 80 , 100 , 25},
	{-1.0f ,-1.0f , 1.0f , 220 , 190 , 34 },
	{-1.0f ,-1.0f , -1.0f , 100 , 123 , 78},

	//top
	{-1.0f ,1.0f , 1.0f , 99 , 98 , 97},
	{ 1.0f ,1.0f , 1.0f , 213 , 183 , 65},
	{-1.0f ,1.0f , -1.0f ,123 , 87 , 90 },
	{ 1.0f ,1.0f , -1.0f , 14 , 78 , 36 },

	//back
	{-1.0f , 1.0f , 1.0f , 123 , 67 , 100},
	{ 1.0f , 1.0f , 1.0f , 220 , 78 , 13},
	{-1.0f , -1.0f , 1.0f , 90 , 54 , 67},
	{ 1.0f , -1.0f , 1.0f , 132 , 78 , 21},

	//right
	{1.0f ,1.0f , 1.0f , 34 , 78 , 90 },
	{1.0f ,1.0f , -1.0f , 123 , 89 , 36 },
	{1.0f ,-1.0f , 1.0f , 24 , 63 , 217 },
	{1.0f ,-1.0f , -1.0f , 24 , 80 , 90 },

	//bottom
	{-1.0f ,-1.0f , -1.0f , 24 , 99 , 213},
	{ 1.0f ,-1.0f , -1.0f , 47 , 76 , 56 },
	{-1.0f ,-1.0f , 1.0f , 90 , 12 , 64 },
	{ 1.0f ,-1.0f , 1.0f , 124 , 76 , 34}
		
	};

	std::vector<unsigned int> indices = {
		2 , 0 ,1,
	2 , 1 ,3,

	6 , 4, 5,
	5 , 7 ,6,

	10 , 8 , 9,
	9 , 11, 10,

	13 , 12 , 14,
	14 , 15 , 13,

	18 , 17 , 16,
	19 , 17 , 18,

	20 , 21 , 22,
	23 , 22 , 21
	};

	canvas.DrawObject(ObjectBuffer, indices);
	
	window.mouse.OnMove = [&](Window& wnd)
	{
		if (window.mouse.IsLeftPressed())
		{
			auto [x, y] = window.mouse.GetXY();
			auto [nx, ny] = canvas.GetNormalizedWindowPos(x, y);
			ObjectBuffer.emplace_back(nx, ny, 0.0f, 255, 255, 255, 255);
			canvas.DrawObject(ObjectBuffer);
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
	

	x_rot.OnSlide = [&](RangeButton& rb)
	{
		canvas.camera.RotateOrientation(rb.GetCurrentPos(), y_rot.GetCurrentPos());
	};
	
	y_rot.OnSlide = [&](RangeButton& rb)
	{
		canvas.camera.RotateOrientation(x_rot.GetCurrentPos(), rb.GetCurrentPos());
	};

	zoom.OnSlide = [&](RangeButton& rb)
	{
		canvas.camera.Zoom(rb.GetMaxPos() - rb.GetCurrentPos() + 1);
	};

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