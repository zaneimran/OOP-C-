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
	p = setv.begin();
    for(p; p!=setv.end(); p++){
       if(!(s->isMember(*p))){
           count++;
           return false;
       }
   }
   if(count==setv.size()){
       return true;
   }
    return false;
}

string SetOfStrings::returnElement(int index)
{
	if (index < (int)setv.size() && index >= 0)
		return setv.at(index);
	else
		return "\n";
}

SetOfStrings *SetOfStrings::product(SetOfStrings *s)
{
	//You are required to implement this as this
	SetOfStrings *out = new SetOfStrings();

	for(int i = 0;i<setv.size();i++){
        for(int j = 0;j<(s->setv).size();j++){
            string element = setv[i] + "," + (s->setv)[j];
            out->insertElement(element);
        }
    }
	return out;
}   

bool SetOfStrings::subset(SetOfStrings *s)
{
	//You are required to implement this as this
   for(int i =0; i<s->size();i++){
       if(!(isMember(s->returnElement(i)))){
           return false;
       }
   }
    return true;
}

void SetOfStrings::print()
{
   //You have implemented this in the lab
   cout <<"{";
   p=setv.begin();
   for (p; p<setv.end();p++){
       cout << *p << " ";
   }
   cout <<"}\n";
}

SetOfStrings::~SetOfStrings(){
}