#include "stdafx.h"
#include "humanplayer.h"
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <iomanip>
using namespace std;
int n;
char c;
void humanplayer::strategy(int pos, MJtile tile, int& action, int& par) {

	for (int i = 0; i < _hand.faceup_len(); ++i)
		cout << "    ";
	cout << "    ";
	for (int i = _hand.faceup_len(); i < _hand.total_len(); ++i)
		cout << ' ' << setw(2) << i - _hand.faceup_len() + 1 << ' ';
	if (_hand.stage())
		cout << "     " << setw(2) << _hand.total_len()-_hand.faceup_len() +1 << ' ';
	cout << '\n';
	cout << _hand;

	if (action == 8) {
		cout << name() << ", enter tile index to play: ";
		if (tinged()) {
			par = _hand.total_len() + _hand._stage - _hand.faceup_len();; 
			cout << "You have Å¥µP. Playing last tile.\n"; 
			for (long long i = 0; i < 1000000000; ++i); 
			return;
		}
		while (1) {
			cin >> par;
			if (par <= 0 || par > _hand.total_len() - _hand.faceup_len() + _hand.stage())
				cout << "INVALID move! Try again\n";
			else return;
		}
	}
	else {
		if (_hand.stage()==1) {
			vector<int>m;
			map<int, string>prompt;
			prompt[4] = "angone"; prompt[5] = "bugone"; prompt[7] = "HUUUU!";
			if (_hand.canangone(tile)) m.push_back(4);
			if (_hand.canbugone(tile)) m.push_back(5);
			if (_hand.canhu(tile)) { action = 7; return; }
			if (m.empty()) {
				action = 0;
				cout << name() << ", you can't angone, bugone, or HUUUUU. Press anthing to continue.\n";
				cin >> c;
				return;
			}
			else {
				cout << name() << ", please enter your action. Actions available:\n";
				for (int i = 0; i < m.size(); ++i)
					cout << ' ' << i+1 << ": " << prompt[m[i]] << '\n';
				cin >> n;
				if (n > 0 && n <= m.size()) {
					action = m[n-1]; return;
				}
				else {
					cout << "INVALID MOVE. You decided to do nothing. Press anthing to continue.\n";
					action = 0; cin>>c; return;
				}
			}
		}
		else{
			vector<int>m;
			map<int, string>prompt;
			prompt[1] = "eat"; prompt[2] = "pong"; prompt[3] = "minggone"; prompt[7] = "HUUUU!";
			if ((_position == pos % 4 + 1))
				if(_hand.caneat(tile)) m.push_back(1);
			if (_hand.canpong(tile)) m.push_back(2);
			if (_position == (pos + 2) % 4 + 1 ||abs(pos - _position) == 2)
				if(_hand.canminggone(tile)) m.push_back(3);
			if (_hand.canhu(tile)) { action = 7; return; }

			if (m.empty()) {
				action = 0;
				cout << name()<<", there are no actions available. Press anthing to continue.\n";
				cin >> c;
				return;
			}
			else {
				cout << name() << ", please enter your action. Actions available:\n";
				for (int i = 0; i < m.size(); ++i)
					cout << ' ' << i+1 << ": " << prompt[m[i]] << '\n';
				cin >> n;
				if (n > 0 && n <= m.size()) {
					action = m[n-1]; 
					if (action == 1) {
						cout << "Enter method you wish to eat with\n";
						cout << "(ex:for tile with rank 3, 1 eats 123, 2 eats 234, 3 eats 345):\n";
						cin >> par;
					}
						return;
				}
				else {
					cout << "INVALID MOVE. You decided to do nothing. Press anthing to continue.\n";
					cin >> c;
					action = 0; return;
				}
			}
		}
	}
	
}

