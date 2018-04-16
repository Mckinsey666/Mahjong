#include "stdafx.h"
#include "Cal.h"
using namespace std;

Cal::Cal() {
}
Cal::Cal(MJtile t, int base, int jPos, int jTime, int round, int pos, int tRemained, MJhand hand, int oppos, bool isself) {
	_t = t;
	_jPos = jPos;
	_jTime = jTime;
	_round = round;
	_pos = pos;
	_tRemained = tRemained;
	mj = hand;
	_oppos = oppos;
	isselfdraw = isself;
	if (isselfdraw) {
		_oppos = _jPos;
	}
	_cnt = base;
	husuit();
	cout << "HUTILES:\n";
	for (int i = 0; i < _hutiles.size(); ++i)
		cout << _hutiles[i];
}
Cal::~Cal() {
}

void Cal::husuit() {
	bool found = false;
	
	if (found) return;
	for (int i = 0; i < mj.eye.size();++i)
		if (mj.eye[0] == _t) {
			for (int j = 0; j < 2; ++j)
				_hutiles.push_back(_t);
			found = true;
			break;
		}

	if (found) return;
	for (int i = 0; i < mj.hushun.size();++i) {
		bool tar = false;
			for (int k = 0; k < 3; k++)
				if (mj.hushun[i].t[k] == _t)
					tar = true;
		if (tar) {
			for (int k = 0; k < 3; k++)
				_hutiles.push_back(mj.hushun[i].t[k]);
			found = true;
			break;
		}
	}

	if (found) return;
	for (int i = 0; i < mj.huke.size();++i)
		if (mj.huke[i].t[0] == _t) {
			for (int j = 0; j < 3; ++j)
				_hutiles.push_back(_t);
			found = true;
			break;
		}
	return;
}
bool Cal::bian() {
	//cout << "bian\n";
	if (_hutiles.size() != 3) return false;
	if (_t.suit() < 4 && !(_hutiles[0].rank() == _hutiles[1].rank())) {
		_cnt += ((_hutiles[0] == _t && _t.rank() == 7) || (_hutiles[2] == _t && _t.rank() == 3));
		return (_hutiles[0] == _t && _t.rank() == 7) || (_hutiles[2] == _t && _t.rank() == 3);
	}
	return false;
}
bool Cal::zhong() {
	//cout << "zhong\n";
	if (_hutiles.size() != 3) return false;
	if (_hutiles[0].rank() + 1 == _t.rank()) {
		_cnt++;
		return true;
	}
	return false;
}
bool Cal::dandiao() {
	//cout << "dandiao\n";
	_cnt += (_hutiles.size() == 2);
	return (_hutiles.size() == 2);
}
bool Cal::jhuang() {
	//cout << "jhuang\n";
	//cout << "��:\n";
	//cout << "me: " << _pos << "juang: " << _jPos << "opponent " << _oppos << '\n';
	if (_oppos == _jPos || _pos == _jPos) {
		_cnt += (2 * _jTime + 1);
		//cout << "�s�� " << _jTime << '\n';
		return true;
	}
	return false;
}
bool Cal::menching() {
	//cout << "menching\n";
	if (!mj.faceupke.size() && !mj.faceupshun.size() && !mj.faceupgone.size()) {
		_cnt++;
		return true;
	}
	return false;
}
bool Cal::menqingzimo() {
	//cout << "menqingzimo\n";
	if (!mj.faceupke.size() && !mj.faceupshun.size() && !mj.faceupgone.size() && isselfdraw) {
		_cnt++;
		return true;
	}
	return false;
}
bool Cal::haidilaoyue() {
	//cout << "haidilaoyue\n";
	if (_tRemained <= 16 && isselfdraw) {
		_cnt++;
		return true;
	}
	return false;
}
bool Cal::sunyuan() {
	//cout << "sunyuan\n";
	int tmp = 0;
	for (int i = 0; i < mj.huke.size();++i)
		tmp += (mj.huke[i].t[0].suit() == 4)&&(mj.huke[i].t[0].rank() > 4 )&& (mj.huke[i].t[0].rank() < 8);
	for (int i = 0; i < mj.faceupgone.size();++i)
		tmp +=(mj.faceupgone[i].t[0].suit() == 4)&&(mj.faceupgone[i].t[0].rank() > 4)&&(mj.faceupgone[i].t[0].rank() < 8);
	for (int i = 0; i < mj.faceupke.size();++i) {
		tmp += (mj.faceupke[i].t[0].suit() == 4) && (mj.faceupke[i].t[0].rank() > 4) && (mj.faceupke[i].t[0].rank() < 8);
	}
	_cnt += tmp;
	return tmp;
}
bool Cal::sameflower() {
	//cout << "sameflower\n";
	int tmp1 = 0;
	int tmp2 = 0;
	for (int i = 0; i< mj.faceup_len(); i++) {
		if (mj._tiles[i].suit() == 4) {
			tmp1 += (mj._tiles[i].rank() == 8);
			tmp2 += (mj._tiles[i].rank() == 9);
		}
	}
	_cnt += 2 * (tmp1 == 4 || tmp2 == 4);
	return (tmp1 == 4 || tmp2 == 4);
}
bool Cal::wind() {//���P
	//cout << "wind\n";
	int tmp = _round % 4;
	if (!tmp)
		tmp = 4;
	int num1 = 0;//����
	for (int i = 0; i < mj.total_len(); i++)
		num1 += (mj._tiles[i].suit() == 4 && mj._tiles[i].rank() == tmp);
	if (num1 > 2)
		_cnt++;
	int num2 = 0;//��m��
	tmp = abs(_pos - _jPos) + 1;
	for (int i = 0; i < mj.total_len(); i++)
		num2 += (mj._tiles[i].suit() == 4 && mj._tiles[i].rank() == tmp);
	if (num2 > 2)
		_cnt++;
	return(num1 > 2 || num2 > 2);
}
bool Cal::selfflower() {//��P
	//cout << "selfflower\n";
	int num = 0;
	int tmp = abs(_pos - _jPos) + 1;
	if (tmp == 2)
		tmp = 4;
	else if (tmp == 4)
		tmp = 2;
	for (int i = 0; i < mj.total_len(); i++)
		num += (mj._tiles[i].flower() == tmp);
	_cnt += num;
	return num;
}
bool Cal::sananke() {
	//cout << "sananke";
	int tmp = mj.huke.size();
	if (!isselfdraw)
		for (int i = 0; i < mj.huke.size();++i)
			tmp -= (_t == mj.huke[i].t[0]);
	if (tmp == 3) {
		_cnt += 4;
		return true;
	}
	return false;
}
bool Cal::sianke() {
	//cout << "sianke\n";
	int tmp = mj.huke.size();
	if (!isselfdraw)
		for (int i = 0; i < mj.huke.size();++i)
			tmp -= (_t == mj.huke[i].t[0]);
	if (tmp == 4) {
		_cnt += 5;
		return true;
	}
	return false;
}
bool Cal::wuanke() {
	//cout << "wuanke\n";
	int tmp = mj.huke.size();
	if (!isselfdraw)
		for (int i = 0; i < mj.huke.size();++i)
			tmp -=(_t == mj.huke[i].t[0]);
	if (tmp == 5) {
		_cnt += 8;
		return true;
	}
	return false;
}
bool Cal::quanqiu() {
	//cout << "quanqiu\n";
	if (_hutiles.size() == 2) {
		_cnt += 2;
		return true;
	}
	return false;
}
bool Cal::pinghu() {
	//cout << "pinghu\n";
	bool hasflower = false;
	for (int i = 0; i < mj.total_len(); i++)
		if (mj._tiles[i].flower())
			hasflower = true;
	if (hasflower && (mj.faceupshun.size() + mj.hushun.size()) == 5) {
		_cnt += 2;
		return true;
	}
	return false;
}
bool Cal::pengpenghu() {
	//cout << "pengpenghu\n";
	if ((mj.faceupke.size() + mj.faceupgone.size() + mj.huke.size()) == 5) {
		_cnt += 4;
		return true;
	}
	return false;
}
//�o��
bool Cal::xiaosanyuan() {
	//cout << "xiaosanyuan\n";
	int tmp = 0;
	//cout << "huke\n";
	for (int i = 0; i < mj.huke.size(); ++i)
		tmp += (mj.huke[i].t[0].suit() == 4) && (mj.huke[i].t[0].rank() > 4) && (mj.huke[i].t[0].rank() < 8);
	//cout << "facegone\n";
	for (int i = 0; i < mj.faceupgone.size(); ++i)
		tmp += (mj.faceupgone[i].t[0].suit() == 4) && (mj.faceupgone[i].t[0].rank() > 4) && (mj.faceupgone[i].t[0].rank() < 8);
	//cout << "faceke\n";
	for (int i = 0; i < mj.faceupke.size(); ++i)
		tmp += (mj.faceupke[i].t[0].suit()) == 4 && (mj.faceupke[i].t[0].rank() > 4) && (mj.faceupke[i].t[0].rank() < 8);
	
		if (mj.eye[0].suit() == 4 && mj.eye[0].rank() > 4 && mj.eye[0].rank() < 8 && tmp == 2) {
			_cnt += 4;
			return true;
		}
	
	return false;
}
bool Cal::hunyise() {
	//cout << "hunyise\n";
	for (int k = 1; k < 4; k++) {
		int tmp = 0;
		for (int i = 0; i < mj.total_len(); i++)
			tmp += !(mj._tiles[i].suit() == 4 || mj._tiles[i].suit() == k);
		if (tmp == 0) {
			_cnt += 4;
			return true;
		}
	}
	return false;
}
//�o��
bool Cal::qingyise() {
	//cout << "qingyise\n";
	int tmp = 0;
	for (int i = 0; i < mj.total_len(); i++) {
		if (mj._tiles[i].flower() == 0)
			tmp += (mj._tiles[i].suit() != mj._tiles[mj.total_len() - 1].suit());
	}
	if (!tmp) {
		_cnt += 8;
		return true;
	}
	return false;
}
bool Cal::dasanyuan() {
	//cout << "dasanyuan\n";
	int tmp = 0;
	for (int i = 0; i < mj.huke.size(); ++i)
		tmp += (mj.huke[i].t[0].suit() == 4) && (mj.huke[i].t[0].rank() > 4) && (mj.huke[i].t[0].rank() < 8);
	for (int i = 0; i < mj.faceupgone.size();++i)
		tmp +=(mj.faceupgone[i].t[0].suit() == 4 )&&(mj.faceupgone[i].t[0].rank() > 4)&&(mj.faceupgone[i].t[0].rank() < 8);
	for (int i = 0; i < mj.faceupke.size();++i)
		tmp += (mj.faceupke[i].t[0].suit() == 4 )&& (mj.faceupke[i].t[0].rank() > 4 )&& (mj.faceupke[i].t[0].rank() < 8);
	if (tmp == 3) {
		_cnt += 8;
		return true;
	}
	return false;
}
//�o��
bool Cal::xiaosixi() {
	//cout << "xiaosixi\n";
	int tmp = 0;
	for (int i = 0; i < mj.huke.size();++i)
		tmp += (mj.huke[i].t[0].suit() == 4 )&& (mj.huke[i].t[0].rank() < 5);
	for (int i = 0; i < mj.faceupgone.size();++i)
		tmp += (mj.faceupgone[i].t[0].suit() == 4 )&&( mj.faceupgone[i].t[0].rank() < 5);
	for (int i = 0; i < mj.faceupke.size();++i)
		tmp +=( mj.faceupke[i].t[0].suit() )== 4 &&( mj.faceupke[i].t[0].rank() < 5);
	
		if (mj.eye[0].suit() == 4 && mj.eye[0].rank() < 5 && tmp == 3) {
			_cnt += 8;
			return true;
		}
	return false;
}
bool Cal::dasixi() {
	//cout << "dasixi\n";
	int tmp = 0;
	for (int i = 0; i < mj.huke.size(); ++i)
		tmp += (mj.huke[i].t[0].suit() == 4) && (mj.huke[i].t[0].rank() < 5);
	for (int i = 0; i < mj.faceupgone.size(); ++i)
		tmp += (mj.faceupgone[i].t[0].suit() == 4) && (mj.faceupgone[i].t[0].rank() < 5);
	for (int i = 0; i < mj.faceupke.size();++i) {
		tmp += (mj.faceupke[i].t[0].suit() == 4) && (mj.faceupke[i].t[0].rank() < 5);
	}
	if (tmp == 4) {
		_cnt += 16;
		return true;
	}
	return false;
}
bool Cal::selfdraw() {//�ۺN�[�@�x
	//cout << "selfdraw\n";
	_cnt += isselfdraw;
	return isselfdraw;
}
void Cal::hu() {
	cout << "Your hand characteristics:\n\n";
	if (jhuang()) cout << "�m���a�n" << endl;
	if (menching()) cout << "�m���M�n" << endl;
	if (menqingzimo()) cout << "�m���M�ۺN�n" << endl;
	if (wind()) cout << "�m���P�n" << endl;
	if (selfflower()) cout << "�m��P�n" << endl;
	if (sunyuan()) cout << "�m�T���n" << endl;
	if (bian()) cout << "�m��i�n" << endl;
	if (zhong()) cout << "�m���}�n" << endl;
	if (dandiao()) cout << "�m��Q�n" << endl;
	//bool selfdraw();//�ۺN
	//bool haidilaoyue();//��������
	//bool gangshangkaihua();//�b�W�}��
	//bool chuanggang();//�m�b
	if (sananke()) cout << "�m�T�t��n" << endl;
	if (pinghu()) cout << "�m���J�n" << endl;
	if (sameflower()) cout << "�m�P�ժ�n" << endl;
	if (quanqiu()) cout << "�m���y�n" << endl;
	if (pengpenghu()) cout << "�m�I�I�J�n" << endl;
	if (xiaosanyuan()) cout << "�m�p�T���n" << endl;
	if (hunyise()) cout << "�m�V�@��n" << endl;
	if (sianke()) cout << "�m�|�t��n" << endl;
	if (qingyise()) cout << "�m�M�@��n" << endl;
	if (wuanke()) cout << "�m���t��n" << endl;
	//bool sigangpai();//�|�b�P
	if (dasanyuan()) cout << "�m�j�T���n" << endl;
	if (xiaosixi()) cout << "�m�p�|�ߡn" << endl;
	if (dasixi()) cout << "�m�j�|�ߡn" << endl;
	//bool diting();//�ať
	//bool tianhu();//�ѭJ
}
void Cal::drawhu() {
	cout << "Your hand characteristics:\n\n";
	if (menching()) cout << "�m���M�n" << endl;
	if (menqingzimo()) cout << "�m���M�ۺN�n" << endl;
	if (wind()) cout << "�m���P�n" << endl;
	if (selfflower()) cout << "�m��P�n" << endl;
	if (sunyuan()) cout << "�m�T���n" << endl;
	if (bian()) cout << "�m��i�n" << endl;
	if (zhong()) cout << "�m���}�n" << endl;
	if (dandiao()) cout << "�m��Q�n" << endl;
	if (selfdraw()) cout << "�m�ۺN�n" << endl;
	if (haidilaoyue()) cout << "�m��������n" << endl;
	//bool gangshangkaihua();//�b�W�}��
	//bool chuanggang();//�m�b
	if (sananke()) cout << "�m�T�t��n" << endl;
	if (pinghu()) cout << "�m���J�n" << endl;
	if (sameflower()) cout << "�m�P�ժ�n" << endl;
	if (quanqiu()) cout << "�m���y�n" << endl;
	if (pengpenghu()) cout << "�m�I�I�J�n" << endl;
	if (xiaosanyuan()) cout << "�m�p�T���n" << endl;
	if (hunyise()) cout << "�m�V�@��n" << endl;
	if (sianke()) cout << "�m�|�t��n" << endl;
	if (qingyise()) cout << "�m�M�@��n" << endl;
	if (wuanke()) cout << "�m���t��n" << endl;
	//bool sigangpai();//�|�b�P
	if (dasanyuan()) cout << "�m�j�T���n" << endl;
	if (xiaosixi()) cout << "�m�p�|�ߡn" << endl;
	if (dasixi()) cout << "�m�j�|�ߡn" << endl;
	//bool diting();//�ať
	//bool tianhu();//�ѭJ
	if (_pos == _jPos) {
		jhuang();
		cout << "�m���a�n" << endl;
		_cnt *= 3;
	}
	else {
		_cnt *= 3;
		jhuang();
		cout << "�m���a�n" << endl;
	}
}

/*
void Cal::baxianguohai() {
_cnt += 8;
cout <<
}*/

int Cal::Tai() {
	if (!isselfdraw)
		hu();
	else if (isselfdraw)
		drawhu();
	/*else if () {
	baxianguohai();//�K�P�L��
	}
	else if () {
	qichuangyi();//�C�m�@
	}*/
	return _cnt;
}
