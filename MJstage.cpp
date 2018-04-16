#include "stdafx.h"
#include "MJstage.h"
#include "humanplayer.h"
#include "AIplayer.h"
#include "MJcollection.h"
#include "Shuffler.h"
#include "dice.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
const int l = 1;
int state, m, to_move, to_play, index, dealer, x;
bool hu = false;
using namespace std;

MJstage::MJstage(int v, int d,int n, MJplayer* p[4]) {
	valueofpoints = v;
	detai = d;
	current_round = 1;
	for (int i = 0; i < 4; ++i)
		player[i] = p[i];
	memset(all_dealers, 0, sizeof(all_dealers));
}

void MJstage::take_tiles() {
	cout << "Drawing tiles.\n\n"; wait(4);
	MJtile m[30];
	//Reset player hand with tile of id 0
	for (int i = 0; i < 4; ++i) {
		player[i]->get_hand().set_hand(m, 30);
		player[i]->get_hand().set_stage(0);
		player[i]->get_hand().reset_visible();
	}

	mjc._frontind = 0; mjc._backind = 143;
	//Reset hand and draw
	for (int i = 0; i < 4; ++i) {
		player[i]->get_hand().set_len(16);
		player[i]->get_hand().set_faceup(0);
		for (int j = 0; j < 16; ++j)
			player[i]->get_hand().set_tile(mjc.drawfronttile(), j);	
	}
	current_status(); wait(2);
	cout << "Players applique.\n"; wait(2);
	for (int i = 0; i < 4; ++i) {
		player[i]->get_hand().initial(mjc);
		player[i]->get_hand().arrange();
	}
	current_status(); wait(1);
}
void MJstage::determine_seats() {
	cout << "Determining seats.\n\n"; wait(4);
	MJhand seats;
	seats.set_faceup(6); seats.set_len(6);
	seats._tiles[0] = MJtile(1); seats._tiles[5] = MJtile(17);
	for (int i = 1; i <= 4; ++i)
		seats._tiles[i] = MJtile(16 * i);
	cout << seats; wait(l); 
	srand(time(0)); 
	int pos = rand() % 4;
	cout << player[pos]->name() << " to decide seat first.\n"; wait(2); 
	int val = rand() % 6 + 1;
	cout << player[pos]->name() << " tossed " << val << "\n"; wait(2);
	if (val % 2 == 0) {
		cout << "Determining seats from right.\n"; wait(2); 
		for (int i = 4; i >= 1; --i) {
			player[pos]->set_position(i);
			pos = (pos + 1) % 4;
		}
	}
	else {
		cout << "Determining seats from left.\n"; wait(2); 
		for (int i = 1; i <= 4; ++i) {
			player[pos]->set_position(i);
			pos = (pos + 1) % 4;
		}
	}
	system("cls"); show_status();
}
void MJstage::reset_dealers() {
	memset(all_dealers, 0, sizeof(all_dealers));
	for (int i = 0; i < 4; ++i)
		player[i]->set_dealer(0);
}
void MJstage::determine_dealers() {
	cout << "Determining dealer.\n\n"; wait(4);
	int p;
	for (p = 0; p < 4; ++p)
		if (player[p]->Get_Pos() == 1)
			break;
	int d = rand() % 6 + 1;
	cout <<"東風位 player "<< player[p]->name() << " tossed " << d << ".\n"; wait(2);
	index = (p + d) % 4, dealer = index;
	player[dealer]->set_dealer(1); all_dealers[dealer] = 1;
	cout << player[dealer]->name() << " is first round dealer.\n"; wait(2);
	system("cls"); show_status();
}
void MJstage::show_player_hands() {
	for (int i = 0; i < 4; ++i) {
		switch (player[i]->Get_Pos()) {
		case 1: cout << "東: "; break;
		case 2: cout << "南: "; break;
		case 3: cout << "西: "; break;
		case 4: cout << "北: "; break;
		}
		cout << player[i]->name();
		if (player[i]->is_dealer()) cout << ": CURRENT DEALER";
		cout << "\n"; player[i]->showhand(); cout << '\n';
		//cout <<'\n'<<player[i]->get_hand() << '\n';
	}
}
void MJstage::current_status() {
	system("cls");  show_status(); 
	for (int i = 0; i < 71; ++i)cout << ' ';
	cout << "Tiles left: " << mjc.size() << '\n'; 
	show_player_hands();  
}
void MJstage::show_status()	 {
	cout << endl;
	for (int i = 0; i < 154; ++i)cout << '*';
	cout << '\n';
	for (int i = 0; i < 64; ++i)cout << '*';
	cout << "** Current Round: " << setw(5) << current_round << " **";
	for (int i = 0; i < 64; ++i)cout << '*';
	cout << '\n';
	for (int i = 0; i < 154; ++i)cout << '*';
	cout << "\n";
	for (int i = 0; i < 154; ++i)cout << '*';
	cout << '\n';

	for (int i = 0; i < 4; ++i) {
		cout << "******  Player " << i + 1 << ": " << setw(112) << player[i]->name();
		if (player[i]->is_dealer()) cout << "  DEALER   *************";
		else cout << "           *************";
		cout << '\n';
	}
	for (int i = 0; i < 154; ++i)cout << '*';
	cout << '\n';

	for (int i = 0; i < 69; ++i)cout << ' ';
	cout << "《各玩家連莊次數》\n";
	for (int i = 0; i < 30; ++i)cout << ' ';
	for (int i = 0; i < 4; ++i)
		cout << setw(20) << player[i]->name() << ' ';
	cout << '\n';
	for (int i = 0; i < 30; ++i)cout << ' ';
	for (int i = 0; i < 4; ++i)
		cout << setw(20) <<  all_dealers[i] << ' ';
	cout << '\n';
}
void MJstage::showpoints(int i) {
	if (i == 0) {
		cout << current_round;
		switch (current_round % 10) {
		case 1: cout << "st "; break;
		case 2: cout << "rd "; break;
		case 3: cout << "rd "; break;
		default: cout << "th "; break;
		}
		cout << "round player points:\n";
		for (int i = 0; i < 4; ++i)
			cout << setw(20) << player[i]->name();
		cout << '\n';
		for (int i = 0; i < 4; ++i)
			cout << setw(20) << player[i]->getmoney();
		cout << '\n';
		wait(l); 
	}
	else {
		cout << "Final points:\n";
		for (int i = 0; i < 4; ++i)
			cout << setw(20) << player[i]->name();
		cout << '\n';
		for (int i = 0; i < 4; ++i)
			cout << setw(20) << player[i]->getmoney();
		cout << '\n';
	}
}

bool MJstage::full_circle() {
	for (int i = 0; i < 4; ++i)
		if (!all_dealers[i])
			return false;
	return true;
}
int MJstage::determine_move(int strat[2][4],int index, int&i) {
	i = index; bool found = false;
	while ((i + 1) % 4 != index) {
		i = (i + 1) % 4;
		if (strat[0][i] == 7) return 7;
	}
	i = index;
	while ((i + 1) % 4 != index) {
		i = (i + 1) % 4;
		if (strat[0][i] == 2 || strat[0][i] == 3) { found = true; break; }
	}
	if (!found) {
		i = index;
		while ((i + 1) % 4 != index) {
			i = (i + 1) % 4;
			if (strat[0][i] == 1)break;
		}
	}
	return strat[0][i];
}

void MJstage::player_eat(int& index, int i, int type, MJtile& t, bool& flag) {
	index = i; 
	int n = 8, to_play = 0;
	cout << player[index]->name() << " to eat tile.\n"; wait(5);
	player[index]->get_hand().eat(t, type); current_status(); wait(2);
	if (player[index]->get_hand().stage() == 1) {

		MJtile eatile[3];
		MJhand hand = player[index]->get_hand();
		for (int i = 0; i < 3; ++i)
			eatile[i] = hand._tiles[hand._faceup_len - i - 1];
		for (int i = 0; i < 4; ++i)
			player[i]->getinfo(0,0, eatile, 3);

		player[index]->strategy(0, 0, n, to_play);
		t = player[index]->get_hand().play(to_play); current_status(); wait(l);
		cout << player[index]->name() << " played:\n" << t; wait(l);
		flag = true; 
		player[index]->to_ting();
		return;
	}
	else {
		return;
	}
}
void MJstage::player_pong(int& index, int i, MJtile& t) {
	index = i; 
	int n = 8, to_play = 0;
	cout << player[index]->name() << " to pong tile.\n"; wait(5);
	player[index]->get_hand().pong(t); current_status(); wait(2);

	MJtile pongtile[3]; 
	MJhand hand = player[index]->get_hand();
	for (int i = 0; i < 3; ++i)
		pongtile[i] = hand._tiles[hand._faceup_len - i - 1];
	for (int i = 0; i < 4; ++i)
		player[i]->getinfo(0, 0,pongtile, 3);

	player[index]->strategy(0, 0, n, to_play);
	t = player[index]->get_hand().play(to_play); current_status(); wait(l);
	cout << player[index]->name() << " played:\n" << t; wait(l);
	player[index]->to_ting();
}
void MJstage::player_minggone(int& index, int i, MJtile& t) {
	index = i; 
	int n = 8, to_play = 0;
	cout << player[index]->name() << " to minggone tile.\n"; wait(5);
	player[index]->get_hand().minggone(t, mjc); current_status(); wait(2);
	MINGGONE.push_back(player[index]->get_hand());

	MJtile gonetile[4];
	MJhand hand = player[index]->get_hand();
	for (int i = 0; i < 4; ++i)
		gonetile[i] = hand._tiles[hand._faceup_len - i - 1];
	for (int i = 0; i < 4; ++i)
		player[i]->getinfo(0, 0,gonetile, 4);

	player[index]->strategy(0, 0, n, to_play);
	t = player[index]->get_hand().play(to_play); current_status(); wait(l);
	cout << player[index]->name() << " played:\n" << t; wait(l);
	player[index]->to_ting();
}
void MJstage::player_hu(int& index, int i, MJtile t, int type) {
	int tai = 0;
	if (type == 1) {
		int temp = index;
		index = i;
		player[index]->get_hand().huother(t); current_status(); wait(l);
		cout << player[index]->name() << " rong-HUUUUED!\n";
		cout << player[index]->get_hand();
		HU_HANDS.push_back(player[index]->get_hand());
		int pos = 0;
		for (pos = 0; pos < 4; ++pos)
			if (player[pos]->is_dealer())
				break;

		//cout << "Your sets:\n";
		//player[index]->get_hand().print_sets();
		MJhand hand = player[index]->get_hand();
		Cal cal(t, detai,player[pos]->Get_Pos(), all_dealers[pos], current_round, player[index]->Get_Pos(), mjc.size(), hand ,player[temp]->Get_Pos(), 0);
		tai = cal.Tai();
		cout << "台數： " << tai << "台\n";

		//cout << "You win " << tai << "*" << valueofpoints << " + " << detai << " = " << tai*valueofpoints + detai << '\n';
		determinepoints(index, temp, tai);
		cin >> tai;
		wait(l); 
		return;
	}
	else {
		int temp = index;
		player[index]->get_hand().huown(); current_status();
		cout << player[index]->name() << " Zhi-MOed!\n";
		cout << player[index]->get_hand();
		ZHIMO.push_back(player[index]->get_hand());
		int pos = 0;
		for (pos = 0; pos < 4; ++pos)
			if (player[pos]->is_dealer())
				break;

		//cout << "Your sets:\n";
		//player[index]->get_hand().print_sets();
		MJhand hand = player[index]->get_hand();
		Cal cal(t, detai,player[pos]->Get_Pos(), all_dealers[pos], current_round, player[index]->Get_Pos(), mjc.size(), hand, player[temp]->Get_Pos(), 1);

		tai = cal.Tai();
		cout << "台數： " << tai << "台\n";
		//cout << "You win " << tai << "*" << valueofpoints << " + " << detai << " = " << tai*valueofpoints + detai << '\n';
		determinepoints(index, -1, tai);
		cin >> tai;
		wait(l); 
		return;
	}
}
void MJstage::player_angone(int& index) {
	MJtile t = player[index]->last();
	int i = player[index]->find_angone(t);
	cout << player[index]->name() << " to angone\n"; wait(5);

	player[index]->get_hand().angone(i, mjc); current_status(); wait(2);
	ANGONE.push_back(player[index]->get_hand());
}
void MJstage::player_bugone(int& index){
	MJtile t = player[index]->last();
	int i = player[index]->find_bugone(t);
	cout << player[index]->name() << " to bugone\n"; wait(5);
	player[index]->get_hand().bugone(i, mjc); current_status(); wait(2);
	MJtile gonetile[4];
	MJhand hand = player[index]->get_hand();
	for (int j = 0; j < 4; ++j)
		gonetile[j] = hand._tiles[hand._faceup_len - 1 + i];
	for (int i = 0; i < 4; ++i)
		player[i]->getinfo(0,0,gonetile, 4);
	BUGONE.push_back(player[index]->get_hand());
}


void MJstage::player_draw(int& index) {
	player[index]->get_hand().draw(mjc); current_status(); wait(l);
}
void MJstage::next_dealer(int& dealer, bool flag) {
	if (flag) {
		for (int i = 0; i < 68; ++i)cout << ' ';
		cout << player[dealer]->name() << " to 連莊.\n";
		player[dealer]->set_dealer(1); all_dealers[dealer]++;
	}
	else {
		player[dealer]->set_dealer(0);
		dealer = (dealer + 1) % 4;
		for (int i = 0; i < 55; ++i)cout << ' ';
		cout << "Dealer of next circle: " << player[dealer]->name() << '\n';
		player[dealer]->set_dealer(1); all_dealers[dealer] = 1;
	}
}

void MJstage::determinepoints(int index, int oppos, int tai) {
	if (oppos < 0) {
		int k = 0;
		for (k = 0; k < 4; ++k)
			if (player[k]->is_dealer())
				break;
		int jhuang = (2 * all_dealers[k] + 1);

		for (int i = 0; i < 4; ++i) {
			if (i == index)
				player[index]->setmoney(tai*valueofpoints);
			else {
				if (player[index]->is_dealer()) player[i]->setmoney(-double(valueofpoints*tai)/ 3);
				else {
					if (!player[i]->is_dealer())player[i]->setmoney(-double((tai - jhuang)*valueofpoints)/ 3);
					else player[i]->setmoney(-double(double(tai - jhuang) / 3 + jhuang)*valueofpoints / 3);
				}
			}
		}
	}
	else {
		player[oppos]->setmoney(-(tai*valueofpoints));
		player[index]->setmoney(tai*valueofpoints);
	}

	cout << "Current player points:\n";
	for (int i = 0; i < 4; ++i)
		cout << setw(20) << player[i]->name();
	cout << '\n';
	for (int i = 0; i < 4; ++i)
		cout << setw(20) << player[i]->getmoney();
	cout << '\n';
}
void MJstage::play() {
	MJtile t;

	reset_dealers();
	show_status(); wait(l);

	determine_seats();
	determine_dealers();
	
	wait(l);
	while (1) {
		hu = false;
		int gone_number = 0;
		bool circle_fail = false;

		for (int i = 0; i < 4; ++i) {
			player[i]->clear_tiles();
			player[i]->set_ting(0);
			player[i]->clear_sets();
		}

		mjc.shuffle(); 
		take_tiles(); 

		while (1) {
			current_status(); 

			player_draw(index); 
			player[index]->strategy(0, player[index]->last(), m, x);
			t = player[index]->last();
			switch (m) {
				case 4: {player_angone(index); break; }
				case 5: {player_bugone(index); break; }
				case 7: {player_hu(index, 0, t, 0); hu = true; break; }
				default: break;
			}
			if (hu) break;
			system("cls"); current_status();

			int n = 8;
			player[index]->strategy(0, 0, n, to_play);
			t = player[index]->get_hand().play(to_play); current_status();
			cout << player[index]->name() << " played tile:\n" << t; wait(5);
			player[index]->to_ting();


		point:
			int strat[2][4];
			memset(strat, 0, sizeof(strat));
			for (int i = 0; i < 4; ++i)
				if (i != index) {
					current_status(); cout << player[index]->name()<<" played tile:\n" << t;
					player[i]->strategy(player[index]->Get_Pos(), t, strat[0][i], strat[1][i]);
					//wait(l);
				}

			m = determine_move(strat, index, to_move);
			bool eat_success = false;

			switch (m) {
			case 1: {
				player_eat(index, to_move, strat[1][to_move], t, eat_success);
				if (eat_success) goto point; break; }
			case 2: {player_pong(index, to_move, t); goto point; break; }
			case 3: {player_minggone(index, to_move, t); gone_number++; goto point; break; }
			case 7: {player_hu(index, to_move, t, 1); hu = true; break; }
			default: break;
			}
			if (hu) break;

			MJtile tile[1]; tile[0] = t;
			for (int i = 0; i < 4; ++i)
				player[i]->getinfo(0, 0,tile, 1);

			index = (index + 1) % 4;
			
			if (mjc.size() <= 16 + gone_number) {//流局 連莊
				system("cls"); current_status();
				cout << '\n';
				for (int i = 0; i < 75; ++i)cout << ' ';
				cout << "流局!\n"; wait(l);
				circle_fail = true;
				break;
			}
		}

		if (full_circle()) {
			system("cls"); current_status();
			cout << "End of " << current_round;
			switch (current_round % 10) {
			case 1: cout << "st "; break;
			case 2: cout << "rd "; break;
			case 3: cout << "rd "; break;
			default: cout << "th "; break;
			}
			cout << "round.\n";
			showpoints(0);
			cout << "Continue to next round? [y/n]\n";
			char c; cin >> c; if (c != 'y')return;
			wait(1); 
			break;
		}
		next_dealer(dealer, circle_fail);
		wait(1); system("cls"); show_status(); wait(1);
	}
	current_round++;
}


