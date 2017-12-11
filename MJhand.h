/****************************************************************************** 
   FileName  [MJhand.h]
   Author    [HsuehYa Huang]
   Synopsis  [define a player's hand] 
******************************************************************************/ 
#ifndef MJHAND
#define MJHAND
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include "MJtile.h" 
using namespace std;

class MJhand{
	friend ostream& operator << (ostream&, const MJhand&);
public:
	MJhand();
	MJhand(MJtile*,int);
	~MJhand();
	
	int faceup_len() const ;
	
	int caneat(const MJtile&);
	bool canpong(const MJtile&);
	bool cangone(const MJtile&);
	
	bool canhu(const MJtile&);
	
	void arrange();
	void draw(MJtile* , int&, int&);
	MJtile play(int);
	void faceup(int);
	
	void applique(int, MJtile* , int&, int&);
	void initial(MJtile* , int&, int&);
	
	void eat(const MJtile&);
	void pong(const MJtile&);
	void gone(const MJtile&);
	bool hu(const MJtile&);
	
	void printcount() {
		for (int i = 1; i <= 36; ++i)
			cout <<setw(2)<< i << ' ';
		cout << '\n';
		for (int i = 1; i <= 36; ++i)
			cout << setw(2)<<tile_count[i] << ' ';
		cout << '\n';
		cout << '\n';
		for (int i = 1; i <= 9; ++i) {
			for (int j = 1; j <= 4; ++j)
				cout << eat_count[i][j] << ' ';
			cout << '\n';
		}
		cout << '\n';
		for(int i=0;i<9;++i){
			for (int j = 0; j < 16; ++j) {
				cout << setw(2) << tile_map[i][j];
				if (j % 4 == 3)
					cout << ' ';
			}
			cout << '\n';
		}
	}
private:
	int _total_len;
	int _faceup_len;
	int _stage;//0 normal stage, 1 draw stage
	MJtile _tiles[30];//total 17 tiles, at most 30 = 17+8+5

//Mine
	int tile_count[37];//Check 4 tiles (use 1-34), to utilize pong and gone
	int tile_map[9][16];//Visualization
	int eat_count[10][5];//utilize eat
}; 
#endif
