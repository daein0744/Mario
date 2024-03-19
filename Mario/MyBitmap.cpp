#include "stdafx.h"
#include "MyBitmap.h"


CMyBitmap::CMyBitmap()
{
}


CMyBitmap::~CMyBitmap()
{
	Release();
}

void CMyBitmap::Load_Bmp(const TCHAR * pFilePath)
{
	HDC		hDC = GetDC(g_hWnd);

	// CreateCompatibleDC : 매개 변수에 해당하는 호환되는 dc를 할당
	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);

	m_hBitmap = (HBITMAP)LoadImage(NULL,	// 프로그램 인스턴스 핸들, 파일로부터 읽어들일 것이어서 NULL
								pFilePath, // 이미지 파일의 경로
								IMAGE_BITMAP, // 타입 옵션
								0, // 이미지의 가로, 세로 사이즈
								0,
								LR_LOADFROMFILE | LR_CREATEDIBSECTION); // LR_LOADFROMFILE :파일로부터 이미지를 불러오겠다는 옵션 LR_CREATEDIBSECTION : 읽어온 파일을 DIB형태로 변환

	// SelectObject : GDI 오브젝트를 선택하기 전에 기존에 장치에 링크된 gdi 오브젝트를 반환
	m_hOldmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

}

void CMyBitmap::Release(void)
{
	SelectObject(m_hMemDC, m_hOldmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
