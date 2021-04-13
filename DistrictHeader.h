#pragma once
namespace election {
	class District {
		private:
			int disctrictNameLen;
			int districtID;
			int numOfReps;
			int distType;
			string districtName;
		public:
			District();
			~District();
			void load(istream& in);
			bool save(ofstream& out_file ) const;
			friend ostream& operator<<(ostream& os, const District& _district);
			void operator=(const District& other);
			District(const District& other);		
			int getDistrictID()const;
			bool setDistName(string name) { this->districtName = name; this->disctrictNameLen = name.length(); return true; };
			bool setdistType(int type) { this->distType = type; return true; };
			bool setdistID(int ID) { this->districtID = ID; return true; };
			int getDistrictType()const {return this->distType;};
			bool setDistrict(string _districtName, int _numOfReps, int _districtID,int distType);
			string getDistrictName()const{return this->districtName;};
			int getNumOfReps()const { return this->numOfReps; };
	};

}

