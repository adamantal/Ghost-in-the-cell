#ifndef LINK_HPP_INCLUDED
#define LINK_HPP_INCLUDED

class Link {
	public:
	int dist;
	int fac1;
	int fac2;
	Link(int d, int a1, int a2):dist(d),fac1(a1),fac2(a2){}
	int whichIs(int k){
		if (fac1 == k) {
			return 1;
		} else if (fac2 == k){
			return 2;
		} else {
			return 0;
		}
	}
	bool either(int k){
		return (fac1 == k) || (fac2 == k);
	}
	int other(int k)const{
		if (k == fac1) {
			return fac2;
		} else if (k == fac2){
			return fac1;
		} else {
			throw "Others have bad pointer";
		}
	}
	bool operator<(const Link& rhs)const{
		return dist < rhs.dist;
	}
	bool operator==(const Link& rhs)const{
		return (dist == rhs.dist && fac1 == rhs.fac1 && fac2 == rhs.fac2);
	}
	int get1()const{
		return fac1;
	}
	int get2()const{
		return fac2;
	}
	int getDist() const{
		return dist;
	}
};

#endif // LINK_HPP_INCLUDED
