#define LGui_OpenGL2
#include "OpenGL2.h"
#include "../../graphicsHandler/font.h"

static GLFWwindow* window = nullptr;

GLFWwindow* OpenGL2::Backend_GetWindow()
{
    return window;
}

void OpenGL2::Backend_Init(int width, int height, const char* title)
{
    if (!glfwInit()) {
        std::cerr << "[LGui/OpenGL] GLFW init failed\n";
        return;
    }

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        std::cerr << "[LGui/OpenGL] Failed to create window\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);  // Make top-left (0,0)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    std::cout << "[LGui/OpenGL] Backend Initialized\n";
}

void OpenGL2::Backend_BeginFrame()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
}

void OpenGL2::Backend_DrawRect(float x, float y, float w, float h, float r, float g, float b) 
{
    glColor3f(r, g, b);
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