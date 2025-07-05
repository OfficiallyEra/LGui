#pragma once
#include "C:\Users\Ayush\Desktop\LGui\LGui\core\lgui.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace OpenGL2
{
	void Backend_Init(int width, int height, const char* title);
	extern void RegisterBackend();
	GLFWwindow* Backend_GetWindow();
	void Backend_BeginFrame();
	void Backend_EndFrame();
	void Backend_Shutdown();
	void Backend_DrawRect(float x, float y, float w, float h, float r, float g, float b);
	void Backend_DrawText(float x, float y, const char* text, float r, float g, float b);
}