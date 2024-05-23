#pragma once

#include "I3DRenderer.h"
#include "DX11Define.h"
#include "unordered_map"

class DX11Device;
class Box;
class Camera;
class Grid;
class IObject;
class Text;

class D3DRenderer : public I3DRenderer
{
public:
	D3DRenderer();
	virtual ~D3DRenderer();

	virtual bool Initialize(int hWnd, int hInstance, int screenWidth, int screenHeight) override;
	virtual void Update(float dTime) override;
	
	virtual void BeginRender() override;
	virtual void Render() override;
	virtual void LateRender() override;
	virtual void EndRender() override;

	virtual void Finalize() override;

	virtual void OnResize() override;
	virtual bool IsValidDevice() override;
	virtual void SetClientSize(int screenWidth, int screenHeight) override;
	virtual void SetWinMinMax(bool isMinimized, bool isMaxmized) override;

	virtual void AddBox(std::string name, int nowRS) override;
	virtual void AddBox(int id, int nowRS) override;
	virtual void SetBoxColor(std::string name, float r, float g, float b, float a) override;
	virtual void SetBoxColor(int id, float r, float g, float b, float a) override;
	virtual void AddGrid(std::string name, int gridSize_x, int gridSize_y) override;

	virtual void SetRenderState(std::string name, int nowRS) override;
	virtual void SetRenderState(int id, int nowRS) override;
	virtual void SetRectSize(std::string name, float scale) override;
	virtual void SetRectSize(int id, float scale) override;
	virtual void Rotate(std::string name, float x, float y, float z) override;
	virtual void TransformObjectFromName(std::string name, const XMMATRIX& world) override;
	virtual void TransformObjectFromID(int id, const XMMATRIX& world) override;
	virtual void DeleteObject(int id) override;
	virtual void DeleteObject(std::string name) override;

	virtual void DrawColoredText(int x, int y, float r, float g, float b, float a, int id, const wchar_t* text) override;

public:
	HWND m_hWnd;
	HINSTANCE m_hInst;
	bool m_appPaused;
	bool m_minimized;
	bool m_maximized;
	int m_screenWidth;
	int m_screenHeight;

private:
	DX11Device* m_dx11Device;
	Camera* m_camera;
	Text* m_text;
	std::vector<IObject*> m_objects;
};

