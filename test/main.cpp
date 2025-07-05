#define LGui_OpenGL2
#include "../core/lgui.h"

int main() {
    OpenGL2::RegisterBackend();

    LGui::Init(800, 600, "LGui Demo");

    while (!glfwWindowShouldClose(OpenGL2::Backend_GetWindow())) 
    {
        LGui::BeginFrame();
        LGui::Text("Welcome to LGui!");
        if (LGui::Button("Click Me!")) 
        {
            std::cout << "You clicked the button!\n";
        }
        LGui::EndFrame();
    }

    LGui::Shutdown();
    return 0;
}