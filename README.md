
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

```c++
LGui::BeginFrame();
LGui::Text("Hello, World!");
if (LGui::Button("Click Me")) {
    std::cout << "Button was clicked!\n";
}
LGui::EndFrame();
```


## 🔧 Backend Flexibility

You choose your renderer with a Single Line of Code

```#define LGui_OpenGL2``` | More backend to come

If no backend is defined, LGui will **alert** you with:
```
[LGui] No rendering backend detected. Error: 0xB00B1E
```

More Alert And Error Codes = More easier to understand the Broken part
## 📦 Ideal For:

- Game developers

- Engine builders

- Tool creators

- Educational and experimental projects

- Anyone who wants Immidiate GUI logic without Immidiate GUI weight


## 🚧 Actively Growing:

Future support planned for:

- ```InputText``` | ```Checkbox``` | ```Slider```

- Custom themes ```(SetStyleColor)```

- ```Groups``` | ```columns``` | ```hotkeys```

- ```Software``` & ```Vulkan``` backend options

## 📜 Update Logs

- ```[07-07-2025]``` [+] Updated backend & added button pressing logic
- ```[07-07-2025]``` [-] Bug while moving the window - the window is ghosting !
