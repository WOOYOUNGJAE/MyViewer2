#pragma once
#include "EngineConfig.h"
#include "Engine_Common/Includes/EngineInterface.h"
#include "Viewer.h"

class CViewer;
struct GLFWwindow;
/**
 * @brief Top-level class
 */
class ENGINEOPENGL_DLL CEngine final : public IEngine
{
	COM_FUNC
public:
	CEngine() = delete;
	CEngine(IEngine::OpenGL identifier, UINT uiWinX, UINT uiWinY, const char* szTitle);
	~CEngine();
public:
	HRESULT Initialize(void*) override;
	/**
	 * @return If WindowShouldClose
	 */
	INT Engine_Tick(FLOAT fDeltaTime) override;
	void BeginRender() override;
	void MainRender() override;
	void EndRender() override;

	// getter
	IRenderer* Get_Renderer() override;

	IMeshObject* Create_EmptyBasicMesh(void* pData) override;
	IMeshObject* Create_EmptyColoredMesh(void* pData) override;
private:
	GLFWwindow* m_pWindow = nullptr;
	CViewer* m_pViewer = nullptr;
	IRenderer* m_pRenderer = nullptr;
};