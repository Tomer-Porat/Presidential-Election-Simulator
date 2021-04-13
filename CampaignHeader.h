#pragma once
namespace election 
{
	class Citizen;
	class District;
	class Party;
	class citizenList;

	class Campaign
	{ 
		protected: 
			int day = 1, month = 1, year = 2020;	
			int maxDistricts = 0;
			District* DistrictArr;//Array of all the districts.
			citizenList** votersList;//Array of all the citizen that allows to vote. The size of the array is the total districts. Each item in the array is linked citizen list. 
			DynamicArray<Party> partyArr;//Array of all the parties.

		public:
			Campaign(int maxDistricts);
			const Campaign& operator=(const Campaign& other);
			Campaign(const Campaign& other);
			virtual ~Campaign();
			void load(istream& in);
			bool save(ofstream& out_file) const;
			District& getDistricts(int distNum) { return this->DistrictArr[distNum]; };
			bool districtExists(int distID);
			int getDay() { return this->day; };
			int getMonth() { return this->month; };
			int getYear() { return this->year; };
			bool setMaxDist(int max) { this->maxDistricts = max; return true; };
			bool setDay(int cDay) { this->day; return true; };
			bool setYear(int year) { this->year; return true; };
			bool setMonth(int month) { this->month; return true; };
			bool addDistrict(string _districtName, int _numOfReps,int _numOfDistrict,int distType);
			virtual bool addCitizen(string _name ,int _nameLen ,int _id, int _birthYear, District* citizenDist);
			virtual void AddParty(string partyName, int leaderID);
			bool addRep(int repID, int partyNum, int districtNum);
			friend ostream& operator<<(ostream& os, const Campaign& _campaign);
			void displayDistricts()const;
			virtual void displayCitizens()const;
			void displayParties()const;
			void addVote(int id, int partyNum);
			void displayResults();
			bool isPartyExist(int index) { return index < partyArr.size(); };
			vector<float> getVotersPrecentage()const;
			int getTotalVotersInDistrict (int district)const;
			void connectPointers();
	};

	class simpleCampaign : public Campaign
	{
		protected:
			int maxDistricts = 1;
		public:
			simpleCampaign(int maxDistricts);
			~simpleCampaign();
			virtual bool addCitizen (string _name, int _nameLen, int _id, int _birthYear ,District* citizenDist)override;
			virtual void AddParty(string partyName, int leaderID) override;
			virtual void displayCitizens ()const override;
	};


};
