#pragma once
#ifndef MJCOLLECTION
#define MJCOLLECTION
#include "MJtile.h"
#include "Shuffler.h"
#include <cstdlib>
#include <algorithm>
using namespace  std;
class MJcollection {
	friend class MJstage;
	friend class MJplayer;
public:
	MJcollection() {
		Shuffler s;
		s.init(); s.fill(_t);
		_frontind = 0; _backind = 143;
	}
	~MJcollection() {}

	int frontind() const {return _frontind;}
	int backind() const {return _backind;}
	int size() const {return _backind - _frontind + 1;}

	bool checkduplicate() const {
		for (int i = 0; i < 144; ++i)
			for (int j = i + 1; j < 144; ++j)
				if (_t[i].getTileId() == _t[j].getTileId())
					return false;
		return true;
	}
	void shuffle() {
		int a, b;
		for (int i = 0; i < 100; ++i) {
			a = rand() % 144; b = rand() % 144;
			swap(_t[a], _t[b]);
		}
	}

	MJtile drawfronttile() const {return _t[_frontind++];}
	MJtile drawbacktile() const {return _t[_backind--];}
	MJtile front() const { return _t[_frontind]; }
	MJtile back() const { return _t[_backind]; }
private:
	MJtile _t[144];
	mutable int _frontind;
	mutable int _backind;
};
#endif
