#include"Window.h"
#include"Canvas3D.h"
//Winmain

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window window;
	Canvas3D canvas(window);
	while (window.IsOpen())
	{
		canvas.ClearCanvas();
		canvas.PresentOnScreen();
		window.ProcessEvents();
	}
	return 0;
}