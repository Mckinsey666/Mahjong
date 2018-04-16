#ifndef  MJPLAYER_H
#define MJPLAYER_H
#include "stdafx.h"
#include <iostream>
#include "MJhand.h"
#include "MJtile.h"
#include "Cal.h"
#include <string>
#include <cstring>

using namespace std;

class MJplayer {
public:
	MJplayer() { dealer = _ting = _money = 0; };
	~MJplayer() {};

	int Get_Pos() const { return _position; }
	int getmoney()const { return _money; }
	void showhand()const;

	int find_angone(MJtile);
	int find_bugone(MJtile);

	virtual void strategy(int position, MJtile t, int&, int&) = 0;
	virtual void getinfo(int position, int type, MJtile* ts, int tiles_num) = 0;
	virtual void to_ting() = 0;

	void set_position(int p) { _position = p; }
	virtual void clear_tiles() = 0;
	
	bool is_dealer() { return dealer; }
	bool tinged() { return _ting; }
	void set_dealer(int n) { dealer = n; }
	void set_ting(int i) { _ting = i; }
	void clear_sets() {
		_hand.huke.clear();
		_hand.hushun.clear();
		_hand.hugone.clear();
		_hand.faceupke.clear();
		_hand.faceupshun.clear();
		_hand.faceupgone.clear();
		_hand.eye.clear();
	}
	void setmoney(int m) { _money += m; }
	string name() { return _name; }

	MJhand& get_hand() { return _hand; }
	MJtile last() { return _hand._tiles[_hand._total_len + _hand._stage - 1]; }
protected:
	string _name;
	MJhand _hand;
	int _position;//east = 1 ,south = 2 , west = 3 , north = 4 
	double _money;
	int dealer;
	int _ting;
};
#endif
