#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "MJplayer.h"
#include <string>
using namespace std;

class humanplayer : public MJplayer {
public:
	humanplayer(const string s) { _name = s; for (int i = 1; i <= 9; ++i)
		for (int j = 1; j <= 4; ++j)
			tiles[i][j] = 4;
	}
	~humanplayer() {}
	void strategy(int pos, MJtile tile, int& action, int& par);
	void clear_tiles() {
		for (int i = 1; i <= 9; ++i)
			for (int j = 1; j <= 4; ++j)
				tiles[i][j] = 4;
	}
	void getinfo(int position, int type, MJtile* ts, int tiles_num) { ; }
	void to_ting(){
		if (_hand.canting() && !tinged()) {
			cout << name() << ", you can Å¥µP. Press 'y' to Å¥µP:\n";
			char c; cin >> c;
			switch (c) {
			case 'y': _ting = 1; break;
			default: break;
			}
		}
	}
private:
	int tiles[10][5];
};
#endif // !HUMANPLAYER_H
