#include "GameProcess.h"
#include "GraphicsEngine.h"
#include "GameTimer.h"


GameProcess::GameProcess()
	: m_Msg(), m_hWnd(nullptr), m_timer(nullptr), m_graphicsEngine(nullptr)
{

}

GameProcess::~GameProcess()
{

}

bool GameProcess::sResizing = false;

static GraphicsEngine* S_pDREngineInstance = nullptr;

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
		m_windowPosX, m_windowPosY, m_screenWidth, m_screenHeight,
		nullptr, nullptr, hInstance, NULL);

	if (!m_hWnd) return S_FALSE;

	/// 그래픽스 엔진 관련
	m_graphicsEngine = new GraphicsEngine((int)m_hWnd, (int)hInstance, m_screenWidth, m_screenHeight);
	S_pDREngineInstance = m_graphicsEngine;

	// 생성된 윈도를 화면에 표시
	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);

	// 클라이언트 영역이 원하는 게임 해상도가 되도록 윈도 사이즈 재조정
	RecalcWindowSize();

	// 시간 조절 관련
	m_timer = new GameTimer;
	m_timer->Initialize();

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
	newRect.right = m_screenWidth;
	newRect.bottom = m_screenHeight;

	AdjustWindowRectEx(&newRect, _style, NULL, _exstyle);

	// 클라이언트 영역보다 윈도 크기는 더 커야 한다. (외곽선, 타이틀 등)
	int _newWidth = (newRect.right - newRect.left);
	int _newHeight = (newRect.bottom - newRect.top);

	SetWindowPos(m_hWnd, HWND_NOTOPMOST, nowRect.left, nowRect.top,
		_newWidth, _newHeight, SWP_SHOWWINDOW);
}

void GameProcess::UpdateAll()
{
	/// 시간 계산
	m_timer->Update();

	/// 키 입력
	if (GetAsyncKeyState(VK_RETURN))
	{
	}

	/// esc로 끄기
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	/// 엔진 업데이트
	m_graphicsEngine->Update(m_timer->GetDTime());
}

void GameProcess::RenderAll()
{
	/// 엔진만의 그리기를 한다.
	m_graphicsEngine->Render();
}

void GameProcess::Finalize()
{
	m_graphicsEngine->Finalize();
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
		S_pDREngineInstance->SetClientSize(LOWORD(lParam), HIWORD(lParam));

		if (S_pDREngineInstance->IsValidDevice())
		{
			if (wParam == SIZE_MINIMIZED)
			{
				//mAppPaused = true;
				S_pDREngineInstance->SetWinMinMax(true, false);
			}
			else if (wParam == SIZE_MAXIMIZED)
			{
				//mAppPaused = false;
				S_pDREngineInstance->SetWinMinMax(false, true);
				S_pDREngineInstance->OnResize();
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
					S_pDREngineInstance->SetWinMinMax(false, false);

					S_pDREngineInstance->OnResize();
				}
			}
		}
	}
	return 0;

	// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
	case WM_ENTERSIZEMOVE:
	{
		//mAppPaused = true;
		sResizing = true;
		//mTimer.Stop();
	}
	return 0;

	// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
	// Here we reset everything based on the new window dimensions.
	case WM_EXITSIZEMOVE:
	{
		//mAppPaused = false;
		sResizing = false;
		//mTimer.Start();
		S_pDREngineInstance->OnResize();
	}
	return 0;

	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		return 0;

	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		return 0;

	case WM_MOUSEMOVE:

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
