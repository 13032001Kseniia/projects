
 // +++ main.h +++

 //
 // ������ ���. ������� �������� �� ���� GDI. �������� �������. ������� ������.
 //

#pragma once


 // --- class CQuad ------------------------------------------------

 //
 // �++-����� ������� - ��������
 //
class CQuad
{
protected:
	 
	 // �������� ���������� �������
	CPoints m_aSrcPoints;

	 // ����� ������� � �������
	COLORREF m_nBorderColor, m_nFillColor;

public:

	 // ����������� �� ��������� - ������������� ����� � ���������� �������� ��������� ������
	CQuad();

	 // ��������� ������ � ������ ������� t_ [0..1]
	void Draw (CDrawContext& context_, double t_);
};

 // --- class CQuad -----------------------------------------------------------


 // --- class CAnimWindow -----------------------------------------------------

 //
 // �++-����� ���� ���������� (�������������� ���� � ������������ ����������)
 //
class CAnimWindow
{
public:

	 // ��� Windows-������ ����
	static LPCTSTR sm_szClassName;

protected:

	 // ���������� ����
	static HWND sm_hWnd;

	 // ����������� Windows-������ ����
	static WORD RegisterClass (HINSTANCE hInstance_);

	 // ������� �������
	static LRESULT CALLBACK WndProc (HWND hWnd_, UINT message_, WPARAM wParam_, LPARAM lParam_);

	 // ����������� ���������
	static void OnCreate (HWND hWnd_);
	static void OnDestroy();
	static void OnPaint();
	static void OnTimer();

public:
	
	 // �������� ����
	static void Create (HINSTANCE hInstance_);
};

 // --- class CAnimWindow -----------------------------------------------------


 // --- main.h ---