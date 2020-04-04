#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## 초기화 ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();
	//이곳에서 초기화를 한다

	//백그라운드 이미지 초기화
	_bgImage = new image;
	_bgImage->init("테이블.bmp", WINSIZEX, WINSIZEY);
	_back = new image;
	_back->init("타로카드뒷면.bmp", 98, 190);
	_startTime = NULL;
	_cardNum1 = NULL;
	_cardNum2 = NULL;
	_gameCount = 0;
	_gameOn = true;

	sprintf(str, "");

	for (int i = 0; i < 20; i++)
	{
		_card[i].cardImg= new image;
		_card[i].open = false;
		_card[i].correct = false;

		if (i < 10) { _card[i].num = i; }
		else { _card[i].num = i - 10; }

		if (i < 5)
		{
			_rc[i] = RectMake(100 + (130 * i), 10, 98, 180);
		}
		else if (i >= 5 && i < 10)
		{
			_rc[i] = RectMake(100 + (130 * (i-5)), 210, 98, 180);
		}
		else if (i >= 10 && i < 15)
		{
			_rc[i] = RectMake(100 + (130 * (i - 10)), 410, 98, 180);
		}
		else if (i >= 15 && i < 20)
		{
			_rc[i] = RectMake(100 + (130 * (i - 15)), 610, 98, 180);
		}
	}
	_card[0].cardImg->init("타로카드1.bmp", 98, 180);
	_card[1].cardImg->init("타로카드2.bmp", 98, 180);
	_card[2].cardImg->init("타로카드3.bmp", 98, 180);
	_card[3].cardImg->init("타로카드4.bmp", 98, 180);
	_card[4].cardImg->init("타로카드5.bmp", 98, 180);
	_card[5].cardImg->init("타로카드6.bmp", 98, 180);
	_card[6].cardImg->init("타로카드7.bmp", 98, 180);
	_card[7].cardImg->init("타로카드8.bmp", 98, 180);
	_card[8].cardImg->init("타로카드9.bmp", 98, 180);
	_card[9].cardImg->init("타로카드10.bmp", 98, 180);
	_card[10].cardImg->init("타로카드1.bmp", 98, 180);
	_card[11].cardImg->init("타로카드2.bmp", 98, 180);
	_card[12].cardImg->init("타로카드3.bmp", 98, 180);
	_card[13].cardImg->init("타로카드4.bmp", 98, 180);
	_card[14].cardImg->init("타로카드5.bmp", 98, 180);
	_card[15].cardImg->init("타로카드6.bmp", 98, 180);
	_card[16].cardImg->init("타로카드7.bmp", 98, 180);
	_card[17].cardImg->init("타로카드8.bmp", 98, 180);
	_card[18].cardImg->init("타로카드9.bmp", 98, 180);
	_card[19].cardImg->init("타로카드10.bmp", 98, 180);

	for (int i = 0; i < 1000; i++)
	{
		int index1 = RND->range(20);
		int index2 = RND->range(20);
		CARD temp = _card[index2];
		_card[index2] = _card[index1];
		_card[index1] = temp;

	}

	//입술 이미지 초기화
	//_lip = new image;
	//_lip->init("입술.bmp", 118, 67, true, RGB(255, 0, 255));

	return S_OK;
}

//=============================================================
//	## 해제 ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();
	//이미지 클래스를 나갈때까진 사용할 일 없다
	//동적할당 new를 사용했다면 이곳에서 SAFE_DELETE() 사용한다

	SAFE_DELETE(_bgImage);
	for (int i = 0; i < 20; i++)
	{
		SAFE_DELETE(_card[i].cardImg);
	}
	SAFE_DELETE(_back);
}


//=============================================================
//	## 업데이트 ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다
	//간단하게 이곳에서 코딩한다고 생각하면 된다

	if (_gameCount == 10)
	{
		sprintf(str, "게임이 끝났습니다. 다시 진행하려면 마우스 오른쪽 버튼을 눌러주세요.");

		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			this->init();
		}
	}


	if (_gameOn == true)
	{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 20; i++)
		{
			if (PtInRect(&_rc[i], _ptMouse))
			{
				_card[i].open = true;

				for (int j = 0; j < 20; j++)
				{
					if (j == i) continue;
					if (_card[j].open == true && _card[j].correct == false)
					{
						_startTime = GetTickCount();
						_cardNum1 = i;
						_cardNum2 = j;
						if (_card[i].num == _card[j].num)
						{
							_gameCount++;
							_card[i].correct = true;
							_card[j].correct = true;
						}

					}
				}

			}

		}
	}

	if (_card[_cardNum1].num != _card[_cardNum2].num)
	{
		if (GetTickCount() - _startTime >= 500){}
		else
		{
			_gameOn = false;
		}
	}

		for (int i = 0; i < 20; i++)
		{
			if (_card[i].correct == true) { _card[i].open = true; }
		}

	}
	else
	{
		if (GetTickCount() - _startTime >= 500)
		{
			_card[_cardNum1].open = false;
			_card[_cardNum2].open = false;
			_cardNum1 = NULL;
			_cardNum2 = NULL;
			_startTime = NULL;
			_gameOn = true;
		}
	}

}

//=============================================================
//	## 렌더 ## render(HDC hdc)
//=============================================================
void mainGame::render(HDC hdc)
{
	//백버퍼 가져오기 (이건 렌더에 두기)
	HDC memDC = this->getBackBuffer()->getMemDC();
	//흰색 빈 비트맵 (이것도 렌더에 그냥 두기)
	//PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================
	//이곳에서 WM_PAINT에서 했던것을 처리하면 된다

	_bgImage->render(memDC, 0, 0);


	for (int i = 0; i < 20; i++)
	{
		if (_card[i].open == true)
		{
			_card[i].cardImg->render(memDC, _rc[i].left, _rc[i].top);
		}
		else
		{
			_back->render(memDC, _rc[i].left, _rc[i].top);
		}
	}

	if (_gameCount == 10)
	{

		SetBkMode(memDC, TRANSPARENT);
		TextOut(memDC, 100, WINSIZEY / 2, str, lstrlen(str));
	}

	//hdc 대신 memDC를 사용한다

//=============================================================
	//백버퍼의 내용을 HDC에 그린다 (이것도 렌더에 그냥 두기)
	this->getBackBuffer()->render(hdc);

}
