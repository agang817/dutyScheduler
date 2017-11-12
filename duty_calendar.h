/********************************************************************************************
*
*	duty_calendar.h
*		created on: 11/11/18
*		    Author: Alyssa Gang
*	   Description: DutyCalendar class definition, Maintains the calendar where the schedule
*                   of duty is created
*
********************************************************************************************/
#pragma once
#ifndef DUTYCALENDAR_H
#define DUTYCALENDAR_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

typedef int date[2];
const string dayOfWeek[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

class DutyCalendar{
public:
	DutyCalendar();
	void initCalendar(date start, date end);

	int calcTotalPts();
	int getTotalPts(){return totalPts;};

	int getCurrentPts(){return currentPts;};
	void setCurrentPts(int pts){currentPts = pts;};
	
	void setRAonDuty(string name, date duty);
	string getRAonDuty(date duty);
	
	int checkDayOfWeek(date day);
	
	void calcPrevDate(date day);
	void calcNextDate(date day);

private:
	vector<vector<string> > duty_cal;

protected:
	const int monthLength[12] = {31,28,31,30,31,30,31,31,30,31,30,31}; //List of the number of days in each month
	const int yearStart = 1; //Value from 1-7 corresponding to the first day of the week of the year (1=Sunday, 7=Saturday)
	int totalPts; //Total points of duty to be split between RAs
	int currentPts = 0; //Total points of duty currently scheduled
	date startDate = {1, 1};
	date endDate = {12, 31};
	date prevDate;
	date nextDate;
};

#endif