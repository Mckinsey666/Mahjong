#include "stdafx.h"
#include <iostream>
#include <cmath>
#include "MJtile.h"
using namespace std;

ostream& operator << (ostream& output, const MJtile& m) {
	output << " __ \n";

	if (m.suit() < 4) {
		output << "| " << m.rank() << "|\n";
		switch (m.suit()) {
		case 1: output << "| O|\n"; break;
		case 2: output << "| I|\n"; break;
		case 3: output << "| W|\n"; break;
		}
	}
	else {
		if (m.rank() < 8) {
			output << "|  |\n";
			switch (m.rank()) {
			case 1: output << "|Ea|\n"; break;
			case 2: output << "|So|\n"; break;
			case 3: output << "|We|\n"; break;
			case 4: output << "|No|\n"; break;
			case 5: output << "|Mi|\n"; break;
			case 6: output << "|Fa|\n"; break;
			case 7: output << "|  |\n"; break;
			}
		}
		else {
			output << "| " << m.flower() << "|\n";
			switch (m.getTileId()) {
			case 125: output << "|Me|\n"; break;
			case 126: output << "|La|\n"; break;
			case 127: output << "|Zu|\n"; break;
			case 128: output << "|Ju|\n"; break;
			case 141: output << "|Sp|\n"; break;
			case 142: output << "|Su|\n"; break;
			case 143: output << "|Au|\n"; break;
			case 144: output << "|Wi|\n"; break;
			}
		}
	}
	output << " -- \n";
	return output;
}
MJtile::MJtile() {}
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
