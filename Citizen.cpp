#include "GlobalHeader.h"
namespace election {
	class citizenNode;
	Citizen::Citizen() {// Init ctor
		this->citizenDist = nullptr;
		this->birthYear = 0;
		this->id = 0;
		this->distNum = -1;
		this->partyVoted = -1;
		this->nameLen = 0;
	}
	Citizen::~Citizen() {}
	int Citizen::getId() const { return this->id; };
	const Citizen& Citizen::operator=(const Citizen& other)
	{
		if (this != &other) {//to prevent self assignment
			this->id = other.id;
			this->birthYear = other.birthYear;
			this->distNum = other.distNum;
			this->partyVoted = other.partyVoted;
			this->citizenDist = other.citizenDist;
			this->name = other.name;
			this->nameLen = other.nameLen;
		}
		return *this;
	}
	Citizen::Citizen(const Citizen& other)
	{
		*this = other;
	}


	ostream& operator<<(ostream& os, const Citizen& _citizen)
	{
			os << "Name:" << _citizen.name
			<< ", ID:" << _citizen.id
			<< ", Birth Year:" << _citizen.birthYear
			<< ", District Number:" << (_citizen.citizenDist->getDistrictID() + 1)
			<< '\n';
		return os;
	}
	bool Citizen::setCitizen(string _name, int _nameLen, int _id, int _birthYear, District* _citizenDist) {
		this->name = _name;
		this->nameLen = _nameLen;
		this->id = _id;
		this->citizenDist = _citizenDist;
		this->distNum = _citizenDist->getDistrictID();
		this->birthYear = _birthYear;
		return true;
	}
	bool Citizen::isVoted() {
		if (this->partyVoted == -1)
			return false;
		else
			return true;
	}
	bool Citizen::save(ostream& out) const
	{
		out.write(rcastcc(&nameLen), sizeof(nameLen));
		for (int i = 0; i < this->nameLen; ++i) {
			out.write(rcastcc(&name[i]), sizeof(name[i]));
		}
		out.write(rcastcc(&id), sizeof(id));
		out.write(rcastcc(&birthYear), sizeof(birthYear));
		out.write(rcastcc(&partyVoted), sizeof(partyVoted));
		out.write(rcastcc(&distNum), sizeof(distNum));
		return out.good();
	}
	void Citizen::load(istream& in)
	{
		in.read(rcastc(&this->nameLen), sizeof(nameLen));
		char ch='0';
		for (int i = 0; i < nameLen; ++i) {
			in.read(rcastc(&ch), sizeof(ch));
			name += ch;
		}
		in.read(rcastc(&this->id), sizeof(this->id));
		in.read(rcastc(&this->birthYear), sizeof(this->birthYear));
		in.read(rcastc(&this->partyVoted), sizeof(this->partyVoted));
		in.read(rcastc(&this->distNum), sizeof(distNum));
	}


	citizenList::citizenList() 
	{
		// start with an empty list 
	}
	citizenList::~citizenList()
	{
		// free all citizenNodes in the list
	}
	void citizenList::printList() const {
		for (auto i : citizenLst) {
			cout << i;
		}
		cout << '\n';

	}
	void citizenList::printList(int numOfRepsElected) const {
		
		if (numOfRepsElected == 0) {
			cout << "No representative were elected\n";
		}
		else{
			int repIndex = 0;
			list<Citizen>::const_iterator iter;
			for (iter = citizenLst.begin(); iter != citizenLst.end(); ++iter) {
				cout << "The #" << repIndex + 1
					<< " representative is: " << *iter;
				repIndex++;
			}
		}
		cout << '\n'; 
	}
	Citizen* citizenList::findCitizen(int id)  
	{
		list<Citizen>::iterator curr; 
		for(curr = citizenLst.begin(); curr != citizenLst.end(); ++curr){
			if (curr->getId() == id) {
				return &(*curr);
			}
		}
		return nullptr;
	}
	int citizenList::getVotesCount() const{
		int res = 0;
		for (auto i : citizenLst) {
			if (i.isVoted()) {
				res++;
			}
		}
		return res;
	}
	int citizenList::getPotentialVoters()const {
		int res = 0;
		for (auto i : citizenLst) {
				res++;
		}
		return res;
	}
	void citizenList::operator=(const citizenList& other){
		this->citizenLst = other.citizenLst;
	}

	bool citizenList::save(ostream& out) const
	{
		int lstLength = this->citizenLst.size();
		out.write(rcastcc(&lstLength), sizeof(lstLength));
		for (auto const& i : citizenLst) {
			i.save(out);
		}
		return out.good();

	}
	void citizenList::load(istream& in)
	{
		in.read(rcastc(&this->lstLength), sizeof(lstLength));
		for (int i = 0; i < lstLength; i++) {
			Citizen curr;
			curr.load(in);
			citizenLst.push_back(curr);
		}
	}
}


