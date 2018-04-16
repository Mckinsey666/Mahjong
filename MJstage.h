#ifndef MJSTAGE_H
#define MJSTAGE_H
#include <iostream>
#include <conio.h>
#include <vector>
#include "MJplayer.h"
#include "MJtile.h"
#include "MJcollection.h"

using namespace std;

class MJstage {
public:
	MJstage() {};
	MJstage(int, int,int, MJplayer*[4]);
	~MJstage() {}
	void wait(int l) {
		for (long long j = 0; j < clk / l; ++j);
	}
	void play();

	void show_status();
	
	void take_tiles();
	void determine_seats();
	void determine_dealers();
	void reset_dealers();

	void show_player_hands();
	void current_status();
	void showpoints(int);

	void determinepoints(int, int, int);

	int determine_move(int[2][4],int,int&);

	void player_eat(int&, int,int, MJtile&, bool&);
	void player_pong(int&, int, MJtile&);
	void player_minggone(int&, int, MJtile&);
	void player_angone(int&);
	void player_bugone(int&);
	void player_hu(int&, int, MJtile, int);
	void player_draw(int&);
	void next_dealer(int&, bool);

	void display(){
		cout << "HU HANDS:\n";
		for (int i = 0; i < HU_HANDS.size(); ++i)
			cout << HU_HANDS[i];
		cout << '\n';
		cout << "ZHIMO:\n";
		for (int i = 0; i < ZHIMO.size(); ++i)
			cout << ZHIMO[i];
		cout << '\n';
		cout << "MINGGONE:\n";
		for (int i = 0; i < MINGGONE.size(); ++i)
			cout << MINGGONE[i];
		cout << '\n';
		cout << "ANGONE:\n";
		for (int i = 0; i < ANGONE.size(); ++i)
			cout << ANGONE[i];
		cout << '\n';
		cout << "BUGONE:\n";
		for (int i = 0; i < BUGONE.size(); ++i)
			cout << BUGONE[i];
	}
	bool full_circle();
private:
	const int clk = 400000000;
	int valueofpoints;
	int detai;
	int rounds;
	int current_round;
	MJplayer* player[4];
	MJcollection mjc;
	vector<MJhand>HU_HANDS;
	vector<MJhand>ZHIMO;
	vector<MJhand>MINGGONE;
	vector<MJhand>ANGONE;
	vector<MJhand>BUGONE;
	int all_dealers[4];
};
#endif // !MJstage
