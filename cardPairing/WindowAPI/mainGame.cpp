#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## �ʱ�ȭ ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();
	//�̰����� �ʱ�ȭ�� �Ѵ�

	//��׶��� �̹��� �ʱ�ȭ
	_bgImage = new image;
	_bgImage->init("���̺�.bmp", WINSIZEX, WINSIZEY);
	_back = new image;
	_back->init("Ÿ��ī��޸�.bmp", 98, 190);
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
	_card[0].cardImg->init("Ÿ��ī��1.bmp", 98, 180);
	_card[1].cardImg->init("Ÿ��ī��2.bmp", 98, 180);
	_card[2].cardImg->init("Ÿ��ī��3.bmp", 98, 180);
	_card[3].cardImg->init("Ÿ��ī��4.bmp", 98, 180);
	_card[4].cardImg->init("Ÿ��ī��5.bmp", 98, 180);
	_card[5].cardImg->init("Ÿ��ī��6.bmp", 98, 180);
	_card[6].cardImg->init("Ÿ��ī��7.bmp", 98, 180);
	_card[7].cardImg->init("Ÿ��ī��8.bmp", 98, 180);
	_card[8].cardImg->init("Ÿ��ī��9.bmp", 98, 180);
	_card[9].cardImg->init("Ÿ��ī��10.bmp", 98, 180);
	_card[10].cardImg->init("Ÿ��ī��1.bmp", 98, 180);
	_card[11].cardImg->init("Ÿ��ī��2.bmp", 98, 180);
	_card[12].cardImg->init("Ÿ��ī��3.bmp", 98, 180);
	_card[13].cardImg->init("Ÿ��ī��4.bmp", 98, 180);
	_card[14].cardImg->init("Ÿ��ī��5.bmp", 98, 180);
	_card[15].cardImg->init("Ÿ��ī��6.bmp", 98, 180);
	_card[16].cardImg->init("Ÿ��ī��7.bmp", 98, 180);
	_card[17].cardImg->init("Ÿ��ī��8.bmp", 98, 180);
	_card[18].cardImg->init("Ÿ��ī��9.bmp", 98, 180);
	_card[19].cardImg->init("Ÿ��ī��10.bmp", 98, 180);

	for (int i = 0; i < 1000; i++)
	{
		int index1 = RND->range(20);
		int index2 = RND->range(20);
		CARD temp = _card[index2];
		_card[index2] = _card[index1];
		_card[index1] = temp;

	}

	//�Լ� �̹��� �ʱ�ȭ
	//_lip = new image;
	//_lip->init("�Լ�.bmp", 118, 67, true, RGB(255, 0, 255));

	return S_OK;
}

//=============================================================
//	## ���� ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();
	//�̹��� Ŭ������ ���������� ����� �� ����
	//�����Ҵ� new�� ����ߴٸ� �̰����� SAFE_DELETE() ����Ѵ�

	SAFE_DELETE(_bgImage);
	for (int i = 0; i < 20; i++)
	{
		SAFE_DELETE(_card[i].cardImg);
	}
	SAFE_DELETE(_back);
}


//=============================================================
//	## ������Ʈ ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	//�̰����� ����, Ű����, ���콺��� ������Ʈ�� �Ѵ�
	//�����ϰ� �̰����� �ڵ��Ѵٰ� �����ϸ� �ȴ�

	if (_gameCount == 10)
	{
		sprintf(str, "������ �������ϴ�. �ٽ� �����Ϸ��� ���콺 ������ ��ư�� �����ּ���.");

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
//	## ���� ## render(HDC hdc)
//=============================================================
void mainGame::render(HDC hdc)
{
	//����� �������� (�̰� ������ �α�)
	HDC memDC = this->getBackBuffer()->getMemDC();
	//��� �� ��Ʈ�� (�̰͵� ������ �׳� �α�)
	//PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================
	//�̰����� WM_PAINT���� �ߴ����� ó���ϸ� �ȴ�

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

	//hdc ��� memDC�� ����Ѵ�

//=============================================================
	//������� ������ HDC�� �׸��� (�̰͵� ������ �׳� �α�)
	this->getBackBuffer()->render(hdc);

}
