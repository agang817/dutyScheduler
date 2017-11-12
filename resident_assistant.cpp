#include "resident_assistant.h"

using namespace std;

ResidentAssistant::ResidentAssistant(){
}

void ResidentAssistant::initRA(string name, int prefs[]){
	RAname = name;

	for (int i=0; i<7; i++){
		preferences[i] = prefs[i];
	}
}

void ResidentAssistant::setName(string name){RAname = name;}
string ResidentAssistant::getName(){return RAname;}

void ResidentAssistant::setGoalPts(int pts){pointGoal = pts;}
int ResidentAssistant::getGoalPts(){return pointGoal;}

void ResidentAssistant::setCurrentPts(int pts){currentPoints = pts;}
int ResidentAssistant::getCurrentPts(){return currentPoints;}

void ResidentAssistant::setSelectionScore(int score){selectionScore = score;}
int ResidentAssistant::getSelectionScore(){return selectionScore;}

int ResidentAssistant::getPref(int weekDay){if (weekDay >= 0 && weekDay <= 7){return preferences[weekDay];}}
void ResidentAssistant::setPref(int weekDay, int pref){if (weekDay >= 0 && weekDay <= 7){preferences[weekDay] = pref;}}

float ResidentAssistant::calcSelectionWeight(int weekDay, int recent){
	float w;
	w = (weightConsts[0]*preferences[weekDay])+(weightConsts[1]*selectionScore)+(weightConsts[2]*currentPoints)+(weightConsts[3]*recent);
	return w;
}