#pragma once
#include <windows.h>


class GraphicsEngine;
class GameTimer;

class GameProcess
{
public:
	GameProcess();
	~GameProcess();

private:
	// 공통적인 설정

	// 윈도 초기 위치
	const int m_windowPosX = 300;
	const int m_windowPosY = 300;

	// 화면의 크기
	const int m_screenWidth = 1024;
	const int m_screenHeight = 768;

	// 윈도 관련
	HWND m_hWnd;
	MSG m_Msg;
	static bool sResizing;


	// 3D 그래픽스 엔진
	GraphicsEngine* m_graphicsEngine;
	// 시간 제어
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
