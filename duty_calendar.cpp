#include "duty_calendar.h"

using namespace std;

DutyCalendar::DutyCalendar(){};

void DutyCalendar::initCalendar(date start, date end){
	vector<string> tempMonth;
	startDate[0] = start[0];
	startDate[1] = start[1];
	endDate[0] = end[0];
	endDate[1] = end[1];

	for (int i=start[0]; i<=end[0]; i++){
		tempMonth.resize(monthLength[i-1]);
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
	totalPts = pts;
	return totalPts;
}

void DutyCalendar::setRAonDuty(string name, date duty){
	int monthIndex = duty[0] - startDate[0];
	duty_cal[monthIndex][duty[1]] = name;
}

string DutyCalendar::getRAonDuty(date duty){
	int monthIndex = duty[0] - startDate[0];
	cout<< duty_cal[monthIndex][duty[1]];
	return duty_cal[monthIndex][duty[1]];
}