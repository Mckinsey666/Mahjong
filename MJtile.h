#pragma once
#ifndef MJTILE_H
#define MJTILE_H
#include "stdafx.h"
#include <iostream>
using namespace std;

class MJtile {
	friend ostream& operator << (ostream&, const MJtile&);
public:
	MJtile();
	MJtile(int);
	~MJtile();
	int suit() const;
	int rank() const;
	int flower() const;
	int getTileId() const;
	bool operator == (const MJtile&) const;
	bool operator != (const MJtile&) const;
	bool fromsuitrank(int, int) const;
	void setfromId(int);//Change current ID to another ID
private:
	int _suit;
	int _rank;
	int _flowernum;
	int _tileId;
};
#endif