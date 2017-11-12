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
	int getEndMonth(){return endDate[0];};
	int getEndDay(){return endDate[1];};
	int getStartMonth(){return startDate[0];};
	int getStartDay(){return startDate[1];};
	void calcPrevDate(date day);
	void calcNextDate(date day);
	int getPrevMonth(){return prevDate[0];};
	int getPrevDay(){return prevDate[1];};
	int getNextMonth(){return nextDate[0];};
	int getNextDay(){return nextDate[1];};

private:
	const int monthLength[12] = {31,28,31,30,31,30,31,31,30,31,30,31}; //List of the number of days in each month
	const int yearStart = 1; //Value from 1-7 corresponding to the first day of the week of the year (1=Sunday, 7=Saturday)
	vector<vector<string> > duty_cal;
	int totalPts;
	int currentPts = 0;
	date startDate = {1, 1};
	date endDate = {12, 31};
	date prevDate;
	date nextDate;
};

#endif