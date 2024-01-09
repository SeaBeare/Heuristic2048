#pragma once

#include <string>
#include <iostream>

using namespace std;

//Object for our leader Board
class LeaderBoard{
public:
	struct NamePlace{
		string name;
		string place;
		bool operator==(NamePlace y){
			if(this->name == y.name && this->place == y.place){
				return true;
			}
			return false;
		}
		bool operator!=(NamePlace y){
			if(this->name == y.name && this->place == y.place){
				return false;
			}
			return true;
		}
	};
	struct PointRank{
		int rank;
		int point;
	};
	PointRank pointRank;
	NamePlace namePlace;
	bool operator<(LeaderBoard&);
	bool operator>(LeaderBoard&);
	bool operator<=(LeaderBoard&);
	bool operator>=(LeaderBoard&);
	friend ostream& operator<<(ostream&, const LeaderBoard&);
};
