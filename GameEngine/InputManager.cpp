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

	// ���콺 ��ġ�� �����´�.
	x = GetLastState().x;
	y = GetLastState().y;



	// ���� ���� �⺻���� �ٸ���
	// ���� x�� y�� ������ġ�� �ٸ��ٸ�
	if (isMouseCenter == false)
	{
		if ((x != prev.x) || (y != prev.y))
		{
			// move ���� ��ȭ���� �Է��ϰ�.
			moveX = x - prev.x;
			moveY = y - prev.y;

			// ���콺 �̵��� true�� �ٲ۴�.
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

