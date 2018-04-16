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
		case 1:output << "�@"; break;
		case 2:output << "�G"; break;
		case 3:output << "�T"; break;
		case 4:output << "�|"; break;
		case 5:output << "��"; break;
		case 6:output << "��"; break;
		case 7:output << "�C"; break;
		case 8:output << "�K"; break;
		case 9:output << "�E"; break;
		}
		output<< "|\n";
		switch (m.suit()) {
		case 1: output << "|��|\n"; break;
		case 2: output << "|��|\n"; break;
		case 3: output << "|�U|\n"; break;
		}
	}
	else {
		if (m.rank() < 8) {
			output << "|  |\n";
			switch (m.rank()) {
			case 1: output << "|�F|\n"; break;
			case 2: output << "|�n|\n"; break;
			case 3: output << "|��|\n"; break;
			case 4: output << "|�_|\n"; break;
			case 5: output << "|��|\n"; break;
			case 6: output << "|�o|\n"; break;
			case 7: output << "|  |\n"; break;
			}
		}
		else {
			output << "|";
			switch (m.flower()) {
			case 1:output << "�@"; break;
			case 2:output << "�G"; break;
			case 3:output << "�T"; break;
			case 4:output << "�|"; break;
			}
			output << "|\n";
			switch (m.getTileId()) {
			case 125: output << "|��|\n"; break;
			case 126: output << "|��|\n"; break;
			case 127: output << "|��|\n"; break;
			case 128: output << "|��|\n"; break;
			case 141: output << "|�K|\n"; break;
			case 142: output << "|�L|\n"; break;
			case 143: output << "|��|\n"; break;
			case 144: output << "|�V|\n"; break;
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
