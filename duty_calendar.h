#ifndef DUTYCALENDAR_H
#define DUTYCALENDAR_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

typedef string RAonDuty;
typedef int date[2];

class DutyCalendar{
public:
	DutyCalendar();
	void initCalendar(date start, date end);
	int calcTotalPts();
	int getTotalPts(){return totalPts;};
	void setPtsLeft(int pts){ptsLeft = pts;}
	int getPtsLeft(){return ptsLeft;}
	void setRAonDuty(string name, date duty);
	string getRAonDuty(date duty);

private:
	int monthLength[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	int yearStart = 1;
	vector<vector<string> > duty_cal;
	int totalPts;
	int ptsLeft;
	date startDate = {1, 1};
	date endDate = {12, 31};
};

#endif