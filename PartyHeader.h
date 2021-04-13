#pragma once
namespace election {
	class Citizen;
	class citizenList;
	class Party {
	private:
		string leaderName;
		string partyName;
		citizenList** repsArray;//Array in the size of the total number of districts. Each item in the array is citizen linked list.
		vector<int> votersArr;//Array in the size of the total number of districts. Each vote for the party is updated like bucket sort.
		int partyNameLen;
		int leaderID;
		int leaderNameLen;
		int totalRepsElected;
		int totalRepsForPresident;
	public:
		static constexpr int MAX_SIZE = 100;
		Party();
		Party(string _partyName, int _partyNameLen, int _leaderID, char* _leaderName, int _leaderNameLen);
		~Party();
		void load(istream& in);
		bool save(ofstream& out_file) const;
		friend ostream& operator<<(ostream& os, const Party& _party);
		void operator=(const Party& other);
		bool operator>(const Party& other);
		void setSimple() { this->totalRepsForPresident = 0; };
		Party(const Party& other);
		bool setParty(string _partyName, int _partyNameLen, int _leaderID, string _leaderName, int _leaderNameLen);
		bool setRep(Citizen& toAdd, int districtNum);
		int getTotalRepsElected()const { return this->totalRepsElected; };
		int getTotalRepsForPresident()const { return this->totalRepsForPresident; };
		string getPartyName() const{ return this->partyName; }
		int getTotalVotes(int districtNum)const { return this->votersArr[districtNum]; };
		bool addVoteToParty(int districtNum);
		void printRepsElected(float percentage, int districtIndex, int numOfRepsInDistrict,District& currDist, float numOfParties, int* isTie);
		string getLeaderName() const{ return this->leaderName; }
		int getVotesNumber()const;
		citizenList** getRepsArray() { return this->repsArray; };
	};

};
