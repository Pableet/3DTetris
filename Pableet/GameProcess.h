#pragma once
#include <windows.h>

class GameEngine;
class I3DRenderer;
class GameTimer;

class GameProcess
{
public:
	GameProcess();
	~GameProcess();

private:
	// 공통적인 설정

	// 윈도 초기 위치
	const int m_WindowPosX = 300;
	const int m_WindowPosY = 300;

	// 화면의 크기
	const int m_ScreenWidth = 1280;
	const int m_ScreenHeight = 768;

	// 윈도 관련
	HWND m_hWnd;
	MSG m_Msg;
	static bool sResizing;

	GameEngine* m_gameEngine;
	I3DRenderer* m_renderer;
	GameTimer* m_timer;
private:
	// for Initialize
	void RecalcWindowSize();

	// for Loop
	void UpdateAll();
	void RenderAll();


public:
	// 게임을 초기화한다.
	HRESULT Initialize(HINSTANCE hInstance);

	// 메인 게임 루프. 실제 게임이 진행되는 반복구문
	void Loop();

	// 게임을 정리한다.
	void Finalize();


	// 메시지 핸들러 (윈도 콜백)
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
