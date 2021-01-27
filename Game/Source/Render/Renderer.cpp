#include <precomp.h>

#include "Renderer.h"

bool Render::Renderer::Init()    
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);        

    if ( !m_Window.Init() )
    {
        LOG_FATAL("Failed to init window!");
        return false;
    }


    if ( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) )
    {
        LOG_ERROR("Glad failed to load gl");
        return false;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    // glDepthFunc(GL_ALWAYS);


    glViewport( 0, 0, WindowData::width, WindowData::height ); 

    glfwSetFramebufferSizeCallback(m_Window.GetGlfwWindow(), Window::FrameBufferResizeCallback);


    // ImGui part
#ifdef _DEBUG
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();       
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();    

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_Window.GetGlfwWindow(), true);
    ImGui_ImplOpenGL3_Init(WindowData::glslVersion);
#endif // _DEBUG    


    lastTime = glfwGetTime();

    LOG_INFO("Renderer initialized");

    return true;
}

void Render::Renderer::Update()
{   

    float timeValue = glfwGetTime();
    float delta = timeValue - lastTime;
    lastTime = timeValue;

    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    


    if (m_Window.IsRunning())
    {        
        m_Window.Update();
    }        
}

bool Render::Renderer::IsRunning()
{
    return m_Window.m_running;
}

Window* Render::Renderer::GetWindow()
{
    return &m_Window;
}

Render::Renderer::~Renderer()
{           
}
