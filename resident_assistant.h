/********************************************************************************************
*
*	resident_assistant.h
*		created on: 11/11/18
*		    Author: Alyssa Gang
*	   Description: ResidentAssistant class definition, holds and maintains information
*		            about a staff members duty scheduling preferences
*
********************************************************************************************/

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

	void incCurrentPts(int pts){currentPoints = currentPoints + pts;}
	int getCurrentPts(){return currentPoints;}

	void incSelectionScore(int score){selectionScore = selectionScore + score;}
	int getSelectionScore(){return selectionScore;}

	int getPref(int weekDay){if (weekDay >= 0 && weekDay <= 7){return preferences[weekDay];}}
	void setPref(int weekDay, int pref){if (weekDay >= 0 && weekDay <= 7){preferences[weekDay] = pref;}}

private:
	string RAname;
	int preferences[7] = {0};
	
	int pointGoal; //Points of duty the RA must fulfill
	int currentPoints = 0; //Points of duty the RA is currently scheduled for
	int selectionScore = 0; //Sum of the preference value fo each duty date scheduled

	//Constants used in the RA weight calculations
	//Order is {preferences, currentScore, currentPts, recentDuty}
	//Weights were selected to put the highest emphasis on RA preferences
	float weightConsts[4] = {0.7, 0.1, 0.1, 0.1};
};

#endif