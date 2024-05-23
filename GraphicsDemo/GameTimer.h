#pragma once

#include <chrono>


class GameTimer
{
public:
	GameTimer();

	void	Initialize();
	void	Update();

	float	GetDTime() const { return m_deltaTime; };	// ¥‹¿ß ms
	int		GetFPS() const { return m_fps; };

private:
	int m_fps;
	float m_deltaTime;

private:
	std::chrono::duration<float> m_dTime;
	std::chrono::system_clock::time_point m_start;
	std::chrono::system_clock::time_point m_end;
};

