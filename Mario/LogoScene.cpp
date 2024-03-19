#include "stdafx.h"
#include "LogoScene.h"
#include "BitmapMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CLogoScene::CLogoScene()
{
}

CLogoScene::~CLogoScene()
{
	Release();
}

void CLogoScene::Initialize()
{
	MBITMAP->Insert_Bmp(L"../Image/Logo/Logo.bmp", L"Logo");
}

void CLogoScene::Update()
{
	if (MKEY->Key_Down(VK_RETURN))
	{
		MSCENE->Scene_Change(SC_MENU);
		return;
	}
}

void CLogoScene::Late_Update()
{
}

void CLogoScene::Render(HDC hDC)
{
	HDC		hLogoDC = CBitmapMgr::Get_Instance()->Find_Img(L"Logo");

	BitBlt(hDC, 0, 0, WINCX, WINCY, hLogoDC, 0, 0, SRCCOPY);

	TextOut(hDC, 350, 500, L"Press Enter Key!", 16);
}

void CLogoScene::Release()
{
	MKEY->Destroy_Instance();
}
