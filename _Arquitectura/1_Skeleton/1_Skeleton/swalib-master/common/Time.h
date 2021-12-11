#pragma once

#include "stdafx.h"
#include "sys.h"

class CTime
{
private:
	//Variables needed to calculate time between frames
	_int64 m_previousCount;
	LARGE_INTEGER m_previousCountLarge;
	LARGE_INTEGER m_currentCount;
	LARGE_INTEGER m_frequency;

	double m_fixedTick; //Time taken up buy logic (limited to 60fps)
	double m_previousTime = 0.f; //Variable needed to calculate elapsed time. Time of previous frame
	double m_refreshTime = 0.f; //Time of current frame
	double m_elapsedTime = 0.f; //Real time between frames

	double m_deltaTimeRatio = 1.; //Ratio which alters the elapsed time and turns it into delta Time

	double GetTime(); //Get the current Time

	const float ELAPSED_TIME_MAX = 1.f / 15.f; //Max time dedicated to logic

public: 

	CTime(){}

	void InitTime();
	void UpdateTime();

	bool ProcessSlots(); //Returns true if there is time left to do a certain action
	void TickSlot() { m_elapsedTime -= m_fixedTick; } //Reduces time after each slots

	double DeltaTime() { return m_elapsedTime * m_deltaTimeRatio; } //Returns elapsed time adjusted to game speed (m_deltaTimeRatio)
	
	double GetRefreshTime() { return m_refreshTime; }

	double GetFixedTick() { return m_fixedTick; }

	double GetElapsedTime() { return m_elapsedTime; }
	void SetElapsedTime(double const _newElapsedTime) { m_elapsedTime = _newElapsedTime; }
};