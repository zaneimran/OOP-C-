#include "SetUI.h"

SetUI::SetUI()
{
	TopicScreen();
}

// Greet the user and shows the developer name.
void SetUI::TopicScreen()
{
	system("clear");
	cout <<"----------------------------------------------------------------------"<< endl; // Replace the name with yours
	cout <<"\033[1;31mSet Calculator\033[0m\nDeveloper Name: " << "\033[1;34mE.g., Zane Imran (zimr397, 769246028)\033[0m\n"; 
	cout <<"To know available commands, please type 'help'" << endl;
	cout <<"---------------------------------------------------------------------"<< endl;
}

bool SetUI::ReadFromFile(string filename, SetOfStrings *ss, StringRelation *sr, bool verbose)
{
	/* Todo:
	 *     This function is NOT completed.
	 *     Reading the data from the input file is done.
	 *     Use it to implement your logic.
	 */
	string line;
	ifstream infile (filename.c_str());
	//return false if the file does not exist
	if (!infile.good()){
		printError("openError");
		return false; 
	}

	getline(infile,line); // Get the first line to extract set member
    line.erase(0,2); // Remove '//' in the lines

	line.erase(remove(line.begin(), line.end(), ' '), line.end()); 

	cout<<line;
	vector<string> element;
	int i = 0; 
	size_t found;
	while((found = line.find(",",i))!=std::string::npos) {
		element.push_back(line.substr(i,found-i));
		ss->insertElement(element.at(element.size()-1));
		i = found+1;	
	}
	element.push_back(line.substr(i));
	ss->insertElement(element.at(element.size()-1));
	cout << endl;
	
	getline(infile,line); // To bypass the second line
	
	//read the rest of the file.
	while (getline(infile,line)){
		if(verbose){cout<<line<<endl;}
		line.erase(remove(line.begin(), line.end(), ' '), line.end());
		// find } as the finisher for file reading
		if (line.find("}")!=string::npos) break; 
		// fetch set and relation in the line 
		if (!getFromLine(ss, sr, line)) return false;
		//cout << endl;
	}
	infile.close();
	sr->setInput(ss);	
	
	cout<<ColorText("File reading was successful\nPlease type 'list' to view the members and relations defined in the graph",GREEN)<<endl;
	cout<<ColorText("If a directory is opened instead of a file, program will generate incorrect outputs", YELLOW);
	cout<<endl;
	if(!(sr->isValid())){ // If invalid
		printError("relation");
		return false;
	}
	loaded = true;
	return true;
}

bool SetUI::getFromLine(SetOfStrings *ss, StringRelation *sr, string line){
	vector<string> element;
	int i = 0;
	size_t found;
	if(line.size()==0){
		return true;
	}
	while((found = line.find("->",i))!=std::string::npos) {
		element.push_back(line.substr(i,found-i));
		i = found+2;
	}
	element.push_back(line.substr(i,line.find("[",i)-i));

	for (int j = 0; j < (int)element.size()-1; j++) {
	}
	
	string temp = line.substr(i,line.find("]",i)-i);
	string stringWeight = "";

  	std::size_t place = temp.find_first_of("0123456789");
  	while (place!=std::string::npos){
    	place=temp.find_first_of("0123456789",place+1);
		stringWeight = stringWeight + temp[place];
  	}

	int w = stoi(stringWeight);
	sr->addWeight(w);

	//Print out the string relation
	for (int j = 0; j < (int)element.size()-1; j++) {
		string test = element.at(j) + "," + element.at(element.size()-1);
		sr->insertElement(test);
	}
	return true;
}

void SetUI::printEquivalenceClass(string member, SetOfStrings* ss){

}

void SetUI::printProperties(string property, bool isProperty){
	if(property == "reflexive"){
		if(isProperty){
			cout<< ColorText("It is reflexive",GREEN) <<endl;
			return;
		}
		else{
			cout<< ColorText("It is reflexive",RED) <<endl;
		return;
		}
	}
	else if(property == "transitive"){
		if(isProperty){
			cout<< ColorText("It is transitive",GREEN) <<endl;
			return;
		}
		else{
			cout<< ColorText("It is transitive",RED) <<endl;
			return;
		}
	}
	else if(property == "symmetric"){
		if(isProperty){
			cout<< ColorText("It is symmetric",GREEN) <<endl;
			return;
		}
		else{
			cout<< ColorText("It is symmetric",RED) <<endl;
			return;
		}
	}
	else if(property == "equivalence"){
		if(isProperty){
			cout<< ColorText("It is equivalence",GREEN) <<endl;
			return;
		}
		else{
			cout<< ColorText("It is equivalence",RED) <<endl;
			return;
		}
	}
}

void SetUI::printReachable(bool reachable){
	if(reachable){
		cout<< ColorText("Reachable!",GREEN)<<endl;
	}
	else{
		cout<< ColorText("Not Reachable",RED)<<endl;
	}
}

void SetUI::printError(string reason)
{
	// error message if the command cannot be understood
	if (reason.compare("command") == 0){
		cout << ColorText("Command cannot be understood. Please enter help to see the available commands\n",RED);
	}
	// error message if the command argument is incorrect
	else if (reason.compare("argument") == 0){
		cout << ColorText("Incorrect command arguments!\n",RED);
		cout << ColorText("Please type help to know about the command arguments\n",RED);
	}

	else if(reason.compare("openFile")==0){
		cout<<ColorText("There is no set loaded to the program",RED)<<endl;
		cout<<ColorText("Please open a file using 'open' command!",RED)<<endl;
	}
	else if(reason.compare("openError")==0){
		cout<<ColorText(" Error occured while reading the input file. \n Possible reasons: \n 1. File does not exist \n 2. Contains a invalid graph \n3. Unreadable data Graph could not be loaded successfully", RED)<<endl;
	}
	else if(reason.compare("reach")==0){
		cout<<ColorText("Path is not reachable",RED)<<endl;
	}
	else if(reason.compare("eqClass")==0){
		cout<<ColorText("Equivalence class request could not be executed",RED)<<endl;
		cout<<ColorText("Possibly the string does not exist in the set or there is no equivalence relation",RED)<<endl;
	}
	else if(reason.compare("relation")==0){
		cout<<ColorText("Invalid Relation Entered",RED)<<endl;
	}
}

string SetUI::GetCommand()
{
	string commandInput;
	cout << ">> ";

	getline (cin, commandInput);

	return commandInput;
}

//prints the help message (Completed)
void SetUI::Help()
{
	cout << "Currently available commands:\n";
	cout << "Anything inside <> bracket is an optional argument, while [] bracket contains a must argument.\n\n";
	cout << left << setw(45) << ColorText("	help", RED) << left << setw(50) << "Show help." << endl << endl;
	cout << left << setw(45) << ColorText("	ls <path> ", RED) << left << setw(50) << "Identical to the ls shell command. If a path is given, then" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "the program returns all the files in that path." << endl << endl;
	cout << left << setw(45) << ColorText("	clear ", RED) << left << setw(50) << "Identical to the clear shell command. Clear the screen." << endl << endl;
	cout << left << setw(45) << ColorText("	open [file_path] <-v>", RED) << left << setw(50) << "Open a file. If the file does not exist, then program returns" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "an error message. If -v (verbose) option is enabled (e.g., open a.txt -v)," << endl;
	cout << left << setw(41) << "" << left << setw(50) << "then each line in the file is printed on console while reading." << endl << endl;
	cout << left << setw(45) << ColorText("	list", RED) << left << setw(50) << "List all the members of set and relation." << endl << endl;
	cout << left << setw(45) << ColorText("	check [OPTION] ", RED) << left << setw(50) << "Check the relation. The option has to be provided. Options are:" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "-r (reflexive)" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "-s (symmetric)" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "-t (transtivie)" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "-e (equivalence relation)" << endl << endl;
	cout << left << setw(45) << ColorText("	eqclass [VALUE]", RED) << left << setw(50) << "Show equivalence class of the given [VALUE = Set member]." << endl;
	cout << left << setw(41) << "" << left << setw(50) << "If VALUE is not a member of set, then the program returns" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "an error message." << endl << endl;
	cout << left << setw(45) << ColorText("	reachable [VALUE1] [VALUE2]", RED) << left << setw(50) << "This command checks if two given members are connected to each other" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "If any of VALUE1 and VALUE2 is not a member of the set, then it" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "returns an error message." << endl << endl;
	cout << left << setw(45) << ColorText("	path [VALUE1] [VALUE2]", RED) << left << setw(50) << "Apply Dijkstra algorithm to find the shortest path." << endl;
	cout << left << setw(41) << "" << left << setw(50) << "VALUE1 and VALUE2 are members of the set. VALUE1 is the starting node, and VALUE2 is the destination." << endl << endl;
	cout << left << setw(45) << ColorText("	exit", RED) << left << setw(50) << "Terminate the program." << endl;
	cout << "\n\n";
}

void SetUI::printShortestPath(int distance, string path){
	cout << "  The shortest path distance: " << ColorText(to_string(distance),GREEN) << endl;
	cout << "  The path is: " << ColorText(path, BLUE) << endl;
}

string SetUI::ColorText(string s, COLOR color)
{
	string temp;
	switch (color) {
		case RED: temp = "\033[1;31m" + s + "\033[0m"; break;
		case BLUE: temp = "\033[1;34m" + s + "\033[0m"; break;
		case YELLOW: temp = "\033[1;33m" + s + "\033[0m"; break;
		case GREEN: temp = "\033[1;32m" + s + "\033[0m"; break;
		case WHITE: temp = "\033[1;37m" + s + "\033[0m"; break;
		default: temp = "\033[0m" + s; break;
	}
	return temp;
}

int SetUI::ListMembers(SetOfStrings *model){
	cout<<"The members of the "<< ColorText("sets",BLUE)<< " are:"<<endl;
	cout<<"=> {";
	for(int i = 0; i<model->size(); i++){
		cout<<ColorText(model->returnElement(i),BLUE);
		if(i != (model->size()-1)){
			cout<<",";
		}
	}
	cout<<"}"<<endl;
}

int SetUI::ListMembers(StringRelation *model){
	cout<<"The members of the "<< ColorText("relation",YELLOW)<< " are:"<<endl;
	cout<<"=> {";
    int i=0, j=0;
    j=model->size(); 
    while(i<j){
        string next;
        next = model->returnElement(i);
	    if(i!=j-1){
			cout<<"("<<ColorText(next,YELLOW)<<")"<<", ";
            ++i;
        }
        else{
            cout<<"("<<ColorText(next,YELLOW)<<")";
            ++i;
        }
    }
    cout<<"}"<<endl;
	cout<<"The associated "<< ColorText("weights",GREEN)<< " are:"<<endl;
	cout<<"=>";
	cout<<"{";
	for(int i =0; i<(model->getWeightVector()).size();i++){
		string k = to_string(model->getWeightVector()[i]);
		cout<<ColorText(k,GREEN);
		if(i != (model->size()-1)){
			cout<<",";
		}
	}
	cout<<"}";
	cout<<endl;
}

bool SetUI::getLoaded(){
	return loaded;
}
