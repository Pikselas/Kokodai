#include "KokodaiManager.h"

KokodaiManager::KokodaiManager()
	:
mainWindow("Kokodai"),
mainCanvas(mainWindow),

uiWindow("Kokodai - control panel", 400, 400),

rotXLabel(uiWindow, "rot-X", 10, 10, 30, 20),
rotYLabel(uiWindow, "rot-Y", 10, 40, 30, 20),
zoomLabel(uiWindow, "zoom", 10, 70, 35, 20),
rollLabel(uiWindow, "Roll", 10, 100, 30, 20),
pitchLabel(uiWindow, "Pitch", 10, 130, 30, 20),
yawLabel(uiWindow, "Yaw", 10, 160, 30, 20),
primitiveLabel(uiWindow, "Primitive", 10, 190, 70, 20),

xRot(uiWindow, 0, 360, 50, 10, 300, 20),
yRot(uiWindow, 0, 360, 50, 40, 300, 20),
zoom(uiWindow, 1, 10, 50, 70, 300, 20),
roll(uiWindow, 0, 360, 50, 100, 300, 20),
pitch(uiWindow, 0, 360, 50, 130, 300, 20),
yaw(uiWindow, 0, 360, 50, 160, 300, 20),
primitive(uiWindow, 80, 190, 100, 100)

{
	primitive.AddItem("Triangle");
	primitive.AddItem("Line");
	primitive.AddItem("Point");

	primitive.OnSelect = [&](DropDownSelect& dd)
	{
		if (const auto selected = dd.GetSelection(); selected == "Triangle")
			mainCanvas.SetPrimitiveTopology(Canvas3D::PrimitiveTopology::Triangle);
		else if (selected == "Line")
			mainCanvas.SetPrimitiveTopology(Canvas3D::PrimitiveTopology::Line);
		else if (selected == "Point")
			mainCanvas.SetPrimitiveTopology(Canvas3D::PrimitiveTopology::Point);
	};

	xRot.OnSlide = [&](RangeButton& rb)
	{
		mainCanvas.camera.RotateOrientation(rb.GetCurrentPos(), yRot.GetCurrentPos());
	};
	yRot.OnSlide = [&](RangeButton& rb)
	{
		mainCanvas.camera.RotateOrientation(xRot.GetCurrentPos(), rb.GetCurrentPos());
	};
	zoom.OnSlide = [&](RangeButton& rb)
	{
		mainCanvas.camera.Zoom(rb.GetMaxPos() - rb.GetCurrentPos() + 1);
	};
	roll.OnSlide = [&](RangeButton& rb)
	{
		mainCanvas.camera.RotatePosition(rb.GetCurrentPos(), pitch.GetCurrentPos(), yaw.GetCurrentPos());
	};
	pitch.OnSlide = [&](RangeButton& rb)
	{
		mainCanvas.camera.RotatePosition(roll.GetCurrentPos(), rb.GetCurrentPos(), yaw.GetCurrentPos());
	};
	yaw.OnSlide = [&](RangeButton& rb)
	{
		mainCanvas.camera.RotatePosition(roll.GetCurrentPos(), pitch.GetCurrentPos(), rb.GetCurrentPos());
	};
}

void KokodaiManager::Run(std::function<void(Object& obj , size_t index)> update)
{
	while (mainWindow.IsOpen() && uiWindow.IsOpen())
	{
		mainCanvas.ClearCanvas();
		size_t s = 0;
		for (const auto& obj : objects)
		{
			if (update)
			{
				update(obj, s++);
			}
			mainCanvas.DrawObject(obj);
		}
		mainCanvas.PresentOnWindow();
		mainWindow.Redraw();
		Window::ProcessWindowEventsNonBlocking();
	}
}

void KokodaiManager::Add(Object& obj)
{
	objects.emplace_back(obj);
}

Canvas3D& KokodaiManager::GetCanvas()
{
	return mainCanvas;
}

Window& KokodaiManager::GetWindow()
{
	return mainWindow;
}
