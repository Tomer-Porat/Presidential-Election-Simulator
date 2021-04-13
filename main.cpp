#include "GlobalHeader.h"
using namespace election;
int main()
{//Main initializations
	int action = 0, numOfReps = 0, districtID = 0, leaderID = 0, id = 0, year = 0, districtNum = 0, repID = 0, distType = DIVIDED,partyNum = 0, voterPartyNum = 0, voterID = 0,cYear = 0, cMonth = 0, cDay = 0,campType = REGULAR, fileAction = CREATE;
	string citName, nameStrings, partyName, fileName;
	Campaign* election = nullptr;
	printOpening();
	cin >> fileAction;
	if (fileAction == EXIT1) {//exit
		cout << "goodbye";
		return 0;
	}
	if (fileAction == LOAD1) {
		cout << "please enter the file name: " << endl;
		cin >> fileName;
		ifstream inFileStart(fileName, ios::binary);
		if (!inFileStart) {
			cout << "file open error" << endl;
			exit(-1);
		}
		try{
			election = new Campaign(MAX_DISTRICTS_POSSIBLE);
		}
		catch(bad_alloc& ex){
			cout << ex.what() << endl;
			exit(1);
		}
		election->load(inFileStart);
		inFileStart.close();
	}
	else if (fileAction == CREATE){//set campaign date
		cout << "\nPlease Enter Campaign Year: ";
		cin >> cYear;
		cout << "\nPlease Enter Campaign Month: ";
		cin >> cMonth;
		cout << "\nPlease Enter Campaign Day date: ";
		cin >> cDay;
		cout << "\nPlease Enter The Campaign type: " << "\nEnter 0 for Regular Campaign and 1 for Simple Campaign." << endl;
		cin >> campType;
		if (campType == REGULAR){
			try{
				election = new Campaign(MAX_DISTRICTS_POSSIBLE);
			}
			catch(bad_alloc& ex){
				cout << ex.what() << endl;
				exit(1);
			}
		}
		else{
			try{
				election = new simpleCampaign(1);
			}
			catch (bad_alloc& ex) {
				cout << ex.what() << endl;
				exit(1);
			}
		}
		election->setYear(cYear);
		election->setMonth(cMonth);
		election->setDay(cDay);
	}
	while (action != QUIT){
			printMainMenu();
			cin >> action;
			while (action > 12 || action < 1) {//Main Menu input check
				system("cls");
				printMainMenu();
				cout << "\nInvalid input - Please select a number between 1-10: \n";
				cin >> action;
			}
			system("cls");
			switch (action)
			{
			case ADD_DISTRICT:
				if (campType == REGULAR)
				{
					cout << "To add a new district, " << "Please enter the district name: ";
					cin.ignore();
					getline (cin, nameStrings);
					if (nameStrings.empty()){//District input checks (in main as required)
						cout << "\nERROR - Invalid name.\n\n";
						break;
					}
					cout << "\nEnter 1 for United district or 0 for Divided district: ";
					cin >> distType;
					if (distType != UNITED && distType != DIVIDED){
						cout << "\nERROR - Invalid number.\n\n";
						break;
					}
					cout << "\nPlease enter the number of district reps: ";
					cin >> numOfReps;
					if (numOfReps < 1){
						cout << "\nERROR - Invalid number.\n\n";
						break;
					}
					try {
						election->addDistrict(nameStrings, numOfReps, districtID, distType);
						districtID++;// this keeps track of the districts ID
					}
					catch (const char* msg) {
						cout << msg << endl;
					}
				}
				else{
					cout << "\nERROR - Simple election.\n\n";
				}
				break;
			case ADD_CITIZEN:
				cout << "Adding a new citizen:";
				cout << "\nPlease enter the citizen name: ";
				cin.ignore();
				getline(cin, citName);
				if (citName.empty() || isNumeric(citName)){//Citizen input checks
					cout << "\nERROR - Invalid name.\n\n";
					break;
				}
				cout << "\nPlease enter the citizen id: ";
				cin >> id;
				if (id < 1 || id > 999999999){
					cout << "\nERROR - Invalid ID.\n\n";
					break;
				}
				cout << "\nPlease enter the citizen birth year: ";
				cin >> year;
				if (year > (election->getYear()-18)){
					cout << "\nERROR - Invalid year.\n\n";
					break;
				}
				if (campType == REGULAR) {
					cout << "\nPlease enter the citizen district number: ";
					cin >> districtNum;
					if (districtNum < 1 || districtNum > MAX_DISTRICTS_POSSIBLE){
						cout << "\nERROR - Invalid district number.\n\n";
						break;
					}
					if (!election->districtExists(districtNum - 1)){
						cout << "\nERROR - district doesn't exist\n";
						break;
					}
				}
				else {//adds to the default single district (if its a simple campaign)
					districtNum = 1;
				}
				election->addCitizen(citName, citName.length() , id, year, &election->getDistricts(districtNum - 1));
				break;
			case ADD_PARTY:
				cout << "Adding a new party:";
				cout << "\nPlease enter the party name: ";
				cin.ignore();
				getline(cin, partyName);
				
				if (partyName.empty()){//Party input checks
					cout << "\nERROR - Invalid party name.\n\n";
					break;
				}
				cout << "\nPlease enter the party leader id: ";
				cin >> leaderID;
				if (leaderID < 1 || leaderID > 999999999){
					cout << "\nERROR - Invalid ID.\n\n";
					break;
				}
				try{
					election->AddParty(partyName, leaderID);
				}
				catch(const char* msg){
					cout << msg << endl;
				}
				break;
			case ADD_REP:
				cout << "Adding a citizen as a party rep: " << "\nPlease enter the citizen ID: ";;
				cin >> repID;
				if (repID < 1 || repID > 999999999){//Representative input checks
					cout << "\nERROR - Invalid ID.\n\n";
					break;
				}
				cout << "\nPlease enter the party number: ";
				cin >> partyNum;
				if (partyNum < 1){
					cout << "\nERROR - Invalid party number.\n\n";
					break;
				}
				if (campType == REGULAR) {
					cout << "\nPlease enter the district number: ";
					cin >> districtNum;
					if (districtNum < 1 || districtNum > MAX_DISTRICTS_POSSIBLE)
					{
						cout << "\nERROR - Invalid district number.\n\n";
						break;
					}
				}
				else //adds to the default single district (if its a simple campaign)
					districtNum = 1;
				try {
					election->addRep(repID, partyNum - 1, districtNum - 1);
				}
				catch(const char* msg){
					cout << msg<<endl;
				}
				break;
			case DISPLAY_DISTRICTS:
				if (campType == SIMPLE) {
					cout << "\nERROR - Simple Campaign.\n";
				}
				else {
					printDistrictListOpener();
					election->displayDistricts();
				}
				break;
			case DISPLAY_CITIZENS:
				printCitizenListOpener();
				election->displayCitizens();
				break;
			case DISPLAY_PARTIES:
				printPartiesListOpener();
				election->displayParties();
				break;
			case VOTE:
				printCastVoteOpener();
				cout << "Please enter voter's ID: ";
				cin >> voterID;
				if (voterID < 1 || voterID > 999999999){//Vote input checks
					cout << "\nERROR - Invalid ID.\n\n";
					break;
				}
				cout << "Please enter voter's party selection: ";
				cin >> voterPartyNum;
				if (voterPartyNum < 1 || election->isPartyExist(voterPartyNum - 1) == false){
					cout << "\nERROR - Invalid party number.\n\n";
					break;
				}
				try{
					election->addVote(voterID, voterPartyNum - 1);
				}
				catch(const char* msg){
					cout << msg << endl;
				}
				break;
			case DISPLAY_RESULTS:
				printElectionResultsOpener();
				cout << "The election date: " << election->getDay() << "/" << election->getMonth() << "/" << election->getYear() << endl;
				election->displayResults();
				break;
			case EXIT:
				cout << "Goodbye";
				break;
			case SAVE:
				{
				char outFileName[MAX_NAME_LEN];
				cout << "Please enter the file name: " << endl;
				cin >> outFileName;
				ofstream outFile(outFileName, ios::binary);
				if (!outFile) { 
					cout << "Cannot open file!" << endl;
					return 0;
				}
				election->save(outFile);
				outFile.close();
				}
				break;
			case LOAD:
				char inFileName[MAX_NAME_LEN];
				cout << "Please enter the file name: " << endl;
				cin >> inFileName;
				ifstream infile(inFileName, ios::binary);
				if (!infile) { 
					cout << "file open error" << endl;
					exit(-1);
				}
				try {election = new Campaign(MAX_DISTRICTS_POSSIBLE);}
				catch (bad_alloc& ex) { 
					cout << ex.what() << endl;
					exit(1);
				}
				election->load(infile);
				infile.close();
				break;
			}
			cout << "_______________________\n\n";
			if (!cin){// user didn't input a number
				cin.clear(); // reset failbit
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input.next, request user reinput
			}
	}
	return 0;
}
