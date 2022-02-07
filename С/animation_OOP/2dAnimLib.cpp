
 // +++ 2dAnimLib.cpp +++

 //
 // Основы ООП. Простая анимация на базе GDI.
 //
 // *** НЕ ИЗМЕНЯТЬ ***
 //

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cassert>
#include <vector>
#include <tchar.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "2dAnimLib.h"


 // --- class CPoints ---------------------------------------------------------

 //
 // массив координат точек
 //

void CPoints::Interpolate (const CPoints& pts0_, const CPoints& pts1_, double t_)
{
	unsigned n = pts0_.Count();
	if (pts1_.Count() != n)
		return;

	resize (n);
	for (unsigned i = 0; i < n; i++)
		at (i).Interpolate (pts0_ [i], pts1_ [i], t_);
}

 // --- class CPoints ---------------------------------------------------------


 // --- class CAffineMatrix ---------------------------------------------------

 //
 // матрица преобразования
 //

 //
 // создание матрицы переноса
 //
CAffineMatrix CAffineMatrix::Translate (double dx_, double dy_)
{
	CAffineMatrix am;
	am.m_data[2][0] = dx_;
	am.m_data[2][1] = dy_;
	return am;
}

 //
 // создание матрицы масштабирования
 //
CAffineMatrix CAffineMatrix::Scale (double kx_, double ky_)
{
	CAffineMatrix am;
	am.m_data[0][0] = kx_;
	am.m_data[1][1] = ky_;
	return am;
}

 //
 // создание матрицы вращения
 //
CAffineMatrix CAffineMatrix::Rotate (const CVector& vCosSin_)
{
	CAffineMatrix am;
	am.m_data[0][0] = am.m_data[1][1] = vCosSin_.x;
	am.m_data[1][0] = -vCosSin_.y;
	am.m_data[0][1] =  vCosSin_.y;
	return am;
}

 //
 // сложение матриц
 //
CAffineMatrix operator + (const CAffineMatrix& am0_, const CAffineMatrix& am1_)
{
	CAffineMatrix am;
	int i, j;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			am.m_data[i][j] = am0_.m_data[i][j] + am1_.m_data[i][j];
	return am;
}

 //
 // вычитание матриц
 //
CAffineMatrix operator - (const CAffineMatrix& am0_, const CAffineMatrix& am1_)
{
	CAffineMatrix am;
	int i, j;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			am.m_data[i][j] = am0_.m_data[i][j] - am1_.m_data[i][j];
	return am;
}

 //
 // умножение матрицы на число
 //
CAffineMatrix operator * (const CAffineMatrix& am_, double v_)
{
	CAffineMatrix am;
	int i, j;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			am.m_data[i][j] = am_.m_data[i][j] * v_;
	return am;
}

 //
 // перемножение матриц
 //
CAffineMatrix operator * (const CAffineMatrix& am0_, const CAffineMatrix& am1_)
{
	CAffineMatrix am;
	ZeroMemory (& am.m_data, sizeof (am.m_data));
	int i, j, k;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			for (k = 0; k < 3; k++)
				am.m_data[i][j] += am0_.m_data[i][k] * am1_.m_data[k][j];
	return am;
}

 //
 // умножение точки на матрицу
 //
CPoint operator * (const CPoint& pt_, const CAffineMatrix& am_)
{
	return CPoint (pt_.x * am_.m_data[0][0] + pt_.y * am_.m_data[1][0] + am_.m_data[2][0],
				   pt_.x * am_.m_data[0][1] + pt_.y * am_.m_data[1][1] + am_.m_data[2][1]);
}

CPoint& operator *= (CPoint& pt_, const CAffineMatrix& am_)
{
	pt_ = pt_ * am_;
	return pt_; 
}

 //
 // умножение массива точек на матрицу
 //
CPoints operator * (const CPoints& pts_, const CAffineMatrix& am_)
{
	unsigned n = pts_.Count(), i;
	CPoints newPts (n);
	for (i = 0; i < n; i++)
		newPts [i] = pts_ [i] * am_;

	return newPts;
}

CPoints& operator *= (CPoints& pts_, const CAffineMatrix& am_)
{
	unsigned n = pts_.Count(), i;
	for (i = 0; i < n; i++)
		pts_ [i] *= am_;

	return pts_; 
}

 // --- class CAffineMatrix ---------------------------------------------------


 // --- class CMemoryBitmap ---------------------------------------------------

 //
 // установка размера в пикселях
 //
void CMemoryBitmap::SetSize (unsigned width_, unsigned height_, bool& fSizeModified_)
{
	fSizeModified_ = false;

	if (! width_ || ! height_)
	{
		Destroy();
		return;
	}
	if (   width_ <= m_width
		&& height_ <= m_height)
	{
		return;
	}
	m_width = width_;
	m_height = height_;
	fSizeModified_ = true;

	if (m_width > 4096)
		m_width = 4096;
	if (m_height > 4096)
		m_height = 4096;

	CGetDC screenDC (nullptr);

	if (! m_hDC)
		m_hDC = CreateCompatibleDC (screenDC);

	if (m_hPrevBitmap)
	{
		SelectObject (m_hDC, m_hPrevBitmap);
		DeleteObject (m_hBitmap);
		m_hPrevBitmap = m_hBitmap = nullptr;
	}

	m_hBitmap = CreateCompatibleBitmap (screenDC, m_width, m_height);
	assert (m_hBitmap);

	m_hPrevBitmap = (HBITMAP) SelectObject (m_hDC, m_hBitmap);
}


void CMemoryBitmap::Clear (COLORREF color_)
{
	CGdiObject brush (CreateSolidBrush (color_));
	RECT rc = { 0, 0, m_width, m_height };
	FillRect (m_hDC, &rc, (HBRUSH) (HGDIOBJ) brush);
}


void CMemoryBitmap::Destroy()
{
	if (m_hPrevBitmap)
	{
		SelectObject (m_hDC, m_hPrevBitmap);
		verify (DeleteObject (m_hBitmap));
		m_hPrevBitmap = m_hBitmap = nullptr;
		verify (DeleteDC (m_hDC));
		m_hDC = nullptr;
		m_width = m_height = 0;
	}
}

 // --- class CMemoryBitmap ---------------------------------------------------


 // --- class CDrawContext ----------------------------------------------------

 //
 // контекст рисования в модельных координатах
 //

void CDrawContext::SetViewport (int left_, int bottom_, int right_, int top_)
{
	m_left = min (left_, right_);
	m_right = max (left_, right_);
	m_bottom = max (bottom_, top_);
	m_top = min (bottom_, top_);

	if (m_right <= m_left)
		m_right = m_left + 1;
	if (m_bottom <= m_top)
		m_bottom = m_top + 1;

	m_ptViewportCenter.x = (m_left + m_right) / 2;
	m_ptViewportCenter.y = (m_bottom + m_top) / 2;
}


void CDrawContext::SetModelBox (double dLeft_, double dBottom_, double dRight_, double dTop_)
{
	m_dLeft = min (dLeft_, dRight_);
	m_dRight = max (dLeft_, dRight_);
	m_dBottom = min (dBottom_, dTop_);
	m_dTop = max (dBottom_, dTop_);

	if (m_dRight - m_dLeft <= EPSILON)
		m_dRight = m_dLeft + 1.0;
	if (m_dTop - m_dBottom <= EPSILON)
		m_dTop = m_dBottom + 1.0;

	if (m_right <= m_left)
		m_right = m_left + 1;
	if (m_bottom <= m_top)
		m_bottom = m_top + 1;

	double viewWtoH = double (m_right - m_left) / (m_bottom - m_top),
		   mxc = (m_dLeft + m_dRight) * 0.5,
		   myc = (m_dBottom + m_dTop) * 0.5,
		   mw = m_dRight - m_dLeft,
		   mh = m_dTop - m_dBottom,
		   modWtoH = mw / mh;

	if (viewWtoH > modWtoH)
	{
		double mw12 = mh * viewWtoH * 0.5;
		m_dLeft = mxc - mw12;
		m_dRight = mxc + mw12;
	}
	else
	{
		double mh12 = mw / viewWtoH * 0.5;
		m_dBottom = myc - mh12;
		m_dTop = myc + mh12;
	}

	m_vModelCenter.x = (m_dLeft + m_dRight) * 0.5;
	m_vModelCenter.y = (m_dBottom + m_dTop) * 0.5;

	m_dModDevRatio = (m_dRight - m_dLeft) / (m_right - m_left);
}


CPoint CDrawContext::DCtoWC (const POINT& pt_) const
{
	return CPoint ((pt_.x - m_ptViewportCenter.x) * m_dModDevRatio + m_vModelCenter.x,
				   (m_bottom + m_top - pt_.y - m_ptViewportCenter.y) * m_dModDevRatio + m_vModelCenter.y);
}


POINT CDrawContext::WCtoDC (const CPoint& v_) const
{
	CPoint v = (v_ - m_vModelCenter) * (1.0 / m_dModDevRatio);
	POINT pt =
	{
		AlRound (v.x) + m_ptViewportCenter.x,
		- (AlRound (v.y) + m_ptViewportCenter.y) + m_bottom + m_top
	};
	return pt;
}


void CDrawContext::Line (const CPoint& p0_, const CPoint& p1_)
{
	POINT pt0 = WCtoDC (p0_),
		  pt1 = WCtoDC (p1_);
	MoveToEx (m_hDC, pt0.x, pt0.y, nullptr);
	LineTo (m_hDC, pt1.x, pt1.y);
}


void CDrawContext::Polyline (const CPoints& pts_, bool fClosed_)
{
	unsigned n = pts_.Count();
	if (! n)
		return;
	std::vector <POINT> intPts (n);
	for (unsigned i = 0; i < n; i++)
		intPts [i] = WCtoDC (pts_ [i]);
	if (fClosed_)
	{
		intPts.push_back (WCtoDC (pts_ [0]));
		n++;
	}
	::Polyline (m_hDC, & intPts.front(), n);
}


void CDrawContext::Polylines (const std::vector <CPoints>& pts_)
{
	unsigned npl = 0, npt = 0, i, j, k, n;
	 // npl - количество линий
	npl = (unsigned) pts_.size();
	if (! npl)
		return;
	 // npt - общее количество точек
	std::vector <DWORD> counts (npl);
	npt = 0;
	for (i = 0; i < npl; i++)
	{
		counts [i] = (unsigned) pts_ [i].size();
		npt += counts [i];
		if (! counts [i])
			return;
	}
	std::vector <POINT> intPts (npt);
	for (i = 0, k = 0; i < npl; i++)
	{
		const CPoints& pts = pts_ [i];
		n = pts.Count();
		for (j = 0; j < n; j++)
			intPts [k++] = WCtoDC (pts [j]);
	}
	PolyPolyline (m_hDC, & intPts.front(), & counts.front(), npl);
}


void CDrawContext::Polygon (const CPoints& pts_)
{
	unsigned n = pts_.Count();
	if (! n)
		return;
	std::vector <POINT> intPts (n);
	for (unsigned i = 0; i < n; i++)
		intPts [i] = WCtoDC (pts_ [i]);
	::Polygon (m_hDC, & intPts.front(), n);
}


void CDrawContext::Polygons (const std::vector <CPoints>& pts_)
{
	unsigned npg = 0, npt = 0, i, j, k, n;
	 // npl - количество многоугольников
	npg = (unsigned) pts_.size();
	if (! npg)
		return;
	 // npt - общее количество точек
	std::vector <INT> counts (npg);
	npt = 0;
	for (i = 0; i < npg; i++)
	{
		counts [i] = (unsigned) pts_ [i].size();
		npt += counts [i];
		if (! counts [i])
			return;
	}
	std::vector <POINT> intPts (npt);
	for (i = 0, k = 0; i < npg; i++)
	{
		const CPoints& pts = pts_ [i];
		n = pts.Count();
		for (j = 0; j < n; j++)
			intPts [k++] = WCtoDC (pts [j]);
	}
	PolyPolygon (m_hDC, & intPts.front(), & counts.front(), npg);
}

 // --- class CDrawContext ----------------------------------------------------


 // --- class CContextMenu ----------------------------------------------------

 //
 // простое контекстное меню для вызова команд
 //

void CContextMenu::AddItem (LPCTSTR szText_, UINT flags_ /* = 0 */)
{
	assert (m_hMenu);
	 // игнорировать все флаги кроме MF_AUX_FLAGS
	flags_ &= MF_AUX_FLAGS;
	UINT nID = GetMenuItemCount (m_hMenu) + 1;
	 // если текст не задан - сформировать по номеру пункта
	if (! szText_)
	{
		TCHAR acBuff [256] = { 0 };
		_stprintf_s (acBuff, _T("Команда %d"), nID);
		AppendMenu (m_hMenu, MF_STRING | flags_, nID, acBuff);
	}
	else
		AppendMenu (m_hMenu, MF_STRING | flags_, nID, szText_);
}


void CContextMenu::AddItem (UINT nCmdID_ /* = 0 */, LPCTSTR szText_ /* = nullptr */, UINT flags_ /* = 0 */)
{
	assert (m_hMenu);
	 // игнорировать все флаги кроме MF_AUX_FLAGS
	flags_ &= MF_AUX_FLAGS;
	 // добавление разделителя
	if (! nCmdID_)
		AppendMenu (m_hMenu, MF_SEPARATOR, 0, nullptr);
	 // если текст не задан - сформировать по ID команды
	else if (! szText_)
	{
		TCHAR acBuff [256] = { 0 };
		_stprintf_s (acBuff, _T("Команда %d"), nCmdID_);
		AppendMenu (m_hMenu, MF_STRING | flags_, nCmdID_, acBuff);
	}
	else
		AppendMenu (m_hMenu, MF_STRING | flags_, nCmdID_, szText_);
}


void CContextMenu::AddItem (CContextMenu& subMenu_, LPCTSTR szText_, UINT flags_ /* = 0 */)
{
	assert (this != &subMenu_);
	 // игнорировать все флаги кроме MF_AUX_FLAGS
	flags_ &= MF_AUX_FLAGS;
	AppendMenu (m_hMenu, MF_POPUP | flags_, (UINT_PTR) subMenu_.m_hMenu, szText_ ? szText_ : _T("Команда"));
}


UINT CContextMenu::Track (HWND hWndOwner_, POINT pt_)
{
	assert (m_hMenu);
	assert (GetMenuItemCount (m_hMenu));
	 // преобразование координат из клиентских окна hWndOwner_ в экранные
	ClientToScreen (hWndOwner_, &pt_);
	return TrackPopupMenu (m_hMenu, TPM_RETURNCMD, pt_.x, pt_.y, 0, hWndOwner_, nullptr);
}


UINT CContextMenu::Track (HWND hWndOwner_)
{
	assert (m_hMenu);
	assert (GetMenuItemCount (m_hMenu));
	POINT pt;
	GetCursorPos (&pt);
	return TrackPopupMenu (m_hMenu, TPM_RETURNCMD, pt.x, pt.y, 0, hWndOwner_, nullptr);
}

 // --- class CContextMenu ----------------------------------------------------

 //
 // битмар в памяти для буферизации рисования
 //
CMemoryBitmap& MemoryBitmap()
{
	static CMemoryBitmap inst;
	return inst;
}

 //
 // вычисление точки пересечения 2 прямых
 //
bool CalcIntersAxisAxis (const CPoint& pb0_, const CPoint& pe0_, const CPoint& pb1_, const CPoint& pe1_,
						 CPoint& pi_)
{
	CVector v0 = pe0_ - pb0_,
			v1 = pb1_ - pe1_;
	double den = v0.x * v1.y - v0.y * v1.x;
	if (fabs (den) <= EPSILON)
		return false;

	CVector v2 = pb1_ - pb0_;
	pi_ = pb0_ + v0 * (v2.x * v1.y - v2.y * v1.x) / den;

	return true;
}

 //
 // вычисление точки пересечения 2 отрезков
 //
bool CalcIntersLineLine (const CPoint& pb0_, const CPoint& pe0_, const CPoint& pb1_, const CPoint& pe1_,
						 CPoint& pi_)
{
	CVector v0 = pe0_ - pb0_,
			v1 = pb1_ - pe1_;
	double den = v0.x * v1.y - v0.y * v1.x;
	if (fabs (den) <= EPSILON)
		return false;

	CVector v2 = pb1_ - pb0_;
	double u0 = (v2.x * v1.y - v2.y * v1.x) / den,
		   u1 = (v2.y * v0.x - v2.x * v0.y) / den;

	 // проверить - точка должна попадать на оба отрезка
	if (   u0 < -EPSILON
		|| u0 > 1.0 + EPSILON
		|| u1 < -EPSILON
		|| u1 > 1.0 + EPSILON)
	{
		return false;
	}
	pi_ = pb0_ + v0 * u0;

	return true;
}

 //
 // вычисление точек пересечения прямой и окружности
 // 
unsigned CalcIntersAxisCircle (const CPoint& pab_, const CPoint& pae_,  // прямая
							   const CPoint& pсc_, double cr_,			// окружность
							   CPoint& pi0_, CPoint& pi1_)
{
	 // использовать ЛСК прямой в точке pab_
	CVector ven (pae_ - pab_),
			vc (pсc_ - pab_);
	ven.Normalize();
	vc.Rotate (-ven.y, ven.x);
	if (fabs (vc.y) > cr_)
		return 0;

	double dc = cr_ * cr_ - vc.y * vc.y;
	if (dc < 0.0)
		return 0;

	dc = sqrt (dc);
	pi0_.x = vc.x - dc;
	pi1_.x = vc.x + dc;
	pi0_.Rotate (ven.y, ven.x);
	pi0_ += pab_;

	if (dc <= EPSILON)
		return 1;

	pi1_.Rotate (ven.y, ven.x);
	pi1_ += pab_;

	return 2;
}

 //
 // вычисление точек пересечения 2 окружностей
 //
unsigned CalcIntersCircleCircle (const CPoint& pc0_, double r0_, const CPoint& pc1_, double r1_,
								 CPoint& pi0_, CPoint& pi1_)
{
	 // найти расстояние между центрами
	CPoint vc (pc1_ - pc0_);
	double d = vc.Length();
	if (   d > r0_ + r1_
		|| d + r0_ < r1_
		|| d + r1_ < r0_)
	{
		return 0;
	}
	 // найти точки пересечения в ЛСК окружности (pc0_, r0_)
	pi0_.x = pi1_.x = (r0_ * r0_ - r1_ * r1_ + d * d) / (2.0 * d);
	double dc = r0_ * r0_ - pi0_.x * pi0_.x;
	if (dc < 0.0)
		return 0;

	 // перенести точки пересечения в МСК
	CVector vcn = vc / d;
	pi0_.y = sqrt (dc);
	pi1_.y = - pi0_.y;
	pi0_.Rotate (vcn.y, vcn.x);
	pi0_ += pc0_;

	if (dc <= EPSILON)
		return 1;

	pi1_.Rotate (vcn.y, vcn.x);
	pi1_ += pc0_;

	return 2;
}

 //
 // тест функций CalcInters...
 //
struct CIntersTest
{
	CIntersTest()
	{
		CPoint piaa;  // д.б. [12.07, -7.05]
		CalcIntersAxisAxis (CPoint (-3, 5), CPoint (-8, 9), CPoint (13, 20), CPoint (12, -9), piaa);

		CPoint pill;  // д.б. [3, 2]
		CalcIntersLineLine (CPoint (1, -1), CPoint (5, 5), CPoint (5, -1), CPoint (1, 5), pill);

		CPoint piac0, piac1;  // д.б. [5.52, 5.78], [10.33, 12.99]
		CalcIntersAxisCircle (CPoint (1, -1), CPoint (5, 5), CPoint (10, 8), 5, piac0, piac1);

		CPoint picc0, picc1;  // д.б. [18.06, 15.95], [21.98, 8.69]
		CalcIntersCircleCircle (CPoint (12.0, 8.0), 10.0, CPoint (25.0, 15.0), 7.0, picc0, picc1);
	}
};  // test;

 // --- 2dAnimLib.cpp ---