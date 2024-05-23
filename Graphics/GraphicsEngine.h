#pragma once

class I3DRenderer;


class GraphicsEngine
{
public:
	GraphicsEngine(int hWnd, int hInstance, int screenWidth, int screenHeight);
	~GraphicsEngine();
	void Update(float deltaTime);
	void Render();
	void Finalize();

public:
	void OnResize();
	bool IsValidDevice();
	void SetClientSize(int screenWidth, int screenHeight);
	void SetWinMinMax(bool isMinimized, bool isMaxmized);

private:
	I3DRenderer* m_renderer;

};

