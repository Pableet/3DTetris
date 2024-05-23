#include "GameTimer.h"

GameTimer::GameTimer()
	: m_fps(0), m_deltaTime(0.)
	, m_dTime{}, m_start{}, m_end{}
{

}

void GameTimer::Initialize()
{
	m_start = std::chrono::system_clock::now();
}

void GameTimer::Update()
{
	m_end = std::chrono::system_clock::now();
	m_dTime = m_end - m_start;
	m_start = m_end;

	// dTime 
	m_deltaTime = m_dTime.count();

	// fps
	m_fps = static_cast<int>(1 / m_dTime.count());
}
