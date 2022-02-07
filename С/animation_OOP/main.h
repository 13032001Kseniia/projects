
 // +++ main.h +++

 //
 // Основы ООП. Простая анимация на базе GDI. Летающий квадрат. Базовый пример.
 //

#pragma once


 // --- class CQuad ------------------------------------------------

 //
 // С++-класс фигурки - квадрата
 //
class CQuad
{
protected:
	 
	 // исходные координаты контура
	CPoints m_aSrcPoints;

	 // цвета контура и заливки
	COLORREF m_nBorderColor, m_nFillColor;

public:

	 // конструктор по умолчанию - инициализация полей и заполнение исходных координат фигуры
	CQuad();

	 // рисование фигуры в момент времени t_ [0..1]
	void Draw (CDrawContext& context_, double t_);
};

 // --- class CQuad -----------------------------------------------------------


 // --- class CAnimWindow -----------------------------------------------------

 //
 // С++-класс окна приложения (предполагается окно в единственном экземпляре)
 //
class CAnimWindow
{
public:

	 // имя Windows-класса окон
	static LPCTSTR sm_szClassName;

protected:

	 // дескриптор окна
	static HWND sm_hWnd;

	 // регистрация Windows-класса окон
	static WORD RegisterClass (HINSTANCE hInstance_);

	 // оконная функция
	static LRESULT CALLBACK WndProc (HWND hWnd_, UINT message_, WPARAM wParam_, LPARAM lParam_);

	 // обработчики сообщений
	static void OnCreate (HWND hWnd_);
	static void OnDestroy();
	static void OnPaint();
	static void OnTimer();

public:
	
	 // создание окна
	static void Create (HINSTANCE hInstance_);
};

 // --- class CAnimWindow -----------------------------------------------------


 // --- main.h ---