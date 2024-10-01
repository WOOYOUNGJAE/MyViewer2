#include "pch.h"
#include "Engine.h"
#include "Viewer.h"

CViewer* g_pViewer;
void On_Resize_Window(GLFWwindow* pWindow, INT winX, INT winY);

void On_Resize_Window(GLFWwindow* pWindow, INT winX, INT winY)
{
    glViewport(0, 0, winX, winY);
    if (g_pViewer)
    {
		g_pViewer->On_Resize_Window((UINT)winX, (UINT)winY);	    
    }
}

CEngine::CEngine(IEngine::OpenGL identifier, UINT uiWinX, UINT uiWinY, const char* szTitle)
{
    // Init GL
    if (!glfwInit())
    {
        ERROR_MESSAGE("Init GLFW Failed");
        return;
    }

	// Create a GLFW window with OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // Request OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE); // Double Buffering

    // Create Window, Context
    m_pWindow = glfwCreateWindow((int)uiWinX, (int)uiWinY, szTitle, nullptr, nullptr);
    glfwMakeContextCurrent(m_pWindow); // Bind Context

    // Init GLAD
    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == false)
    {
        ERROR_MESSAGE("Init GLAD Failed");
        return;
    }

    // Create Viewer
    m_pViewer = new CViewer(uiWinX, uiWinY);
    g_pViewer = m_pViewer;

    // Register Callback win Resizing Func
    glfwSetFramebufferSizeCallback(m_pWindow, On_Resize_Window);
}

CEngine::~CEngine()
{
    DELETE_INSTANCE(m_pViewer);
}

INT CEngine::Engine_Tick(BOOL bShouldClose, FLOAT fDeltaTime)
{
    if (bShouldClose)
    {
        glfwTerminate();
        return TRUE;
    }

    if (m_pViewer == nullptr)
    {
        ERROR_MESSAGE("Viewer is Null");
        __debugbreak();
        return TRUE;
    }
    if (glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_pWindow, true);
        glfwTerminate();
        return TRUE;
    }


    glfwPollEvents();

    m_pViewer->BeginRender();
    m_pViewer->MainRender();
    m_pViewer->EndRender(m_pWindow);

    return glfwWindowShouldClose(m_pWindow);
}
