#include "GlobalHeader.h"

void printMainMenu()
{
	cout << "1. Add district\n"
		<< "2. Add Citizen\n"
		<< "3. Add Party\n"
		<< "4. Add Citizen As Party Representative\n"
		<< "5. Display all Districts\n"
		<< "6. Display all Citizens\n"
		<< "7. Display all Parties\n"
		<< "8. VOTE!\n"
		<< "9. Election Results\n"
		<< "10. Quit\n"
		<< "11. Save to file\n"
		<< "12. Load from file\n"
		<< "___________________\n"
		<< "Please enter the requested action: ";
}

bool isNumeric(string str) {
	for (int i = 0; i < str.length(); i++)
		if (isdigit(str[i]) == false)
			return false; //when one non numeric value is found, return false
	return true;
}
void printOpening(){
	cout << "\n_______________________\n"
		 << "--Elections 2020--\n"
		<< "_______________________\n\n\n";
	cout << "Enter 1 to create new campaign" << endl;
	cout << "Enter 2 to load election campaign"<<endl;
	cout << "Enter 3 to exit." << endl;
}
void printDistrictListOpener(){
	cout << "_______________________\n"
		<< "---Districts List---\n"
		<< "_______________________\n\n";
}
void printPartiesListOpener(){
	cout << "_______________________\n"
		<< "---Parties List---\n"
		<< "_______________________\n\n";
}
void printCastVoteOpener(){
	cout << "_______________________\n"
		<< "---Cast Vote---\n"
		<< "_______________________\n\n";
}
void printCitizenListOpener(){
	cout << "_______________________\n"
		<< "---Citizens List---\n"
		<< "_______________________\n\n";
}
void printElectionResultsOpener(){
	cout << "_______________________\n"
		<< "---Election Results---\n"
		<< "_______________________\n";
}