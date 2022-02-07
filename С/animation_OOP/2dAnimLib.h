
 // +++ 2dAnimLib.h +++

 //
 // ������ ���. ������� �������� �� ���� GDI.
 //
 // *** �� �������� ***
 //

#pragma once

#ifdef _DEBUG
	#define verify(expression) assert(expression)
#else
	#define verify(expression) expression
#endif

#define EPSILON 1e-9

 //
 // ���������� ����� � ���������� �� ������ ��������
 //
inline int AlRound (double d_)
{
	double d = 0.0;
	if (d_ > 0.0)
	{
		d = floor (d_);
		if (d_ - d >= 0.5)
			d += 1.0;
	}
	else if (d_ < 0.0)
	{
		d = ceil (d_);
		if (d - d_ >= 0.5)
			d -= 1.0;
	}
	return int (d);
}

 //
 // ��������� ���������� ����� (������������)
 //
inline COLORREF MixedColor (COLORREF color1_, COLORREF color2_, double t_)
{
	double t1 = 1.0 - t_;
	BYTE r1 = GetRValue (color1_),
		 g1 = GetGValue (color1_),
		 b1 = GetBValue (color1_),
		 r2 = GetRValue (color2_),
		 g2 = GetGValue (color2_),
		 b2 = GetBValue (color2_),
		 r = BYTE (t1 * r1 + t_ * r2),
		 g = BYTE (t1 * g1 + t_ * g2),
		 b = BYTE (t1 * b1 + t_ * b2);
	return RGB (r, g, b);
}

 //
 // ��������� ���������� ����� �� ��������� [ min_, max_ ]
 //
inline double Rnd (double min_, double max_)
{
	double t = double (rand()) / RAND_MAX;
	return (1.0 - t) * min_ + t * max_;
}

inline int Rnd (int min_, int max_)
{
	return AlRound (Rnd ((double) min_, (double) max_));
}

 //
 // ��������� ���������� �����
 //
inline COLORREF RndColor()
{
	return RGB (BYTE (rand() % 255), BYTE (rand() % 255), BYTE (rand() % 255));
}


 // --- struct CPoint ---------------------------------------------------------

 //
 // ���������� ����� ��� �������
 //
struct CPoint
{
	double x, y;

	 // �������������
	CPoint() : x (0.0), y (0.0)
	{}

	CPoint (double x_, double y_) : x (x_), y (y_)
	{}

	 // ����������� �����������, �������� ����������� -
	 // ������������ ����������� ������������

	 // ��������, ���������
	CPoint operator + (const CPoint& other_) const
	{
		return CPoint (x + other_.x, y + other_.y);
	}

	CPoint& operator += (const CPoint& other_)
	{
		x += other_.x;
		y += other_.y;

		return *this;
	}

	CPoint operator - (const CPoint& other_) const
	{
		return CPoint (x - other_.x, y - other_.y);
	}

	CPoint& operator -= (const CPoint& other_)
	{
		x -= other_.x;
		y -= other_.y;

		return *this;
	}

	 // ���������, ������� �� �����
	CPoint operator * (double v_) const
	{
		return CPoint (x * v_, y * v_);
	}

	CPoint& operator *= (double v_)
	{
		x *= v_;
		y *= v_;

		return *this;
	}

	CPoint operator / (double v_) const
	{
		if (0.0 == v_)
		{
			assert (! "������� ������� �� 0");
			return CPoint();
		}
		return CPoint (x / v_, y / v_);
	}

	CPoint& operator /= (double v_)
	{
		if (0.0 == v_)
			assert (! "������� ������� �� 0");
		else
		{
			x /= v_;
			y /= v_;
		}
		return *this;
	}

	 // ���������
	bool operator == (const CPoint& other_) const
	{
		return x == other_.x && y == other_.y;
	}

	bool operator != (const CPoint& other_) const
	{
		return    x != other_.x
			   || y != other_.y;
	}

	 // �������� - ����� ������� ?
	bool IsNull() const
	{
		return    0.0 == x
			   && 0.0 == y;
	}

	 // ���������� ����� �������
	double Length() const
	{
		return _hypot (x, y);
	}

	 // ������������ �������
	bool Normalize()
	{
		if (IsNull())
			return false;

		double L = Length();
		x /= L;
		y /= L;

		return true;
	}

	 // ��������� ������������ ��������
	double operator * (const CPoint& other_) const
	{
		return x * other_.x + y * other_.y;
	}

	 // ��������
	void Rotate (double dSin_, double dCos_)
	{
		double x0 = x,
			   y0 = y;
		x = x0 * dCos_ - y0 * dSin_;
		y = x0 * dSin_ + y0 * dCos_;
	}

	 // �������� ������������ - ��������� �����,
	 // ����������� ����� ������� p0_ � p1_, � ����������� t_ �� ����������
	void Interpolate (const CPoint& p0_, const CPoint& p1_, double t_)
	{
		x = p0_.x * (1.0 - t_) + p1_.x * t_;
		y = p0_.y * (1.0 - t_) + p1_.y * t_;
	}
};

 // �������������� ��� - ���������� �������,
 // ������������� ������������ � �������, ����� [ x, y ] ���������� �����������, � �� �������
typedef CPoint CVector;

 // --- struct CPoint ---------------------------------------------------------


 // --- struct CRect ----------------------------------------------------------

 //
 // ������������� �� ���������, ������������� ���� ���������
 //
struct CRect
{
	double left, bottom, right, top;

	 // �������������
	CRect() : left (0.0), bottom (0.0), right (0.0), top (0.0)
	{}

	CRect (double left_, double bottom_, double right_, double top_) :
		left (left_), bottom (bottom_), right (right_), top (top_)
	{
		Norm();
	}

	CRect (const CPoint& pt0_, const CPoint& pt1_) :
		left (pt0_.x), bottom (pt0_.y), right (pt1_.x), top (pt1_.y)
	{
		Norm();
	}

	 // ������������ (������������ ��������)
	void Norm()
	{
		if (left > right)
			std::swap (left, right);
		if (top < bottom)
			std::swap (top, bottom);
	}
};

 // --- struct CRect ----------------------------------------------------------


 // --- class CPoints ---------------------------------------------------------

 //
 // ������ ��������� �����
 //
class CPoints : public std::vector <CPoint>
{
public:

	 // �������������, ����������� - ������������ ���������� �� std::vector
	CPoints() : std::vector <CPoint>()
	{}

	CPoints (unsigned nCount_) : std::vector <CPoint> (nCount_)
	{}

	 // ����������� �����������, �������� ����������� -
	 // ������������ ����������� ������������

	 // ���������� �����
	void Add (double x_, double y_)
	{
		push_back (CPoint (x_, y_));
	}

	void Add (const CPoint& pt_)
	{
		push_back (pt_);
	}

	 // ��������� ���������� �����
	unsigned Count() const
	{
		return (unsigned) size();
	}

	 // �������� ������������ ��� ���� �����
	void Interpolate (const CPoints& pts0_, const CPoints& pts1_, double t_);
};

 // --- class CPoints ---------------------------------------------------------


 // --- class CAffineMatrix ---------------------------------------------------

 //
 // ������� ��������������
 //
class CAffineMatrix
{
protected:

	double m_data[3][3];

public:

	 //
	 // ��������� ��������� �������
	 //
	CAffineMatrix()
	{
		SetIdentity();
	}

	 // ����������� �����������, �������� ����������� -
	 // ������������ ����������� ������������

	 //
	 // ���������, ��������� �������� �� ��������
	 //
	double& operator () (unsigned i_, unsigned j_)  // ��������� ��� ���������
	{
		assert (i_ < 3);
		assert (j_ < 3);
		return m_data[i_][j_];
	}

	double operator () (unsigned i_, unsigned j_) const  // ������ ���������
	{
		assert (i_ < 3);
		assert (j_ < 3);
		return m_data[i_][j_];
	}

	 //
	 // ��������� ��������� �������
	 //
	void SetIdentity()
	{
		ZeroMemory (&m_data, sizeof (m_data));
		m_data[0][0] = m_data[1][1] = m_data[2][2] = 1.0;
	}

	 //
	 // �������� ������� ��������
	 //
	static CAffineMatrix Translate (double dx_, double dy_);
	
	static CAffineMatrix Translate (const CPoint& offset_)
	{
		return Translate (offset_.x, offset_.y);
	}

	 //
	 // �������� ������� ���������������
	 //
	static CAffineMatrix Scale (double kx_, double ky_);

	static CAffineMatrix Scale (const CPoint& scale_)
	{
		return Scale (scale_.x, scale_.y);
	}

	 // �������� ������� ��������
	static CAffineMatrix Rotate (const CVector& vCosSin_);

	static CAffineMatrix Rotate (double angle_)
	{
		return Rotate (CVector (cos (angle_), sin (angle_)));
	}

	 //
	 // �������� ������� ���������
	 //
	static CAffineMatrix MirrorX()
	{
		return Scale (-1.0, 1.0);  // ����� x
	}

	static CAffineMatrix MirrorY()
	{
		return Scale (1.0, -1.0);  // ����� y
	}

	 // �������� ������
	friend CAffineMatrix operator + (const CAffineMatrix& am0_, const CAffineMatrix& am1_);

	 // ��������� ������
	friend CAffineMatrix operator - (const CAffineMatrix& am0_, const CAffineMatrix& am1_);

	 // ��������� ������� �� �����
	friend CAffineMatrix operator * (const CAffineMatrix& am_, double v_);

	 // ������������ ������
	friend CAffineMatrix operator * (const CAffineMatrix& am0_, const CAffineMatrix& am1_);

	 // ��������� ����� �� �������
	friend CPoint operator * (const CPoint& pt_, const CAffineMatrix& am_);
	friend CPoint& operator *= (CPoint& pt_, const CAffineMatrix& am_);

	 // ��������� ������� ����� �� �������
	friend CPoints operator * (const CPoints& pts_, const CAffineMatrix& am_);
	friend CPoints& operator *= (CPoints& pts_, const CAffineMatrix& am_);
};

 // --- class CAffineMatrix ---------------------------------------------------


 // --- class COnPaintDC ------------------------------------------------------

 //
 // �����, ����������� �������� BeginPaint -- EndPaint (��� ��������� � ���� �� ��������� WM_PAINT)
 //
class COnPaintDC
{
protected:

	 // ����, � ������� ����� ��������
	HWND m_hWnd;

	 // ������ ���������
	PAINTSTRUCT m_ps;

	 // ���������� �������� ���������
	HDC m_hDC;

public:

	COnPaintDC (HWND hWnd_) :
		m_hWnd (hWnd_),
		m_hDC  (nullptr)
	{
		m_hDC = BeginPaint (m_hWnd, & m_ps);
	}

	~COnPaintDC()
	{
		EndPaint (m_hWnd, & m_ps);
	}

	operator HDC() const
	{
		return m_hDC;
	}

	const PAINTSTRUCT& PaintStruct() const
	{
		return m_ps;
	}

	 // ����������� � ������������ ���������
private:

	COnPaintDC (const COnPaintDC &);
	COnPaintDC& operator = (const COnPaintDC &);
};

 // --- class COnPaintDC ------------------------------------------------------


 // --- class CGetDC ----------------------------------------------------------

 //
 // �����, ����������� �������� GetDC -- ReleaseDC (��� ��������� � ����)
 //
class CGetDC
{
protected:

	 // ����, � ������� ����� ��������
	HWND m_hWnd;

	 // ���������� �������� ���������
	HDC m_hDC;

public:

	CGetDC (HWND hWnd_) :
		m_hWnd (hWnd_),
		m_hDC  (nullptr)
	{
		m_hDC = GetDC (m_hWnd);
	}

	~CGetDC()
	{
		ReleaseDC (m_hWnd, m_hDC);
	}

	operator HDC() const
	{
		return m_hDC;
	}

	 // ����������� � ������������ ���������
private:

	CGetDC (const CGetDC &);
	CGetDC& operator = (const CGetDC &);
};

 // --- class CGetDC ----------------------------------------------------------


 // --- class CGdiObject ------------------------------------------------------

 //
 // ����� ��� ���������� �������� GDI
 //
class CGdiObject
{
protected:

	 // ������ GDI, ����������� ������ ��������
	HGDIOBJ m_hObject;

	 // ��������, � ������� ������ ����������� ������ GDI
	HDC m_hDC;
	HGDIOBJ m_hOldObject;

	 // ������� ������ GDI ��� �������� ������� �������
	bool m_fAutoDelete;

public:

	 // ����������� - ����� ������� GDI � �������� ���������
	 //   hObj_ - ����������� ������ GDI
	 //   hDCforSelect_ - ��������, � ������� ����� ������� ����������� ������ GDI (���� �� ����� - nullptr),
	 //                   ���� == nullptr - ������ GDI �� ����������
	 //   fAutoDelete_ - ������� ����������� ������ GDI ��� �������� ������� ������� (���� �� ����� - true)
	CGdiObject (HGDIOBJ hObj_, HDC hDCforSelect_ = nullptr, bool fAutoDelete_ = true) :
		m_hObject (hObj_),
		m_hDC (hDCforSelect_),
		m_hOldObject (nullptr),
		m_fAutoDelete (fAutoDelete_)
	{
		assert (m_hObject);
		if (m_hDC)
		{
			m_hOldObject = SelectObject (m_hDC, m_hObject);
			assert (m_hOldObject != m_hObject);
		}
	}

	 // ����������� - ����� ������������ ������� GDI � �������� ���������
	CGdiObject (int iStockObj_, HDC hDCforSelect_ = nullptr) :
		m_hObject (GetStockObject (iStockObj_)),
		m_hDC (hDCforSelect_),
		m_hOldObject (nullptr),
		m_fAutoDelete (false)
	{
		assert (m_hObject);
		if (m_hDC)
		{
			m_hOldObject = SelectObject (m_hDC, m_hObject);
			assert (m_hOldObject != m_hObject);
		}
	}

	 // ���������� - ����� � �������� ����� ��������� ��������� ������� GDI,
	 // �������� ������������ ������� GDI
	~CGdiObject()
	{
		if (   m_hDC
			&& m_hOldObject)
		{
			SelectObject (m_hDC, m_hOldObject);
		}
		if (   m_hObject
			&& m_fAutoDelete)
		{
			DeleteObject (m_hObject);
		}
	}

	 // ��������� ������������ ������� GDI
	operator HGDIOBJ() const
	{
		return m_hObject;
	}

	 // ������ ���������� �������� GDI
	HGDIOBJ Detach()
	{
		HGDIOBJ hObj = m_hObject;
		m_hObject = nullptr;
		m_hDC = nullptr;
		m_hOldObject = nullptr;
		m_fAutoDelete = false;
		return hObj;
	}

	 // �������� ������������ ������� GDI
	void Delete()
	{
		if (   m_hDC
			&& m_hOldObject)
		{
			SelectObject (m_hDC, m_hOldObject);
		}
		if (m_hObject)
		{
			DeleteObject (m_hObject);
		}
		m_hObject = nullptr;
		m_hDC = nullptr;
		m_hOldObject = nullptr;
		m_fAutoDelete = false;
	}

	 // ����������� � ������������ ���������
private:

	CGdiObject (const CGdiObject &);
	CGdiObject& operator = (const CGdiObject &);
};

 // --- class CGdiObject ------------------------------------------------------


 // --- class CPen ------------------------------------------------------------

 //
 // ����� ��� ���������� �����
 //
class CPen : public CGdiObject
{
public:

	 // �������� � ����� ����
	CPen (COLORREF color_, HDC hDCforSelect_ = nullptr, bool fAutoDelete_ = true) :
		CGdiObject (CreatePen (PS_SOLID, 3, color_), hDCforSelect_, fAutoDelete_)
	{}

	CPen (int style_, int width_, COLORREF color_, HDC hDCforSelect_ = nullptr, bool fAutoDelete_ = true) :
		CGdiObject (CreatePen (style_, width_, color_), hDCforSelect_, fAutoDelete_)
	{}
};

 // --- class CPen ------------------------------------------------------------


 // --- class CBrush ----------------------------------------------------------

 //
 // ����� ��� ���������� ������
 //
class CBrush : public CGdiObject
{
public:

	 // �������� � ����� ����� ��� �������� �������
	CBrush (COLORREF color_, HDC hDCforSelect_ = nullptr, bool fAutoDelete_ = true) :
		CGdiObject (CreateSolidBrush (color_), hDCforSelect_, fAutoDelete_)
	{}

	 // �������� � ����� ��������� �����
	CBrush (int style_, COLORREF color_, HDC hDCforSelect_ = nullptr, bool fAutoDelete_ = true) :
		CGdiObject (CreateHatchBrush (style_, color_), hDCforSelect_, fAutoDelete_)
	{}
};

 // --- class CBrush ----------------------------------------------------------


 // --- class CMemoryBitmap ---------------------------------------------------

 //
 // ������ � ������ ��� ����������� ��������� (��������, ��� ���������� �������� ��������)
 //
class CMemoryBitmap
{
protected:

	 // ��������, ��������� � ��������
	HDC m_hDC;

	 // ������
	HBITMAP m_hBitmap, m_hPrevBitmap;
	 
	 // ������� � ��������
	unsigned m_width, m_height;

public:

	 // �������������
	CMemoryBitmap() :
		m_hDC (nullptr),
		m_hBitmap (nullptr),
		m_hPrevBitmap (nullptr),
		m_width (0),
		m_height (0)
	{}

	 // ���������� - ������������ ������, ���������� ��������
	~CMemoryBitmap()
	{
		Destroy();
	}

	 // ��������� ������� � ��������
	void SetSize (unsigned width_, unsigned height_, bool& fSizeModified_);

	 // ��������� ���������, ���������� � ��������
	operator HDC() const
	{
		return m_hDC;
	}

	 // �������� ������� ������
	void Clear (COLORREF color_);

	 // ����������� ����������� (��������) �� �������� ����������� (��������) hDC_
	void BlitTo (HDC hDC_, int dstX_ = 0, int dstY_ = 0, int srcX_ = 0, int srcY_ = 0) const
	{
		BitBlt (hDC_, dstX_, dstY_, m_width, m_height, m_hDC, srcX_, srcY_, SRCCOPY);
	}

	 // ����������� ����������� � �������� ����������� hDC_
	void BlitFrom (HDC hDC_, int srcX_ = 0, int srcY_ = 0, int dstX_ = 0, int dstY_ = 0) const
	{
		BitBlt (m_hDC, dstX_, dstY_, m_width, m_height, hDC_, srcX_, srcY_, SRCCOPY);
	}

	 // �������� �������
	void Destroy();

	 // ����������� � ������������ ���������
private:

	CMemoryBitmap (const CMemoryBitmap &);
	CMemoryBitmap& operator = (const CMemoryBitmap &);
};

 // --- class CMemoryBitmap ---------------------------------------------------


 // --- class CDrawContext ----------------------------------------------------

 //
 // �������� ��������� � ��������� �����������
 //
class CDrawContext
{
protected:

	 // �������� ��������� GDI
	HDC m_hDC;

	 // ������� ��������� � �������� (viewport)
	int m_left, m_bottom, m_right, m_top;

	 // ������� ��������� � ��������� ����������� (model box / window)
	double m_dLeft, m_dBottom, m_dRight, m_dTop;

	 // ����� ������� ������ � ��������
	POINT m_ptViewportCenter;

	 // ����� ������ � ��������� �����������
	CPoint m_vModelCenter;

	 // ����������� ������������ ��������� ������ � �������� ����
	double m_dModDevRatio;

public:

	 // �������������
	CDrawContext() :
		m_hDC (nullptr),
		m_left (0), m_bottom (1), m_right (1), m_top (0),
		m_dLeft (0.0), m_dBottom (0.0), m_dRight (1.0), m_dTop (1.0),
		m_dModDevRatio (1.0)
	{}

	CDrawContext (int left_, int bottom_, int right_, int top_,
				  double dLeft_, double dBottom_, double dRight_, double dTop_) :
		m_hDC (nullptr),
		m_left (0), m_bottom (1), m_right (1), m_top (0),
		m_dLeft (0.0), m_dBottom (0.0), m_dRight (1.0), m_dTop (1.0),
		m_dModDevRatio (1.0)
	{
		SetViewport (left_, bottom_, right_, top_);
		SetModelBox (dLeft_, dBottom_, dRight_, dTop_);
	}

	CDrawContext (HDC hDC_,
				  int left_, int bottom_, int right_, int top_,
				  double dLeft_, double dBottom_, double dRight_, double dTop_) :
		m_hDC (hDC_),
		m_left (0), m_bottom (1), m_right (1), m_top (0),
		m_dLeft (0.0), m_dBottom (0.0), m_dRight (1.0), m_dTop (1.0),
		m_dModDevRatio (1.0)
	{
		SetViewport (left_, bottom_, right_, top_);
		SetModelBox (dLeft_, dBottom_, dRight_, dTop_);
	}

	CDrawContext (HWND hWnd_,
				  double dLeft_, double dBottom_, double dRight_, double dTop_) :
		m_hDC (nullptr),
		m_left (0), m_bottom (1), m_right (1), m_top (0),
		m_dLeft (0.0), m_dBottom (0.0), m_dRight (1.0), m_dTop (1.0),
		m_dModDevRatio (1.0)
	{
		RECT rc;
		GetClientRect (hWnd_, &rc);
		SetViewport (rc.left, rc.bottom, rc.right, rc.top);
		SetModelBox (dLeft_, dBottom_, dRight_, dTop_);
	}

	CDrawContext (HWND hWnd_, HDC hDC_,
				  double dLeft_, double dBottom_, double dRight_, double dTop_) :
		m_hDC (hDC_),
		m_left (0), m_bottom (1), m_right (1), m_top (0),
		m_dLeft (0.0), m_dBottom (0.0), m_dRight (1.0), m_dTop (1.0),
		m_dModDevRatio (1.0)
	{
		RECT rc;
		GetClientRect (hWnd_, &rc);
		SetViewport (rc.left, rc.bottom, rc.right, rc.top);
		SetModelBox (dLeft_, dBottom_, dRight_, dTop_);
	}

	 // ���������, ��������� ��������� ��������� GDI
	void SetDC (HDC hDC_)
	{
		m_hDC = hDC_;
	}

	void ResetDC()
	{
		m_hDC = nullptr;
	}

	operator HDC() const
	{
		return m_hDC;
	}

	 // ��������� ������� ������ � �������� ����
	void SetViewport (int left_, int bottom_, int right_, int top_);

	 // ��������� ������� ��������� � �������� ������
	void SetModelBox (double dLeft_, double dBottom_, double dRight_, double dTop_);

	 // �������������� ���������:
	 // ������� ���� -> ������� ������
	CPoint DCtoWC (const POINT& pt_) const;

	 // ������� ������ -> ������� ����
	POINT WCtoDC (const CPoint& v_) const;

	 // ��������� �����
	void Line (const CPoint& p0_, const CPoint& p1_);

	 // ��������� ������� �����
	void Polyline (const CPoints& pts_, bool fClosed_);

	 // ��������� ������ ������� �����
	void Polylines (const std::vector <CPoints>& pts_);

	 // ��������� ��������������
	void Polygon (const CPoints& pts_);

	 // ��������� ������ ���������������
	void Polygons (const std::vector <CPoints>& pts_);

	 // ����������� � ������������ ���������
private:

	CDrawContext (const CDrawContext &);
	CDrawContext& operator = (const CDrawContext &);
};

 // --- class CDrawContext ----------------------------------------------------


 // --- class CContextMenu ----------------------------------------------------

 //
 // ������� ����������� ���� ��� ������ ������
 //
class CContextMenu
{
protected:

	HMENU m_hMenu;

public:

	 // ����� �������� ���� - ����������, �������
	enum
	{
		MF_AUX_FLAGS = MF_DISABLED | MF_CHECKED,
	};

	CContextMenu() :
		m_hMenu (nullptr)
	{
		 // ������� ����������� ����
		verify (m_hMenu = CreatePopupMenu());
	}

	~CContextMenu()
	{
		 // ������� ����
		assert (m_hMenu);
		verify (DestroyMenu (m_hMenu));
	}

	 // ���������� � ���� ��������
	 //   szText_ - �����, ���� nullptr - ����� ����������� �� ������ ������
	 //   flags_ - �������������� �������� (MF_DISABLED, MF_CHECKED), ���� �� ����� - 0
	void AddItem (LPCTSTR szText_, UINT flags_ = 0);
	
	 // ���������� � ���� ��������
	 //   nCmdID_ - ID ������� (���� �� ����� - 0),
	 //             ���� 0 - ����������� �����������
	 //   szText_ - ����� (���� �� ����� - nullptr),
	 //             ���� nullptr - ����� ����������� �� nCmdID_)
	 //   flags_ - �������������� �������� (MF_DISABLED, MF_CHECKED), ���� �� ����� - 0
	void AddItem (UINT nCmdID_ = 0, LPCTSTR szText_ = nullptr, UINT flags_ = 0);

	 // ���������� � ���� ��������-�������
	 //   subMenu_ - �������
	 //   szText_ - �����
	 //   flags_ - �������������� �������� (MF_DISABLED, MF_CHECKED), ���� �� ����� - 0
	void AddItem (CContextMenu& subMenu_, LPCTSTR szText_, UINT flags_ = 0);

	 // ��������� ���������� ��������� ����
	UINT GetItemCount() const
	{
		return GetMenuItemCount (m_hMenu);
	}

	 // ����� ���� �� �����
	 //   hWndOwner_ - ������������ ����
	 //   pt_ - ������� ������ �������� ���� ���� � ���������� ������� ���� hWndOwner_
	UINT Track (HWND hWndOwner_, POINT pt_);
	UINT Track (HWND hWndOwner_);
};

 // --- class CContextMenu ----------------------------------------------------


 // ������ � ������ ��� ����������� ���������
CMemoryBitmap& MemoryBitmap();

 // --- ������� ���������� ����� ����������� �������������� ��������� ---

 // ���������� ����� ����������� 2 ������
bool CalcIntersAxisAxis (const CPoint& pb0_, const CPoint& pe0_,  // ������ 0
						 const CPoint& pb1_, const CPoint& pe1_,  // ������ 1
						 CPoint& pi_);

 // ���������� ����� ����������� 2 ��������
bool CalcIntersLineLine (const CPoint& pb0_, const CPoint& pe0_,  // ������� 0
						 const CPoint& pb1_, const CPoint& pe1_,  // ������� 1
						 CPoint& pi_);

 // ���������� ����� ����������� ������ � ����������
unsigned CalcIntersAxisCircle (const CPoint& pab_, const CPoint& pae_,  // ������
							   const CPoint& p�c_, double �r_,			// ����������
							   CPoint& pi0_, CPoint& pi1_);

 // ���������� ����� ����������� 2 �����������
unsigned CalcIntersCircleCircle (const CPoint& ptc0_, double r0_,  // ���������� 0
								 const CPoint& ptc1_, double r1_,  // ���������� 1
								 CPoint& pi0_, CPoint& pi1_);

 // --- 2dAnimLib.h ---