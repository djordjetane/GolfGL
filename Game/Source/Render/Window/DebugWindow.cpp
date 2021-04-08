#include <precomp.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "DebugWindow.h"

#include <Window/Window.h>

/* Initialize after setting up native opengl viewport */
bool Window::DebugWindow::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    bool retval = ImGui_ImplGlfw_InitForOpenGL(Window::GetGlfwWindow(), true);
    return retval && ImGui_ImplOpenGL3_Init(WindowData::glslVersion);
}

bool Window::DebugWindow::Update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Debug Window", &m_DebugMenuActive, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize);

    DrawLightMenu();

    ImGui::Separator();

    DrawGFXSettings();

    float frametime = 1000.f / ImGui::GetIO().Framerate;
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", frametime, ImGui::GetIO().Framerate);

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    m_ViewportsEnable = (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) != 0;

    if (m_ViewportsEnable)
    {
        GLFWwindow *backupCurrentContext = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backupCurrentContext);
    }

    return true;
}

void Window::DebugWindow::Destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    m_DebugMenuActive = false;
}

void Window::DebugWindow::DrawLightMenu()
{
    ImGui::BeginGroup();

    ImGui::Text("Light:");
    ImGui::InputFloat3("Light position", &LIGHT.LightPosition[0]);
    ImGui::InputFloat3("Light ambient", &LIGHT.Ambient[0]);
    ImGui::InputFloat3("Light diffuse", &LIGHT.Diffuse[0]);
    ImGui::InputFloat3("Light specular", &LIGHT.Specular[0]);

    ImGui::EndGroup();
}

void Window::DebugWindow::DrawGFXSettings()
{
    ImGui::Text("Graphics settings:");
    ImGui::BeginGroup();

    if (ImGui::BeginMenu("Resolution"))
    {
        if (ImGui::MenuItem("1280x720"))
        {
            glfwSetWindowSize(Window::GetGlfwWindow(), 1280, 720);
            glViewport(0, 0, 1280, 720);
        }
        if (ImGui::MenuItem("1920x1080"))
        {
            glfwSetWindowSize(Window::GetGlfwWindow(), 1920, 1080);
            glViewport(0, 0, 1920, 1080);
        }

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Anti-Aliasing"))
    {
        if (ImGui::MenuItem("None"))
        {
            WindowData::fxaa = false;
        }
        if (ImGui::MenuItem("FXAA"))
        {
            WindowData::fxaa = true;
        }

        ImGui::EndMenu();
    }

    ImGui::EndGroup();
}