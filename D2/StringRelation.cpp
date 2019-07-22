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
	if(out->subset(this)) return true;
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

	//You are required to implement this as this
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
    
    for(i = 0; i<set1->size(); i++){
        k = 0;
        while(k<setv.size()){
            if(createReflexiveElement(set1->returnElement(i)) == setv[k]){
                count++;
                //k++;
            }
            k++;
        }
    }
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

    for(int i = 0; i<setv.size();i++){
        k = 0;
        while(k<setv.size()){
            if(setv[i] == computeDual(setv[k])){
                count++;
                //k++;
            }
            k++;
        }
    }
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

    if(count == size){
        return true;
    }   
    return false;
}

//return true if the relation is an equivalence relation
//return false otherwise
bool StringRelation::isEquivalence(){

	//You are required to implement this

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

    if(!isEquivalence()){
        return out;
    }

    for(int i = 0; i<setv.size();i++){
        if(isFirstComponent(element,setv[i])){
            out->insertElement(returnSecondComponent(setv[i]));
        }
    }
	return out;
}

SetOfStrings *StringRelation::returnNeighbours(string element){
	//You are required to implement this
	SetOfStrings *out = new SetOfStrings();

    for(int i = 0; i<setv.size();i++){
        if(isFirstComponent(element,setv[i])){
            out->insertElement(returnSecondComponent(setv[i]));
        }
    }
	return out;
}

bool StringRelation::recursive(string src, string dst, SetOfStrings* visited, bool found){
    int i;

    SetOfStrings *eqclass =  returnNeighbours(src);

    if(src == dst){
        found = true;
        return true;
    }

    if(found){
        return true;
    }

    if(eqclass->isEmpty() && !found){
        return false;
    }

    if(visited->isMember(src) && !found){
        return false;
    }

    visited->insertElement(src);

    for(i = 0; i<eqclass->size();i++){
        found = recursive(eqclass->returnElement(i), dst, visited, found);
    }
    return found;
}

bool StringRelation::isReachable(string src, string dst, SetOfStrings* visited, bool found){
    bool reachable;
    
    int i;

    SetOfStrings *eqclass =  returnNeighbours(src);

    for(i = 0; i<eqclass->size();i++){
        found = recursive(eqclass->returnElement(i), dst, visited, found);
    }
    reachable = recursive(src, dst, visited, found);
    
    return reachable;

}

int StringRelation::getWeight(string s){
    int index;
    for(int i = 0; i< setv.size(); i++){
        if(setv[i] == s){
            index = i;
        }
    }
    return weight[index];
}

vector<int> StringRelation::getWeightVector(){
    return weight;
}

void StringRelation::addWeight(int x){
    weight.push_back(x);
}

// Dijkstra algorithm implementation
// Input: source node, destination node
// Output: path length (integer)
// Note: the generated path is also stored in "path" variable
int StringRelation::computeShortest(string source, string destination){
    
SetOfStrings *Q = new SetOfStrings;
SetOfStrings *pathVector = new SetOfStrings;
string u = source;
int cost;
vector<int> dist;
vector<string> prev;
vector<string> pathVec;

// Initialise the distance and previous node vector as well as Q set
for(int i = 0; i<set1->size();i++){
    dist.push_back(999999);
    prev.push_back("-1");
    pathVec.push_back("-1");
    Q->insertElement(set1->returnElement(i));
}
// Set distance to starting node as 0
dist[returnIndex(u)] = 0;

while(!Q->isEmpty()){ 
    // make the current node the lowest cost node
    u = set1->returnElement(minIndex(dist, Q));
    // remove the chosen node
    Q->removeElement(u);

    SetOfStrings *E = returnNeighbours(u);
    string edge;
    // Cycle through the neighbouring nodes
    for(int v=0; v < E->size();v++){
        int distv = 99999; // Initialise cost to neighbouring node
        int newDist = 0; // Initialise tentative weight
        edge = u + "," + E->returnElement(v); // create edge from current node to neighbouring node
        if(!(u==E->returnElement(v))){ //Make sure node node doesnt point to itself
            newDist = dist[returnIndex(u)] + getWeight(edge); // create the tentative weight 
            distv = dist[returnIndex(E->returnElement(v))]; // gets the current neighbouring node weight
            if(newDist<distv){ // If the tentative weight is less than current update the distance and previous node
                dist[returnIndex(E->returnElement(v))] = newDist;
                pathVec[returnIndex(E->returnElement(v))] = u;
            }
        }
    }
    cost = dist[returnIndex(destination)]; // Get cost to destination
}
    // Go back through previous nodes to get path
    pathVector->insertElement(destination);
    while(pathVec[returnIndex(destination)]!=source){
        pathVector->insertElement(pathVec[returnIndex(destination)]);
        destination = pathVec[returnIndex(destination)];
    }
    pathVector->insertElement(source);
    // add the nodes to the path string
    path = "";
    for(int i = pathVector->size()-1; i>=0;i--){
        path = path + pathVector->returnElement(i);
        if(i!=pathVector->size() && i!=0){
            path = path + " -> ";
        }
    }
	return cost;
}

string StringRelation::getPath(){
    return path;
}

int StringRelation::minIndex(vector<int> dist, SetOfStrings* Q){
    int min = dist[returnIndex(Q->returnElement(0))]; // Set current smallest distance
    int index = returnIndex(Q->returnElement(0)); // Keep its index
    // Cycle through unvisited nodes
    for(int i = 1; i<Q->size(); i++){
        if(dist[returnIndex(Q->returnElement(i))]<min){ // If new minimum is found update values
            min = dist[returnIndex(Q->returnElement(i))];
            index = returnIndex(Q->returnElement(i));
        }
    }
    return index;
}

int StringRelation::returnIndex(string s){
    int index = 0;
    for(int i =0; i<set1->size();i++){
        if(set1->returnElement(i) == s){
            index = i;
            return index;
        }
    }
    return -1;
}

StringRelation::~StringRelation(){
    delete set1;
}