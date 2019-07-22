#include "SetOfStrings.h"

using namespace std; 

bool SetOfStrings::isEmpty()
{
    if(setv.empty()) return true;
    else return false;
}
        
int SetOfStrings::size(){
    return (int) setv.size();
}

bool SetOfStrings::isMember(string s)
{
    p=setv.begin();
    while(p!=setv.end()){
        if(*p==s)return true;
        ++p;
    }
    return false;
}

void SetOfStrings::insertElement(string s)
{
    if(!isMember(s)){
        setv.push_back(s);
    }
}

string SetOfStrings::ColourText(string s, COLOUR c)
{
	string temp;
	switch (c) {
		case RED: temp = "\033[1;31m" + s + "\033[0m"; break;
		case BLUE: temp = "\033[1;34m" + s + "\033[0m"; break;
		case YELLOW: temp = "\033[1;33m" + s + "\033[0m"; break;
		case GREEN: temp = "\033[1;32m" + s + "\033[0m"; break;
		case WHITE: temp = "\033[1;37m" + s + "\033[0m"; break;
		default: temp = "\033[0m" + s; break;
	}
	return temp;
}
void SetOfStrings::print()
{
   //You have implemented this in the lab
   cout <<"The elements are {";
   p=setv.begin();
   for (p; p<setv.end();p++){
       cout << *p << " ";
   }
   cout <<"}\n";
}

void SetOfStrings::removeElement(string s)
{
    //You have implemented this in the lab
    if(isMember(s)){
         for(int i=0; i<setv.size();i++){
            if(setv[i]==s){
                setv.erase(setv.begin() + i);
            }
        }
    }

}

SetOfStrings *SetOfStrings::setUnion(SetOfStrings *s)
{
    //You have implemented this in the lab

    SetOfStrings *out = new SetOfStrings();
    //Add every element of setv to s1
    p = setv.begin();
    for(p; p!=setv.end(); p++){ 
       out->insertElement(*p);
    }
    // Add every element of s to s1
    k = (s->setv).begin();
    for(k; k!=(s->setv).end(); k++){ 
      if(!(isMember(*k))){
        out->insertElement(*k);
      }
    }
    
    return out;
}

bool SetOfStrings::isEqual(SetOfStrings *s)
{
	//You have implemented this in the lab
    int count = 0;
    //
	p = setv.begin();
    for(p; p!=setv.end(); p++){
       if(!(s->isMember(*p))){
           return false;
        }
        count++; // Keep of how many elements are the same
    }
    if(count==setv.size()){ //Of it is a subset and has same number of elements return true
       return true;
       }

    return false;
}

string SetOfStrings::returnElement(int index)
{
	int i=0;
	if(index > size()) return "\n";
    p=setv.begin();
    while(p!=setv.end()){
       if(i==index)
    	   return  *p;
       else
       	   {
    	   	   ++i;
    	   	   ++p;
       	   }
    }
    return "\n";
}

SetOfStrings *SetOfStrings::product(SetOfStrings *s)
{
	//You are required to implement this
    SetOfStrings *out = new SetOfStrings();
    // Cycle through each element of setv and s
    for(int i = 0;i<setv.size();i++){
        for(int j = 0;j<(s->setv).size();j++){
            // Create an element made up from an element from setv and s
            string element = setv[i] + "," + (s->setv)[j];
            out->insertElement(element); // Addi this element to out
        }
    }
    return out;
}

bool SetOfStrings::subset(SetOfStrings *s)
{
    // Cycle through each element and make sure they are a memeber of current set
   for(int i =0; i<s->size();i++){
       if(!(isMember(s->returnElement(i)))){
           return false;
       }
   }
    return true;
}
