#include"Window.h"

//Winmain

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window window;
	Window::MainLoop(Window::ALL_WINDOWS);
	return 0;
}