#ifndef SetOfStrings_SetOfStrings_h
#define SetOfStrings_SetOfStrings_h
#include <iostream>
#include <iostream>
#include <vector>
#include <cstring>
#include <stdio.h>

using namespace std;
enum COLOUR {RED=0, BLUE, GREEN, WHITE, YELLOW};

class SetOfStrings{
protected:
    vector<string> setv;
    vector<string>::iterator p;
	vector<string>::iterator k;
	vector<string>::iterator r;
public:

	// Set calculation (Students need to complete this section)
	SetOfStrings *setUnion(SetOfStrings *set1);
	SetOfStrings *setIntersection(SetOfStrings *set1);
	SetOfStrings *product(SetOfStrings *set1);
	
	// Utility methods
    bool isEmpty();
    bool isEqual(SetOfStrings *s);
    bool isMember(string s);
	bool subset(SetOfStrings *s);
	int size();
	
	// Insert and remove
    void insertElement(string s);
    void removeElement(string s); 
    
	// Getter
    string returnElement(int index);
    //helper
	string ColourText(string s, COLOUR c);
	//view
    void print();
};

#endif


