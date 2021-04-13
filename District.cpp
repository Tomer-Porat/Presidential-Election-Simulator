#include "GlobalHeader.h"

namespace election {
	District::District() {
		this->distType = 0;
		this->districtName;
		this->disctrictNameLen = 0;
		this->districtID = -1;
		this->numOfReps = 0;
	}
	District::~District(){}
	void District::operator=(const District& other) {
		if (this != &other) {//to prevent self assignment
			districtName.clear();
			districtName = other.districtName;
			this->numOfReps = other.numOfReps;

		}
	}
	District::District(const District& other) {
		*this = other;
	}
	ostream& operator<<(ostream& os, const District& _district)
	{
		if(_district.distType==UNITED)
		{
			os << "District Name: " << _district.districtName
			<<" District ID: " << (_district.districtID + 1)
			<<", District Type: United"
			<< ", District Number Of Reps: " << _district.numOfReps
			<< '\n';
		}
		else if(_district.distType==DIVIDED)
		{
			os << "District Name: " << _district.districtName
			<<" District ID: " << (_district.districtID + 1)
			<<" District Type: Divided"
			<< ", District Number Of Reps: " << _district.numOfReps
			<< '\n';
		}
		return os;
	}
	int District::getDistrictID()const { return this->districtID; }

	bool District::setDistrict(string _districtName, int _numOfReps, int _districtID,int distType) {
		this->districtName = _districtName;
		this->disctrictNameLen = _districtName.size();
		this->districtID = _districtID;
		this->numOfReps = _numOfReps;
		if(distType)
			this->distType = UNITED;
		else
			this->distType = DIVIDED;
		return true;
	}

	void District::load(istream& in) {
		in.read(rcastc(&this->disctrictNameLen), sizeof(int));
		char ch= '0';
		for (int i = 0; i < disctrictNameLen; ++i) {
			in.read(rcastc(&ch), sizeof(ch));
			this->districtName += ch;
		}
		in.read(rcastc(&this->districtID), sizeof(int));
		in.read(rcastc(&this->distType), sizeof(int));
		in.read(rcastc(&this->numOfReps), sizeof(int));
	}
	bool District::save(ofstream& out_file)const {
		out_file.write(rcastcc(&disctrictNameLen), sizeof(disctrictNameLen));
		for (int i = 0; i < disctrictNameLen; ++i) {
			out_file.write(rcastcc(&this->districtName[i]), sizeof(districtName[i]));
		}
		out_file.write(rcastcc(&this->districtID), sizeof(int));
		out_file.write(rcastcc(&this->distType), sizeof(int));
		out_file.write(rcastcc(&this->numOfReps), sizeof(int));
		return out_file.good();
	}
}