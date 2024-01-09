#include "LeaderBoard.hpp"
// All of these are O(1)
bool LeaderBoard::operator<(LeaderBoard& d){return pointRank.point < d.pointRank.point;}
bool LeaderBoard::operator>(LeaderBoard& d){return pointRank.point > d.pointRank.point;}
bool LeaderBoard::operator<=(LeaderBoard& d){return pointRank.point <= d.pointRank.point;}
bool LeaderBoard::operator>=(LeaderBoard& d){return pointRank.point >= d.pointRank.point;}

ostream& operator<<(ostream& os, const LeaderBoard& data){
	os << data.pointRank.rank << ' ' << data.namePlace.name
			<< ' ' << data.namePlace.place << ' ' << data.pointRank.point;
	return os;
}

