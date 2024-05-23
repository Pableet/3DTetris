#pragma once

#include "SingleTon.h"
#include <windows.h>
#include "../DXTK/Inc/Keyboard.h"
#include "../DXTK/Inc/Mouse.h"


class InputManager : public SingleTon<InputManager>
{
public:
	void Initialize(HWND hWnd);
	void Update();
	void Release();

private:
	class Keyboard : public DirectX::Keyboard::KeyboardStateTracker
	{
	public:
		bool __cdecl IsKeyHold(char _key) const noexcept;

		bool __cdecl IsKeydown(char _key) const noexcept;
		
		bool __cdecl IsKeyUp(char _key) const noexcept;
	};

	class Mouse : public DirectX::Mouse::ButtonStateTracker
	{
	public:

		bool __cdecl IsButtonDown(ButtonState _bs) const noexcept;

		bool __cdecl IsButtonHold(ButtonState _bs) const noexcept;

		bool __cdecl IsButtonUp(ButtonState _bs) const noexcept;

		bool __cdecl IsButtonHover(ButtonState _bs) const noexcept;

		void MouseMove();

		bool isMove = false;
		int moveX = 0;
		int moveY = 0;

		DirectX::Mouse::State prev = {};
		bool isMouseCenter = false;
	};

public:
	Keyboard m_Keyboard;
	Mouse m_Mouse;
	RECT windowRect = { 0,0 };
	RECT clientRect = { 0,0 };

private:
	HWND m_hWnd = nullptr;


private:

	friend class GameProcess;
	std::unique_ptr<DirectX::Keyboard> m_pKeyboardData;
	std::unique_ptr<DirectX::Mouse> m_pMouseData;

};

