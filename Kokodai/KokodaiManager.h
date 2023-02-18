#pragma once
#include"Label.h"
#include"Window.h"
#include"Canvas3D.h"
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
	Label zoomLabel;
	Label rollLabel;
	Label pitchLabel;
	Label yawLabel;
	Label primitiveLabel;
private:
	RangeButton xRot;
	RangeButton yRot;
	RangeButton zoom;
	RangeButton roll;
	RangeButton pitch;
	RangeButton yaw;
private:
	DropDownSelect primitive;
private:
	std::vector<std::reference_wrapper<Object>> objects;
public:
	KokodaiManager();
	~KokodaiManager() = default;
public:
	void Run(std::function<void(Object& obj)> update = nullptr);
	void Add(Object& obj);
	Canvas3D& GetCanvas();
	Window& GetWindow();
};