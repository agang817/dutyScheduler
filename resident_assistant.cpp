#include "resident_assistant.h"

using namespace std;

ResidentAssistant::ResidentAssistant(){}

void ResidentAssistant::initRA(string name, int prefs[]){
	RAname = name;

	for (int i=0; i<7; i++){
		preferences[i] = prefs[i];
	}
}

float ResidentAssistant::calcSelectionWeight(int weekDay, int recent){
	float w;
	w = (weightConsts[0]*preferences[weekDay])+(weightConsts[1]*selectionScore)+(weightConsts[2]*currentPoints)+(weightConsts[3]*recent);
	return w;
}

bool ResidentAssistant::isDone(){
	if (currentPoints==pointGoal){return true;}
	return false;
}