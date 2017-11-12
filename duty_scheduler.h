/********************************************************************************************
*
*	duty_scheduler.h
*		created on: 11/11/18
*		    Author: Alyssa Gang
*	   Description: DutyScheduler class definition, Manages and performs the scheduling of
*                   duty for RAs on the duty calendar
*
********************************************************************************************/
#pragma once
#ifndef DUTYSCHEDULER_H
#define DUTYSCHEDULER_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "duty_calendar.h"
#include "resident_assistant.h"
#include <algorithm>

using namespace std;

class DutyScheduler: public DutyCalendar{
public:
	DutyScheduler(string filename, date start, date end);
	void initStaff(string filename);
	void setRAPointSplit();
	void calcRAWeights(date day, int weekDay);
	void generateDutySchedule();
	void scheduleDuty(date day);
	int findMinWeight(int weekDay);

private:
	vector<ResidentAssistant> staffList;
	vector<int> stillSelecting;  //List of IDs (indexes in staffList) for RAs that are still selecting duty
	float RAWeights[25] = {9999}; //Set all weights to a large value to star 
	int staffSize;
};


#endif