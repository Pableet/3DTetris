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
	// �������� ����

	// ���� �ʱ� ��ġ
	const int m_windowPosX = 300;
	const int m_windowPosY = 300;

	// ȭ���� ũ��
	const int m_screenWidth = 1024;
	const int m_screenHeight = 768;

	// ���� ����
	HWND m_hWnd;
	MSG m_Msg;
	static bool sResizing;


	// 3D �׷��Ƚ� ����
	GraphicsEngine* m_graphicsEngine;
	// �ð� ����
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
