#include "KokodaiManager.h"

KokodaiManager::KokodaiManager()
	:
mainWindow("Kokodai"),
mainCanvas(mainWindow),

uiWindow("Kokodai - control panel", 400, 400),

rotXLabel(uiWindow, "rot-X", 10, 10, 30, 20),
rotYLabel(uiWindow, "rot-Y", 10, 40, 30, 20),
camXLabel(uiWindow, "X", 15, 70, 15, 20),
camYLabel(uiWindow, "Y", 115, 70, 15, 20),
camZLabel(uiWindow, "Z", 225, 70, 15, 20),
rollLabel(uiWindow, "Roll", 10, 100, 30, 20),
pitchLabel(uiWindow, "Pitch", 10, 130, 30, 20),
yawLabel(uiWindow, "Yaw", 10, 160, 30, 20),
primitiveLabel(uiWindow, "Primitive", 10, 190, 70, 20),

xRot(uiWindow, 0, 360, 50, 10, 300, 20),
yRot(uiWindow, 0, 360, 50, 40, 300, 20),
roll(uiWindow, 0, 360, 50, 100, 300, 20),
pitch(uiWindow, 0, 360, 50, 130, 300, 20),
yaw(uiWindow, 0, 360, 50, 160, 300, 20),

xCam(uiWindow, 35, 70, 35, 20),
yCam(uiWindow, 135, 70, 35, 20),
zCam(uiWindow, 245, 70, 35, 20),

xInc(uiWindow, "+", 75, 70, 35, 10),
xDec(uiWindow, "-", 75, 80, 35, 10),
yInc(uiWindow, "+", 175, 70, 35, 10),
yDec(uiWindow, "-", 175, 80, 35, 10),
zInc(uiWindow, "+", 285, 70, 35, 10),
zDec(uiWindow, "-", 285, 80, 35, 10),

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

	auto GetF = [](const std::string& s)
	{
		try
		{
			return std::stof(s);
		}
		catch (const std::exception&)
		{
			return 0.1f;
		}
	};
	
	xCam.SetText("0.0");
	yCam.SetText("0.0");
	zCam.SetText("1.0");
	
	xCam.OnTextChange = [&](TextEntry& te)
	{
		mainCanvas.camera.SetPosition(GetF(te.GetText()), GetF(yCam.GetText()), GetF(zCam.GetText()));
	};
	yCam.OnTextChange = [&](TextEntry& te)
	{
		mainCanvas.camera.SetPosition(GetF(te.GetText()), GetF(yCam.GetText()), GetF(zCam.GetText()));
	};
	zCam.OnTextChange = [&](TextEntry& te)
	{
		mainCanvas.camera.SetPosition(GetF(te.GetText()), GetF(yCam.GetText()), GetF(zCam.GetText()));
	};

	xInc.OnClick = [&](TextButton& b)
	{
		xCam.SetText(std::to_string(GetF(xCam.GetText()) + 1.0f));
	};
	xDec.OnClick = [&](TextButton& b)
	{
		xCam.SetText(std::to_string(GetF(xCam.GetText()) - 1.0f));
	};
	yInc.OnClick = [&](TextButton& b)
	{
		yCam.SetText(std::to_string(GetF(yCam.GetText()) + 1.0f));
	};
	yDec.OnClick = [&](TextButton& b)
	{
		yCam.SetText(std::to_string(GetF(yCam.GetText()) - 1.0f));
	};
	zInc.OnClick = [&](TextButton& b)
	{
		zCam.SetText(std::to_string(GetF(zCam.GetText()) + 1.0f));
	};
	zDec.OnClick = [&](TextButton& b)
	{
		zCam.SetText(std::to_string(GetF(zCam.GetText()) - 1.0f));
	};
}

void KokodaiManager::Run(std::span<Object> objects)
{
	while (mainWindow.IsOpen() && uiWindow.IsOpen())
	{
		mainCanvas.ClearCanvas();
		for (auto& obj : objects)
		{
			if (obj.OnUpdate)
			{
				obj.OnUpdate(obj);
			}
			mainCanvas.DrawObject(obj);
		}
		mainCanvas.PresentOnWindow();
		mainWindow.Redraw();
		Window::ProcessWindowEventsNonBlocking();
	}
}

Canvas3D& KokodaiManager::GetCanvas()
{
	return mainCanvas;
}

Window& KokodaiManager::GetWindow()
{
	return mainWindow;
}
