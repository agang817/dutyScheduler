/********************************************************************************************
*
*	resident_assistant.cpp
*		created on: 11/11/18
*		    Author: Alyssa Gang
*	   Description: Resident Assistant class methods
*
********************************************************************************************/
#include "resident_assistant.h"

using namespace std;

ResidentAssistant::ResidentAssistant(){}

void ResidentAssistant::initRA(string name, int prefs[]){
	//Initialize the RA
	//Inputs:
	//	@param name - Name of the RA
	//	@param prefs - array of preferences (ranked 0-7)for each day of the week
	
	RAname = name;

	for (int i=0; i<7; i++){
		preferences[i] = prefs[i];
	}
}

float ResidentAssistant::calcSelectionWeight(int weekDay, int recent){
	//Calculate selection weight or how available for duty the RA is for a given day
	//Inputs:
	//	@param weekDay - day of the week
	//	@param recent - Value corresponding to if the RA was on duty recently (higher the closer the RA's last duty was)

	float w;
	w = (weightConsts[0]*preferences[weekDay])+(weightConsts[1]*selectionScore)+(weightConsts[2]*currentPoints)+(weightConsts[3]*recent);
	return w;
}

bool ResidentAssistant::isDone(){
	//Check if the RA is done selecting duty (point goal was reached)
	//Return true if done, false if not
	
	if (currentPoints==pointGoal){return true;}
	return false;
}