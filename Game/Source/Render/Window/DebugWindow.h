#pragma once

namespace Window
{
    /* Wrapper for ImGui window */
    class DebugWindow
    {
    public:
        bool Init();
        bool Update();

        void Destroy();

        DebugWindow()  = default;
        ~DebugWindow() = default;

    private:
        void DrawLightMenu();
        void DrawGFXSettings();

        bool m_DebugMenuActive = true;
        bool m_ViewportsEnable = false;
    };
} // namespace Window