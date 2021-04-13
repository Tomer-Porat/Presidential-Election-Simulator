#include "GlobalHeader.h"
namespace election {
	class District;
	class Party;
	class citizenNode;
	////   Regular Campaign   ///
	/* <Initializers> */
	Campaign::Campaign(int maxDistricts) {
		setMaxDist(maxDistricts);
		try {
			this->votersList = new citizenList * [this->maxDistricts];
		}
		catch(bad_alloc& ex){
			cout << ex.what() << endl;
			exit(1);
		}

		for (int i = 0; i < this->maxDistricts; i++) {
			try {
				this->votersList[i] = new citizenList;
			}
			catch (bad_alloc& ex) {
				cout << ex.what() << endl;
				exit(1);
			}
		}
		try {
			this->DistrictArr = new District[this->maxDistricts];
		}
		catch (bad_alloc& ex) {
			cout << ex.what() << endl;
			exit(1);
		}
		if (maxDistricts == 1) {//is Simple Campaign
			int strSize = 8;
			this->DistrictArr[0].setDistName("Deafult");
			this->DistrictArr[0].setdistType(DIVIDED);
			this->DistrictArr[0].setdistID(1);
		}
	}
	Campaign::~Campaign() {
		delete[] this->votersList;
		delete[] this->DistrictArr;
	}
	ostream& operator<<(ostream& os, const Campaign& _campaign)
	{
		os << "|Election Date: " << _campaign.year
			<< "/" << _campaign.month
			<< "/" << _campaign.day
			<< "|\n";
		return os;
	}
	const Campaign& Campaign::operator=(const Campaign& other)
	{
		if (this != &other)
		{
			this->day = other.day;
			this->month = other.month;
			this->year = other.year;
		}
		return *this;
	}
	Campaign::Campaign(const Campaign& other)
	{
		*this = other;
	}
	/* </Initializers> */

	bool Campaign::districtExists(int distID) {
		if (!this->DistrictArr[distID].getDistrictName().empty())
			return true;
		else
			return false;
	}

	/* </Setters/Getters Methods> */



	/* <Display Methods> */
	void Campaign::displayCitizens()const {
		for (int i = 0; i < this->maxDistricts; i++) {
			if (!this->DistrictArr[i].getDistrictName().empty()) {
				this->votersList[i]->printList();
			}
		}
	}
	void Campaign::displayDistricts() const {
		for (int i = 0; i < this->maxDistricts; i++) {
			if (this->DistrictArr[i].getDistrictID() != -1) {

				cout << this->DistrictArr[i] << "\n";
			}
		}
	}
	void Campaign::displayParties()const {
		for (int i = 0; i < this->partyArr.size(); i++) {
			cout << "\n";
			cout << (i + 1) << "." << this->partyArr[i] << "\n";

		}
	}
	/* </Display Methods> */

	/* <Add Methods> */
	bool Campaign::addDistrict(string _districtName, int _numOfReps, int _districtID, int distType) {
		bool flag = false;
		flag = this->DistrictArr[_districtID].setDistrict(_districtName, _numOfReps, _districtID, distType);
		if (flag) {
			return true;
		}
		else{
			throw "setting district failed";
		}
	}
	bool Campaign::addCitizen(string _name,int nameLen, int _id, int _birthYear, District* citizenDist)
	{
		Citizen toaddciv;
		toaddciv.setCitizen(_name,  nameLen, _id, _birthYear, citizenDist);
		this->votersList[citizenDist->getDistrictID()]->citizenLst.push_front(toaddciv);
		return true;
	}
	void Campaign::AddParty(string partyName, int leaderID)
	{
		Citizen* partyLeader = nullptr;
		string leaderName;
		for (int districtIndex = 0; districtIndex < this->maxDistricts; districtIndex++)
		{
			partyLeader = this->votersList[districtIndex]->findCitizen(leaderID);
			if (partyLeader) {
				leaderName = partyLeader->getName();
				break;
			}
		}
		if (partyLeader == nullptr) {
			 throw "ERROR - Party leader does not exist as a citizen\n";
		}
		// add new value
		Party* toAdd;
		try{
			toAdd = new Party;
		}
		catch(bad_alloc& ex){
			cout << ex.what() << endl;
			exit(1);
		}
		toAdd->setParty(partyName, partyName.length(), leaderID, leaderName, leaderName.length());
		this->partyArr.push_back(*toAdd);
	}
	bool Campaign::addRep(int repID, int partyNum, int districtNum)
	{
		Citizen* rep;
		citizenList* tmp;
		for (int distIndex = 0; distIndex < MAX_DISTRICTS_POSSIBLE; distIndex++)
		{
			tmp = votersList[distIndex];
			rep = tmp->findCitizen(repID);
			if (rep!=nullptr)
				break;
		}
		if (rep == nullptr)
		{
			throw "\nError - Citizen not existed.\n Please add the citizen using option 2 in Main Menu.\n";
		}
		if (this->partyArr.size() < partyNum)//checks if the party exists
		{
			throw "\nError - Party doesn't existed.\n";
		}
		this->partyArr[partyNum].setRep(*rep, districtNum);
		return true;
	}



	void Campaign::addVote(int id, int partyNum)
	{
		Citizen* voter;
		int voterDistrictNum;
		for (int i = 0; i < this->maxDistricts; i++)
		{
			voter = this->votersList[i]->findCitizen(id);
			if (voter) {//voter found
				if (!voter->isVoted()) // If the citizen not voted already.
				{
					voterDistrictNum = voter->getDistrictNum();
					voter->setVote(partyNum);
					this->partyArr[partyNum].addVoteToParty(voterDistrictNum);
				}
				else
				{//input checks
					throw "\nThe citizen already voted.";
				}
			}
		}
	}
	vector<float> Campaign::getVotersPrecentage()const {
		vector<float> res;
		res.resize(this->maxDistricts);
		float potentialVoters = 0;
		float Voters = 0;
		for (int i = 0; i < this->maxDistricts; i++) {
			potentialVoters = static_cast<float>(this->votersList[i]->getPotentialVoters());
			Voters = static_cast<float>(this->votersList[i]->getVotesCount());
			if (potentialVoters != 0)
				res[i] = (Voters / potentialVoters) * 100;//calculate %
			else
				res[i] = 0;//if no one voted the % of voters is 0
		}
		return res;
	}
	int Campaign::getTotalVotersInDistrict(int district) const {
		int res = 0;
		for (int i = 0; i < this->partyArr.size(); i++) {
			res += partyArr[i].getTotalVotes(district);
		}
		return res;
	}
	void Campaign::displayResults()
	{
		vector<float> votesPrecentage = this->getVotersPrecentage();//calcuates the % of total votes for each district
		vector<int> repsInParties;
		for (int districtIndex = 0; districtIndex < this->maxDistricts; districtIndex++)
		{
			int numOfRepsInDistrict = 0, isTie = 0;
			if (this->DistrictArr[districtIndex].getDistrictID() != -1)
			{//If the district is not empty, display it:
			// Print the voting percentage of the total district.
				cout << "_______________________";
				cout.precision(4);
				cout << "\n" << this->DistrictArr[districtIndex] << "With " << votesPrecentage[districtIndex] << "% of citizens voted\n";
				// Print the total number of votes:
				float totalVotesInDistrict = getTotalVotersInDistrict(districtIndex);
				for (int partyIndex = 0; partyIndex < partyArr.size(); partyIndex++)
				{
					float partyPercentage = 0;
					if (!this->partyArr[partyIndex].getPartyName().empty())
					{
						float totalVotesForParty = this->partyArr[partyIndex].getTotalVotes(districtIndex);
						string partyName = this->partyArr[partyIndex].getPartyName();
						// Print the total votes of each party:
						cout << "\nThe Party: '" << partyName
							<< "' got total of: " << totalVotesForParty << " votes.";
						// Print the percentage of votes from total votes of each party
						if (totalVotesInDistrict == 0 || totalVotesForParty == 0)
							partyPercentage = 0;
						else { // Calculate the percentage:
							partyPercentage = (totalVotesForParty / totalVotesInDistrict) * 100;
						}
						cout << "\nAnd gained " << partyPercentage << "% of the district total votes. ";
						// Print the list of reps elected:
						if (partyPercentage != 0)
						{
							numOfRepsInDistrict = this->DistrictArr[districtIndex].getNumOfReps();
							cout << "\nThe Representatives Elected: \n";
							this->partyArr[partyIndex].printRepsElected(partyPercentage, districtIndex, numOfRepsInDistrict, this->DistrictArr[districtIndex], static_cast<float>(partyArr.size()), &isTie);
						}
						else
						{
							cout << "\n-No representatives were elected for this party-\n";
						}
					}
				}
			}
		}
		//Sort the parties by the number of reps elected:
		if (this->maxDistricts == SIMPLE) {	
			for (int i = 0; i < partyArr.size(); i++) {
				partyArr[i].setSimple();
			}
			this->partyArr.ourSort();
		}
		else {//REGULAR
			this->partyArr.ourSort();
		}
		cout << "\n\n---Final Results---\n\n";
		//summary
		for (int i = 0; i < partyArr.size(); i++)
		{
			if (i == 0) {
				cout << "The President Elect is: " << partyArr[i].getLeaderName();
			}
			else
			{
				cout << "\n#" << i + 1 << " " << partyArr[i].getLeaderName();
			}
			cout << " Leader of " << partyArr[i].getPartyName()
				<< "\nWith total of: " << this->partyArr[i].getVotesNumber()
				<< " Votes, and total of: "
				<< this->partyArr[i].getTotalRepsElected()
				<< " Representatives Elected\n";
			cout << "_______________________";

		}
		cout << "\n---END---\n";
	}

	////   Simple Campaign   ///
	simpleCampaign::simpleCampaign(int maxDistricts) : Campaign(maxDistricts)
	{
	}
	simpleCampaign::~simpleCampaign()
	{

	}
	bool simpleCampaign::addCitizen(string _name, int _nameLen, int _id, int _birthYear, District* citizenDist)
	{
		Citizen toaddciv;
		toaddciv.setCitizen(_name, _nameLen, _id, _birthYear, &DistrictArr[0]);
		this->votersList[0]->citizenLst.push_front(toaddciv);
		return true;
	}
	void simpleCampaign::AddParty(string partyName, int leaderID)
	{
		Citizen* partyLeader = nullptr;
		string leaderName;
		partyLeader = this->votersList[0]->findCitizen(leaderID);
		if (partyLeader)
			leaderName = partyLeader->getName();
		else { //(partyLeader == nullptr) 
			throw "ERROR - Party leader does not exist as a citizen\n";
		}
		// add new value
		Party* toAdd = nullptr;
		try {
			toAdd = new Party;
		}
		catch (bad_alloc& ex) {
			cout << ex.what() << endl;
			exit(1);
		}
		toAdd->setParty(partyName, partyName.length(), leaderID, leaderName, leaderName.length());
		this->partyArr.push_back(*toAdd);
	}
	void simpleCampaign::displayCitizens()const {
		citizenList* currList = nullptr;
		this->votersList[0]->printList();
	}
	void Campaign::load(istream& in) {
		in.read(rcastc(&day), sizeof(day));
		in.read(rcastc(&month), sizeof(month));
		in.read(rcastc(&year), sizeof(year));
		in.read(rcastc(&this->maxDistricts), sizeof(maxDistricts));
		for (int i = 0; i < this->maxDistricts; i++)
		{
			this->DistrictArr[i].load(in);
		}

		for (int i = 0; i < this->maxDistricts; i++)
		{
			this->votersList[i]->load(in);
		}
		int arrLen;
		in.read(rcastc(&arrLen), sizeof(arrLen));
		for (int i = 0; i < arrLen; i++)
		{
			Party tmp;
			tmp.load(in);
			this->partyArr.push_back(tmp);
		}
		this->connectPointers();
	}
	bool Campaign::save(ofstream& out_file)const {
		out_file.write(rcastcc(&day), sizeof(day));
		out_file.write(rcastcc(&month), sizeof(month));
		out_file.write(rcastcc(&year), sizeof(year));
		out_file.write(rcastcc(&this->maxDistricts), sizeof(maxDistricts));
		for (int i = 0; i < this->maxDistricts; i++)
		{
			this->DistrictArr[i].save(out_file);
		}

		for (int i = 0; i < this->maxDistricts; i++)
		{
			this->votersList[i]->save(out_file);
		}
		int arrLen = partyArr.size();
		out_file.write(rcastcc(&arrLen), sizeof(arrLen));
		for (int i = 0; i < this->partyArr.size(); i++)
		{
			this->partyArr[i].save(out_file);
		}
		return out_file.good();
	}


	void Campaign::connectPointers() {
		list<Citizen>::iterator iter;
		for (int i = 0; i < this->maxDistricts; i++)
		{
			for (iter = this->votersList[i]->citizenLst.begin(); iter != this->votersList[i]->citizenLst.end(); ++iter) {
				int distNum = iter->getDistrictNum();
				iter->setDistrict(&this->DistrictArr[distNum]);
			}
		}

		for (int i = 0; i < this->partyArr.size(); i++)
		{//Loop in party arr:
			citizenList** currRepsArray = this->partyArr[i].getRepsArray();
			for (int j = 0; j < this->maxDistricts; j++)
			{			
				for (iter = currRepsArray[j]->citizenLst.begin(); iter != currRepsArray[j]->citizenLst.end(); ++iter) {
					int distNum = iter->getDistrictNum(); 
					iter->setDistrict(&this->DistrictArr[distNum]);
				}
			}
		}
	}
}

