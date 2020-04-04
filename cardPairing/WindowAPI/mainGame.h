#pragma once
#include "gameNode.h"

struct CARD
{
	image* cardImg;
	int num;
	bool open;
	bool correct;

};

class mainGame : public gameNode
{
private:
	image* _bgImage;
	image* _back;

	CARD _card[20];

	RECT _rc[20];

	int _startTime;
	int _cardNum1, _cardNum2;
	int _gameCount;
	
	char str[100];

	bool _gameOn;


public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);


	mainGame() {}
	~mainGame() {}
};

