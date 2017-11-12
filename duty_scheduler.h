#ifndef DUTYSCHEDULER_H
#define DUTYSCHEDULER_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "duty_calendar.h"
#include "resident_assistant.h"

using namespace std;

class DutyScheduler: public DutyCalendar{
public:
	DutyScheduler(string filename, date start, date end);
	void initStaff(string filename);
	void setRAPointSplit();
	void calcRAWeights(date day);

private:
	vector<ResidentAssistant> staffList;
	vector<int> stillSelecting;

	//Constants used in the RA weight calculations
	//Order is {preferences, currentScore, currentPts, recentDuty}
	//Weights were selected to put the highest emphasis on RA preferences
	float weightConsts[4] = {0.7, 0.1, 0.1, 0.1};
	float RAWeights[25] = {9999}; //Set all weights to a large value to star 
	int staffSize;
};


#endif