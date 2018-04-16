#include "stdafx.h"
#include <iostream> 
#include <algorithm>
#include <cmath>
#include <cassert>
#include <cstring>
#include "MJhand.h"
#include <vector>

using namespace std;


bool MJcompare(const MJtile& i, const MJtile& j) {
	if (i.suit() < j.suit())
		return true;
	else if (i.suit() == j.suit())
		return i.getTileId() < j.getTileId();
	return false;
}
void MJhand::arrange() {
	sort(_tiles + _faceup_len, _tiles + _total_len + _stage, MJcompare);
}

MJhand::MJhand() {
	_total_len = _faceup_len = _stage = 0;
	memset(invisible, 0, sizeof(invisible));
	memset(eat_count, 0, sizeof(eat_count));
}
MJhand::MJhand(MJtile* t, int n) {
	_total_len = n;
	_faceup_len = _stage = 0;
	memset(eat_count, 0, sizeof(eat_count));
	for (int i = 0; i < n; ++i) {
		_tiles[i] = t[i];
		eat_count[t[i].rank()][t[i].suit()]++;
	}
}
MJhand::~MJhand() {
}

//Valid play checks
int MJhand::caneat(const MJtile& t) {
	//can't eat fong and flower
	if (t.suit() == 4)
		return 0;
	int x = t.rank(), y = t.suit();
	int a = 0, b = 0, c = 0, d = 0;
	for (int i = _faceup_len; i < _total_len+_stage; ++i)
		if (_tiles[i].suit() == t.suit()) {
			if (_tiles[i].rank() == x - 2)
				a = 1;
			else if (_tiles[i].rank() == x - 1)
				b = 1;
			else if (_tiles[i].rank() == x + 1)
				c = 1;
			else if (_tiles[i].rank() == x + 2)
				d = 1;
		}
	return 1 * (a&&b) + 2 * (b&&c) + 4 * (c&&d);
}
bool MJhand::canpong(const MJtile& t) {
	//can't pong flower
	if (t.flower())
		return false;
	int ct = 0;
	for (int i = _faceup_len; i < _total_len+_stage; ++i)
		if (_tiles[i] == t)
			ct++;
	return (ct >= 2);
}
bool MJhand::canminggone(const MJtile& t) {
	if (t.flower()) return false;
	int ct = 0;
	for (int i = _faceup_len; i < _total_len + _stage; ++i)
		if (_tiles[i] == t)
			ct++;
	return (ct == 3);
}
bool MJhand::canangone(const MJtile& t) {
	if (t.flower()) return false;
	int ct = 0;
	//to _total_len!!
	for (int i = _faceup_len; i < _total_len + _stage; ++i)
		if (_tiles[i] == t)
			ct++;
	return (ct == 4);
}
bool MJhand::canbugone(const MJtile& t) {
	if (t.flower()) return false;
	int ct = 0;
	for (int i = 0; i < _faceup_len; ++i)
		if (_tiles[i] == t)
			ct++;
	return (ct == 3);
}
void MJhand::draw(MJcollection& mjc) {
	if (mjc.frontind() <= mjc.backind()) {
		_tiles[_total_len] = mjc.drawfronttile();
		_stage = 1;
		applique(_total_len + _stage - 1, mjc);
	}
	return;
}

//Player moves
MJtile MJhand::play(int index) {
	int returnid = 0;
	if (index + _faceup_len <= _total_len + _stage && index > 0) {
		returnid = _tiles[_faceup_len + index - 1].getTileId();
		for (int i = _faceup_len + index - 1; i < _total_len; i++)
			_tiles[i] = _tiles[i + 1];
		_stage = 0;
		arrange();
	}
	return MJtile(returnid);
}
void MJhand::faceup(int index) {
	swap(_tiles[_faceup_len], _tiles[index]);
	_faceup_len++;
	arrange();
}
void MJhand::applique(int index, MJcollection& mjc) {
	if(_tiles[index].flower()) {
		faceup(index);
		_tiles[_total_len + _stage] = mjc.drawbacktile();
		_total_len++;
		applique(_total_len + _stage - 1, mjc);
	}
	return;
}
void MJhand::initial(MJcollection& mjc) {
	arrange();
	for (int pos = _faceup_len; pos < _total_len + _stage; pos++)
		applique(pos, mjc);
	arrange();
}
void MJhand::pong(const MJtile& t) {
	if (canpong(t)) {
		_tiles[_total_len] = t;
		_stage = 1;
		arrange();
		for (int i = 0; i < 3; ++i) {
			for (int j = _faceup_len; j < _total_len + _stage; ++j)
				if (_tiles[j] == t) {
					faceup(j);
					break;
				}
		}
		three pongtile;
		for (int i = 0; i < 3; ++i)
			pongtile.t[i] = t;
		faceupke.push_back(pongtile);
	}
	return;
}
void MJhand::eat(const MJtile& t, int n) {
	MJtile temp = t; int r = t.rank(); int s = t.suit();
	if (n > 3)
		return;
	int k = caneat(t);
	//cout << "eat: " << caneat(t) << '\n';
	int check[3] = {};
	for (int i = 0; i < 3; ++i) {
		check[i] = k % 2;
		k /= 2;
	}

	int method;
	if (check[0] + check[1] + check[2] == 1) {
		for (int i = 0; i < 3; ++i)
			if (check[i] == 1)
				method = i + 1;
	}
	else if (check[n - 1] == 1)
		method = n;
	else return;

	_tiles[_total_len] = t;
	_stage = 1;
	arrange();

	switch (method) {
	case 1: {
		three eattile;
		eattile.t[2] = t;

		temp.setfromId(t.getTileId() - 16);
		eattile.t[1] = temp;

		temp.setfromId(t.getTileId() - 32);
		eattile.t[0] = temp;
		faceupshun.push_back(eattile);

		for (int i = _faceup_len;; ++i)
			if ((_tiles[i].suit() == s) && _tiles[i].rank() == r - 2) {
				faceup(i);
				break;
			}
		for (int i = _faceup_len;; ++i)
			if ((_tiles[i].suit() == s) && _tiles[i].rank() == r) {
				faceup(i);
				break;
			}
		for (int i = _faceup_len;; ++i)
			if ((_tiles[i].suit() == s) && _tiles[i].rank() == r - 1) {
				faceup(i);
				break;
			}
	}break;
	case 2: {
		three eattile;
		temp.setfromId(t.getTileId() - 16);
		eattile.t[0] = temp;

		eattile.t[1] = t;

		temp.setfromId(t.getTileId() + 16);
		eattile.t[2] = temp;
		faceupshun.push_back(eattile);
		for (int i = _faceup_len;; ++i)
			if ((_tiles[i].suit() == s) && _tiles[i].rank() == r - 1) {
				faceup(i);
				break;
			}
		for (int i = _faceup_len;; ++i)
			if ((_tiles[i].suit() == s) && _tiles[i].rank() == r) {
				faceup(i);
				break;
			}
		for (int i = _faceup_len;; ++i)
			if ((_tiles[i].suit() == s) && _tiles[i].rank() == r + 1) {
				faceup(i);
				break;
			}
	}break;
	case 3: {
		three eattile;
		eattile.t[0] = t;

		temp.setfromId(t.getTileId() + 16);
		eattile.t[1] = temp;

		temp.setfromId(t.getTileId() + 32);
		eattile.t[2] = temp;
		faceupshun.push_back(eattile);

		for (int i = _faceup_len;; ++i)
			if ((_tiles[i].suit() == s) && _tiles[i].rank() == r + 1) {
				faceup(i);
				break;
			}
		for (int i = _faceup_len;; ++i)
			if ((_tiles[i].suit() == s) && _tiles[i].rank() == r) {
				faceup(i);
				break;
			}
		for (int i = _faceup_len;; ++i)
			if ((_tiles[i].suit() == s) && _tiles[i].rank() == r + 2) {
				faceup(i);
				break;
			}
	}break;
		return;
	}
}
void MJhand::minggone(const MJtile& t, MJcollection& mjc) {
	if (canminggone(t)) {
		_tiles[_total_len] = t;
		_stage = 1;
		arrange();
		for (int i = 0; i < 4; ++i) {
			for (int j = _faceup_len; j < _total_len + _stage; ++j) {
				if (_tiles[j] == t) {
					faceup(j);
					break;
				}
			}
		}
		arrange();

		_tiles[_total_len + _stage] = mjc.drawbacktile();
		_total_len++;
		applique(_total_len + _stage - 1, mjc);

		four gone;
		for (int i = 0; i < 4; ++i)
			gone.t[i] = t;
		faceupgone.push_back(gone);
	}
	return;
}
void MJhand::angone(int ind, MJcollection& mjc) {
	MJtile t = _tiles[_faceup_len + ind - 1];
	if (canangone(t)) {
		for (int x = 0; x<4; x++) {
			for (int i = _faceup_len; i<_total_len + _stage; i++) {
				if (_tiles[i] == t) {
					faceup(i);
					break;
				}
			}
		}
		for (int i = 1; i <= 4; ++i)invisible[_faceup_len - i] = 1;
		//_stage=1;
		_tiles[_total_len + _stage] = mjc.drawbacktile();
		_total_len++;
		applique(_total_len + _stage - 1, mjc);

		four gone;
		for (int i = 0; i < 4; ++i)
			gone.t[i] = t;
		faceupgone.push_back(gone);
	}
	return;
}
void MJhand::bugone(int index, MJcollection& mjc) {

	MJtile t = _tiles[index + _faceup_len - 1];
	if (canbugone(t)) {
		faceup(index + _faceup_len - 1);
		int i = _faceup_len - 1;
		while (_tiles[i - 1] != t) {
			swap(_tiles[i], _tiles[i - 1]);
			i--;
		}
		arrange();

		_tiles[_total_len + _stage] = mjc.drawbacktile();
		_total_len++;
		applique(_total_len + _stage - 1, mjc);

		for (int i = 0; i < faceupke.size(); ++i)
			if (faceupke[i].t[0] == t) {
				faceupke.erase(faceupke.begin() + i);
				break;
			}
		four gone;
		for (int i = 0; i < 4; ++i)
			gone.t[i] = t;
		faceupgone.push_back(gone);
	}
}

//HU
void MJhand::huother(const MJtile& t) {
	//TO call after other players play. current stage=0
	_tiles[_total_len + _stage] = t;
	_stage = 0; _total_len++;
	arrange();
}
void MJhand::huown() {
	//TO call after draw, _stage=1->0
	_stage = 0; _total_len++;
	arrange();
}
bool MJhand::canhu(const MJtile& t) {
	huke.clear();
	hushun.clear();
	hugone.clear();
	eye.clear();


	if (t.flower())return false;
	int check[9][4] = {};
	int not_flower = 1;
	check[t.rank() - 1][t.suit() - 1]++;
	for (int i = _faceup_len; i < _total_len; ++i)
		if (!_tiles[i].flower()) {
			check[_tiles[i].rank() - 1][_tiles[i].suit() - 1]++;
			not_flower++;
		}
	vector<int> used(not_flower, 0);
	return checkhu(check, used, used.size());
}

//Utility functions to facilitate hu process
bool MJhand::find_pong(int check[9][4], int& x, int& y) {
	for (x = 0; x < 9; ++x)
		for (y = 0; y < 4; ++y)
			if (!((y == 3) && (x == 7 || x == 8)))
				if (check[x][y] >= 3)
					return true;
	return false;
}
bool MJhand::find_gone(int check[9][4], int& x, int& y) {
	for (x = 0; x < 9; ++x)
		for (y = 0; y < 4; ++y)
			if (!((y == 3) && (x == 7 || x == 8)))
				if (check[x][y] == 4)
					return true;
	return false;
}
bool MJhand::find_eat(int check[9][4], int& x, int& y) {
	for (x = 0; x < 7; ++x)
		for (y = 0; y < 3; ++y)
			if (y!=3)
				if (check[x][y] * check[x + 1][y] * check[x + 2][y] > 0)
					return true;
	return false;
}
bool MJhand::full_set(int check[9][4], int len) {
	MJtile tile;
	if (len == 0)
		return true;
	int x, y;
	if (find_pong(check, x, y)) {
		tile.setfromId(4 * (4 * x + y + 1));
		three huthree;
		for (int i = 0; i < 3; ++i)
			huthree.t[i] = tile;
		check[x][y] -= 3; len -= 3;
		huke.push_back(huthree);
		if (full_set(check,len))
			return true;
		check[x][y] += 3; len += 3;
		huke.pop_back();
	}
	
	if (find_gone(check, x, y)) {
		tile.setfromId(4 * (4 * x + y + 1));
		four hufour;
		for (int i = 0; i < 4; ++i)
			hufour.t[i] = tile;
		check[x][y] -= 3; len -= 3;
		hugone.push_back(hufour);
		check[x][y] -= 4; len -= 4;
		if (full_set(check, len))
			return true;
		check[x][y] += 4; len += 4;
		hugone.pop_back();
	}

	if (find_eat(check, x, y)) {
		tile.setfromId(4 * (4 * x + y + 1));
		three huthree;
		huthree.t[0] = tile;
		tile.setfromId(4 * (4 * (x+1) + y + 1));
		huthree.t[1] = tile;
		tile.setfromId(4 * (4 * (x+2) + y + 1));
		huthree.t[2] = tile;
		hushun.push_back(huthree);
		check[x][y] --; check[x + 1][y] --; check[x + 2][y] --; len -= 3;
		if (full_set(check,len))
			return true;
		check[x][y] ++; check[x + 1][y] ++; check[x + 2][y] ++; len += 3;
		hushun.pop_back();
	}
	return false;
}
bool MJhand::checkhu(int check[9][4], vector<int>&used,int len) {
	int pairs[20][2] = {};
	memset(pairs, -1, sizeof(pairs));
	int k = 0;
	for (int i = 0; i < 9; ++i)
		for (int j = 0; j < 4; ++j) {
			if (check[i][j] >= 2) {
				pairs[k][0] = i;
				pairs[k++][1] = j;
			}
		}
//No pairs;
	if (pairs[0][0] < 0)
		return false;
//Recursively enumerate every pair and corresponding 3-tile sets
	for (int i = 0; i < k; ++i) {
		MJtile tile(4 * (4 * pairs[i][0] + pairs[i][1] + 1));
		check[pairs[i][0]][pairs[i][1]] -= 2; len -= 2;
		eye.push_back(tile); eye.push_back(tile);
		if (full_set(check,len))
			return true;
		check[pairs[i][0]][pairs[i][1]] += 2; len += 2;
		eye.clear();
	}
	return false;
}

bool MJhand::canting() {
	for (int i = 1; i <= 36; ++i) {
		MJtile t(4 * i);
		if (canhu(t))
			return true;
	}
	return false;
}

ostream& operator << (ostream& os, const MJhand& h) {

	//part 1 " __ "
	for (int i = 0; i<h._total_len + h._stage; i++) {
		if (i == h.faceup_len())
			os << "    ";//4 spaces
		if (h._stage && i == h._total_len + h._stage - 1)
			os << "    ";//4 spaces
		os << " __ ";
	}
	os << endl;

	//part 2 "| N|"
	for (int i = 0; i<h._total_len + h._stage; i++) {
		if (i == h.faceup_len())
			os << "    ";//4 spaces
		if (h._stage && i == h._total_len + h._stage - 1)
			os << "    ";//4 spaces
		os << "|";

		if (h._tiles[i].getTileId() == -1)
			os << "█";
		else if (h._tiles[i].suit() == 4) {
			if (h._tiles[i].flower())
				os << " " << h._tiles[i].flower();
			else
				os << "  ";
		}
		else {
			switch (h._tiles[i].rank()) {
			case 1:
				os << "一";
				break;
			case 2:
				os << "二";
				break;
			case 3:
				os << "三";
				break;
			case 4:
				os << "四";
				break;
			case 5:
				os << "五";
				break;
			case 6:
				os << "六";
				break;
			case 7:
				os << "七";
				break;
			case 8:
				os << "八";
				break;
			case 9:
				os << "九";
				break;
			default:
				assert(false);
			}
		}
		os << "|";
	}
	os << endl;

	//part 3 "|XX|"
	for (int i = 0; i<h._total_len + h._stage; i++) {
		if (i == h.faceup_len())
			os << "    ";//4 spaces
		if (h._stage && i == h._total_len + h._stage - 1)
			os << "    ";//4 spaces
		os << "|";

		if (h._tiles[i].getTileId() == -1)
			os << "█";
		else if (h._tiles[i].suit() == 4)
			switch (h._tiles[i].rank()) {
			case 1:
				os << "東";
				break;
			case 2:
				os << "南";
				break;
			case 3:
				os << "西";
				break;
			case 4:
				os << "北";
				break;
			case 5:
				os << "中";
				break;
			case 6:
				os << "發";
				break;
			case 7:
				os << "  ";
				break;
			case 8:
				switch (h._tiles[i].flower()) {
				case 1:
					os << "梅";
					break;
				case 2:
					os << "蘭";
					break;
				case 3:
					os << "竹";
					break;
				case 4:
					os << "菊";
					break;
				default:
					assert(false);
				}
				break;
			case 9:
				switch (h._tiles[i].flower()) {
				case 1:
					os << "春";
					break;
				case 2:
					os << "夏";
					break;
				case 3:
					os << "秋";
					break;
				case 4:
					os << "冬";
					break;
				default:
					assert(false);
				}
				break;
			default:
				assert(false);
			}
		else {
			switch (h._tiles[i].suit()) {
			case 1:
				os << "筒";
				break;
			case 2:
				os << "條";
				break;
			case 3:
				os << "萬";
				break;
			default:
				assert(false);
			}
		}
		os << "|";
	}
	os << endl;

	//part 4 " -- "
	for (int i = 0; i<h._total_len + h._stage; i++) {
		if (i == h.faceup_len())
			os << "    ";//4 spaces
		if (h._stage && i == h._total_len + h._stage - 1)
			os << "    ";//4 spaces
		os << " -- ";
	}
	os << endl;
	return os;
}