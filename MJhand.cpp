#include "stdafx.h"
#include <iostream> 
#include <algorithm>
#include <cmath>
#include <cassert>
#include <cstring>
#include "MJhand.h"
using namespace std;


bool MJcompare(const MJtile& i, const MJtile& j) {
	if (i.suit() < j.suit())
		return true;
	else if (i.suit() == j.suit())
		return i.getTileId() < j.getTileId();
	return false;
}

void MJhand::arrange() {
	sort(_tiles + _faceup_len, _tiles + _total_len, MJcompare);
}

MJhand::MJhand() {
	_total_len = _faceup_len = _stage = 0;
	memset(tile_count, 0, sizeof(tile_count));
	memset(eat_count, 0, sizeof(eat_count));
	memset(tile_map, 0, sizeof(tile_map));
}

MJhand::MJhand(MJtile* t, int n) {
	_total_len = n;
	_faceup_len = _stage = 0;
	memset(tile_count, 0, sizeof(tile_count));
	memset(eat_count, 0, sizeof(eat_count));
	memset(tile_map, 0, sizeof(tile_map));

	for (int i = 0; i < n; ++i) {
		_tiles[i] = t[i];
		tile_count[int(ceil(double(t[i].getTileId()) / 4))]++;
		eat_count[t[i].rank()][t[i].suit()]++;
		tile_map[(t[i].getTileId() - 1) / 16][(t[i].getTileId() - 1) % 16] = 1;
	}
}

MJhand::~MJhand() {
}

int MJhand::faceup_len() const {
	return _faceup_len;
}

int MJhand::caneat(const MJtile& t) {
	//can't eat fong and flower
	if (t.suit() == 4)
		return 0;
	int x = t.rank(), y = t.suit();
	int a = 0, b = 0, c = 0, d = 0;
	int eat = 0;
	int i;
	for (i = _faceup_len; i < _total_len; ++i)
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

	if (a == 1 && b == 1)
		eat += 1;
	if (b == 1 && c == 1)
		eat += 2;
	if (c == 1 && d == 1)
		eat += 4;
	
	/*if (x + 2 < 10)
		if (eat_count[x+1][y] * eat_count[x+2][y] > 0)
			eat += 4;
	if (x - 2 > 0)
		if (eat_count[x-1][y] * eat_count[x-2][y] > 0)
			eat += 1;
	if (x - 1 > 0 && y + 1 < 10)
		if (eat_count[x-1][y] * eat_count[x+1][y] > 0)
			eat += 2;*/
	return eat;
}

bool MJhand::canpong(const MJtile& t){
	//can't pong flower
	if (t.suit() == 4 && (t.rank() == 8 || t.rank() == 9))
		return false;
	int ct = 0;
	for (int i = _faceup_len; i < _total_len; ++i)
		if (_tiles[i].fromsuitrank(t.suit(), t.rank()))
			ct++;
	return (ct >= 2);
}

bool MJhand::cangone(const MJtile& t){
	//can't gone flower
	if (t.suit() == 4 && (t.rank() == 8 || t.rank() == 9))
		return false;
	int ct = 0;
	for (int i = _faceup_len; i < _total_len; ++i)
		if (_tiles[i].fromsuitrank(t.suit(), t.rank()))
			ct++;
	return (ct == 3);
}



void MJhand::draw(MJtile* mjtiles, int& frontind, int& backind){
	_tiles[_total_len] = mjtiles[frontind++];
	while (_tiles[_total_len].flower()) {
		applique(_total_len - _faceup_len + 1, mjtiles, frontind, backind);
	}
	
	_stage = 1;
	/*tile_count[int(ceil(double(t.getTileId()) / 4))]++;
	eat_count[t.rank()][t.suit()]++;
	tile_map[(t.getTileId() - 1) / 16][(t.getTileId() - 1) % 16] = 1;*/
	/*_tiles[_total_len] = mjtiles[frontind];
	frontind++;
	while (_tiles[_total_len].flower() > 0) {
		applique(_total_len - _faceup_len, mjtiles, frontind, backind);
	}

	_stage = 1;*/
	return;
}

MJtile MJhand::play(int index){
	arrange();
	MJtile t = _tiles[index + _faceup_len - 1];
	for (int i = index + _faceup_len - 1; i < _total_len && i < 29;i++) {
		_tiles[i] = _tiles[i + 1];
	}

	if (_total_len == 30)
		_tiles[29] = MJtile();
	/*tile_count[int(ceil(double(t.getTileId()) / 4))]--;
	eat_count[t.rank()][t.suit()]--;
	tile_map[(t.getTileId() - 1) / 16][(t.getTileId() - 1) % 16] = 0;*/
	arrange();
	_stage = 0;
	return t;
}

void MJhand::faceup(int index){
	swap(_tiles[_faceup_len], _tiles[index+_faceup_len-1]);
	_faceup_len++;
	arrange();
}

void MJhand::applique(int index, MJtile* mjtiles, int& frontind, int& backind){
	if (_tiles[index + _faceup_len-1].flower()) {
		faceup(index);
		_tiles[++_total_len] = mjtiles[backind--];
	}
	/*if (_tiles[index + _faceup_len ].flower() > 0) {
		MJtile tmp = _tiles[index + _faceup_len];
		for (int i = 0; i < index + _faceup_len - 1; i++) {
			_tiles[i + 1] = _tiles[i];
		}
		_tiles[0] = tmp;
		_tiles[_total_len] = mjtiles[backind];
		backind--;
		_total_len++;
		_faceup_len++;
	}*/
	return;
}

void MJhand::initial(MJtile* mjtiles, int& frontind, int& backind){
	arrange();
	_total_len--;
	for (int i = _faceup_len; i <= _total_len+1; i++) {
		applique(i - _faceup_len, mjtiles, frontind, backind);
	}
	_total_len++;
	arrange();
	
	/*arrange();
	for (int i = _faceup_len; i < _total_len; i++) {
		applique(i - _faceup_len + 1, mjtiles, frontind, backind);
	}
	arrange();*/
}


void MJhand::pong(const MJtile& t) {
	if (canpong(t)) {
		//tile_count[(int)ceil(double(t.getTileId()) / 4)] -= 2;
		//eat_count[t.rank()][t.suit()] -= 2;

		int index;
		for (index = 0;; ++index)
			if (_tiles[index + _faceup_len].fromsuitrank(t.suit(),t.rank()))
				break;
		index++;

		faceup(index);
		//Drawn tile is in the middle
		_tiles[_total_len++] = t;
		arrange();
		faceup(index); faceup(index);
		_total_len--;
		//_total len doesn't change
		_stage = 1;
	}
	return;
}

/*
ostream& operator << (ostream& os, const MJhand& h){
	
	//part 1 " __ "
	for(int i=0;i<h._total_len+h._stage;i++){
		if(i==h.faceup_len())
			os<<"    ";//4 spaces
		if(h._stage && i==h._total_len+h._stage-1)
			os<<"    ";//4 spaces
		os<<" __ ";
	}
	os<<endl;
	
	//part 2 "| N|"
	for(int i=0;i<h._total_len+h._stage;i++){
		if(i==h.faceup_len())
			os<<"    ";//4 spaces
		if(h._stage && i==h._total_len+h._stage-1)
			os<<"    ";//4 spaces
		os<<"|";
		if(h._tiles[i].suit()==4){ 
			if(h._tiles[i].flower())
				os<<" "<<h._tiles[i].flower();
			else 
				os<<"  ";
		} 
		else{
			switch(h._tiles[i].rank()){
				case 1:
					os<<"一";
					break; 
				case 2:
					os<<"二";
					break; 
				case 3:
					os<<"三";
					break; 
				case 4:
					os<<"四";
					break; 
				case 5:
					os<<"五";
					break; 
				case 6:
					os<<"六";
					break; 
				case 7:
					os<<"七";
					break; 
				case 8:
					os<<"八";
					break; 
				case 9:
					os<<"九";
					break; 
				default:
					assert(false); 
			}
		} 
		os<<"|";
	}
	os<<endl;
	
	//part 3 "|XX|"
	for(int i=0;i<h._total_len+h._stage;i++){
		if(i==h.faceup_len())
			os<<"    ";//4 spaces
		if(h._stage && i==h._total_len+h._stage-1)
			os<<"    ";//4 spaces
		os<<"|";
		if(h._tiles[i].suit()==4)
			switch(h._tiles[i].rank()){
				case 1:
					os<<"東";
					break; 
				case 2:
					os<<"南";
					break; 
				case 3:
					os<<"西";
					break; 
				case 4:
					os<<"北";
					break; 
				case 5:
					os<<"中";
					break; 
				case 6:
					os<<"發";
					break; 
				case 7:
					os<<"  ";
					break; 
				case 8:
					switch(h._tiles[i].flower()){
						case 1:
							os<<"梅";
							break; 
						case 2:
							os<<"蘭";
							break; 
						case 3:
							os<<"竹";
							break; 
						case 4:
							os<<"菊";
							break; 
						default:
							assert(false); 
					} 
					break; 
				case 9:
					switch(h._tiles[i].flower()){
						case 1:
							os<<"春";
							break; 
						case 2:
							os<<"夏";
							break; 
						case 3:
							os<<"秋";
							break; 
						case 4:
							os<<"冬";
							break; 
						default:
							assert(false); 
					} 
					break; 
				default:
					assert(false); 
			}
		else{
			switch(h._tiles[i].suit()){
				case 1:
					os<<"筒";
					break; 
				case 2:
					os<<"條";
					break; 
				case 3:
					os<<"萬";
					break; 
				default:
					assert(false); 
			}
		} 
		os<<"|";
	}
	os<<endl;
	
	//part 4 " -- "
	for(int i=0;i<h._total_len+h._stage;i++){
		if(i==h.faceup_len())
			os<<"    ";//4 spaces
		if(h._stage && i==h._total_len+h._stage-1)
			os<<"    ";//4 spaces
		os<<" ￣ ";
	}
	os<<endl; 
	return os;
} 
//*/

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
		if (h._tiles[i].suit() == 4) {
			if (h._tiles[i].flower())
				os << " " << h._tiles[i].flower();
			else
				os << "  ";
		}
		else {
			switch (h._tiles[i].rank()) {
			case 1:
				os << " 1";
				break;
			case 2:
				os << " 2";
				break;
			case 3:
				os << " 3";
				break;
			case 4:
				os << " 4";
				break;
			case 5:
				os << " 5";
				break;
			case 6:
				os << " 6";
				break;
			case 7:
				os << " 7";
				break;
			case 8:
				os << " 8";
				break;
			case 9:
				os << " 9";
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
		if (h._tiles[i].suit() == 4)
			switch (h._tiles[i].rank()) {
			case 1:
				os << "Ea";
				break;
			case 2:
				os << "So";
				break;
			case 3:
				os << "We";
				break;
			case 4:
				os << "No";
				break;
			case 5:
				os << "Mi";
				break;
			case 6:
				os << "Fa";
				break;
			case 7:
				os << "  ";
				break;
			case 8:
				switch (h._tiles[i].flower()) {
				case 1:
					os << "Me";
					break;
				case 2:
					os << "La";
					break;
				case 3:
					os << "Zu";
					break;
				case 4:
					os << "Ju";
					break;
				default:
					assert(false);
				}
				break;
			case 9:
				switch (h._tiles[i].flower()) {
				case 1:
					os << "Sp";
					break;
				case 2:
					os << "Su";
					break;
				case 3:
					os << "Au";
					break;
				case 4:
					os << "Wi";
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
				os << " O";
				break;
			case 2:
				os << " I";
				break;
			case 3:
				os << " W";
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
