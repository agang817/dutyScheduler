/********************************************************************************************
*
*	MainScheduler.cpp
*		created on: 11/11/18
*		    Author: Alyssa Gang
*	   Description: Main function
*
********************************************************************************************/
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
	int testStart[] = {9,2};
	int testEnd[] = {12,16};
	string staff_info = "test_staff.txt";

	//Initialize the staff and calendar
	DutyScheduler test_scheduler(staff_info, testStart, testEnd);

	//Schedule duty
	test_scheduler.generateDutySchedule();

	return 0;
}