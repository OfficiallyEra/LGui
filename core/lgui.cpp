#define LGui_OpenGL2
#include "lgui.h"
#include <iostream>

bool sameLineNext = false;
static bool backendLinked = false;

extern GLFWwindow* OpenGL2::Backend_GetWindow();

namespace LGui 
{
    static int screenWidth = 0, screenHeight = 0;

    void NotifyBackendLinked() 
    {
        backendLinked = true;
    }

    BackendStatus DetectBackend() 
    {
        if (!backendLinked) 
        {
            std::cout << "[LGui] No rendering backend detected. Error: 0xB00B1E\n";
            return BACKEND_MISSING;
        }
        return BACKEND_OK;
    }

    void Init(int w, int h, const char* title) 
    {
        screenWidth = w;
        screenHeight = h;

        if (!title || *title == '\0') {
            std::cout << "[LGui] Error: Window title must not be empty. Error: 0xB00B1F\n";
            return;
        }

        if (DetectBackend() == BACKEND_MISSING)
            return;

        std::cout << "[LGui] Initialized (" << w << "×" << h << ") Title: \"" << title << "\"\n";

        #if defined(LGui_OpenGL2)
                OpenGL2::Backend_Init(w, h, title);  // initialize the window
        #endif
    }

    void BeginFrame() 
    {
        if (!backendLinked) return;

        ctx.cursorX = 10.0f;  // reset position
        ctx.cursorY = 10.0f;

        OpenGL2::Backend_BeginFrame();
    }

    bool Button(const char* label)
    {
        if (!backendLinked) return false;

        float x = ctx.cursorX;
        float y = ctx.cursorY;
        float w = ctx.itemWidth;
        float h = ctx.itemHeight;
        if (ctx.sameLineNext) {
            ctx.cursorX += w + ctx.itemSpacing;  // move right
            ctx.sameLineNext = false;
        }
        else {
            ctx.cursorX = 10.0f;                 // reset X
            ctx.cursorY += h + ctx.itemSpacing;  // move down
        }

        double mx, my;
        GLFWwindow* win = OpenGL2::Backend_GetWindow();
        glfwGetCursorPos(win, &mx, &my);

        bool hovered = (mx >= x && mx <= x + w && my >= y && my <= y + h);
        bool clicked = hovered && glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

        OpenGL2::Backend_DrawRect(x, y, w, h,
            hovered ? 0.2f : 0.1f,
            hovered ? 0.7f : 0.5f,
            1.0f);

        return clicked;
    }

    void Text(const char* label)
    {
        if (!backendLinked || !label) return;

        float x = ctx.cursorX;
        float y = ctx.cursorY;

        // --- Approximate text width (each char ~8 pixels in stb_easy_font)
        int textWidth = static_cast<int>(strlen(label)) * 8;

        // --- Draw the text
        OpenGL2::Backend_DrawText(x, y, label, 1.0f, 1.0f, 1.0f);

        // --- Layout handling
        if (ctx.sameLineNext) {
            ctx.cursorX += textWidth + ctx.itemSpacing;  // stay on same row
            ctx.sameLineNext = false;
        }
        else {
            ctx.cursorX = 10.0f;                          // reset X
            ctx.cursorY += 20.0f;                         // move to next line
        }
    }

    void SameLine()
    {
        ctx.sameLineNext = true;
    }

    void EndFrame() 
    {
        if (!backendLinked) return;
        OpenGL2::Backend_EndFrame();
    }

    void Shutdown() 
    {
        if (!backendLinked) return;
        OpenGL2::Backend_Shutdown();
    }
}