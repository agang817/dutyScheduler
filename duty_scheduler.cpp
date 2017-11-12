/********************************************************************************************
*
*	duty_scheduler.cpp
*		created on: 11/11/18
*		    Author: Alyssa Gang
*	   Description: DutyScheduler class methods
*
********************************************************************************************/
#include "duty_scheduler.h"

using namespace std;

DutyScheduler::DutyScheduler(string fileName, date start, date end){
	//Initiallize the duty scheduler
	//Inputs:
	//	@param fileName - Name of the file containing RA staff preferences
	//	@param start - Date of the first day of duty to be scheduled
	//	@param end - Date of the last day of duty to be scheduled 

	initStaff(fileName);
	initCalendar(start, end);
	setRAPointSplit();
}

void DutyScheduler::initStaff(string fileName){ 
	//Initiallize the staff list
	//Inputs:
	//	@param fileName - Name of the file containing RA staff preferences
 
	string temp;
	string tempName;
	char c;
	int tempPref[7];
	ResidentAssistant tempRA;

	ifstream fin;
	fin.open(fileName.c_str());
	if (!fin){
		cout<< "Error: cannot open file " << fileName << "\n";
		exit(1);
	}

	while(fin>>temp){ //While there is more to read from the file
		if (temp!=":"){ //Read in RA name
			tempName = temp;
		}
		else{ //Read in RA preferences
			for (int i=0;i<7;i++){
				fin>>tempPref[i];
			}

			//Add to the staff list once all preferences have been read
			tempRA.initRA(tempName, tempPref);
			staffList.push_back(tempRA);
		}
	}

	staffSize = staffList.size(); //Save the size of the staff to access later

	//Add all RAs to the list of RAs still eligible for selecting duty
	for (int i=0;i<staffSize;i++){
		stillSelecting.push_back(i);
	}
}

void DutyScheduler::setRAPointSplit(){
	//Calculate and assign the amount of duty points each RA must fulfill
	//The points for the semester may not divide evenly among RAs
	//Thus, part of the staff will have n points of duty and the other part will have n+1 points of duty
	
	int pts, amt;
	int total = calcTotalPts();
	pts = total/staffSize;
	amt = total - (pts*staffSize); // The amount of the staff that will need n+1 points

	for (int i=0;i<staffSize;i++){
		if (i<amt){staffList[i].setGoalPts(pts+1);}
		else{staffList[i].setGoalPts(pts);}
	}
}

void DutyScheduler::calcRAWeights(date day, int weekDay){
	//Calculate RA selection weights
	//Inputs:
	//	@param date - The calendar date that duty is being scheduled for
	//	@param weekDay - Day of the week corresponding to the date

	int numRAsLeft = stillSelecting.size();
	calcPrevDate(day);
	date prev = {prevDate[0], prevDate[1]};
	for (int i=0; i<numRAsLeft; i++){
		int staffID = stillSelecting[i];
		int recentDuty = 0;

		//If the RA was on duty the night before, increase their weight to lean more towards not being on duty again tonight
		if (getRAonDuty(prev) == staffList[staffID].getName()){recentDuty = 999999;}

		//Calculate the selection weight for each RA
		RAWeights[staffID] = staffList[staffID].calcSelectionWeight(weekDay, recentDuty);
		if (staffList[staffID].getPref(weekDay) == 0){RAWeights[staffID] = 9999;} //A 0 preference means that the RA cannot be on duty on the given night
	}
}

int DutyScheduler::findMinWeight(int weekDay){
	//Identify the RA with the lowest weight or most available for that duty date
	//Inputs:
	//	@param weekDay - Day of the week for the duty date in question

	float minWeight = 99999;
	int index = 0;

	for (int i=0; i<staffSize; i++){
		if (RAWeights[i]<minWeight){  //If a new minimum was found
			index = i;
			minWeight = RAWeights[i];
		}
		else if(RAWeights[i]==minWeight){  //If 2 RAs have the same weight as the minimum
			if(staffList[i].getCurrentPts()<staffList[index].getCurrentPts()){index = i;}  //Select the RA with less duty scheduled
			else if(staffList[i].getPref(weekDay)<staffList[index].getPref(weekDay)){index = i;}  //Select the RA that prefers the weekday more
		}
	}
	return index;
}

void DutyScheduler::scheduleDuty(date day){
	//Recursive method used to schedule duty
	//Inputs:
	//	@param day - Date of interest for scheduling duty

	if (!((day[0]==endDate[0])&&(day[1]>endDate[1]))){ //Check that the end date has not been reached yet
		int weekDay = checkDayOfWeek(day);
		calcRAWeights(day, weekDay);

		//Select the RA with the lowest weight (best availability) to be on duty
		int staffID = findMinWeight(weekDay);
		setRAonDuty(staffList[staffID].getName(), day);
		
		//Update RA and scheduler point counts
		staffList[staffID].incCurrentPts(1);
		staffList[staffID].incSelectionScore(staffList[staffID].getPref(weekDay));
		setCurrentPts(currentPts + 1);

		//Print the date, day of week and name of the RA on duty
		cout<<day[0]<<"/"<<day[1]<<": "<<dayOfWeek[weekDay-1]<<": "<<staffList[staffID].getName()<<endl;

		if (staffList[staffID].isDone()){ //Check if the RA is done selecting
			//Remove from being able to be selected for duty
			RAWeights[staffID] = 9999;
			stillSelecting.erase(remove(stillSelecting.begin(), stillSelecting.end(), staffID));
		}

		//Check that there are still points to schedule and RAs to select duty
		if((currentPts == getTotalPts())||(stillSelecting.size()==0)){return;}
		
		calcNextDate(day);
		date next = {nextDate[0], nextDate[1]};
		scheduleDuty(next); //Schedule the next day of duty
	}
	return;  //Once the end date has been reached
}

void DutyScheduler::generateDutySchedule(){
	//Generate the schedule for duty between the given dates for the staff
	cout<<"Duty Schedule:\n";
	setCurrentPts(0);
	scheduleDuty(startDate);

	//Print the number of points that were scheduled for each day
	cout<<"\nPoints scheduled for each RA:\n";
	for (int i=0;i<staffSize;i++){
		cout<<staffList[i].getName()<<": "<<staffList[i].getCurrentPts()<<endl;
	}
}