#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "Shuffler.h"
#include "MJtile.h"
using namespace std;

void Shuffler::init() {
	srand(time(0));
	for (int i = 0; i < 144; ++i)
		random[i] = i + 1;
	for (int i = 0; i < 100; ++i){
		int a = rand() % 144, b = rand() % 144;
		swap(random[a], random[b]);
	}
}

void Shuffler::fill(MJtile mt[144]) {
	for (int i = 0; i < 144; ++i) {
		MJtile m(random[i]);
		mt[i] = m;
	}
}