#pragma once

#include <Entities/EntityManager.h>
#include <Window/DebugWindow.h>
#include <Window/Window.h>

namespace Render
{
    class Framebuffer;

    class Renderer
    {
    public:
        Renderer(const Renderer &) = delete;
        Renderer(Renderer &&) = delete;
        void operator=(const Renderer &) = delete;

        bool Init();
        void Update();
        bool IsRunning();

        GLFWwindow *GetWindow();

        Renderer() = default;
        ~Renderer();

    private:
        float lastTime;
        Window::Window m_Window;
        Window::DebugWindow m_DebugWindow;

        Framebuffer *m_FrameBuff = nullptr;
        Entities::EntityManager *m_EntryManager = nullptr;

        inline static float m_clearColorRgba[4] = {0.5f, 0.5f, 0.5f, 1.f};

        inline void m_clearColor();
        inline void m_UpdateWindows();
    };
} // namespace Render
