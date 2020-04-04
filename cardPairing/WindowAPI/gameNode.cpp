#include "stdafx.h"
#include "gameNode.h"

//=============================================================
//	## �ʱ�ȭ ## init()
//=============================================================
HRESULT gameNode::init()
{
	SetTimer(_hWnd, 1, 10, NULL);		//Ÿ�̸� �ʱ�ȭ
	KEYMANAGER->init();					//Ű�Ŵ��� �ʱ�ȭ
	RND->init();						//������� �ʱ�ȭ
	
	setBackBuffer();					//����� �ʱ�ȭ(�� ����)
	
	return S_OK;
}

void gameNode::setBackBuffer()
{
	_backBuffer = new image;
	_backBuffer->init(WINSIZEX, WINSIZEY);
}

//=============================================================
//	## ���� ## release()
//=============================================================
void gameNode::release()
{
	//Ÿ�̸� ����
	KillTimer(_hWnd, 1);
	//Ű�Ŵ��� �̱��� ����
	KEYMANAGER->release();
	KEYMANAGER->releaseSingleton();
	//������� �̱��� ����
	RND->release();
	RND->releaseSingleton();

	//����� �̹��� ����(������ �����)
	SAFE_DELETE(_backBuffer);
}

//=============================================================
//	## ������Ʈ ## update()
//=============================================================
void gameNode::update()
{
	//���ΰ�ħ (���߿� ������ Ÿ�̸Ӹ� ���� �Ŀ��� ������� �ʴ´�)
	//�������۸� ���� ������� �ʴ´� (true => false)
	InvalidateRect(_hWnd, NULL, false);
}

//=============================================================
//	## ���� ## render(HDC hdc)
//=============================================================
void gameNode::render(HDC hdc)
{
}

//=============================================================
//	## �������ν��� ## MainProc()
//=============================================================
LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;		 
	PAINTSTRUCT ps; 

	switch (iMessage)
	{
	case WM_TIMER:
		this->update();
		break;
	case WM_PAINT:			
		hdc = BeginPaint(hWnd, &ps);
		this->render(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:		
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:		
		switch (wParam)
		{
		case VK_ESCAPE:	
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}