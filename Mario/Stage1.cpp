#include "stdafx.h"
#include "Stage1.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "BitmapMgr.h"
#include "BlockMgr.h"
#include "CollilsionMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"


CStage1::CStage1()
{
}


CStage1::~CStage1()
{
	Release();
}

void CStage1::Initialize()
{
	MBITMAP->Insert_Bmp(L"../Image/Ground.bmp", L"Ground");
	MOBJ->AddObject(PLAYER, CAbstractFactory<CPlayer>::Create());
	MOBJ->AddObject(MONSTER, CAbstractFactory<CTurtle>::Create());
	MOBJ->AddObject(MONSTER, CAbstractFactory<CGoomba>::Create(800, 150));
	MOBJ->AddObject(MONSTER, CAbstractFactory<CGoomba>::Create(700, 150));
	MOBJ->AddObject(MONSTER, CAbstractFactory<CGoomba>::Create(600, 150));
	MOBJ->AddObject(MONSTER, CAbstractFactory<CTurtle>::Create(1000, 150));
	MOBJ->AddObject(MONSTER, CAbstractFactory<CTurtle>::Create(1300, 150));
	BLOCK->Load_File(L"../Data/Blocks.dat");

	
}

void CStage1::Update()
{
	MOBJ->Update();
	BLOCK->Update();

		
}

void CStage1::Late_Update()
{
	MOBJ->Late_Update();
	BLOCK->Late_Update();
	CCollilsionMgr::Collision_RectEx(*MOBJ->GetObjList(PLAYER), *MOBJ->GetObjList(MONSTER));
	for (size_t i = 0; i < BlockEnd; ++i)
	{
		for (size_t j = 0; j < OBJ_END; ++j)
		{
			CCollilsionMgr::Collision_BlockEx(*BLOCK->GetBlockList((BLOCKID)i), *MOBJ->GetObjList((OBJID)j));
		}
	}
}

void CStage1::Render(HDC hDC)
{
	HBRUSH myBrush, oldBrush;
	myBrush = CreateSolidBrush(RGB(92, 148, 252));
	oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC, 0, 0, 800, 600);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

	

	HDC hMemDC = MBITMAP->Find_Img(CLOUD1);
	int      iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	for (int i = 0; i < 20; i++)
	{
		GdiTransparentBlt(hDC,      // ���� ���� ���� DC
			i*500 + iScrollX, // ���� ���� �ؽ�ó ��ġ ��ǥ X
			100+i*10, // ���� ���� �ؽ�ó ��ġ ��ǥ Y
			96, // �ؽ�ó ���� ������
			55, // �ؽ�ó ���� ������
			hMemDC,   // ������ DC
			0,   // ��Ʈ�� ��� ��ǥ X
			0,   // ��Ʈ�� ��� ��ǥ Y
			96, // ������ ��Ʈ�� �ؽ�ó ���� ������
			55, // ������ ��Ʈ�� �ؽ�ó ���� ������
			RGB(1, 1, 1)); // ������ �ȼ� ����
	}

	hMemDC = MBITMAP->Find_Img(MOUNTAIN2);
	GdiTransparentBlt(hDC,      // ���� ���� ���� DC
		200 + iScrollX, // ���� ���� �ؽ�ó ��ġ ��ǥ X
		500, // ���� ���� �ؽ�ó ��ġ ��ǥ Y
		160, // �ؽ�ó ���� ������
		69, // �ؽ�ó ���� ������
		hMemDC,   // ������ DC
		0,   // ��Ʈ�� ��� ��ǥ X
		0,   // ��Ʈ�� ��� ��ǥ Y
		160, // ������ ��Ʈ�� �ؽ�ó ���� ������
		69, // ������ ��Ʈ�� �ؽ�ó ���� ������
		RGB(1, 1, 1)); // ������ �ȼ� ����

	hMemDC = MBITMAP->Find_Img(GRASS2);
	GdiTransparentBlt(hDC,      // ���� ���� ���� DC
		600 + iScrollX, // ���� ���� �ؽ�ó ��ġ ��ǥ X
		520, // ���� ���� �ؽ�ó ��ġ ��ǥ Y
		131, // �ؽ�ó ���� ������
		32, // �ؽ�ó ���� ������
		hMemDC,   // ������ DC
		0,   // ��Ʈ�� ��� ��ǥ X
		0,   // ��Ʈ�� ��� ��ǥ Y
		131, // ������ ��Ʈ�� �ؽ�ó ���� ������
		32, // ������ ��Ʈ�� �ؽ�ó ���� ������
		RGB(1, 1, 1)); // ������ �ȼ� ����

	hMemDC = MBITMAP->Find_Img(GOALFLAG);
	GdiTransparentBlt(hDC,      // ���� ���� ���� DC
		1500 + iScrollX, // ���� ���� �ؽ�ó ��ġ ��ǥ X
		210, // ���� ���� �ؽ�ó ��ġ ��ǥ Y
		48, // �ؽ�ó ���� ������
		334, // �ؽ�ó ���� ������
		hMemDC,   // ������ DC
		0,   // ��Ʈ�� ��� ��ǥ X
		0,   // ��Ʈ�� ��� ��ǥ Y
		48, // ������ ��Ʈ�� �ؽ�ó ���� ������
		334, // ������ ��Ʈ�� �ؽ�ó ���� ������
		RGB(1, 1, 1)); // ������ �ȼ� ����

	list<CObj*>* playerlist = MOBJ->GetObjList(PLAYER);
	if (playerlist)
	{
		CObj* player = playerlist->front();
		if (player)
		{
			cout << player->Get_Info().fX << " " << 1500 + iScrollX << endl;
			if (player->Get_Info().fX >= 1500)
			{
				MSCENE->Scene_Change(SC_STAGE2);
			}
		}
	}

	
	MOBJ->Render(hDC);
	BLOCK->Render(hDC);
}

void CStage1::Release()
{
	MOBJ->DeleteObject(PLAYER);
	MOBJ->Release();
	MOBJ->Destroy_Instance();
	BLOCK->Release();
	BLOCK->Destroy_Instance();
}
