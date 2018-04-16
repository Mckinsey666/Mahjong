#ifndef MJHAND
#define MJHAND
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include "MJtile.h" 
#include "MJcollection.h"
using namespace std;


struct three {
	MJtile t[3];
};
struct four {
	MJtile t[4];
};

class MJhand{
	friend ostream& operator << (ostream&, const MJhand&);
	friend class MJplayer;
	friend class AIplayer;
	friend class humanplayer;
	friend class MJstage;
	friend class Cal;
public:
	MJhand();
	MJhand(MJtile*,int);
	~MJhand();
	
	int total_len() const { return _total_len; }
	int faceup_len() const { return _faceup_len; }
	bool stage() const { return _stage; }
//Valid plays
	int caneat(const MJtile&);
	bool canpong(const MJtile&);
	bool canminggone(const MJtile&);
	bool canangone(const MJtile&);
	bool canbugone(const MJtile&);
//Moves
	void arrange();
	void draw(MJcollection&);
	MJtile play(int);
	void faceup(int);
	void applique(int, MJcollection&);
	void initial(MJcollection&);
	void eat(const MJtile&, int);
	void pong(const MJtile&);
	void minggone(const MJtile&, MJcollection&);
	void angone(int, MJcollection&);
	void bugone(int, MJcollection&);
	
	void set_hand(MJtile* m, int n) {
		for (int i = 0; i < n; ++i)
			_tiles[i] = m[i];
	}
	void set_tile(MJtile tile, int i) { _tiles[i] = tile; }
	void set_len(int l) { _total_len = l; }
	void set_faceup(int l) { _faceup_len = l; }
	void reset_visible() { for (int i = 0; i < 30; ++i)invisible[i] = 0; }
	
//Hu-Related
	void huother(const MJtile&);
	void huown();
	void set_faceup_len(int f) { _faceup_len = f; }
	void set_stage(bool s) { _stage = s; }
	void print_sets() {
		cout << "Faceup area:\n";
		cout << "吃的順子:\n";
		for (int i = 0; i < faceupshun.size(); ++i) {
			cout << "============\n";
			for (int j = 0; j < 3; ++j)
				cout << faceupshun[i].t[j];
		}
		cout << '\n';
		cout << "碰的刻子:\n";
		for (int i = 0; i < faceupke.size(); ++i) {
			cout << "============\n";
			for (int j = 0; j < 3; ++j)
				cout << faceupke[i].t[j];
		}
		cout << '\n';
		cout << "槓:\n";
		for (int i = 0; i < faceupgone.size(); ++i) {
			cout << "============\n";
			for (int j = 0; j < 4; ++j)
				cout << faceupgone[i].t[j];
		}
		cout << '\n';
		cout << "HU area:\n";
		cout << "胡的時候的順子:\n";
		for (int i = 0; i < hushun.size(); ++i) {
			cout << "============\n";
			for (int j = 0; j < 3; ++j)
				cout << hushun[i].t[j];
		}
		cout << '\n';
		cout << "胡的時候的刻子:\n";
		for (int i = 0; i < huke.size(); ++i) {
			cout << "============\n";
			for (int j = 0; j < 3; ++j)
				cout << huke[i].t[j];
		}
		for (int i = 0; i < hugone.size(); ++i) {
			cout << "============\n";
			for (int j = 0; j < 4; ++j)
				cout << hugone[i].t[j];
		}
		cout << '\n';
		cout << "眼:\n";
		for (int i = 0; i < eye.size(); ++i)
			cout << eye[i];
	}
	

	bool canhu(const MJtile&);
	bool checkhu(int[9][4], vector<int>&, int);
	bool find_gone(int[9][4], int&, int&);
	bool find_pong(int[9][4], int&, int&);
	bool find_eat(int[9][4], int&, int&);
	bool full_set(int[9][4], int);

	bool canting();

//Utilizing
	void print() {
		for (int i = 1; i <= 9; ++i) {
			for (int j = 1; j <= 4; ++j)
				cout << eat_count[i][j] << ' ';
			cout << '\n';
		}
	}
private:
	int _total_len;
	int _faceup_len;
	int _stage;//0 normal stage, 1 draw stage
	MJtile _tiles[30];//total 17 tiles, at most 30 = 17+8+5
	int eat_count[10][5];
	bool invisible[30];
	vector<MJtile>eye;
	vector<three>faceupke;
	vector<three>faceupshun;
	vector<four>faceupgone;
	vector<three>huke;
	vector<three>hushun;
	vector<four>hugone;
}; 
#endif
