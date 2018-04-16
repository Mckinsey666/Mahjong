#ifndef  AIPLAYER_H
#define AIPLAYER_H
#include "MJplayer.h"
#include <string>
using namespace std;

class AIplayer : public MJplayer {
public:
	AIplayer() { ++ct; _name = "AI player " + to_string(ct);
	for (int i = 1; i <= 9; ++i)
		for (int j = 1; j <= 4; ++j)
			tiles[i][j] = 4;
	}
	~AIplayer(){}
	void strategy(int position, MJtile t, int&, int&);
	/*void clear_tiles() {
		for (int i = 1; i <= 9; ++i)
			for (int j = 1; j <= 4; ++j)
				tiles[i][j] = 4;
	}*/
	void getinfo(int position, int type, MJtile* ts, int tiles_num);
	/*void to_ting() { ; }*/
private:
	static int ct;
	int tiles[10][5];
};
#endif // ! AIPLAYER_H
