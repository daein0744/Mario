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

	// CreateCompatibleDC : �Ű� ������ �ش��ϴ� ȣȯ�Ǵ� dc�� �Ҵ�
	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);

	m_hBitmap = (HBITMAP)LoadImage(NULL,	// ���α׷� �ν��Ͻ� �ڵ�, ���Ϸκ��� �о���� ���̾ NULL
								pFilePath, // �̹��� ������ ���
								IMAGE_BITMAP, // Ÿ�� �ɼ�
								0, // �̹����� ����, ���� ������
								0,
								LR_LOADFROMFILE | LR_CREATEDIBSECTION); // LR_LOADFROMFILE :���Ϸκ��� �̹����� �ҷ����ڴٴ� �ɼ� LR_CREATEDIBSECTION : �о�� ������ DIB���·� ��ȯ

	// SelectObject : GDI ������Ʈ�� �����ϱ� ���� ������ ��ġ�� ��ũ�� gdi ������Ʈ�� ��ȯ
	m_hOldmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

}

void CMyBitmap::Release(void)
{
	SelectObject(m_hMemDC, m_hOldmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
