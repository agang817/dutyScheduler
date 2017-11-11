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
		void setName(string name);
		string getName();
		void setGoalPts(int pts);
		int getGoalPts();
		void setCurrentPts(int pts);
		int getCurrentPts();
		void setSelectionScore(int score);
		int getSelectionScore();
		int getPref(int weekDay);
		void setPref(int weekDay, int pref);

	private:
		string RAname;
		int preferences[7] = {0};
		int pointGoal;
		int currentPoints = 0;
		int selectionScore = 0;
};

#endif