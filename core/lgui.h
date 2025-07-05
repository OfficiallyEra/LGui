#pragma once

// --- Auto-include backend based on user define ---
#if defined(LGui_OpenGL2)
#include "../backend/OpenGL/OpenGL2.h"
#elif defined(LGui_Software)
#include "../backend/SW_BackEnd.h"
#else
#pragma message("No LGui backend defined. Define LGui_OpenGL2 or LGui_Software before including LGui.h")
#endif

// --- LGui Core API ---
namespace LGui 
{
    enum BackendStatus 
    {
        BACKEND_OK = 0,
        BACKEND_MISSING = 0xB00B1E
    };
    
    void Text(const char* label);
    void SameLine();

    struct Context {
        float cursorX = 10.0f;
        float cursorY = 10.0f;
        float itemSpacing = 10.0f;
        float itemWidth = 120.0f;
        float itemHeight = 40.0f;
        bool sameLineNext = false;
    };

    static Context ctx;

    void Init(int width, int height, const char* title);
    void BeginFrame();
    bool Button(const char* label);
    void EndFrame();
    void Shutdown();

    BackendStatus DetectBackend();
    void NotifyBackendLinked();
}