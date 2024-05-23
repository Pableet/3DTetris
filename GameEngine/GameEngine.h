#pragma once

#include "windows.h"

class I3DRenderer;
class ObjectManager;
class SceneManager;

class GameEngine
{
public:
	GameEngine(HWND hWNd, HINSTANCE hInst, int screenWidth, int screenHeight);
	~GameEngine();

public:
	void Initialize();
	void Update(float dTime);
	void Render();
	void Release();

	void SetRenderer(I3DRenderer* renderer)
	{
		m_renderer = renderer;
	}

private:
	HWND m_hWnd;
	HINSTANCE m_hInst;
	int m_screenWidth;
	int m_screenHeight;

	float m_dTime;
	float m_fixTime;

	I3DRenderer* m_renderer;
	ObjectManager* m_objectManager;
	SceneManager* m_sceneManager;

};

