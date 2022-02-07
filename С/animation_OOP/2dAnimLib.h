
 // +++ 2dAnimLib.h +++

 //
 // Основы ООП. Простая анимация на базе GDI.
 //
 // *** НЕ ИЗМЕНЯТЬ ***
 //

#pragma once

#ifdef _DEBUG
	#define verify(expression) assert(expression)
#else
	#define verify(expression) expression
#endif

#define EPSILON 1e-9

 //
 // округление числа к ближайшему по модулю значению
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
 // получение смешанного цвета (интерполяция)
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
 // получение случайного числа из диапазона [ min_, max_ ]
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
 // получение случайного цвета
 //
inline COLORREF RndColor()
{
	return RGB (BYTE (rand() % 255), BYTE (rand() % 255), BYTE (rand() % 255));
}


 // --- struct CPoint ---------------------------------------------------------

 //
 // координаты точки или вектора
 //
struct CPoint
{
	double x, y;

	 // инициализация
	CPoint() : x (0.0), y (0.0)
	{}

	CPoint (double x_, double y_) : x (x_), y (y_)
	{}

	 // конструктор копирования, оператор копирования -
	 // используются формируемые компилятором

	 // сложение, вычитание
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

	 // умножение, деление на число
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
			assert (! "Деление вектора на 0");
			return CPoint();
		}
		return CPoint (x / v_, y / v_);
	}

	CPoint& operator /= (double v_)
	{
		if (0.0 == v_)
			assert (! "Деление вектора на 0");
		else
		{
			x /= v_;
			y /= v_;
		}
		return *this;
	}

	 // сравнение
	bool operator == (const CPoint& other_) const
	{
		return x == other_.x && y == other_.y;
	}

	bool operator != (const CPoint& other_) const
	{
		return    x != other_.x
			   || y != other_.y;
	}

	 // проверка - точка нулевая ?
	bool IsNull() const
	{
		return    0.0 == x
			   && 0.0 == y;
	}

	 // вычисление длины вектора
	double Length() const
	{
		return _hypot (x, y);
	}

	 // нормализация вектора
	bool Normalize()
	{
		if (IsNull())
			return false;

		double L = Length();
		x /= L;
		y /= L;

		return true;
	}

	 // скалярное произведение векторов
	double operator * (const CPoint& other_) const
	{
		return x * other_.x + y * other_.y;
	}

	 // вращение
	void Rotate (double dSin_, double dCos_)
	{
		double x0 = x,
			   y0 = y;
		x = x0 * dCos_ - y0 * dSin_;
		y = x0 * dSin_ + y0 * dCos_;
	}

	 // линейная интерполяция - получение точки,
	 // находящейся между точками p0_ и p1_, в соотношении t_ по расстоянию
	void Interpolate (const CPoint& p0_, const CPoint& p1_, double t_)
	{
		x = p0_.x * (1.0 - t_) + p1_.x * t_;
		y = p0_.y * (1.0 - t_) + p1_.y * t_;
	}
};

 // дополнительный тип - координаты вектора,
 // рекомендуется использовать в случаях, когда [ x, y ] определяют направление, а не позицию
typedef CPoint CVector;

 // --- struct CPoint ---------------------------------------------------------


 // --- struct CRect ----------------------------------------------------------

 //
 // прямоугольник со сторонами, параллельными осям координат
 //
struct CRect
{
	double left, bottom, right, top;

	 // инициализация
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

	 // нормализация (упорядочение значений)
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
 // массив координат точек
 //
class CPoints : public std::vector <CPoint>
{
public:

	 // инициализация, копирование - используется реализация из std::vector
	CPoints() : std::vector <CPoint>()
	{}

	CPoints (unsigned nCount_) : std::vector <CPoint> (nCount_)
	{}

	 // конструктор копирования, оператор копирования -
	 // используются формируемые компилятором

	 // добавление точки
	void Add (double x_, double y_)
	{
		push_back (CPoint (x_, y_));
	}

	void Add (const CPoint& pt_)
	{
		push_back (pt_);
	}

	 // получение количества точек
	unsigned Count() const
	{
		return (unsigned) size();
	}

	 // линейная интерполяция для всех точек
	void Interpolate (const CPoints& pts0_, const CPoints& pts1_, double t_);
};

 // --- class CPoints ---------------------------------------------------------


 // --- class CAffineMatrix ---------------------------------------------------

 //
 // матрица преобразования
 //
class CAffineMatrix
{
protected:

	double m_data[3][3];

public:

	 //
	 // установка единичной матрицы
	 //
	CAffineMatrix()
	{
		SetIdentity();
	}

	 // конструктор копирования, оператор копирования -
	 // используются формируемые компилятором

	 //
	 // установка, получение элемента по индексам
	 //
	double& operator () (unsigned i_, unsigned j_)  // установка или получение
	{
		assert (i_ < 3);
		assert (j_ < 3);
		return m_data[i_][j_];
	}

	double operator () (unsigned i_, unsigned j_) const  // только получение
	{
		assert (i_ < 3);
		assert (j_ < 3);
		return m_data[i_][j_];
	}

	 //
	 // установка единичной матрицы
	 //
	void SetIdentity()
	{
		ZeroMemory (&m_data, sizeof (m_data));
		m_data[0][0] = m_data[1][1] = m_data[2][2] = 1.0;
	}

	 //
	 // создание матрицы переноса
	 //
	static CAffineMatrix Translate (double dx_, double dy_);
	
	static CAffineMatrix Translate (const CPoint& offset_)
	{
		return Translate (offset_.x, offset_.y);
	}

	 //
	 // создание матрицы масштабирования
	 //
	static CAffineMatrix Scale (double kx_, double ky_);

	static CAffineMatrix Scale (const CPoint& scale_)
	{
		return Scale (scale_.x, scale_.y);
	}

	 // создание матрицы вращения
	static CAffineMatrix Rotate (const CVector& vCosSin_);

	static CAffineMatrix Rotate (double angle_)
	{
		return Rotate (CVector (cos (angle_), sin (angle_)));
	}

	 //
	 // создание матрицы отражения
	 //
	static CAffineMatrix MirrorX()
	{
		return Scale (-1.0, 1.0);  // вдоль x
	}

	static CAffineMatrix MirrorY()
	{
		return Scale (1.0, -1.0);  // вдоль y
	}

	 // сложение матриц
	friend CAffineMatrix operator + (const CAffineMatrix& am0_, const CAffineMatrix& am1_);

	 // вычитание матриц
	friend CAffineMatrix operator - (const CAffineMatrix& am0_, const CAffineMatrix& am1_);

	 // умножение матрицы на число
	friend CAffineMatrix operator * (const CAffineMatrix& am_, double v_);

	 // перемножение матриц
	friend CAffineMatrix operator * (const CAffineMatrix& am0_, const CAffineMatrix& am1_);

	 // умножение точки на матрицу
	friend CPoint operator * (const CPoint& pt_, const CAffineMatrix& am_);
	friend CPoint& operator *= (CPoint& pt_, const CAffineMatrix& am_);

	 // умножение массива точек на матрицу
	friend CPoints operator * (const CPoints& pts_, const CAffineMatrix& am_);
	friend CPoints& operator *= (CPoints& pts_, const CAffineMatrix& am_);
};

 // --- class CAffineMatrix ---------------------------------------------------


 // --- class COnPaintDC ------------------------------------------------------

 //
 // класс, управляющий вызовами BeginPaint -- EndPaint (для рисования в окне по сообщению WM_PAINT)
 //
class COnPaintDC
{
protected:

	 // окно, в котором нужно рисовать
	HWND m_hWnd;

	 // данные рисования
	PAINTSTRUCT m_ps;

	 // полученный контекст рисования
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

	 // копирование и присваивание запретить
private:

	COnPaintDC (const COnPaintDC &);
	COnPaintDC& operator = (const COnPaintDC &);
};

 // --- class COnPaintDC ------------------------------------------------------


 // --- class CGetDC ----------------------------------------------------------

 //
 // класс, управляющий вызовами GetDC -- ReleaseDC (для рисования в окне)
 //
class CGetDC
{
protected:

	 // окно, в котором нужно рисовать
	HWND m_hWnd;

	 // полученный контекст рисования
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

	 // копирование и присваивание запретить
private:

	CGetDC (const CGetDC &);
	CGetDC& operator = (const CGetDC &);
};

 // --- class CGetDC ----------------------------------------------------------


 // --- class CGdiObject ------------------------------------------------------

 //
 // класс для управления объектом GDI
 //
class CGdiObject
{
protected:

	 // объект GDI, управляемый данным объектом
	HGDIOBJ m_hObject;

	 // контекст, в котором выбран управляемый объект GDI
	HDC m_hDC;
	HGDIOBJ m_hOldObject;

	 // удалять объект GDI при удалении данного объекта
	bool m_fAutoDelete;

public:

	 // конструктор - выбор объекта GDI в заданном контексте
	 //   hObj_ - управляемый объект GDI
	 //   hDCforSelect_ - контекст, в котором нужно выбрать управляемый объект GDI (если не задан - nullptr),
	 //                   если == nullptr - объект GDI не выбирается
	 //   fAutoDelete_ - удалить управляемый объект GDI при удалении данного объекта (если не задан - true)
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

	 // конструктор - выбор стандартного объекта GDI в заданном контексте
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

	 // деструктор - выбор в заданном ранее контексте исходного объекта GDI,
	 // удаление управляемого объекта GDI
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

	 // получение управляемого объекта GDI
	operator HGDIOBJ() const
	{
		return m_hObject;
	}

	 // отмена управления объектом GDI
	HGDIOBJ Detach()
	{
		HGDIOBJ hObj = m_hObject;
		m_hObject = nullptr;
		m_hDC = nullptr;
		m_hOldObject = nullptr;
		m_fAutoDelete = false;
		return hObj;
	}

	 // удаление управляемого объекта GDI
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

	 // копирование и присваивание запретить
private:

	CGdiObject (const CGdiObject &);
	CGdiObject& operator = (const CGdiObject &);
};

 // --- class CGdiObject ------------------------------------------------------


 // --- class CPen ------------------------------------------------------------

 //
 // класс для управления пером
 //
class CPen : public CGdiObject
{
public:

	 // создание и выбор пера
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
 // класс для управления кистью
 //
class CBrush : public CGdiObject
{
public:

	 // создание и выбор кисти для сплошной заливки
	CBrush (COLORREF color_, HDC hDCforSelect_ = nullptr, bool fAutoDelete_ = true) :
		CGdiObject (CreateSolidBrush (color_), hDCforSelect_, fAutoDelete_)
	{}

	 // создание и выбор штриховой кисти
	CBrush (int style_, COLORREF color_, HDC hDCforSelect_ = nullptr, bool fAutoDelete_ = true) :
		CGdiObject (CreateHatchBrush (style_, color_), hDCforSelect_, fAutoDelete_)
	{}
};

 // --- class CBrush ----------------------------------------------------------


 // --- class CMemoryBitmap ---------------------------------------------------

 //
 // битмап в памяти для буферизации рисования (например, для уменьшения мерцания анимации)
 //
class CMemoryBitmap
{
protected:

	 // контекст, связанный с битмапом
	HDC m_hDC;

	 // битмап
	HBITMAP m_hBitmap, m_hPrevBitmap;
	 
	 // размеры в пикселях
	unsigned m_width, m_height;

public:

	 // инициализация
	CMemoryBitmap() :
		m_hDC (nullptr),
		m_hBitmap (nullptr),
		m_hPrevBitmap (nullptr),
		m_width (0),
		m_height (0)
	{}

	 // деструктор - освобождение памяти, занимаемой битмапом
	~CMemoryBitmap()
	{
		Destroy();
	}

	 // установка размера в пикселях
	void SetSize (unsigned width_, unsigned height_, bool& fSizeModified_);

	 // получение контекста, связанного с битмапом
	operator HDC() const
	{
		return m_hDC;
	}

	 // сплошная заливка цветом
	void Clear (COLORREF color_);

	 // копирование изображения (блиттинг) на заданную поверхность (контекст) hDC_
	void BlitTo (HDC hDC_, int dstX_ = 0, int dstY_ = 0, int srcX_ = 0, int srcY_ = 0) const
	{
		BitBlt (hDC_, dstX_, dstY_, m_width, m_height, m_hDC, srcX_, srcY_, SRCCOPY);
	}

	 // копирование изображения с заданной поверхности hDC_
	void BlitFrom (HDC hDC_, int srcX_ = 0, int srcY_ = 0, int dstX_ = 0, int dstY_ = 0) const
	{
		BitBlt (m_hDC, dstX_, dstY_, m_width, m_height, hDC_, srcX_, srcY_, SRCCOPY);
	}

	 // удаление битмапа
	void Destroy();

	 // копирование и присваивание запретить
private:

	CMemoryBitmap (const CMemoryBitmap &);
	CMemoryBitmap& operator = (const CMemoryBitmap &);
};

 // --- class CMemoryBitmap ---------------------------------------------------


 // --- class CDrawContext ----------------------------------------------------

 //
 // контекст рисования в модельных координатах
 //
class CDrawContext
{
protected:

	 // контекст рисования GDI
	HDC m_hDC;

	 // область просмотра в пикселях (viewport)
	int m_left, m_bottom, m_right, m_top;

	 // область просмотра в модельных координатах (model box / window)
	double m_dLeft, m_dBottom, m_dRight, m_dTop;

	 // центр области вывода в пикселях
	POINT m_ptViewportCenter;

	 // центр модели в модельных координатах
	CPoint m_vModelCenter;

	 // коэффициент соответствия модельных единиц и пикселей окна
	double m_dModDevRatio;

public:

	 // инициализация
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

	 // установка, получение контекста рисования GDI
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

	 // установка области вывода в пикселях окна
	void SetViewport (int left_, int bottom_, int right_, int top_);

	 // установка области просмотра в единицах модели
	void SetModelBox (double dLeft_, double dBottom_, double dRight_, double dTop_);

	 // преобразование координат:
	 // пиксели окна -> единицы модели
	CPoint DCtoWC (const POINT& pt_) const;

	 // единицы модели -> пиксели окна
	POINT WCtoDC (const CPoint& v_) const;

	 // рисование линии
	void Line (const CPoint& p0_, const CPoint& p1_);

	 // рисование ломаной линии
	void Polyline (const CPoints& pts_, bool fClosed_);

	 // рисование набора ломаных линий
	void Polylines (const std::vector <CPoints>& pts_);

	 // рисование многоугольника
	void Polygon (const CPoints& pts_);

	 // рисование набора многоугольников
	void Polygons (const std::vector <CPoints>& pts_);

	 // копирование и присваивание запретить
private:

	CDrawContext (const CDrawContext &);
	CDrawContext& operator = (const CDrawContext &);
};

 // --- class CDrawContext ----------------------------------------------------


 // --- class CContextMenu ----------------------------------------------------

 //
 // простое контекстное меню для вызова команд
 //
class CContextMenu
{
protected:

	HMENU m_hMenu;

public:

	 // флаги элемента меню - недоступен, отмечен
	enum
	{
		MF_AUX_FLAGS = MF_DISABLED | MF_CHECKED,
	};

	CContextMenu() :
		m_hMenu (nullptr)
	{
		 // создать контекстное меню
		verify (m_hMenu = CreatePopupMenu());
	}

	~CContextMenu()
	{
		 // удалить меню
		assert (m_hMenu);
		verify (DestroyMenu (m_hMenu));
	}

	 // добавление в меню элемента
	 //   szText_ - текст, если nullptr - текст формируется по номеру пункта
	 //   flags_ - дополнительные свойства (MF_DISABLED, MF_CHECKED), если не задан - 0
	void AddItem (LPCTSTR szText_, UINT flags_ = 0);
	
	 // добавление в меню элемента
	 //   nCmdID_ - ID команды (если не задан - 0),
	 //             если 0 - добавляется разделитель
	 //   szText_ - текст (если не задан - nullptr),
	 //             если nullptr - текст формируется по nCmdID_)
	 //   flags_ - дополнительные свойства (MF_DISABLED, MF_CHECKED), если не задан - 0
	void AddItem (UINT nCmdID_ = 0, LPCTSTR szText_ = nullptr, UINT flags_ = 0);

	 // добавление в меню элемента-подменю
	 //   subMenu_ - подменю
	 //   szText_ - текст
	 //   flags_ - дополнительные свойства (MF_DISABLED, MF_CHECKED), если не задан - 0
	void AddItem (CContextMenu& subMenu_, LPCTSTR szText_, UINT flags_ = 0);

	 // получение количества элементов меню
	UINT GetItemCount() const
	{
		return GetMenuItemCount (m_hMenu);
	}

	 // вывод меню на экран
	 //   hWndOwner_ - родительское окно
	 //   pt_ - позиция левого верхнего угла меню в клиентской области окна hWndOwner_
	UINT Track (HWND hWndOwner_, POINT pt_);
	UINT Track (HWND hWndOwner_);
};

 // --- class CContextMenu ----------------------------------------------------


 // битмар в памяти для буферизации рисования
CMemoryBitmap& MemoryBitmap();

 // --- функции вычисления точек пересечения геометрических элементов ---

 // вычисление точки пересечения 2 прямых
bool CalcIntersAxisAxis (const CPoint& pb0_, const CPoint& pe0_,  // прямая 0
						 const CPoint& pb1_, const CPoint& pe1_,  // прямая 1
						 CPoint& pi_);

 // вычисление точки пересечения 2 отрезков
bool CalcIntersLineLine (const CPoint& pb0_, const CPoint& pe0_,  // отрезок 0
						 const CPoint& pb1_, const CPoint& pe1_,  // отрезок 1
						 CPoint& pi_);

 // вычисление точек пересечения прямой и окружности
unsigned CalcIntersAxisCircle (const CPoint& pab_, const CPoint& pae_,  // прямая
							   const CPoint& pсc_, double сr_,			// окружность
							   CPoint& pi0_, CPoint& pi1_);

 // вычисление точек пересечения 2 окружностей
unsigned CalcIntersCircleCircle (const CPoint& ptc0_, double r0_,  // окружность 0
								 const CPoint& ptc1_, double r1_,  // окружность 1
								 CPoint& pi0_, CPoint& pi1_);

 // --- 2dAnimLib.h ---