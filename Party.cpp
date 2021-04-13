#include "GlobalHeader.h"
namespace election {
	Party::Party()
	{
		this->totalRepsForPresident = 0;
		this->partyNameLen = 0;
		this->leaderID = 0;
		this->leaderNameLen = 0;
		this->totalRepsElected = 0;
		try {
			this->repsArray = new citizenList * [MAX_DISTRICTS_POSSIBLE];
		}
		catch (bad_alloc& ex) {
			cout << ex.what() << endl;
			exit(1);
		}
		for (int i = 0; i < MAX_DISTRICTS_POSSIBLE; i++) {
			try {
				this->repsArray[i] = new citizenList();
			}
			catch (bad_alloc& ex) {
				cout << ex.what() << endl;
				exit(1);
			}
		}
		votersArr.resize(MAX_DISTRICTS_POSSIBLE);
		for(int i = 0; i < MAX_DISTRICTS_POSSIBLE; i++)
		{
			votersArr.push_back(0);
		}

	}
	Party::Party(string _partyName, int _partyNameLen, int _leaderID, char* _leaderName, int _leaderNameLen)
	{
		this->totalRepsForPresident = 0;
		this->totalRepsElected = 0;
		this->partyNameLen = 0;
		this->leaderID = 0;
		this->leaderNameLen = 0;
		try {
			this->repsArray = new citizenList* [MAX_DISTRICTS_POSSIBLE];
		}
		catch (bad_alloc& ex) {
			cout << ex.what() << endl;
			exit(1);
		}
		for (int i = 0; i < MAX_DISTRICTS_POSSIBLE; i++) {
			this->repsArray[i] = new citizenList();
		}
		votersArr.resize(MAX_DISTRICTS_POSSIBLE);
		for(int i = 0; i < MAX_DISTRICTS_POSSIBLE; i++)
		{
			votersArr.push_back(0);
		}
	}
	Party::~Party()
	{
		delete[] (this->repsArray);
	}
	ostream& operator<<(ostream& os, const Party& _party)
	{
		os << "Party Name: " << _party.partyName
			<< ", Leader Name: " << _party.leaderName
			<< ", Leader ID: " << _party.leaderID
			<<"\n"<<"Party Representatives: \n";

		for (int i = 0; i < MAX_DISTRICTS_POSSIBLE; i++) {
			if(!_party.repsArray[i]->citizenLst.empty()){
					_party.repsArray[i]->printList();
			}
		}
		return os;
	}
	void Party::operator=(const Party& other)
	{
		if(this != &other)
		{
			partyName.clear();
			leaderName.clear();
			this->partyName = other.partyName;
			this->leaderName = other.leaderName;
			this->leaderID = other.leaderID;
			this->partyNameLen = other.partyNameLen;
			this->leaderNameLen = other.leaderNameLen;
			this->totalRepsElected = other.totalRepsElected;
			this->totalRepsForPresident = other.totalRepsForPresident;
			for (int i = 0; i < MAX_DISTRICTS_POSSIBLE; i++)
			{
				if(this->repsArray[i] != nullptr)
					*this->repsArray[i] = *other.repsArray[i];
			}
			for (int i = 0; i < MAX_DISTRICTS_POSSIBLE; i++)
			{
				this->votersArr.at(i) = other.votersArr.at(i);
			}
		}
	}
	Party::Party(const Party& other)
	{
		*this = other;
	}
	bool Party::setParty(string _partyName, int _partyNameLen, int _leaderID, string _leaderName, int _leaderNameLen)
	{
		this->partyName.assign(_partyName);
		this->partyNameLen = partyName.length();
		this->leaderID = _leaderID;
		this->leaderName = _leaderName;
		this->leaderNameLen = leaderName.length();
		return true;
	}
	bool Party::setRep(Citizen& toAdd, int districtNum)
	{
	    this->repsArray[districtNum]->citizenLst.push_back(toAdd);
		return true;
	}
	bool Party::addVoteToParty(int districtNum)
	{
		this->votersArr[districtNum] += 1;
		return true;
	}

	void Party::printRepsElected(float percentage, int districtIndex, int numOfRepsInDistrict,District& currDist, float numOfParties, int* isTie)
	{
		int numOfRepsElected = (percentage / 100) * numOfRepsInDistrict;
		this->totalRepsElected += numOfRepsElected;
		if(currDist.getDistrictType()==DIVIDED){
			this->totalRepsForPresident += numOfRepsElected;
		}
		else if(currDist.getDistrictType()==UNITED){//UNITED DIST
			if (percentage > 100.0 / numOfParties)  {
				this->totalRepsForPresident += numOfRepsInDistrict;
			}
			else if ((percentage == 100.0 / numOfParties) && *isTie == 0) {
				this->totalRepsForPresident += numOfRepsInDistrict;
				*isTie = 1;
			}
		}
		citizenList* curr = this->repsArray[districtIndex];
		curr->printList(numOfRepsElected);
	}
	int Party::getVotesNumber()const {
		int res = 0;
		for (int i = 0; i < MAX_DISTRICTS_POSSIBLE; i++)
		{
			res+=this->votersArr[i];
		}
		return res;
	}
	bool Party::save(ofstream& out_file) const{
		//save leader name
		int stringLength = this->leaderName.size();
		out_file.write(rcastcc(&stringLength), sizeof(stringLength));
		for (int i = 0; i < stringLength; ++i) {
			out_file.write(rcastcc(&this->leaderName[i]), sizeof(this->leaderName[i]));
		}
		
		//save party name
		stringLength = this->partyName.size();
		out_file.write(rcastcc(&stringLength), sizeof(stringLength));
		for (int i = 0; i < stringLength; ++i) {
			out_file.write(rcastcc(&this->partyName[i]), sizeof(this->partyName[i]));
		}

		//save voters arr
		for (int i = 0; i < MAX_DISTRICTS_POSSIBLE; ++i) {
			out_file.write(rcastcc(&this->votersArr[i]), sizeof(votersArr[i]));
		}

		//save reps arr
		for (int i = 0; i < MAX_DISTRICTS_POSSIBLE; ++i) {
			this->repsArray[i]->save(out_file);
		}

		out_file.write(rcastcc(&this->leaderID), sizeof(int));
		out_file.write(rcastcc(&this->totalRepsElected), sizeof(int));
		out_file.write(rcastcc(&this->totalRepsForPresident), sizeof(int));
		return out_file.good();
	}
	void Party::load(istream& in){
		//load leader name
		in.read(rcastc(&this->leaderNameLen), sizeof(this->leaderNameLen));
		char ch = '0';
		for (int i = 0; i < this->leaderNameLen; ++i) {
			in.read(rcastc(&ch), sizeof(ch));
			leaderName += ch;
		}

		//load party name
		in.read(rcastc(&this->partyNameLen), sizeof(this->partyNameLen));
		for (int i = 0; i < this->partyNameLen; ++i) {
			in.read(rcastc(&ch), sizeof(ch));
			partyName += ch;
		}

		//load voters arr
		for (int i = 0; i < MAX_DISTRICTS_POSSIBLE; ++i) {
			in.read(rcastc(&this->votersArr[i]), sizeof(votersArr[i]));
		}

		//load reps arr
		for (int i = 0; i < MAX_DISTRICTS_POSSIBLE; ++i) {
			citizenList* tmp = nullptr;
			try {
				tmp = new citizenList;
			}
			catch (bad_alloc& ex) {
				cout << ex.what() << endl;
				exit(1);
			}
			tmp->load(in);
			this->repsArray[i] = tmp;
		}
		in.read(rcastc(&this->leaderID), sizeof(int));
		in.read(rcastc(&this->totalRepsElected), sizeof(int));
		in.read(rcastc(&this->totalRepsForPresident), sizeof(int));
	}
	bool Party::operator>(const Party& other) {
		if ((this->getTotalRepsForPresident() == 0) && (other.getTotalRepsForPresident() == 0)) {
			return this->getVotesNumber() > other.getVotesNumber();
		}
		else {
			return this->getTotalRepsForPresident() > other.getTotalRepsForPresident();
		}

	}

}

