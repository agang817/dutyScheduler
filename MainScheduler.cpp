#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "resident_assistant.h"
#include "duty_calendar.h"
#include "duty_scheduler.h"

using namespace std;

int main(){
	int pref_array[] = {1,2,3,4,5,6,7};
	int testStart[] = {9,2};
	int testEnd[] = {12,16};
	int checkDate[] = {10,10};
	string staff_info = "test_staff.txt";
	// string testName = "John";
	// ResidentAssistant testing;
	// testing.initRA(testName, pref_array);
	// DutyCalendar testCal;
	// testCal.initCalendar(testStart,testEnd);
	// testCal.setRAonDuty(testName, testStart);
	// testCal.getRAonDuty(testStart);
	DutyScheduler test_scheduler(staff_info, testStart, testEnd);
	test_scheduler.generateDutySchedule();
	//cout<<test_scheduler.checkDayOfWeek(testStart)<<endl;
	//test_scheduler.initStaff(staff_info);

	//int testCalc;
	//testCalc = 85/18;
	//cout<<testCalc<<endl;

	return 0;
}