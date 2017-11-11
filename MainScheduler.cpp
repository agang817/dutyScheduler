#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "resident_assistant.h"
#include "duty_calendar.h"

using namespace std;

int main(){
	int pref_array[] = {1,2,3,4,5,6,7};
	int testStart[] = {9,2};
	int testEnd[] = {12,16};
	string testName = "John";
	ResidentAssistant testing;
	testing.initRA(testName, pref_array);
	DutyCalendar testCal;
	testCal.initCalendar(testStart,testEnd);
	testCal.setRAonDuty(testName, testStart);
	testCal.getRAonDuty(testStart);

	return 0;
}