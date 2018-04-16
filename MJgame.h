#ifndef  MJGAME_H
#define MJGAME_H
#include "stdafx.h"
#include <iostream> 
#include <vector>
#include "MJplayer.h"
#include "humanplayer.h"
#include "AIplayer.h"
#include "MJstage.h"
#include <conio.h>
#include <string>
using namespace std;

bool validinput(string s) {
	for (int i = 0; i < s.size(); ++i)
		if (!isdigit(s[i]))
			return false;
	return true;
}

class MJgame {
	friend ostream& operator << (ostream&, const MJhand&);
public:
	MJgame();
	~MJgame();

	void start();
	void setting(bool&);
	void end();
	void wait(int d){ for (int i = 0; i < clk/d; ++i); }
	void print(){
		cout << endl;
		for (int i = 0; i < 154; ++i)cout << '*';
		cout << '\n';
		for (int i = 0; i < 62; ++i)cout << '*';
		cout << " 《台灣麻將》--TAIWAN MAHJONG ";
		for (int i = 0; i < 62; ++i)cout << '*';
		cout << '\n';
		for (int i = 0; i < 154; ++i)cout << '*';
		cout << '\n';
	}
private:
	int rounds;//圈數 一個風為一圈 
	int valueofpoints;//一台多少錢 
	int detai;
	int player_num;
	int clk = 1000000000;
	MJplayer* players[4];
};

MJgame::MJgame() {
	print();

	for (int i = 0; i < 60; ++i)cout << ' ';
	cout << "Press anything to continue....\n";
	char c = getchar();
	system("cls");
}
MJgame::~MJgame() {
}

void MJgame::setting(bool& par) {
	print();
	string s;
x:system("cls"); print();
	while (1) {
		cout << "[press 'q' to quit]\n     Please enter rounds you wish to play: ";
		cin >> s;
		if (s == "q") { par = false; return; }
		if(!validinput(s)) { cout << "Invalid rounds!\n"; wait(4); system("cls"); print(); }
		else {
			rounds = stoi(s);
			if (rounds > 0) { system("cls"); print(); break; }
			else { cout << "Invalid rounds!\n"; wait(4); system("cls"); print(); }
		}
	}
y:system("cls"); print();
	while (1) {
		cout << "[press 'r' to return]\n     Please enter value of each 台 (positive value) : ";
		cin >> s;
		if (s == "r")goto x;
		if (!validinput(s)) { cout << "Invalid value!\n"; wait(4); system("cls"); print(); }
		else {
			valueofpoints = stoi(s);
			if (valueofpoints > 0) { system("cls"); print(); break; }
			else { cout << "Invalid value!\n"; wait(4); system("cls"); print(); }
		}
	}
z:system("cls"); print();
	while (1) {
		cout << "[press 'r' to return]\n     Please enter value of 底 ( = ? 台) (positive value): ";
		cin >> s;
		if (s == "r")goto y;
		if (!validinput(s)) { cout << "Invalid value!\n"; wait(4); system("cls"); print(); }
		else{
			detai = stoi(s);
			if (detai > 0) { system("cls"); print(); break; }
			else { cout << "Invalid value!\n"; wait(4); system("cls"); print(); }
		}
	}
w:system("cls"); print();
	while (1) {
		cout << "[press 'r' to return]\n   Please enter number of actual players (less or equal than 4): ";
		cin >> s;
		if (s == "r")goto z;
		if (!validinput(s)) { cout << "Invalid value!\n"; wait(4); system("cls"); print(); }
		else{
			player_num = stoi(s);
			if (player_num <= 4) { system("cls"); print(); break; }
			else { cout << "Invalid number of players!\n"; wait(4); system("cls"); print(); }
		}
	}
	cout << "[press 'r' to return, anything else to continue]\n     You will be playing with " << player_num << " players and "
		<< 4 - player_num << " AI.\n";
	cin >> s;
	if (s == "r")goto w;

	wait(4); system("cls");
	if (player_num > 0) {
		string name;
		for (int i = 0; i < player_num; ++i) {
			while (1) {
				system("cls"); print();
				cout << "Please enter player name (name length <= 20): \n";
				cout << "Player " << i + 1 << ": "; cin >> name;
				if (name.size() > 20) { cout << "Invalid name!\n"; wait(2); }
				else { players[i] = new humanplayer(name); break; }
			}
		}
	}
	for (int i = player_num; i < 4; ++i)
		players[i] = new AIplayer();

	/*for (long long i = 0; i < 100000000; ++i);
	system("cls"); print();
	for (int i = 0; i < 3; ++i) {
		cout << "Loading";
		for (int j = 0; j < 3; ++j) {
			cout << '.';
			for (long long j = 0; j < 1000000000/2; ++j);
		}
		system("cls"); print();
	}*/
	system("cls"); 
}

void MJgame::start() {
	MJstage stage(valueofpoints,detai, player_num, players);
	while (rounds) {
		stage.play();
		rounds--; system("cls");
	}
	//stage.display();
	stage.showpoints(1);
}

void MJgame::end() {
	system("cls"); print();

	for (int i = 0; i < 70; ++i)cout << ' ';
	cout << "Game End." << endl;
	for (int i = 0; i < 63; ++i)cout << ' ';
	cout << "Press any button to exit.." << endl;
	cin.get();
}
#endif

