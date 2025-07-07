
# 🪶 LGui – Lightweight Immidiate Mode GUI Library


LGui is a fast, minimal, and developer-friendly GUI library inspired by ImGui — designed for those who want UI rendering without the bloat. Built from scratch using GLFW + OpenGL2 (pluggable backend system), LGui gives you full control over GUI rendering with a syntax that feels familiar but is faster to set up and easier to customize.


## Author

- [@OfficiallyEra](https://github.com/OfficiallyEra)


## ✨ Key Features:
Immediate Mode UI rendering

💡 Backend-agnostic design — OpenGL2 out of the box, more to come

⚡ Zero-dependency core, ultra-light footprint

🔌 Plug-and-play integration — no build headaches

🖱 Built-in interaction: button clicks, text rendering, mouse hover, etc.

🧱 Auto-layout & SameLine() logic

🧰 Easily extensible — you own every line
## 🧩 Example Usage

- [1] Clone the repository
- [2] Copy and paste the folders as it is in your project directory
- [3] And that's it now you can use it in your project !
```c++
#define LGui_OpenGL2
#include "../core/lgui.h"

int main() {
    OpenGL2::RegisterBackend();

    const char* targetWindowTitle = "Untitled - Notepad";
    int counter = 0;

    LGui::Init(800, 600, "LGui Demo", targetWindowTitle);

    while (!glfwWindowShouldClose(OpenGL2::Backend_GetWindow()))
    {
        LGui::Begin("LGui");

        LGui::Text("Welcome to LGui!");

        if (LGui::Button("Click Me!")) 
        {
            counter++;
            std::cout << "You clicked the button! ["<<counter<<"] times\n";
        }

        LGui::EndFrame();
    }

    LGui::Shutdown();
    return 0;
}
```




## 🔧 Backend Flexibility

- ***You choose your backend renderer with a Single Line of Code***

- Supported Backend(s) - > **OpenGL2**  | More backend to come

```#define LGui_OpenGL2``` <- *Simple Implimentation*

If no backend is defined, LGui will **alert** you with:
```
[LGui] No rendering backend detected. Error: 0xB00B1E
```

More Alert And Error Codes = More easier to understand the Broken part
## 📦 Ideal For:

- ****Game developers****

- ****Engine builders****

- ****Tool creators****

- ****Educational and experimental projects****

- ****Anyone who wants Immidiate GUI logic without**** ```Immidiate GUI weight``` 


## 🚧 Actively Growing:

Future support planned for:

- ```InputText``` | ```Checkbox``` | ```Slider```

- Custom themes ```(SetStyleColor)```

- ```Groups``` | ```columns``` | ```hotkeys```

- ```Software``` & ```Vulkan``` backend options

- ```DirectX``` and ```Vulken``` Backend Support
## 📜 Update Logs

- ```[07-07-2025]``` [+] Updated backend & added button pressing logic
- ```[07-07-2025]``` [-] Bug while moving the window - the window is ghosting !
