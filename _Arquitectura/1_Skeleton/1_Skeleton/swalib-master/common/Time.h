#pragma once

#include "stdafx.h"
#include "sys.h"

class CTime
{
private:
	//Variables necesarias para el calculo de tiempo entre frames
	_int64 m_previousCount;
	LARGE_INTEGER m_previousCountLarge;
	LARGE_INTEGER m_currentCount;
	LARGE_INTEGER m_frequency;

	double m_fixedTick;
	double m_previousTime = 0.f;
	double m_refreshTime = 0.f;
	double m_elapsedTime = 0.f;

	double m_deltaTimeRatio = 1.; //Cambiar esto para alterar la velocidad de las pelotas

	double GetTime();

	const float ELAPSED_TIME_MAX = 1.f / 15.f;

public: 

	CTime() {}
	void InitTime();
	void UpdateTime();
	bool ProcessSlots();
	void LogicWorldSlot();

	double DeltaTime() { return m_elapsedTime * m_deltaTimeRatio; }
	double GetRefreshTime() { return m_refreshTime; }
};