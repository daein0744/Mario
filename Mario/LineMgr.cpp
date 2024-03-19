#include "stdafx.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"

CLineMgr*		CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
	ZeroMemory(m_LinePoint, sizeof(m_LinePoint));
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(void)
{
	MYPOINT Line[2] = { { 0,500 },{ 3200,500 } };
	m_LineList.push_back(new CLine(Line[0], Line[1]));
}

int CLineMgr::Update(void)
{
	//POINT		pt{};

	//GetCursorPos(&pt);
	//ScreenToClient(g_hWnd, &pt);

	//pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//cout << (int)CScrollMgr::Get_Instance()->Get_ScrollX() << endl;
	//if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	//{

	//	// ����Ʈ ���� ����
	//	if (!m_LinePoint[LEFT].fX && !m_LinePoint[LEFT].fY)
	//	{
	//		m_LinePoint[LEFT].fX = (float)pt.x;
	//		m_LinePoint[LEFT].fY = (float)pt.y;
	//	}
	//	// ����
	//	else
	//	{
	//		m_LinePoint[RIGHT].fX = (float)pt.x;
	//		m_LinePoint[RIGHT].fY = (float)pt.y;

	//		m_LineList.push_back(new CLine(m_LinePoint[LEFT], m_LinePoint[RIGHT]));

	//		m_LinePoint[LEFT].fX = m_LinePoint[RIGHT].fX;
	//		m_LinePoint[LEFT].fY = m_LinePoint[RIGHT].fY;

	//	}	
	//}

	//if (CKeyMgr::Get_Instance()->Key_Down('S'))
	//{
	//	Save_File();
	//	return 0;
	//}

	//if (CKeyMgr::Get_Instance()->Key_Down('L'))
	//{
	//	Load_File();
	//	return 0;
	//}

	/*if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(5.f);*/
	
	/*if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-5.f);*/
	
	return 0;
}

void CLineMgr::Late_Update(void)
{
}

void CLineMgr::Render(HDC _hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(_hDC);
}

void CLineMgr::Release(void)
{
	for_each(m_LineList.begin(), m_LineList.end(), Safe_Delete<CLine*>);
	m_LineList.clear();
}

bool CLineMgr::Collision_Line(float& _fX, float* _pfY)
{
	if (m_LineList.empty())
		return false;

	CLine*		pTargetLine = nullptr;

	for (auto& iter : m_LineList)
	{
		if (_fX >= iter->Get_Info().tLPoint.fX &&
			_fX <= iter->Get_Info().tRPoint.fX)
			pTargetLine = iter;
	}

	if (nullptr == pTargetLine)
		return false;
	
	// Y  = ((y2 - y1) / (x2 - x1)) * (X - x1) + y1

	float	x1 = pTargetLine->Get_Info().tLPoint.fX;
	float	y1 = pTargetLine->Get_Info().tLPoint.fY;
	
	float	x2 = pTargetLine->Get_Info().tRPoint.fX;
	float	y2 = pTargetLine->Get_Info().tRPoint.fY;

	*_pfY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

	return true;
}

void CLineMgr::Save_File(void)
{
	// ���� ����
	HANDLE		hFile = CreateFile(L"../Data/Line.dat",		// ���� ��ο� �̸��� ���
									GENERIC_WRITE,			// ���� ���� ���(���� ����), GENERIC_READ(�б� ����)
									NULL,					// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ���� �� �� �㰡�ϴ� �Ϳ� ���� ����, NULL�� �����ϸ� �������� �ʰڴٴ� �ǹ�
									NULL,					// ���� �Ӽ�, NULL�� ��� �⺻������ ���� ���¸� ����
									CREATE_ALWAYS,			// ���� ���, �ش� ������ ��� �۾��� �� ������, ���� ���� ������ ����(CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING : ������ ���� ��쿡�� ����)
									FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�, FILE_ATTRIBUTE_NORMAL �ƹ��� �ӽ� ���� �Ϲ����� ���� ����
									NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����, �Ⱦ��ϱ� NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
		return;
	}

	DWORD		dwByte = 0;

	for (auto& iter : m_LineList)
	{
		// ���� ����
		WriteFile(hFile, &(iter->Get_Info()), sizeof(LINE), &dwByte, nullptr);
		// 1. ������ ����
		// 2. ������ �������� �ּ�
		// 3. ������ �������� ũ�� ����
		// 4. ����ó�� �� ������ �ּ�
		// 5. ��
	}

	// ���� �Ҹ�
	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save ����"), L"����", MB_OK);
}

void CLineMgr::Load_File(void)
{
	Release();

	// ���� ����
	HANDLE		hFile = CreateFile(L"../Data/Line.dat",		// ���� ��ο� �̸��� ���
						GENERIC_READ,			// ���� ���� ���(���� ����), GENERIC_READ(�б� ����)
						NULL,					// ���� ���, ������ ���� �ִ� ���¿��� �ٸ� ���μ����� ���� �� �� �㰡�ϴ� �Ϳ� ���� ����, NULL�� �����ϸ� �������� �ʰڴٴ� �ǹ�
						NULL,					// ���� �Ӽ�, NULL�� ��� �⺻������ ���� ���¸� ����
						OPEN_EXISTING,			// ���� ���, �ش� ������ ��� �۾��� �� ������, ���� ���� ������ ����(CREATE_ALWAYS : ������ ���ٸ� ����, �ִٸ� �����, OPEN_EXISTING : ������ ���� ��쿡�� ����)
						FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�, FILE_ATTRIBUTE_NORMAL �ƹ��� �ӽ� ���� �Ϲ����� ���� ����
						NULL);					// ������ ������ �Ӽ��� ������ ���ø� ����, �Ⱦ��ϱ� NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD		dwByte = 0;
	LINE		tInfo{};

	while(true)
	{
		// ���� ����
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);
		// 1. ������ ����
		// 2. ������ �������� �ּ�
		// 3. ������ �������� ũ�� ����
		// 4. ����ó�� �� ������ �ּ�
		// 5. ��

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo));

	}

	// ���� �Ҹ�
	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load ����"), L"����", MB_OK);
}
