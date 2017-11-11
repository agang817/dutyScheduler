#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "resident_assistant.h"

using namespace std;

int main(){
	//cout<<"Hello!";
	int pref_array[] = {1,2,3,4,5,6,7};
	string testName = "John";
	ResidentAssistant testing;
	testing.initRA(testName, pref_array);
	//testing.printName();
	//cout << "Hello!";
	return 0;
}