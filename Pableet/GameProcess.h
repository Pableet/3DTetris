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
	// �������� ����

	// ���� �ʱ� ��ġ
	const int m_WindowPosX = 300;
	const int m_WindowPosY = 300;

	// ȭ���� ũ��
	const int m_ScreenWidth = 1280;
	const int m_ScreenHeight = 768;

	// ���� ����
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
	// ������ �ʱ�ȭ�Ѵ�.
	HRESULT Initialize(HINSTANCE hInstance);

	// ���� ���� ����. ���� ������ ����Ǵ� �ݺ�����
	void Loop();

	// ������ �����Ѵ�.
	void Finalize();


	// �޽��� �ڵ鷯 (���� �ݹ�)
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
