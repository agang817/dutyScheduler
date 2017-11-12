#include "duty_calendar.h"

using namespace std;

DutyCalendar::DutyCalendar(){};

void DutyCalendar::initCalendar(date start, date end){
	vector<string> tempMonth;
	startDate[0] = start[0];
	startDate[1] = start[1];
	endDate[0] = end[0];
	endDate[1] = end[1];

	for (int i=0; i<12; i++){
		tempMonth.resize(monthLength[i]);
		duty_cal.push_back(tempMonth);
	}
}

int DutyCalendar::calcTotalPts(){
	int pts = 0;
	for (int i=startDate[0]; i<=endDate[0]; i++){
		if (i==startDate[0]){pts = monthLength[i-1]-startDate[1];}
		else if (i==endDate[0]){pts = pts + endDate[1];}
		else{pts = pts + monthLength[i-1];}
	}
	totalPts = pts + 1;
	return totalPts;
}

void DutyCalendar::setRAonDuty(string name, date duty){duty_cal[duty[0]-1][duty[1]-1] = name;}
string DutyCalendar::getRAonDuty(date duty){return duty_cal[duty[0]-1][duty[1]-1];}

int DutyCalendar::checkDayOfWeek(date day){
	//Return the day of week code for the input date
	//Value from 1-7 corresponding to Sunday-Saturday
	int dayOfWeek = 0;
	for (int i=0; i<day[0]-1; i++){
		dayOfWeek = dayOfWeek + monthLength[i];
	}
	dayOfWeek = (dayOfWeek + day[1])%7;
	if (dayOfWeek == 0){dayOfWeek=7;}
	return dayOfWeek;
}

void DutyCalendar::calcPrevDate(date day){
	if (day[1]==1){
		prevDate[0] = day[0]-1;
		prevDate[1] = monthLength[day[0]-2];
	}
	else{
		prevDate[0] = day[0];
		prevDate[1] = day[1]-1;
	}
}

void DutyCalendar::calcNextDate(date day){
	if (day[1]>=monthLength[day[0]-1]){
		nextDate[0] = day[0]+1; 
		nextDate[1] = 1;
	}
	else{
		nextDate[0] = day[0];
		nextDate[1] = day[1]+1;
	}
}