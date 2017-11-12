#include "duty_scheduler.h"

using namespace std;

DutyScheduler::DutyScheduler(string fileName, date start, date end){
	initStaff(fileName);
	initCalendar(start, end);
	setRAPointSplit();
}

void DutyScheduler::initStaff(string fileName){ //initiallize the RAs on staff and their preferences
	string temp;
	string tempName;
	char c;
	int tempPref[7];
	ResidentAssistant tempRA;
	string seperator = ":"; //Seperator between names and preferences in the txt file

	ifstream fin;
	fin.open(fileName.c_str());
	if (!fin){
		cout<< "Error: cannot open file " << fileName << "\n";
		exit(1);
	}

	while(fin>>temp){ //While there is more to read from the file
		if (temp!=seperator){ //Read in RA name
			tempName = temp;
		}
		else if (temp == seperator){ //Read in RA preferences
			for (int i=0;i<7;i++){
				fin>>tempPref[i];
			}
			//Add to the staff list
			tempRA.initRA(tempName, tempPref);
			staffList.push_back(tempRA);
		}
	}

	staffSize = staffList.size();

	//Add all RAs to the list of RAs still eligible for selecting duty
	for (int i=0;i<staffSize;i++){
		stillSelecting.push_back(i);
	}
}

void DutyScheduler::setRAPointSplit(){
	//The points for the semester may not divide evenly among RAs
	//Thus, part of the staff will have n points of duty and the other part will have n+1 points of duty
	int pts, amt;
	int total = calcTotalPts();
	pts = total/staffSize;
	amt = total - (pts*staffSize); // The amount of the staff that will 

	for (int i=0;i<staffSize;i++){
		if (i<amt){staffList[i].setGoalPts(pts+1);}
		else{staffList[i].setGoalPts(pts);}
	}
}

void DutyScheduler::calcRAWeights(date day, int weekDay){
	int numRAsLeft = stillSelecting.size();
	calcPrevDate(day);
	date prev = {getPrevMonth(), getPrevDay()};
	for (int i=0; i<numRAsLeft; i++){
		int staffID = stillSelecting[i];
		int recentDuty = 0;
		if (getRAonDuty(prev) == staffList[staffID].getName()){recentDuty = 999999;} //Check if the RA was scheduled for duty the night before
		RAWeights[staffID] = staffList[staffID].calcSelectionWeight(weekDay, recentDuty);
		if (staffList[staffID].getPref(weekDay) == 0){RAWeights[staffID] = 9999;}
	}
}

int DutyScheduler::findMinWeight(int weekDay){
	float minWeight = 99999;
	int index = 0;

	for (int i=0; i<staffSize; i++){
		if (RAWeights[i]<minWeight){
			index = i;
			minWeight = RAWeights[i];
		}
		else if(RAWeights[i]==minWeight){
			if(staffList[i].getCurrentPts()<staffList[index].getCurrentPts()){index = i;}
			else if(staffList[i].getPref(weekDay)<staffList[index].getPref(weekDay)){index = i;}
		}
	}
	return index;
}

void DutyScheduler::scheduleDuty(date day){
	int endMonth = getEndMonth();
	int endDay = getEndDay();
	if (!((day[0]==endMonth)&&(day[1]>endDay))){
		int staffID = 0;

		int weekDay = checkDayOfWeek(day);
		calcRAWeights(day, weekDay);

		staffID = findMinWeight(weekDay);
		setRAonDuty(staffList[staffID].getName(), day);
		
		staffList[staffID].setCurrentPts(1);
		staffList[staffID].incSelectionScore(staffList[staffID].getPref(weekDay));
		int pointsScheduled = getCurrentPts() + 1;
		setCurrentPts(pointsScheduled);

		cout<<day[0]<<"/"<<day[1]<<": "<<dayOfWeek[weekDay-1]<<": "<<staffList[staffID].getName()<<endl;

		if (staffList[staffID].isDone()){
			RAWeights[staffID] = 9999;
			stillSelecting.erase(remove(stillSelecting.begin(), stillSelecting.end(), staffID));
		}

		if((pointsScheduled == getTotalPts())||stillSelecting.size()==0){return;}
		calcNextDate(day);
		date next = {getNextMonth(), getNextDay()};
		scheduleDuty(next);
	}
	return;
}

void DutyScheduler::generateDutySchedule(){
	cout<<"Duty Schedule:\n";
	setCurrentPts(0);
	date start = {getStartMonth(), getStartDay()};
	scheduleDuty(start);

	cout<<"\nPoints scheduled for each RA:\n";
	for (int i=0;i<staffSize;i++){
		cout<<staffList[i].getName()<<": "<<staffList[i].getCurrentPts()<<endl;
	}
}