#include "StringRelation.h"

//will be used for calling the ColourText() method in print() functions
SetOfStrings *S = new SetOfStrings();

//This helps by assigning the composition member
//s is the pointer to the input set
//and R \subseteq s \times s
void StringRelation::setInput(SetOfStrings *s)
{
	set1=s;
}

//check if the relation provided as input is a
//valid relation i.e., R \subseteq S \times S
//Return true when valid; false otherwise
bool StringRelation::isValid(){
	//Create the product of set1 with itself
	//out= set1 /times set1
	SetOfStrings *out = new SetOfStrings();
	out = set1->product(set1);
	//Overloaded printRelation method used for printing the relation that is
	//equal to the product set
	printRelation(out);
	//this->printRelation();
	if(out->subset(this)){
		return true;
	}
	else return false;
}

//This is one of the main helper function provided as a
//tokenizer to parse relational elements and separate them into components
//This takes a relation element in the form "a,b" and returns
//a string vector containing "a" and "b"
vector<string> StringRelation::makeTokens(string next){
	vector<string> out;
	vector<string>::iterator p;
	char *a = new char [next.length()+1];
	strcpy(a,next.c_str());
	char* token = std::strtok(a,",");
			int index=0;
				while (token != NULL) {
					//std::cout << "The next token is: "<< token << '\n';
					out.push_back(token);
					token = std::strtok(NULL, ",");
					index++;
				}
	return out;
}

void StringRelation::printRelation()
{
    cout<<"The elements of the relation are: "<<S->ColourText("{", RED);
    int i=0, j=0;
    j=size();
    while(i<j){
        string next;
        next = returnElement(i);
        if(i!=j-1){
            cout<<S->ColourText("(", RED)<<S->ColourText(next, RED)<<S->ColourText(")", RED)<<S->ColourText(", ", RED);
            //cout<<"("<<next<<")"<<", ";
            ++i;
        }
        else{
            cout<<S->ColourText("(",RED)<<S->ColourText(next, RED)<<S->ColourText(")", RED);
            //cout<<"("<<next<<")";
            ++i;
        }
    }
    //cout<<"}\n";
    cout<<S->ColourText("}", RED)<<"\n";
}

void StringRelation::printRelation(SetOfStrings *s)
{
    SetOfStrings *out = new SetOfStrings();
    out = set1->product(set1);
    if(!out->isEqual(s)){
        cout<<S->ColourText("Invalid argument -- argument must be a product set of set1", RED)<< "\n";
        return;
    }
    else{
        cout<<"The elements of the relation that is equal to the product set are:"<< S->ColourText("{", BLUE);
        int i=0, j=0;
        j=s->size();
        while(i<j){
            string next;
            next = s->returnElement(i);
            if(i!=j-1){
                cout<<S->ColourText("(", BLUE)<<S->ColourText(next, BLUE)<<S->ColourText(")", BLUE)<<S->ColourText(", ", BLUE);
                ++i;
            }
            else{
                cout<<S->ColourText("(",BLUE)<<S->ColourText(next, BLUE)<<S->ColourText(")", BLUE);
                ++i;
            }
        }
        cout<<S->ColourText("}", BLUE)<<"\n";
    }
}
void StringRelation::printEquivalenceClasses(){
    if(!isEquivalence()){
        cout<<"Not a equivalence relation"<<endl;
        cout<<"Exiting"<<endl;
        return;
    }
    int i=0;
    int j=set1->size();
    while(i<j){
        
        string next=set1->returnElement(i);
        cout<<"The next equivalence class for:"<<next<<endl;
        SetOfStrings *out = computeEquivalenceClass(next);
        cout<<"The next equivalence class is"<<endl;
        out->print();
        ++i;
    }
}


//helper function that returns the string "a,a" when input is "a"
string StringRelation::createReflexiveElement(string s){
	string next, next1;
	next = s;
	next1=next;
	next.append(",");
	next.append(next1);
	//cout<<"The reflexive element created"<<next<<endl;
	return next;
}


//helper function that creates a dual of "a,b" as "b,a"
string StringRelation::computeDual(string s){

	vector<string> tokens=makeTokens(s);
	vector<string>::iterator p;
	p=tokens.begin();
	string other, other1;
	while(p!=tokens.end()-1){
		other=*p;
		//cout<<"Other: "<< *p << "\n";
		other1=*(p+1);
		//cout<<"Other1: "<<other1<<"\n";
		other1.append(",");
		other1.append(other);
		++p;
	}
	//cout<<"Other1:"<<other1<<endl;
	return other1;
}

//return "b" if s is of the form "a,b"
string StringRelation::returnSecondComponent(string s){
    vector<string> tokens;
    vector<string>::iterator p;
    tokens=makeTokens(s);
    p=tokens.begin();
    return *(p+1);
}


//check if s is of the form "a,a" and return true if so
//return false otherwise
bool StringRelation::isReflexiveElement(string s){
    return true;
}

//check if the relation is reflexive
//if for all s \in set1, (s,s) \in r then reflexive
bool StringRelation::isReflexive(){
    //You are required to implement this
    int i,k,count;
    i = 0;
    count = 0;
    k = 0;
    if(!isValid()){return false;}

    // Cycle through each element of set1
    for(i = 0; i<set1->size(); i++){
        k = 0;
        // Check if the reflexive element for each memeber of set1 is in relation
        while(k<setv.size()){
            if(createReflexiveElement(set1->returnElement(i)) == setv[k]){
                count++;
            }
            k++;
        }
    }
    // If every element of set1 is reflexive return true
    if(count = set1->size()){
        return true;
    }
    return false;
}

//check if the relation is symmetric
//if for any s1,s2 \in set1, (s1,s2) \in R implies (s2,s1) \in R
bool StringRelation::isSymmetric(){
	//You are required to implement this 
    int count,k;
    count = 0;
    k = 0;
    if(!isValid()){return false;}
    // Cycle through each element of the relation
    for(int i = 0; i<setv.size();i++){
        k = 0;
        // Check if the symmetric version of the element exists in the relation
        while(k<setv.size()){
            if(setv[i] == computeDual(setv[k])){
                count++;
            }
            k++;
        }
    }
    // If every element in the relation has a symmetric pair return true
    if(count == setv.size()){
        return true;
    }
    return false;
}

//check if the relation is transitive
// for all x,y,z \in set1, (x -> y AND y -> z) implies x -> z
bool StringRelation::isTransitive(){
	//You are required to implement this 
    int count,k,j,size;
    count = 0;
    k = 0;
    j = 0;
    size = 0;
    //if(!isValid()){return false;}    
    // Iterate through each element of the relation
    for(int i = 0; i<setv.size();i++){ 
        k = 0;
        // Compare iteration with every other element
        while(k<setv.size()){
            // Check all elements which have same first element
            // as the second element of the iteration
            if(isFirstComponent(returnSecondComponent(setv[i]), setv[k])){
                j=0;
                size++;
                // Create match that is required
                string var = returnSecondComponent(computeDual(setv[i])) + "," + returnSecondComponent(setv[k]);
                // Search for match with desired element
                while(j<setv.size()){
                    if(setv[j] == var){
                        count++;
                        //j++;
                    }
                    j++;
                }
            }
            k++;
        }
    }
    // If every element is transitive return true
    if(count == size){
        return true;
    }   
    return false;
}

//return true if the relation is an equivalence relation
//return false otherwise
bool StringRelation::isEquivalence(){
	//You are required to implement this
    // Make sure relation meets the 3 criteria for equivalance
    if(isTransitive() && isReflexive() && isSymmetric()){
        return true;
    } 
    return false;    
}

//s1 is of the form "a" while s2 is of the form "p,q"
//if a==p then return true
bool StringRelation::isFirstComponent(string s1, string s2){
	//You are required to implement this
    if(s1 == returnSecondComponent(computeDual(s2))){
        return true;
    }
    return false;
}


//Given a member of set1, this function determine the equivalence class
//for this element s1 i.e. {s| (s,s1) \in R and R is a equivalence relation}
SetOfStrings *StringRelation::computeEquivalenceClass(string element){
    //You are required to implement this
	SetOfStrings *out = new SetOfStrings();
    // Make sure it is an equivalence relation
    if(isEquivalence()){
        // Iterate through relation
        for(int i = 0; i<setv.size();i++){
            // Checl that element is the same as first element of relation member
            if(isFirstComponent(element,setv[i])){
                out->insertElement(returnSecondComponent(setv[i]));
            }
        }
    }
    return out;
}