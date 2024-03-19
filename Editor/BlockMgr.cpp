#include "stdafx.h"
#include "BlockMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "QuestionBlock.h"
#include "BrickBlock.h"
#include "TerrainBlock.h"

CBlockMgr* CBlockMgr::m_pInstance = nullptr;

CBlockMgr::CBlockMgr() :
	m_eCurBlockID(BlockEnd),
	m_eCurWorldID(WorldEnd)
{
}

CBlockMgr::~CBlockMgr()
{
	Release();
}

void CBlockMgr::Initialize()
{
	Release();
}

int CBlockMgr::Update(void)
{
	Mouse_Input();
	Key_Input();	
	return 0;
}

void CBlockMgr::Late_Update(void)
{
}

void CBlockMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < BlockEnd; ++i)
	{
		for (auto& iter : m_BlockList[i])
		{
			iter->Render(hDC);
		}
	}
}

void CBlockMgr::Release(void)
{
	for (size_t i = 0; i < BlockEnd; ++i)
	{
		for_each(m_BlockList[i].begin(), m_BlockList[i].end(), Safe_Delete<CBlock*>);
		m_BlockList[i].clear();
	}

}

void CBlockMgr::CalculateGrid(int& x, int& y, float fSizeX, float fSizeY, POINT& pt)
{
	x = (int)(pt.x / fSizeX);
	y = (int)(pt.y / fSizeY);
	x *= (int)fSizeX;
	y *= (int)fSizeY;
	x += (int)(fSizeX * 0.5f);
	y += (int)(fSizeY * 0.5f);
}

void CBlockMgr::Save_File(const TCHAR* pFilePath)
{
	// 파일 개방
	HANDLE		hFile = CreateFile(
		pFilePath,		
		GENERIC_WRITE,			
		NULL,					
		NULL,					
		CREATE_ALWAYS,			
		FILE_ATTRIBUTE_NORMAL, 
		NULL);					

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
		return;
	}

	DWORD		dwByte = 0;

	for (int i = 0; i < BlockEnd; i++)
	{
		for (auto iter : m_BlockList[i])
		{
			// 파일 쓰기
			WriteFile(hFile, (iter), sizeof(CBlock), &dwByte, nullptr);
			// 1. 개방한 파일
			// 2. 저장할 데이터의 주소
			// 3. 저장할 데이터의 크기 단위
			// 4. 예외처리 용 변수의 주소
			// 5. 모름
		}
	}
	

	// 파일 소멸
	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save 성공"), L"성공", MB_OK);
}

void CBlockMgr::Load_File(const TCHAR* pFilePath)
{
	Release();

	// 파일 개방
	HANDLE		hFile = CreateFile(
		pFilePath,		
		GENERIC_READ,			
		NULL,					
		NULL,					
		OPEN_EXISTING,			
		FILE_ATTRIBUTE_NORMAL,  
		NULL);					

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD		dwByte = 0;
	CBlock		tInfo;

	while (true)
	{
		// 파일 쓰기
		ReadFile(hFile, &tInfo, sizeof(CBlock), &dwByte, nullptr);

		if (0 == dwByte)
			break;
		CBlock* tmp = nullptr;
		switch (tInfo.GetBlockID())
		{
		case QuestionBlock:
			tmp = new CQuestionBlock(true, tInfo.GetBlockID(), tInfo.GetWorldID(), tInfo.Get_Info());
			break;
		case BrickBlock:
			tmp = new CBrickBlock(true, tInfo.GetBlockID(), tInfo.GetWorldID(), tInfo.Get_Info());
			break;
		case TerrainBlock:
			tmp = new CTerrainBlock(true, tInfo.GetBlockID(), tInfo.GetWorldID(), tInfo.Get_Info());
			break;
		default:
			break;
		}

		if (tmp)
			m_BlockList[tInfo.GetBlockID()].push_back(tmp);
	}

	// 파일 소멸
	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load 성공"), L"성공", MB_OK);
}

void CBlockMgr::Mouse_Input()
{
	POINT		pt{};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x += (int)CScrollMgr::Get_Instance()->Get_ScrollX();

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	{
		if (m_eCurWorldID == WorldEnd)
		{
			MessageBox(g_hWnd, L"컨셉을 선택해주세요", L"실패", MB_OK);
			return;
		}

		if (m_eCurBlockID == BlockEnd)
		{
			EraseBlock(pt);
		}
		else
		{
			MakeBlock(m_eCurBlockID, pt);
		}
		
	}
}

void CBlockMgr::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Down('Q'))
	{
		m_eCurWorldID = OverWorld;
		return;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('W'))
	{
		m_eCurWorldID = UnderWorld;
		return;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('E'))
	{
		m_eCurWorldID = BossWorld;
		return;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('S'))
	{
		Save_File(L"../Data/Blocks.dat");
		return;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('L'))
	{
		Load_File(L"../Data/Blocks.dat");
		return;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('Z'))
	{
		m_eCurBlockID = QuestionBlock;
		return;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('X'))
	{
		m_eCurBlockID = BrickBlock;
		return;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('C'))
	{
		m_eCurBlockID = TerrainBlock;
		return;
	}

	if (CKeyMgr::Get_Instance()->Key_Down('V'))
	{
		m_eCurBlockID = BlockEnd;
		return;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
		CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);

	if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
		CScrollMgr::Get_Instance()->Set_ScrollX(5.f);
}

void CBlockMgr::MakeBlock(BLOCKID _eCurBlockID, POINT& pt)
{
	bool bCollision = false;
	CBlock* pBlock = nullptr;
	RECT tmp{};
	
	int x, y;

	float fSizeX, fSizeY;
	fSizeX = 32.f; // 그리드 X사이즈
	fSizeY = 32.f; // 그리드 Y사이즈

	CalculateGrid(x, y, fSizeX, fSizeY, pt);
	// 클릭한 좌표를 격자 정보로 만들기 위한 계산
	switch (_eCurBlockID)
	{
	case QuestionBlock:
	{		
		pBlock = new CQuestionBlock(true, QuestionBlock, m_eCurWorldID, INFO{ (float)x,(float)y, fSizeX, fSizeY });
		break;
	}
	case BrickBlock:
	{
		pBlock = new CBrickBlock(true, BrickBlock, m_eCurWorldID, INFO{ (float)x,(float)y, fSizeX, fSizeY });
		break;
	}
	case TerrainBlock:
	{
		pBlock = new CTerrainBlock(true, TerrainBlock, m_eCurWorldID, INFO{ (float)x,(float)y, fSizeX, fSizeY });
		break;
	}
	default:
		break;
	}

	// 기존의 사각형과 겹치는지 검사.
	for (size_t i = 0; i < BlockEnd; ++i)
	{
		for (auto& iter : m_BlockList[i])
		{
			RECT blockRect = pBlock->Get_Rect();
			RECT otherRect = iter->Get_Rect();
			if (IntersectRect(&tmp, &blockRect, &otherRect))
			{
				bCollision = true;
				break;
			}
		}

		if (bCollision == true)
			break;
	}

	// 겹치는 사각형이 있으면 생성한 정보를 지우기.
	if (bCollision)
	{
		delete pBlock;
		return;
	}

	m_BlockList[_eCurBlockID].push_back(pBlock);

}

void CBlockMgr::EraseBlock(POINT& pt)
{
	bool bCollision = false;
	CBlock* pBlock = nullptr;
	RECT tmp{};

	int x, y;

	float fSizeX, fSizeY;
	fSizeX = 32.f; // 그리드 X사이즈
	fSizeY = 32.f; // 그리드 Y사이즈

	CalculateGrid(x, y, fSizeX, fSizeY, pt);

	for (int i = 0; i < BlockEnd; i++)
	{
		for (auto it = m_BlockList[i].begin(); it != m_BlockList[i].end(); it++)
		{
			INFO info = (*it)->Get_Info();
			if (info.fX == x && info.fY == y)
			{
				Safe_Delete(*it);
				m_BlockList[i].erase(it);
				return;
			}
		}
	}
}
