#pragma once
#include "C:\Users\Ayush\Desktop\LGui\LGui\core\lgui.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <iostream>
#include <windows.h>
#include <dwmapi.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "gdi32.lib")    // for Windows windowing
#pragma comment(lib, "user32.lib")   // for input events
#pragma comment(lib, "shell32.lib")  // for cursor
#pragma comment(lib, "dwmapi.lib")

namespace OpenGL2
{
	void Backend_Init(int width, int height, const char* title, const char* targetWindowTitle);
	extern void RegisterBackend();
	GLFWwindow* Backend_GetWindow();
	void Backend_BeginFrame();
	void Backend_EndFrame();
	void Backend_Shutdown();
	void Backend_DrawRect(float x, float y, float w, float h, float r, float g, float b);
	void Backend_DrawText(float x, float y, const char* text, float r, float g, float b);
}