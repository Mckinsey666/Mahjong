#include "stdafx.h"
#include "MJplayer.h"
#include <cstring>
#include <iostream>

using namespace std;

int MJplayer::find_angone(MJtile tile) {
	for (int i = _hand._faceup_len; i < _hand._total_len + _hand._stage; ++i)
		if (_hand._tiles[i] == tile) return i - _hand._faceup_len + 1;
}

int MJplayer::find_bugone(MJtile tile) {
	for (int i = _hand._faceup_len; i < _hand._total_len + _hand._stage; ++i)
		if (_hand._tiles[i] == tile) return i - _hand._faceup_len + 1;
}

void MJplayer::showhand() const {
	MJhand toshow;
	int l = _hand.faceup_len();
	int t = _hand.total_len();
	toshow.set_faceup(l);
	toshow.set_len(t);
	if (_hand.stage() == 1)
		toshow.set_stage(1);
	for (int i = 0; i < l; ++i) {
		if (_hand.invisible[i]) toshow._tiles[i].setfromId(-1);
		else toshow._tiles[i] = _hand._tiles[i];
	}
	for (int i = l; i < t+_hand.stage(); ++i)
		toshow._tiles[i].setfromId(-1);
	cout << toshow;
}