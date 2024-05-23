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
	/// Win32 ����
	// ���� Ŭ����
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

	// ���� Ŭ���� ���
	RegisterClassExW(&wcex);

	// ���� ����
	m_hWnd = CreateWindowW(szAppName, szAppName,
		WS_OVERLAPPEDWINDOW,
		m_windowPosX, m_windowPosY, m_screenWidth, m_screenHeight,
		nullptr, nullptr, hInstance, NULL);

	if (!m_hWnd) return S_FALSE;

	/// �׷��Ƚ� ���� ����
	m_graphicsEngine = new GraphicsEngine((int)m_hWnd, (int)hInstance, m_screenWidth, m_screenHeight);
	S_pDREngineInstance = m_graphicsEngine;

	// ������ ������ ȭ�鿡 ǥ��
	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);

	// Ŭ���̾�Ʈ ������ ���ϴ� ���� �ػ󵵰� �ǵ��� ���� ������ ������
	RecalcWindowSize();

	// �ð� ���� ����
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

// â ����� ���, Ŭ���̾�Ʈ ������ ũ��� ���� ũ���� ���̸� �����Ѵ�.
// ���� ����� ������ ���ϴ� ���̶��, �� ���� ���� ��Ÿ�ϰ� �������� �� �ٸ���.
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

	// Ŭ���̾�Ʈ �������� ���� ũ��� �� Ŀ�� �Ѵ�. (�ܰ���, Ÿ��Ʋ ��)
	int _newWidth = (newRect.right - newRect.left);
	int _newHeight = (newRect.bottom - newRect.top);

	SetWindowPos(m_hWnd, HWND_NOTOPMOST, nowRect.left, nowRect.top,
		_newWidth, _newHeight, SWP_SHOWWINDOW);
}

void GameProcess::UpdateAll()
{
	/// �ð� ���
	m_timer->Update();

	/// Ű �Է�
	if (GetAsyncKeyState(VK_RETURN))
	{
	}

	/// esc�� ����
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	/// ���� ������Ʈ
	m_graphicsEngine->Update(m_timer->GetDTime());
}

void GameProcess::RenderAll()
{
	/// �������� �׸��⸦ �Ѵ�.
	m_graphicsEngine->Render();
}

void GameProcess::Finalize()
{
	m_graphicsEngine->Finalize();
}

// �޽��� �ڵ鷯 (���� �ݹ�)
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
