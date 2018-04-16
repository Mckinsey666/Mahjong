#pragma once
#ifndef SHUFFLER_H
#define SHUFFLER_H
#include "stdafx.h"
#include "MJtile.h"
using namespace std;

class Shuffler {
public:
	Shuffler() {};
	~Shuffler() {};	
	void init();
	void fill(MJtile[144]);
private:
	int random[144];
};
#endif