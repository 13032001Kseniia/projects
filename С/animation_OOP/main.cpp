
 // +++ main.cpp +++

 //
 // ������ ���. ������� �������� �� ���� GDI. �������� �������. ������� ������.
 //

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cassert>
#include <vector>
#include <tchar.h>
#define _USE_MATH_DEFINES
#include <math.h>

 // ���������� ������� ��� ���������
#include "2dAnimLib.h"

#include "main.h"


 // --- ���������� ���������� ---

 // �������� ����� (��������� �������, ��������, �����)
const double g_dSceneLeft = -10.0,
			 g_dSceneBottom = -5.0,
			 g_dSceneRight = 10.0,
			 g_dSceneTop = 5.0;

 // ������� ������
unsigned g_nTime = 0,  // ������� ��������
		 g_nTimeInc = 1;  // ������� ����������
const unsigned g_nMaxTime = 100,  // ������������ �������� (��������� ����)
			   g_nTimerElapse = 40;  // �������� ������� � ����

 // �������-�������
CQuad g_quad;
CQuad g_quad1;

 // --- class CQuad -----------------------------------------------------------

 //
 // ����������� �� ��������� - ������������� ����� � ���������� �������� ��������� ������
 //
CQuad::CQuad() :
	m_nBorderColor (RGB (0, 0,255)),
	m_nFillColor (RGB (0,255,0))
{
	 // ������ �������� - 1�1
	m_aSrcPoints.Add (0,0);
	m_aSrcPoints.Add (0.2,0.2);
	m_aSrcPoints.Add (0,0.4);
	m_aSrcPoints.Add (0.2,0.4);
	m_aSrcPoints.Add(0.4,0.6);
	m_aSrcPoints.Add(0.6,0.4);
	m_aSrcPoints.Add(0.4,0.6);
	m_aSrcPoints.Add(0.2,0.4);
	m_aSrcPoints.Add(0.8,0.4);
	m_aSrcPoints.Add(0.6,0.2);
	m_aSrcPoints.Add(0.8,0);
	m_aSrcPoints.Add(0.4,0.2);


	m_aSrcPoints.Add(10, 0.2);


}

 //
 // ��������� ������ � ������ ������� t_ [0..1]
 //
void CQuad::Draw (CDrawContext& context_, double t_)
{
	 // --- ��������� ������� ��������������, ��������������� ������� ������� t_ [0..1] ---

	CAffineMatrix transform;

	 // �� ������ �������� - �������� ��������������� � �������
	//if (t_ > 0.5)
		transform =   CAffineMatrix::Scale (atan(-sin(t_)), atan(-sin(t_))) * CAffineMatrix::Rotate(atan(-sin(t_)));

	 // ����������� - �������� �� ���� �� ���� "�����" (������ �������� - 1�1)
	CVector vOffset((1 - t_) *  (g_dSceneLeft + 1.0) + t_ *  (g_dSceneRight - 1.0),
		cos((1 - t_) * (g_dSceneBottom + 1.0) + t_ * (g_dSceneTop - 1.0)));
		//(g_dSceneLeft + 1.0) + t_ * (g_dSceneRight - 1.0)
		// * (g_dSceneBottom + 1.0) + t_ * (g_dSceneTop - 1.0)
	 // ����� ��������������
	transform = transform * CAffineMatrix::Translate (vOffset);

	 // ������� ������ � ������������ � ������ ��������������
	CPoints aPnts = m_aSrcPoints * transform;

	 // --- ���������� ������������� ---

	 // ������� � ������� ���� � ����� ��� ���������
	CPen pen (PS_SOLID, 3, m_nBorderColor, context_);
	CBrush brush (m_nFillColor, context_);

	context_.Polygon (aPnts);
}

 // --- class CQuad -----------------------------------------------------------


 // --- class CAnimWindow -----------------------------------------------------

 //
 // �++-����� ���� ����������
 //

LPCTSTR CAnimWindow::sm_szClassName = _T("2dAnimClass");

HWND CAnimWindow::sm_hWnd = nullptr;

 //
 // ����������� Windows-������ ����
 //
WORD CAnimWindow::RegisterClass (HINSTANCE hInstance_)
{
	WNDCLASS wc;
	memset (&wc, 0, sizeof (wc));
	
	wc.style		 = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc	 = WndProc;
	wc.hInstance	 = hInstance_;
	wc.hCursor		 = LoadCursor (nullptr, IDC_ARROW);
	 // �������� ���� �� �����, �.�. ������������ ������� �����������, ��� ���� �������� ����
	wc.hbrBackground = (HBRUSH) GetStockObject (NULL_BRUSH);
	wc.lpszClassName = sm_szClassName;

	return ::RegisterClass (&wc);
}

 //
 // ������� �������
 //
LRESULT CALLBACK CAnimWindow::WndProc (HWND hWnd_, UINT message_, WPARAM wParam_, LPARAM lParam_)
{
	switch (message_)
	{
		case WM_CREATE:
			OnCreate (hWnd_);
		break;
		
		case WM_DESTROY:
			OnDestroy();
		break;

		case WM_PAINT:
			OnPaint();
		break;

		case WM_TIMER:
			OnTimer();
		break;
	}
	return DefWindowProc (hWnd_, message_, wParam_, lParam_);
}  //CAnimWindow::WndProc

 //
 // ����������� ���������
 //

void CAnimWindow::OnCreate (HWND hWnd_)
{
	sm_hWnd = hWnd_;
	SetTimer (sm_hWnd, 0, g_nTimerElapse, nullptr);
}


void CAnimWindow::OnDestroy()
{
	PostQuitMessage (0);
}


void CAnimWindow::OnPaint()
{
	 // --- ��������� ����� ��������� ---

	CMemoryBitmap& bitmap = MemoryBitmap();  // ������ (�����) - ��� ���������� ������
	RECT rc;
	GetClientRect (sm_hWnd, & rc);
	bool fSizeModified;
	bitmap.SetSize (rc.right, rc.bottom, fSizeModified);
	bitmap.Clear(RGB(0, 255,255)); //(RGB (rand(),rand(), rand()));

	 // --- ������� �������� ���������, ������� ��� � ������� ��������� ---

	CDrawContext drawContext (bitmap, rc.left, rc.bottom, rc.right, rc.top,
							  g_dSceneLeft, g_dSceneBottom, g_dSceneRight, g_dSceneTop);

	 // --- ������������ ����������� � ������ ---

	double t = double (g_nTime) / g_nMaxTime;
	g_quad.Draw (drawContext, t);
	g_quad1.Draw(drawContext, t);
	 // --- ����������� ����������� �� ������ � ���� ---

	COnPaintDC dc (sm_hWnd);
	bitmap.BlitTo (dc);
}


void CAnimWindow::OnTimer()
{
	g_nTime += g_nTimeInc;

	if (g_nTime >= g_nMaxTime)
		g_nTimeInc = -1;
	else if (g_nTime == 0)
		g_nTimeInc = 1;

	InvalidateRect (sm_hWnd, nullptr, TRUE);
}


void CAnimWindow::Create (HINSTANCE hInstance_)
{
	RegisterClass (hInstance_);
	sm_hWnd = ::CreateWindow (sm_szClassName, _T("�������� �������"), WS_VISIBLE | WS_OVERLAPPEDWINDOW,
							  0, 0, 600, 400, nullptr, nullptr, hInstance_, 0L);
}

 // --- class CAnimWindow -----------------------------------------------------


 // --- WinMain ---------------------------------------------------------------

 //
 // ������� �������
 //
int APIENTRY WinMain (HINSTANCE hInstance_, HINSTANCE, LPSTR, int)
{
	 // ������� ����
	CAnimWindow::Create (hInstance_);

	MSG msg;
	while (GetMessage (&msg, nullptr, 0, 0))
		DispatchMessage (&msg);
		
	return (int) msg.wParam;
}

 // --- WinMain ---------------------------------------------------------------

 // --- main.cpp ---