#pragma once
#ifndef RESIDENTASISTANT_H
#define RESIDENTASSISTANT_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class ResidentAssistant{
//Stores and maintains information regarding an RA's availability and preferences
public:
	ResidentAssistant();
	void initRA(string name, int prefs[]);

	float calcSelectionWeight(int weekDay, int recent);
	bool isDone();

	void setName(string name){RAname = name;}
	string getName(){return RAname;}

	void setGoalPts(int pts){pointGoal = pts;}
	int getGoalPts(){return pointGoal;}

	void setCurrentPts(int pts){currentPoints = currentPoints + pts;}
	int getCurrentPts(){return currentPoints;}

	void incSelectionScore(int score){selectionScore = selectionScore + score;}
	int getSelectionScore(){return selectionScore;}

	int getPref(int weekDay){if (weekDay >= 0 && weekDay <= 7){return preferences[weekDay];}}
	void setPref(int weekDay, int pref){if (weekDay >= 0 && weekDay <= 7){preferences[weekDay] = pref;}}

private:
	string RAname;
	int preferences[7] = {0};
	int pointGoal;
	int currentPoints = 0;
	int selectionScore = 0;

	//Constants used in the RA weight calculations
	//Order is {preferences, currentScore, currentPts, recentDuty}
	//Weights were selected to put the highest emphasis on RA preferences
	float weightConsts[4] = {0.7, 0.1, 0.1, 0.1};
};

#endif