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

	//	// 에디트 실행 최초
	//	if (!m_LinePoint[LEFT].fX && !m_LinePoint[LEFT].fY)
	//	{
	//		m_LinePoint[LEFT].fX = (float)pt.x;
	//		m_LinePoint[LEFT].fY = (float)pt.y;
	//	}
	//	// 이후
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
	// 파일 개방
	HANDLE		hFile = CreateFile(L"../Data/Line.dat",		// 파일 경로와 이름을 명시
									GENERIC_WRITE,			// 파일 접근 모드(쓰기 전용), GENERIC_READ(읽기 전용)
									NULL,					// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대한 설정, NULL을 지정하면 공유하지 않겠다는 의미
									NULL,					// 보안 속성, NULL인 경우 기본값으로 보안 상태를 설정
									CREATE_ALWAYS,			// 생성 방식, 해당 파일을 열어서 작업을 할 것인지, 새로 만들 것인지 설정(CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING : 파일이 있을 경우에만 연다)
									FILE_ATTRIBUTE_NORMAL,  // 파일 속성, FILE_ATTRIBUTE_NORMAL 아무런 속싱 없는 일반적인 파일 생성
									NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일, 안쓰니까 NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
		return;
	}

	DWORD		dwByte = 0;

	for (auto& iter : m_LineList)
	{
		// 파일 쓰기
		WriteFile(hFile, &(iter->Get_Info()), sizeof(LINE), &dwByte, nullptr);
		// 1. 개방한 파일
		// 2. 저장할 데이터의 주소
		// 3. 저장할 데이터의 크기 단위
		// 4. 예외처리 용 변수의 주소
		// 5. 모름
	}

	// 파일 소멸
	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Save 성공"), L"성공", MB_OK);
}

void CLineMgr::Load_File(void)
{
	Release();

	// 파일 개방
	HANDLE		hFile = CreateFile(L"../Data/Line.dat",		// 파일 경로와 이름을 명시
						GENERIC_READ,			// 파일 접근 모드(쓰기 전용), GENERIC_READ(읽기 전용)
						NULL,					// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대한 설정, NULL을 지정하면 공유하지 않겠다는 의미
						NULL,					// 보안 속성, NULL인 경우 기본값으로 보안 상태를 설정
						OPEN_EXISTING,			// 생성 방식, 해당 파일을 열어서 작업을 할 것인지, 새로 만들 것인지 설정(CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING : 파일이 있을 경우에만 연다)
						FILE_ATTRIBUTE_NORMAL,  // 파일 속성, FILE_ATTRIBUTE_NORMAL 아무런 속싱 없는 일반적인 파일 생성
						NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일, 안쓰니까 NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD		dwByte = 0;
	LINE		tInfo{};

	while(true)
	{
		// 파일 쓰기
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);
		// 1. 개방한 파일
		// 2. 저장할 데이터의 주소
		// 3. 저장할 데이터의 크기 단위
		// 4. 예외처리 용 변수의 주소
		// 5. 모름

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo));

	}

	// 파일 소멸
	CloseHandle(hFile);

	MessageBox(g_hWnd, _T("Load 성공"), L"성공", MB_OK);
}
