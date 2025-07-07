#define LGui_OpenGL2
#pragma warning(disable : 4244)
#pragma warning(disable : 4305)
#define GLFW_EXPOSE_NATIVE_WIN32
#include "OpenGL2.h"
#include "../../graphicsHandler/font.h"

static GLFWwindow* window = nullptr;
HWND hwnd = glfwGetWin32Window(window);

GLFWwindow* OpenGL2::Backend_GetWindow()
{
    return window;
}

namespace OpenGL2 
{
    void Backend_Init(int width, int height, const char* title, const char* targetWindowTitle)
    {
        if (!glfwInit()) {
            std::cerr << "[LGui/OpenGL] GLFW init failed\n";
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_STENCIL_BITS, 8);

        if (LGui::TWindowBG)
        {
            glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
            glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
            glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
        }

        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window) {
            std::cerr << "[LGui/OpenGL] Failed to create window\n";
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);

        // Get valid HWND after window creation
        HWND hwnd = glfwGetWin32Window(window);  // ✅ RIGHT PLACE

        // Optional: Position over target
        if (targetWindowTitle && targetWindowTitle[0] != '\0') {
            std::wstring wideTitle(targetWindowTitle, targetWindowTitle + strlen(targetWindowTitle));
            HWND target = FindWindowW(NULL, wideTitle.c_str());
            if (target) {
                RECT rect;
                GetWindowRect(target, &rect);
                int w = rect.right - rect.left;
                int h = rect.bottom - rect.top;
                glfwSetWindowPos(window, rect.left, rect.top);
                glfwSetWindowSize(window, w, h);
            }
        }

        if (LGui::TWindowBG)
        {
            // Enable full transparency and remove black ghost
            MARGINS margins = { -1 };
            DwmExtendFrameIntoClientArea(hwnd, &margins);

            LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
            SetWindowLong(hwnd, GWL_EXSTYLE, exStyle | WS_EX_LAYERED);
            SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
        }

        if (LGui::ClickThrough)
        {
            LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
            SetWindowLong(hwnd, GWL_EXSTYLE, exStyle | WS_EX_LAYERED | WS_EX_TRANSPARENT);
            SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
        }

        // Setup OpenGL viewport
        int fbWidth, fbHeight;
        glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
        glViewport(0, 0, fbWidth, fbHeight);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0f, fbWidth, fbHeight, 0.0f, -1.0f, 1.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        std::cout << "[LGui/OpenGL] Backend Initialized\n";
    }


}

void OpenGL2::Backend_BeginFrame()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (LGui::TWindowBG)
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // Fully transparent
    else
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // Solid background

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // Prevent ghosting on transparent windows
    if (LGui::TWindowBG)
        glFinish();

    glLoadIdentity();
}


void OpenGL2::Backend_DrawRect(float x, float y, float w, float h, float r, float g, float b) 
{
    glColor4f(r, g, b, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

void OpenGL2::Backend_DrawText(float x, float y, const char* text, float r, float g, float b) 
{
    char buffer[99999]; // very large
    int quads = stb_easy_font_print(x, y, (char*)text, nullptr, buffer, sizeof(buffer));

    glColor3f(r, g, b);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 16, buffer);
    glDrawArrays(GL_QUADS, 0, quads * 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void OpenGL2::Backend_EndFrame()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void OpenGL2::Backend_Shutdown()
{
    glfwDestroyWindow(window);
    glfwTerminate();
    std::cout << "[LGui/OpenGL] Backend Shut Down\n";
}

// Register the backend on load
void OpenGL2::RegisterBackend()
{
    LGui::NotifyBackendLinked();
}