#include "InputManager.h"
#include "GameProcess.h"
#include "../Graphics/I3DRenderer.h"
#include "GameTimer.h"
#include "GameEngine.h"
GameProcess::GameProcess()
	: m_Msg(), m_hWnd(nullptr), m_gameEngine(nullptr), m_renderer(nullptr)
	, m_timer(nullptr)
{

}

GameProcess::~GameProcess()
{
	m_gameEngine->Release();
	delete m_renderer;
	delete m_gameEngine;
	delete m_timer;
}

bool GameProcess::sResizing = false;

static I3DRenderer* S_pRendererInstance = nullptr;

HRESULT GameProcess::Initialize(HINSTANCE hInstance)
{
	/// Win32 관련
	// 윈도 클래스
	wchar_t szAppName[] = L"Game";
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = this->WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = szAppName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	// 윈도 클래스 등록
	RegisterClassExW(&wcex);

	// 윈도 생성
	m_hWnd = CreateWindowW(szAppName, szAppName,
		WS_OVERLAPPEDWINDOW,
		m_WindowPosX, m_WindowPosY, m_ScreenWidth, m_ScreenHeight,
		nullptr, nullptr, hInstance, NULL);

	if (!m_hWnd) return S_FALSE;

	/// 그래픽스 엔진 관련

	// 생성된 윈도를 화면에 표시

	// 클라이언트 영역이 원하는 게임 해상도가 되도록 윈도 사이즈 재조정
	m_timer = new GameTimer;
	m_timer->Initialize();

	m_renderer = I3DRenderer::CreateRenderer();
	S_pRendererInstance = m_renderer;
	m_renderer->Initialize((int)m_hWnd, (int)hInstance, m_ScreenWidth, m_ScreenHeight);

	m_gameEngine = new GameEngine(m_hWnd, hInstance, m_ScreenWidth, m_ScreenHeight);
	m_gameEngine->SetRenderer(m_renderer);
	m_gameEngine->Initialize();

	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);

	RecalcWindowSize();

	return S_OK;
}

void GameProcess::Loop()
{
	while (true)
	{
		if (PeekMessage(&m_Msg, NULL, 0, 0, PM_REMOVE))
		{
			if (m_Msg.message == WM_QUIT) break;

			DispatchMessage(&m_Msg);
		}
		else
		{
			UpdateAll();
			RenderAll();
		}
	}
}

// 창 모드인 경우, 클라이언트 영역의 크기와 윈도 크기의 차이를 보정한다.
// 만약 상수를 적당히 더하는 것이라면, 그 값이 윈도 스타일과 버전따라 다 다르다.
void GameProcess::RecalcWindowSize()
{
	RECT nowRect;
	DWORD _style = (DWORD)GetWindowLong(m_hWnd, GWL_STYLE);
	DWORD _exstyle = (DWORD)GetWindowLong(m_hWnd, GWL_EXSTYLE);

	GetWindowRect(m_hWnd, &nowRect);

	RECT newRect;
	newRect.left = 0;
	newRect.top = 0;
	newRect.right = m_ScreenWidth;
	newRect.bottom = m_ScreenHeight;

	AdjustWindowRectEx(&newRect, _style, NULL, _exstyle);

	// 클라이언트 영역보다 윈도 크기는 더 커야 한다. (외곽선, 타이틀 등)
	int _newWidth = (newRect.right - newRect.left);
	int _newHeight = (newRect.bottom - newRect.top);

	SetWindowPos(m_hWnd, HWND_NOTOPMOST, nowRect.left, nowRect.top,
		_newWidth, _newHeight, SWP_SHOWWINDOW);
}

void GameProcess::UpdateAll()
{
	

	/// 엔진 업데이트
	m_timer->Update();
	m_renderer->Update(m_timer->GetDTime());
	m_gameEngine->Update(m_timer->GetDTime());
}

void GameProcess::RenderAll()
{
	/// 엔진만의 그리기를 한다.
	m_renderer->BeginRender();
	m_gameEngine->Render();
	m_renderer->EndRender();
}

void GameProcess::Finalize()
{
	m_gameEngine->Release();
}

// 메시지 핸들러 (윈도 콜백)
LRESULT CALLBACK GameProcess::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT ps;

	switch (message)
	{
		// WM_ACTIVATE is sent when the window is activated or deactivated.  
		// We pause the game when the window is deactivated and unpause it 
		// when it becomes active.  
	case WM_ACTIVATE:
		/*
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			mAppPaused = true;
			mTimer.Stop();
		}
		else
		{
			mAppPaused = false;
			mTimer.Start();
		}
		*/
		return 0;

		// WM_SIZE is sent when the user resizes the window.  
	case WM_SIZE:
	{
		// Save the new client area dimensions.
		S_pRendererInstance->SetClientSize(LOWORD(lParam), HIWORD(lParam));

		if (S_pRendererInstance->IsValidDevice())
		{
			if (wParam == SIZE_MINIMIZED)
			{
				//mAppPaused = true;
				S_pRendererInstance->SetWinMinMax(true, false);
			}
			else if (wParam == SIZE_MAXIMIZED)
			{
				//mAppPaused = false;
				S_pRendererInstance->SetWinMinMax(false, true);
				S_pRendererInstance->OnResize();
			}
			else if (wParam == SIZE_RESTORED)
			{
				// Restoring from minimized state?
				// Restoring from maximized state?
				if (sResizing)
				{
					// If user is dragging the resize bars, we do not resize 
					// the buffers here because as the user continuously 
					// drags the resize bars, a stream of WM_SIZE messages are
					// sent to the window, and it would be pointless (and slow)
					// to resize for each WM_SIZE message received from dragging
					// the resize bars.  So instead, we reset after the user is 
					// done resizing the window and releases the resize bars, which 
					// sends a WM_EXITSIZEMOVE message.
				}
				else // API call such as SetWindowPos or mSwapChain->SetFullscreenState.
				{
					S_pRendererInstance->SetWinMinMax(false, false);

					S_pRendererInstance->OnResize();
				}
			}
		}
	}
	return 0;

	// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
	case WM_ENTERSIZEMOVE:
	{
		//mAppPaused = false;
		sResizing = false;
		//mTimer.Start();
		S_pRendererInstance->OnResize();
	}
	return 0;

	

#pragma region Mouse

	case WM_ACTIVATEAPP:
		InputManager::GetInstance()->m_pKeyboardData->ProcessMessage(message, wParam, lParam);
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
		InputManager::GetInstance()->m_pMouseData->ProcessMessage(message, wParam, lParam);
		break;

#pragma endregion
#pragma region Keyboard


	case WM_SYSKEYDOWN:
		if (wParam == VK_RETURN && (lParam & 0x60000000) == 0x20000000)
		{
			// This is where you'd implement the classic ALT+ENTER hotkey for fullscreen toggle
		}
		InputManager::GetInstance()->m_pKeyboardData->ProcessMessage(message, wParam, lParam);
		break;

	case WM_KEYDOWN:
		if (GetAsyncKeyState(VK_ESCAPE) & 0x01)
			PostQuitMessage(0);
	case WM_KEYUP:
	case WM_SYSKEYUP:
		InputManager::GetInstance()->m_pKeyboardData->ProcessMessage(message, wParam, lParam);
		break;

#pragma endregion


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
