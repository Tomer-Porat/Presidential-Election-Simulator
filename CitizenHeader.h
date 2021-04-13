	#pragma once
namespace election {

	class Citizen {
	private:
		string name;
		int nameLen;
		int id;
		int birthYear;
		int distNum;
		int partyVoted; // (-1) = Not voted yet.
		District* citizenDist;
	public:
		Citizen();//ctor
		~Citizen(); //dctor
		int getId() const;
		const Citizen& operator=(const Citizen& other);// = operand
		Citizen(const Citizen& other); //copy ctor
		friend ostream& operator<<(ostream& os, const Citizen& _citizen); //print operator
		bool setCitizen(string _name, int _nameLen, int _id, int _birthYear, District* districtNum);
		bool isVoted(); // Return true if the citizen already voted;
		bool setDistrict(District* dist) { this->citizenDist = dist; return true; };
		int getDistrictNum()const { return this->distNum; };
		string getName()const {return this->name;};
		void setVote(int partyNum) { this->partyVoted = partyNum; }
		bool save(ostream& out) const;
		void load(istream& in);
	};

	
	class citizenList
	{
	private:
		friend class Campaign;
		int lstLength = 0;
	public:
		list<Citizen> citizenLst;
		citizenList();
		~citizenList();
		// citizenList(const citizenList&);
		void operator=(const citizenList& other);
		void printList() const;
		Citizen* findCitizen(int id);
		bool save(ostream& out) const;
		void load(istream& in);
		int getVotesCount()const;
		int getPotentialVoters()const;
		void printList(int numOfRepsElected) const;	
	};
};