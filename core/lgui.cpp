#define LGui_OpenGL2
#pragma warning(disable : 4244)
#pragma warning(disable : 4305)
#include "lgui.h"
#include <iostream>

bool sameLineNext = false;
static bool backendLinked = false;
static bool mousePressedLastFrame = false;

extern GLFWwindow* OpenGL2::Backend_GetWindow();

namespace LGui 
{

    struct WindowContext {
        float x = 100, y = 100;
        float width = 250, height = 300;
        bool dragging = false;
        float dragOffsetX = 0, dragOffsetY = 0;
        const char* title = nullptr;
    };

    static WindowContext g_window;

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

    void Init(int w, int h, const char* title, const char* targetWindowTitle)
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
        OpenGL2::Backend_Init(w, h, title, targetWindowTitle);  // initialize the window
        #endif
    }

    bool Begin(const char* title)
    {
        g_window.title = title;

        double mouseX, mouseY;
        int winW, winH;
        glfwGetCursorPos(OpenGL2::Backend_GetWindow(), &mouseX, &mouseY);
        glfwGetWindowSize(OpenGL2::Backend_GetWindow(), &winW, &winH);

        // Mouse click detection
        if (glfwGetMouseButton(OpenGL2::Backend_GetWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            float titlebarHeight = 24.0f;
            bool hovered = (mouseX >= g_window.x && mouseX <= g_window.x + g_window.width &&
                mouseY >= g_window.y && mouseY <= g_window.y + titlebarHeight);
            if (hovered && !g_window.dragging) {
                g_window.dragging = true;
                g_window.dragOffsetX = mouseX - g_window.x;
                g_window.dragOffsetY = mouseY - g_window.y;
            }
        }
        else {
            g_window.dragging = false;
        }

        if (g_window.dragging) {
            g_window.x = mouseX - g_window.dragOffsetX;
            g_window.y = mouseY - g_window.dragOffsetY;
        }

        // Draw window background
        OpenGL2::Backend_DrawRect(g_window.x, g_window.y, g_window.width, g_window.height, 0.15f, 0.15f, 0.15f);

        // Draw titlebar
        OpenGL2::Backend_DrawRect(g_window.x, g_window.y, g_window.width, 24.0f, 0.2f, 0.2f, 0.2f);

        // Draw title text
        OpenGL2::Backend_DrawText(g_window.x + 6, g_window.y + 6, title, 1.0f, 1.0f, 1.0f);


        ctx.cursorX = g_window.x + 10.0f;
        ctx.cursorY = g_window.y + 30.0f;
        return true;
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

        float w = ctx.itemWidth;
        float h = ctx.itemHeight;

        // Set position based on layout context
        float x = ctx.cursorX;
        float y = ctx.cursorY;

        // Layout update
        if (ctx.sameLineNext) {
            ctx.cursorX += w + ctx.itemSpacing;  // move right
            ctx.sameLineNext = false;
        }
        else {
            ctx.cursorX = g_window.x + 10.0f;    // align to window start
            ctx.cursorY += h + ctx.itemSpacing;  // move down
        }

        // Input
        double mx, my;
        GLFWwindow* win = OpenGL2::Backend_GetWindow();
        glfwGetCursorPos(win, &mx, &my);

        bool hovered = (mx >= x && mx <= x + w && my >= y && my <= y + h);
        bool isDown = glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
        bool clicked = hovered && isDown && !mousePressedLastFrame;
        mousePressedLastFrame = isDown;

        // Draw
        OpenGL2::Backend_DrawRect(x, y, w, h,
            hovered ? 0.2f : 0.1f,
            hovered ? 0.7f : 0.5f,
            1.0f);  // RGB only — use glColor4f if you want alpha buttons

        OpenGL2::Backend_DrawText(x + 10.0f, y + 12.0f, label, 1.0f, 1.0f, 1.0f);

        return clicked;
    }

    void Text(const char* label)
    {
        if (!backendLinked || !label) return;

        float x = ctx.cursorX;
        float y = ctx.cursorY;

        int textWidth = static_cast<int>(strlen(label)) * 8;

        // Draw
        OpenGL2::Backend_DrawText(x, y, label, 1.0f, 1.0f, 1.0f);

        // Layout update
        if (ctx.sameLineNext) {
            ctx.cursorX += textWidth + ctx.itemSpacing;
            ctx.sameLineNext = false;
        }
        else {
            ctx.cursorX = g_window.x + 10.0f;
            ctx.cursorY += 20.0f;
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