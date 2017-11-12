/********************************************************************************************
*
*	duty_calendar.cpp
*		created on: 11/11/18
*		    Author: Alyssa Gang
*	   Description: DutyCalendar class methods
*
********************************************************************************************/
#include "duty_calendar.h"

using namespace std;

DutyCalendar::DutyCalendar(){};

void DutyCalendar::initCalendar(date start, date end){
	//Initiallize the calendar and store the start and end dates
	//Inputs:
	//	@param start - Date of the first day of duty to be scheduled
	//	@param end - Date of the last day of duty to be scheduled 
	
	vector<string> tempMonth;
	startDate[0] = start[0];
	startDate[1] = start[1];
	endDate[0] = end[0];
	endDate[1] = end[1];

	for (int i=0; i<12; i++){
		tempMonth.resize(monthLength[i]); //Set the length of the month
		duty_cal.push_back(tempMonth);
	}
}

int DutyCalendar::calcTotalPts(){
	//Calculate the total amount of duty points to be scheduled

	int pts = 0;
	for (int i=startDate[0]; i<=endDate[0]; i++){ //For each month
		if (i==startDate[0]){pts = monthLength[i-1]-startDate[1];} //For the start month, subtract the days before the start date
		else if (i==endDate[0]){pts = pts + endDate[1];} //for the last month, add the number of days to the end date
		else{pts = pts + monthLength[i-1];} //For months in between, add the number of days in the month
	}
	totalPts = pts + 1; //Add 1 point lost when subtracting in the first month
	return totalPts;
}

//Functions to set and get who the RA on duty for a given date is
void DutyCalendar::setRAonDuty(string name, date duty){duty_cal[duty[0]-1][duty[1]-1] = name;}
string DutyCalendar::getRAonDuty(date duty){return duty_cal[duty[0]-1][duty[1]-1];}

int DutyCalendar::checkDayOfWeek(date day){
	//Return the day of the week of a given date
	//Value from 1-7 corresponding to Sunday-Saturday
	//Inputs:
	//	@param day - calendar date

	int dayOfWeek = 0;
	for (int i=0; i<day[0]-1; i++){
		dayOfWeek = dayOfWeek + monthLength[i];
	}
	dayOfWeek = (dayOfWeek + day[1])%7;
	if (dayOfWeek == 0){dayOfWeek=7;}
	return dayOfWeek;
}

void DutyCalendar::calcPrevDate(date day){
	//Determine the date immediately before the given date
	//Inputs:
	//	@param day - calendar date

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
	//Determine the date immediately after the given date
	//Inputs:
	//	@param day - calendar date

	if (day[1]>=monthLength[day[0]-1]){
		nextDate[0] = day[0]+1; 
		nextDate[1] = 1;
	}
	else{
		nextDate[0] = day[0];
		nextDate[1] = day[1]+1;
	}
}