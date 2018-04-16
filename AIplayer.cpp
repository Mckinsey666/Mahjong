#include "stdafx.h"
#include "AIplayer.h"
#include <cstdlib>
#include <vector>
#include <algorithm>
int AIplayer::ct = 0;

void AIplayer::strategy(int pos, MJtile tile, int& action, int& par) {
	//To play
	//print();

	int map[10][5]; memset(map, 0, sizeof(map));
	for (int i = _hand._faceup_len; i < _hand._total_len + _hand._stage; ++i)
		map[_hand._tiles[i].rank()][_hand._tiles[i].suit()]++;
	int l = _hand.total_len() + _hand._stage - _hand.faceup_len();
	int* index = new int[l];//紀錄faceuplen數來第index張
	for (int i = 0; i < l; ++i) index[i] = 0;

	if (action == 8){
		//cout << name() << " determining move.\n";
		//for (long long i = 0; i < 200000000; ++i);

		/*if (tinged()) {
			par = l; return;
		}*/

		MJtile t;
		int b;
			int i,j, ct = 0;
			for (i = 1; i <= 9; ++i)
				for (j = 1; j <= 4; ++j)
					if (map[i][j] == 2)
						ct++;

			if (ct==1) {
				for (int k = _hand.faceup_len(); k < _hand.total_len() + _hand.stage(); ++k) {
					if (_hand._tiles[k].rank() == i&&_hand._tiles[k].suit() == j) {
						index[k - _hand.faceup_len()] = -1;
					}
				}
			}

			for (int i = 0; i < l; ++i) {
				if (index[i] > 0) {
					t = _hand._tiles[_hand._faceup_len + i];
					map[t.rank()][t.suit()]--;
					MJhand test = _hand; test.play(_hand._faceup_len + i);
					int tot = 0;
					for (int j = 1; j <= 36; ++j) {
						MJtile t(4 * j); int r = t.rank(), s = t.suit();
						bool valid = (tiles[r][s] - map[r][s]) > 0;
						if (test.canpong(t) && valid) tot += (tiles[r][s] - map[r][s]);
						if (test.canminggone(t) && valid) tot += (tiles[r][s] - map[r][s]);
						if (test.canangone(t) && valid) tot += (tiles[r][s] - map[r][s]);
						if (test.canbugone(t) && valid) tot += (tiles[r][s] - map[r][s]);
						if (test.caneat(t) && valid) {
							if (r > 1)tot += (tiles[r - 1][s] - map[r - 1][s]);
							if (r < 9)tot += (tiles[r + 1][s] - map[r + 1][s]);
						}
					}
					index[i] = tot;
				}
			}

			int _max = 0, c, p;
			vector<int>moves;
			for (int i = 0; i < l; ++i)
				_max = max(index[i], _max);
			for (int i = 0; i < l; ++i)
				if (index[i] == _max)moves.push_back(i + 1);

			srand(time(0));
			b = moves[rand() % moves.size()];
		
		
		int a;
		vector<int>fong;
		for (int i = 0; i < l; ++i) index[i] = 0;
			int f = _hand.faceup_len() - 1;
			for (a = 1; a <= l; ++a) {
				int r = _hand._tiles[a+f].rank(), s = _hand._tiles[a+f].suit();
				if (map[r][s] == 1) {
					if (r > 1 && r < 9)
						if ((map[r - 1][s] + map[r + 1][s]) == 0)  break;
					if (r == 1 && (map[2][s]+ map[3][s]) == 0)break;
					if (r == 9 && (map[8][s]+map[7][s]) == 0)break;
				}
			}
			if (a == l + 1) {
				moves.clear();
				srand(time(0));
				for (int k = 1; k <= l; ++k) {
					int r = _hand._tiles[k + f].rank(), s = _hand._tiles[k + f].suit();
					if (map[r][s] >= 2) index[k - 1] = 1;
					if (r < 8) {
						if (!(map[r][s] * map[r + 1][s] * map[r + 2][s]) == 0)
							if (map[r][s] == 1) index[k - 1] = 1;
						if (r > 1)
							if (!(map[r - 1][s] * map[r + 1][s] * map[r][s]) == 0)
								if (map[r][s] == 1) index[k - 1] = 1;
					}
					if (r == 3)
						if (!(map[1][s] * map[2][s] * map[3][s]) == 0)
							if (!(map[1][s] * map[2][s] * map[3][s]) == 0)
								if (map[3][s] == 1) index[k - 1] = 1;
					if (s == 4) fong.push_back(k);
				}
				for (int i = 0; i < l; ++i) if (!index[i])moves.push_back(i + 1);
				if (!moves.empty()) a = moves[rand() % moves.size()];
				else if(!fong.empty())a = fong[rand() % fong.size()];
				else a = rand() % l + 1;
			}
		
		if (l <= 7) {
			srand(time(0));
			int p = rand() % 100;
			if (p > 90)par = b;
			else par = a;
		}
		else {
			srand(time(0));
			int p = rand() % 100;
			if (p > 50)par = b;
			else par = a;
		}

		return;
	}
	else
	{
		if (_hand.stage() == 1) {
			if (_hand.canhu(tile)) { action = 7; return; }
			if (_hand.canangone(tile)) { action = 4; return; }
			if (_hand.canbugone(tile)) { action = 5; return; }
			action = 0; return;
		}
		else {
			//cout << name() << " determining move.\n";
			//for (long long i = 0; i < 200000000; ++i);
			int sets = 0;
			for (int i = 1; i <= 9; ++i)
				for (int j = 1; j <= 4; ++j) {
					if (map[i][j] >= 3)sets++;
					if (i < 8)
						if (map[i][j] * map[i + 1][j] * map[i + 2][j] != 0)
							sets++;
				}
			vector<int>moves_a;
			vector<int>moves_b;
			if ((_position == pos % 4 + 1)) {
				if (_hand.caneat(tile)) {
						moves_a.push_back(1);
						moves_b.push_back(1);
				}
			}
			if (_hand.canpong(tile)) {
				moves_b.push_back(2);
				int check[10][5] = { 0 };
				for (int i = 1; i <= 9; ++i)
					for (int j = 1; j <= 4; ++j)
						check[i][j] = map[i][j];
				check[tile.rank()][tile.suit()] -= 3;
				int k = 0;
				for (int i = 1; i <= 9; ++i)
					for (int j = 1; j <= 4; ++j) {
						if (check[i][j] >= 3)k++;
						if (i < 8)
							if (check[i][j] *check[i + 1][j] * check[i + 2][j] != 0)
								k++;
					}
				if (k + 1 >= sets)
					moves_a.push_back(2);
			}
			if (_position == (pos + 2) % 4 + 1 || abs(pos - _position) == 2) {
				if (_hand.canminggone(tile)) {
					moves_b.push_back(3);
					int check[10][5] = { 0 };
					for (int i = 1; i <= 9; ++i)
						for (int j = 1; j <= 4; ++j)
							check[i][j] = map[i][j];
					check[tile.rank()][tile.suit()] -= 4;
					int k = 0;
					for (int i = 1; i <= 9; ++i)
						for (int j = 1; j <= 4; ++j) {
							if (check[i][j] >= 3)k++;
							if (i < 8)
								if (check[i][j] * check[i + 1][j] * check[i + 2][j] != 0)
									k++;
						}
					if (k + 1 >= sets)
						moves_a.push_back(3);
				}
			}
			if (_hand.canhu(tile)) { action = 7; return; }

			if (moves_a.empty()&&moves_b.empty())
				action = 0;
			else {
				if (l <= 7) {
					int p = rand() % 100;
					if (p > 70 && !moves_a.empty()) action = moves_a[rand() % moves_a.size()];
					else action = moves_b[rand() % moves_b.size()];
				}
				else
				{	int p = rand() % 100;
					if (p > 20 && !moves_a.empty()) action = moves_a[rand() % moves_a.size()];
					else action = moves_b[rand() % moves_b.size()];
				}
				if (action == 1) {
					int m = _hand.caneat(tile);
					int method[3] = { 0 };
					for (int i = 0; i < 3; ++i) {
						method[i] = m % 2;
						m /= 2;
					}
					for (par = 0; par < 3; ++par)
						if (method[par]) {
							par++;
							return;
					}
				}
			}
		}
	}
}

void AIplayer::getinfo(int position, int type, MJtile* ts, int tiles_num) {
	if (type == 7)
		for (int i = 1; i <= 9; ++i)
			for (int j = 1; j <= 4; ++j)
				tiles[i][j] = 4;
	else {
		for (int i = 0; i < tiles_num; ++i) {
			tiles[ts[i].rank()][ts[i].suit()]--;
			if (tiles[ts[i].rank()][ts[i].suit()] < 0)
				tiles[ts[i].rank()][ts[i].suit()] = 0;
		}
	}
}