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

void DutyScheduler::calcRAWeights(date day){
	int weekDay = checkDayOfWeek(day);
	int numRAsLeft = stillSelecting.size();
	int recentDuty = 0;
	for (int i=0; i<numRAsLeft; i++){
		int staffID = stillSelecting[i];
		if (getRAonDuty(day) == staffList[staffID].RAname){recent = 100;}
		RAWeights[staffID] = staffList[staffID].calcSelectionWeight(weekDay, recent);
	}
}

void DutyScheduler::generateDutySchedule(){
	
}