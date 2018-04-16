#ifndef CAL_H
#define CAL_H
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
#include"MJtile.h"
#include"MJhand.h"

class Cal {
public:
	Cal();
	Cal(MJtile t, int base,int jPos, int jTime, int round, int pos, int tRemained, MJhand hand, int oppos, bool isself);//constructor
	~Cal();

	//ultilizing

	void husuit();




	//bool isselfdraw();//�O�_���ۺN
	//tai-checking																																//init(int Jpos);//�Ϊ���m

	bool jhuang();//���a
	bool menching();//���M
	bool menqingzimo();//���M�ۺN
	bool wind();//���P
	bool selfflower();//��P
	bool sunyuan();//�T��
	bool bian();//��i
	bool zhong();//���}
	bool dandiao();//��Q
	bool selfdraw();//�ۺN
	bool haidilaoyue();//��������
					   //bool gangshangkaihua();//�b�W�}��
					   //bool chuanggang();//�m�b
	bool sananke();//�T�t��
	bool pinghu();//���J
	bool sameflower();//�P�ժ�
	bool quanqiu();//���y
	bool pengpenghu();//�I�I�J
	bool xiaosanyuan();//�p�T��
	bool hunyise();//�V�@��
	bool sianke();//�|�t��
	bool qingyise();//�M�@��
					//bool sigangpai();//�|�b�P
	bool wuanke();//���t��
	bool dasanyuan();//�j�T��
	bool xiaosixi();//�p�|��
					//bool diting();//�ať
	bool dasixi();//�j�|��
				  //bool tianhu();//�ѭJ


				  //main move
	void hu();//�J�O�H
	void drawhu();//�ۺN�J
	void baxianguohai();//�K�P�L��
	void qichuangyi();//�C�m�@
					  //void rst();//���s�s���@��
	int Tai();//��X�x��

private:
	//�ǤJ
	MJtile _t;
	int _jPos;
	int _jTime;
	int _round;
	int _pos;
	//int _wind;
	int _tRemained;
	int _oppos;//��j���H or  �ۺN �N����a
	MJhand mj;
	bool isselfdraw;

	//�ۤv�p��
	int _cnt;
	vector<MJtile> _hutiles;
};
#endif
