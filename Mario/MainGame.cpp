#include "stdafx.h"
#include "MainGame.h"
#include "LineMgr.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"
#include "BitmapMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "LineMgr.h"

CMainGame::CMainGame()
	:m_dwTime(GetTickCount())
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{	
	m_hDC = GetDC(g_hWnd);
	MBITMAP->Insert_Bmp(L"../Image/Back.bmp", L"Back");
	MBITMAP->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");
	// ������
	MBITMAP->Insert_Bmp(L"../Image/Blocks/BrickWall1.bmp", L"BrickOverWorld");
	MBITMAP->Insert_Bmp(L"../Image/Blocks/BrickWall2.bmp", L"BrickUnderWorld");
	MBITMAP->Insert_Bmp(L"../Image/Blocks/BrickWall3.bmp", L"BrickBossWorld");

	// ������
	MBITMAP->Insert_Bmp(L"../Image/Blocks/CrackedBlock1.bmp", L"TerrainOverWorld");
	MBITMAP->Insert_Bmp(L"../Image/Blocks/CrackedBlock2.bmp", L"TerrainUnderWorld");
	MBITMAP->Insert_Bmp(L"../Image/Blocks/CrackedBlock3.bmp", L"TerrainBossWorld");

	// ����ǥ��
	MBITMAP->Insert_Bmp(L"../Image/Blocks/QuestionBlock1_104x32.bmp", L"QuestionOverWorld");
	MBITMAP->Insert_Bmp(L"../Image/Blocks/QuestionBlock2_104x32.bmp", L"QuestionUnderWorld");


	// �̴� ������
	MBITMAP->Insert_Bmp(L"../Image/Mario/Mario_LRun.bmp", MINI_MARIO_LRUN);
	MBITMAP->Insert_Bmp(L"../Image/Mario/Mario_RRun.bmp", MINI_MARIO_RRUN);
	MBITMAP->Insert_Bmp(L"../Image/Mario/Mario_LIdle.bmp", MINI_MARIO_LIDLE);
	MBITMAP->Insert_Bmp(L"../Image/Mario/Mario_RIdle.bmp", MINI_MARIO_RIDLE);
	MBITMAP->Insert_Bmp(L"../Image/Mario/Mario_LJump.bmp", MINI_MARIO_LJUMP);
	MBITMAP->Insert_Bmp(L"../Image/Mario/Mario_RJump.bmp", MINI_MARIO_RJUMP);
	MBITMAP->Insert_Bmp(L"../Image/Mario/Mario_RJump.bmp", MINI_MARIO_RJUMP);

	// � ������
	MBITMAP->Insert_Bmp(L"../Image/Mario/AdultMario_LRUN.bmp", ADULT_MARIO_LRUN);
	MBITMAP->Insert_Bmp(L"../Image/Mario/AdultMario_RRUN.bmp", ADULT_MARIO_RRUN);
	MBITMAP->Insert_Bmp(L"../Image/Mario/AdultMario_LJump.bmp", ADULT_MARIO_LJUMP);
	MBITMAP->Insert_Bmp(L"../Image/Mario/AdultMario_RJump.bmp", ADULT_MARIO_RJUMP);
	MBITMAP->Insert_Bmp(L"../Image/Mario/AdultMario_LIDLE.bmp", ADULT_MARIO_LIDLE);
	MBITMAP->Insert_Bmp(L"../Image/Mario/AdultMario_RIDLE.bmp", ADULT_MARIO_RIDLE);

	// �ö�� ������
	MBITMAP->Insert_Bmp(L"../Image/Mario/FlowerMario_LRUN.bmp", FLOWER_MARIO_LRUN);
	MBITMAP->Insert_Bmp(L"../Image/Mario/FlowerMario_RRUN.bmp", FLOWER_MARIO_RRUN);
	MBITMAP->Insert_Bmp(L"../Image/Mario/FlowerMario_LIDLE.bmp", FLOWER_MARIO_LIDLE);
	MBITMAP->Insert_Bmp(L"../Image/Mario/FlowerMario_RIDLE.bmp", FLOWER_MARIO_RIDLE);
	MBITMAP->Insert_Bmp(L"../Image/Mario/FlowerMario_LJUMP.bmp", FLOWER_MARIO_LJUMP);
	MBITMAP->Insert_Bmp(L"../Image/Mario/FlowerMario_RJUMP.bmp", FLOWER_MARIO_RJUMP);
	MBITMAP->Insert_Bmp(L"../Image/Mario/FlowerMario_LFIRE.bmp", FLOWER_MARIO_LFIRE);
	MBITMAP->Insert_Bmp(L"../Image/Mario/FlowerMario_RFIRE.bmp", FLOWER_MARIO_RFIRE);

	// ��� ������Ʈ�� (��, ����, Ǯ)
	MBITMAP->Insert_Bmp(L"../Image/Scene/Mountain1.bmp", MOUNTAIN1);
	MBITMAP->Insert_Bmp(L"../Image/Scene/Mountain2.bmp", MOUNTAIN2);
	MBITMAP->Insert_Bmp(L"../Image/Scene/Cloud1.bmp", CLOUD1);
	MBITMAP->Insert_Bmp(L"../Image/Scene/Cloud2.bmp", CLOUD2);
	MBITMAP->Insert_Bmp(L"../Image/Scene/Grass1.bmp", GRASS1);
	MBITMAP->Insert_Bmp(L"../Image/Scene/Grass2.bmp", GRASS2);
	MBITMAP->Insert_Bmp(L"../Image/Scene/Grass3.bmp", GRASS3);

	// UI��
	MBITMAP->Insert_Bmp(L"../Image/Scene/UICoin.bmp", UICOIN);

	// ��� ������Ʈ�� (��, ����, Ǯ)
	MBITMAP->Insert_Bmp(L"../Image/Scene/Mountain1.bmp", MOUNTAIN1);
	MBITMAP->Insert_Bmp(L"../Image/Scene/Mountain2.bmp", MOUNTAIN2);
	MBITMAP->Insert_Bmp(L"../Image/Scene/Cloud1.bmp", CLOUD1);
	MBITMAP->Insert_Bmp(L"../Image/Scene/Cloud2.bmp", CLOUD2);
	MBITMAP->Insert_Bmp(L"../Image/Scene/Grass1.bmp", GRASS1);
	MBITMAP->Insert_Bmp(L"../Image/Scene/Grass2.bmp", GRASS2);
	MBITMAP->Insert_Bmp(L"../Image/Scene/Grass3.bmp", GRASS3);

	// ���
	MBITMAP->Insert_Bmp(L"../Image/Scene/GoalFlag.bmp", GOALFLAG);

	// ���� Ÿ�� �� ����
	MBITMAP->Insert_Bmp(L"../Image/Scene/BossTile.bmp", BOSSTILE);
	MBITMAP->Insert_Bmp(L"../Image/Scene/BossAxe.bmp", BOSSAXE);

	MSCENE->Scene_Change(SC_LOGO);
}

void CMainGame::Update(void)
{
	MSCENE->Update();
}

void CMainGame::Late_Update(void)
{
	MSCENE->Late_Update();

}

void CMainGame::Render(void)
{
	HDC		hBackDC = MBITMAP->Find_Img(L"Back");
	MSCENE->Render(hBackDC);
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);

	
}

void CMainGame::Release(void)
{
	MBITMAP->Release();
	MBITMAP->Destroy_Instance();
	MSCENE->Release();
	MSCENE->Destroy_Instance();
	MSCROLL->Destroy_Instance();
	MKEY->Destroy_Instance();
	ReleaseDC(g_hWnd, m_hDC);
}
