#include "stdafx.h"
#include <iostream>
#include <cmath>
#include "MJtile.h"
using namespace std;

ostream& operator << (ostream& output, const MJtile& m) {
	output << " __ \n";

	if (m.suit() < 4) {
		output << "|";
		switch (m.rank()) {
		case 1:output << "一"; break;
		case 2:output << "二"; break;
		case 3:output << "三"; break;
		case 4:output << "四"; break;
		case 5:output << "五"; break;
		case 6:output << "六"; break;
		case 7:output << "七"; break;
		case 8:output << "八"; break;
		case 9:output << "九"; break;
		}
		output<< "|\n";
		switch (m.suit()) {
		case 1: output << "|筒|\n"; break;
		case 2: output << "|條|\n"; break;
		case 3: output << "|萬|\n"; break;
		}
	}
	else {
		if (m.rank() < 8) {
			output << "|  |\n";
			switch (m.rank()) {
			case 1: output << "|東|\n"; break;
			case 2: output << "|南|\n"; break;
			case 3: output << "|西|\n"; break;
			case 4: output << "|北|\n"; break;
			case 5: output << "|中|\n"; break;
			case 6: output << "|發|\n"; break;
			case 7: output << "|  |\n"; break;
			}
		}
		else {
			output << "|";
			switch (m.flower()) {
			case 1:output << "一"; break;
			case 2:output << "二"; break;
			case 3:output << "三"; break;
			case 4:output << "四"; break;
			}
			output << "|\n";
			switch (m.getTileId()) {
			case 125: output << "|梅|\n"; break;
			case 126: output << "|蘭|\n"; break;
			case 127: output << "|竹|\n"; break;
			case 128: output << "|菊|\n"; break;
			case 141: output << "|春|\n"; break;
			case 142: output << "|夏|\n"; break;
			case 143: output << "|秋|\n"; break;
			case 144: output << "|冬|\n"; break;
			}
		}
	}
	output << " -- \n";
	return output;
}

MJtile::MJtile() { _tileId = 0; }

MJtile::~MJtile() {}

MJtile::MJtile(int id) {
	_tileId = id;
	if (id % 16 == 0)
		_suit = int(ceil(double(id % 16 + 16) / 4));
	else
		_suit = int(ceil(double(id % 16) / 4));

	_rank = int(ceil(double(id) / 16));

	if (((id >= 125) && (id <= 128)) || ((id >= 141)&&(id<=144)))
		_flowernum = (id - 1) % 4 + 1;
	else
		_flowernum = 0;
}

void MJtile::setfromId(int id) {
	MJtile new_tile(id);
	(*this) = new_tile;//Becomes another tile
	return;
}

int MJtile::suit() const {
	return _suit;
}

int MJtile::rank() const {
	return _rank;
}

int MJtile::flower() const {
	return _flowernum;
}

int MJtile::getTileId() const {
	return _tileId;
}

bool MJtile::operator==(const MJtile& m)const {
	return (_rank == m.rank() && _suit == m.suit());
}

bool MJtile::operator!=(const MJtile& m)const {
	return !((*this) == m);
}

bool MJtile::fromsuitrank(int a, int b) const {
	return (_suit == a&&_rank == b);
}
