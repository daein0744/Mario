#include "stdafx.h"
#include "MenuScene.h"
#include "BitmapMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"


CMenuScene::CMenuScene()
	:m_eSelect(MENU_END), m_fStar(0.f)
{
}


CMenuScene::~CMenuScene()
{
	Release();
}

void CMenuScene::Initialize()
{
	MBITMAP->Insert_Bmp(L"../Image/Menu/Menu.bmp", L"Menu");
	MBITMAP->Insert_Bmp(L"../Image/Menu/Star.bmp", L"Star");
}

void CMenuScene::Update()
{
	if (MKEY->Key_Down(VK_RETURN))
	{
		switch (m_eSelect)
		{
		case MENU_START:
			MSCENE->Scene_Change(SC_STAGE1);
			return;
		case MENU_EDIT:
			//MSCENE->Scene_Change(SC_EDIT);
			return;
		case MENU_EXIT:
			DestroyWindow(g_hWnd);
			return;
		default:
			MSCENE->Scene_Change(SC_STAGE1);
			return;
		}
	}
}

void CMenuScene::Late_Update()
{
}

void CMenuScene::Render(HDC hDC)
{
	HDC	hMenuDC = MBITMAP->Find_Img(L"Menu");
	HDC	hStarDC = MBITMAP->Find_Img(L"Star");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMenuDC, 0, 0, SRCCOPY);
	GdiTransparentBlt(hDC, 300, 360, 16, 16, hStarDC, 0, 0, 16, 16, RGB(1, 1, 1));
}

void CMenuScene::Release()
{
}
