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




	//bool isselfdraw();//是否為自摸
	//tai-checking																																//init(int Jpos);//樁的位置

	bool jhuang();//莊家
	bool menching();//門清
	bool menqingzimo();//門清自摸
	bool wind();//風牌
	bool selfflower();//花牌
	bool sunyuan();//三元
	bool bian();//邊張
	bool zhong();//中洞
	bool dandiao();//單吊
	bool selfdraw();//自摸
	bool haidilaoyue();//海底撈月
					   //bool gangshangkaihua();//槓上開花
					   //bool chuanggang();//搶槓
	bool sananke();//三暗刻
	bool pinghu();//平胡
	bool sameflower();//同組花
	bool quanqiu();//全球
	bool pengpenghu();//碰碰胡
	bool xiaosanyuan();//小三元
	bool hunyise();//混一色
	bool sianke();//四暗刻
	bool qingyise();//清一色
					//bool sigangpai();//四槓牌
	bool wuanke();//五暗刻
	bool dasanyuan();//大三元
	bool xiaosixi();//小四喜
					//bool diting();//地聽
	bool dasixi();//大四喜
				  //bool tianhu();//天胡


				  //main move
	void hu();//胡別人
	void drawhu();//自摸胡
	void baxianguohai();//八仙過海
	void qichuangyi();//七搶一
					  //void rst();//重製新的一局
	int Tai();//輸出台數

private:
	//傳入
	MJtile _t;
	int _jPos;
	int _jTime;
	int _round;
	int _pos;
	//int _wind;
	int _tRemained;
	int _oppos;//放槍的人 or  自摸 就放莊家
	MJhand mj;
	bool isselfdraw;

	//自己計算
	int _cnt;
	vector<MJtile> _hutiles;
};
#endif
