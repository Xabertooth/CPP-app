/*Chapter 10, Exercise 1: Write a Program Calculating
the sum of all integers written in a file and separated by spaces.*/

#include "std_lib_facilities.h"
#include <fstream>

int main(){
	ifstream ist{"digit.txt"};
	if(!ist) error("Open file error!");
	vector<int> digit(0);
	int d;
	while(ist >> d) digit.push_back(d);
	ist.close();
	d=0;
	for(int i : digit) d+=i;
	cout << d;
}