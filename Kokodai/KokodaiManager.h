#pragma once
#include"Label.h"
#include"Window.h"
#include"Canvas3D.h"
#include"TextEntry.h"
#include"TextButton.h"
#include"RangeButton.h"
#include"DropDownSelect.h"

#include<functional>
class KokodaiManager
{
private:
	Window mainWindow;
	Canvas3D mainCanvas;
private:
	Window uiWindow;
private:
	Label rotXLabel;
	Label rotYLabel;
	Label camXLabel;
	Label camYLabel;
	Label camZLabel;
	Label rollLabel;
	Label pitchLabel;
	Label yawLabel;
	Label primitiveLabel;
private:
	RangeButton xRot;
	RangeButton yRot;
	RangeButton roll;
	RangeButton pitch;
	RangeButton yaw;
private:
	TextEntry xCam;
	TextEntry yCam;
	TextEntry zCam;
private:
	TextButton xInc;
	TextButton xDec;
	TextButton yInc;
	TextButton yDec;
	TextButton zInc;
	TextButton zDec;
private:
	DropDownSelect primitive;
public:
	KokodaiManager();
	~KokodaiManager() = default;
public:
	void Run(std::span<Object> objects);
	Canvas3D& GetCanvas();
	Window& GetWindow();
};