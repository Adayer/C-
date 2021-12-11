#include "Time.h"

void CTime::InitTime()
{
	m_fixedTick = 1. / 60.;
	QueryPerformanceCounter(&m_previousCountLarge);
	m_previousCount = m_previousCountLarge.QuadPart;
}

void CTime::UpdateTime()
{
	m_elapsedTime += GetTime();

	if (m_elapsedTime > ELAPSED_TIME_MAX)
	{
		m_elapsedTime = ELAPSED_TIME_MAX;
	}
}

double  CTime::GetTime()
{
	QueryPerformanceCounter(&m_currentCount);
	QueryPerformanceFrequency(&m_frequency);
	_int64 resta = (m_currentCount.QuadPart - m_previousCount);

	double iResult = resta / static_cast<double>(m_frequency.QuadPart);
	m_previousCount = m_currentCount.QuadPart;

	return iResult;
}

bool CTime::ProcessSlots()
{
	return (m_elapsedTime >= m_fixedTick);
}