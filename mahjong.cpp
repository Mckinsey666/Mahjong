// mahjong.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include "dice.h"
#include "Mjgame.h"

using namespace std;

int main()
{
	MJgame g;
	bool gameparameter = 1;
	g.setting(gameparameter);
	if(gameparameter)
		g.start();
	g.end();

	/*MJhand hand;
	hand.set_faceup_len(0);
	hand.set_len(16);
	hand._tiles[0].setfromId(1);
	hand._tiles[1].setfromId(17);
	hand._tiles[2].setfromId(33);
	hand._tiles[3].setfromId(33);
	hand._tiles[4].setfromId(49);
	hand._tiles[5].setfromId(65);
	hand._tiles[6].setfromId(33);
	hand._tiles[7].setfromId(49);
	hand._tiles[8].setfromId(65);
	hand._tiles[9].setfromId(74);
	hand._tiles[10].setfromId(90);
	hand._tiles[11].setfromId(106);
	hand._tiles[12].setfromId(108);
	hand._tiles[13].setfromId(124);
	hand._tiles[14].setfromId(140);
	hand._tiles[15].setfromId(13);
	cout << hand;
	if (hand.canhu(MJtile(13)))
		cout << "yes\n";

	cout << "eye:\n";
	for (int i = 0; i < 2; ++i)
		cout << hand.eye[i];
	cout << "ke:\n";
	for (int i = 0; i < hand.hu3.size(); ++i) {
		for (int j = 0; j < 3; ++j)
			cout << hand.hu3[i].t[j];
		cout << '\n';
	}
	cout << "gone:\n";
	for (int i = 0; i < hand.hu4.size(); ++i) {
		for (int j = 0; j < 4; ++j)
			cout << hand.hu4[i].t[j];
	}*/
    return 0;
}

