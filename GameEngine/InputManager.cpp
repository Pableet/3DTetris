#include "InputManager.h"


void InputManager::Initialize(HWND hWnd)
{
	m_hWnd = hWnd;
	m_pMouseData = std::make_unique<DirectX::Mouse>();
	m_pKeyboardData = std::make_unique<DirectX::Keyboard>();
}

void InputManager::Release()
{

}

void InputManager::Update()
{
	GetWindowRect(m_hWnd, &windowRect);
	GetClientRect(m_hWnd, &clientRect);
	m_Keyboard.Update(m_pKeyboardData.get()->GetState());
	m_Mouse.Update(m_pMouseData.get()->GetState());
	m_Mouse.MouseMove();


}


bool __cdecl InputManager::Keyboard::IsKeyHold(char _key) const noexcept
{
	return lastState.IsKeyDown((DirectX::Keyboard::Keys)_key);
}

bool __cdecl InputManager::Keyboard::IsKeydown(char _key) const noexcept
{

	return IsKeyPressed((DirectX::Keyboard::Keys)_key);
}

bool __cdecl InputManager::Keyboard::IsKeyUp(char _key) const noexcept
{

	return IsKeyReleased((DirectX::Keyboard::Keys)_key);
}

bool __cdecl InputManager::Mouse::IsButtonDown(ButtonState _bs) const noexcept
{
	return (_bs == PRESSED);
}

bool __cdecl InputManager::Mouse::IsButtonHold(ButtonState _bs) const noexcept
{
	return (_bs == HELD);
}

bool __cdecl InputManager::Mouse::IsButtonUp(ButtonState _bs) const noexcept
{
	return (_bs == RELEASED);
}

bool __cdecl InputManager::Mouse::IsButtonHover(ButtonState _bs) const noexcept
{
	return (_bs == UP);
}

void InputManager::Mouse::MouseMove()
{
	isMove = false;
	static int x, y;

	// 마우스 위치를 가져온다.
	x = GetLastState().x;
	y = GetLastState().y;



	// 이전 값이 기본값과 다르면
	// 현재 x나 y가 이전위치와 다르다면
	if (isMouseCenter == false)
	{
		if ((x != prev.x) || (y != prev.y))
		{
			// move 값에 변화량을 입력하고.
			moveX = x - prev.x;
			moveY = y - prev.y;

			// 마우스 이동을 true로 바꾼다.
			isMove = true;
		}
	}
	else
	{
		moveX = 0;
		moveY = 0;
		isMouseCenter = false;
	}

	prev = GetLastState();
}

