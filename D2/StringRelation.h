#ifndef STRINGRELATION_H_
#define STRINGRELATION_H_
#include "SetOfStrings.h"
#include <vector>
#include <algorithm>

class StringRelation : public SetOfStrings{
	private:
		// the set over which the relation is created
		SetOfStrings *set1;
		string path; // string for dijkstra's path
    
		// String splitter, which is a helper function
		vector<string> makeTokens(string input);
		//given string "a,b" return string "b,a"
		string computeDual(string);
		//given "a", returns "a,a"
		string createReflexiveElement(string s);
		//return true if s is of the form "a,a"
		bool isReflexiveElement(string s);
		//return true if s1 is the first component of s2
		//e.g. s1=a and s2=a,b
		bool isFirstComponent(string s1, string s2);
		//Return the second component of the string "a,b" as b
		string returnSecondComponent(string s);
		//This function converts the product of set1 with itself passed as "s" into
		//A relation called "n". This is so that we can print the elements of the
		
		// Return the weight of an edge
		int getWeight(string s);
		vector<int> weight; // weight vector
		
	public:
		string getPath();
		int minIndex(vector<int> dist, SetOfStrings* Q);
		void addWeight(int w);
		vector<int> getWeightVector();
		int returnIndex(string s);
		int minDist(SetOfStrings *Q,string prevU);
		bool recursive(string src, string dst, SetOfStrings* visited, bool found);
		bool isReachable(string src, string dst, SetOfStrings* visited, bool found);
		//bool isReachable(string src, string dst);
		void setInput(SetOfStrings *s);
		//creates a relation that is identical to the product set of set1
		bool isValid();
		bool isReflexive();
		bool isSymmetric();
		bool isTransitive();
		bool isEquivalence();
		SetOfStrings *returnNeighbours(string element);
		SetOfStrings *computeEquivalenceClass(string element);
		
		// Finding the shortest path
		int computeShortest(string source, string destination);
		~StringRelation();

};
#endif
