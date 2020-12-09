#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include <windows.h>

class Camera2D
{
public:
	bool isDragging;
protected:
	double X0, Y0;						// Экранные координаты начала мировой системы координат
	double px, py;		// Единицы масштаба мировой системы координат, выраженные в пикселях
	int W, H;							// Разрешение рабочей области окна
	double prevX0, prevY0;

	int WorldToScreenX(double X)		// Переход от мировых координат к экранным (для абсциссы)
	{
		return int(X0 + px * X);
	}
	int WorldToScreenY(double Y)		// Переход от мировых координат к экранным (для ординаты)
	{
		return int(Y0 - py * Y);
	}
	double ScreenToWorldX(int X)		// Переход от экранных координат к мировым (для абсциссы)
	{
		return (((double)X - X0 + 0.5)/px);
	}
	double ScreenToWorldY(int Y)		// Переход от экранных координат к мировым (для ординаты)
	{
		return (-((double)Y - Y0 + 0.5)/py);
	}
	double L()							// Абсцисса левой границы рабочей области окна (в мировых координатах)
	{
		return -(X0 / px);
	}
	double R()							// Абсцисса правой границы рабочей области окна (в мировых координатах)
	{
		return (W - X0) / px;
	}
	double T()							// Абсцисса левой границы рабочей области окна (в мировых координатах)
	{
		return Y0/ py;
	}
	double B()							// Абсцисса левой границы рабочей области окна (в мировых координатах)
	{
		return (Y0 - H) / py;
	}
private:
	double posX, posY;					// Позиция графического курсора в мировых координатах (для функций MoveTo и LineTo)
public:
	Camera2D(double X0, double Y0, double px, double py) : X0(X0), Y0(Y0), px(px), py(py)
	{
	}
	void Clear(HDC dc)
	{
		RECT r;
		GetClientRect(WindowFromDC(dc), &r);
		Rectangle(dc, 0, 0, r.right, r.bottom);
	}
	void SetResolution(HDC dc)
	{
		// Данная процедура вызывается при изменении размеров окна
		// В ней задаются значения величин W, H, а также настраиваются значения параметров X0, Y0, px, py таким образом, чтобы обеспечить одинаковые масштабы по координатным осям
		RECT r;
		GetClientRect(WindowFromDC(dc), &r);
		W = r.right + 1;
		H = r.bottom + 1;
		
	}
	void MoveTo(double X, double Y)
	{
		posX = X;
		posY = Y;
		// Перемещение графического курсора (posX, posY)
		// Обратите внимание, что мы действуем в мировых координатах
	}
	void LineTo(HDC dc, double X, double Y)
	{
		// Отрисовка линии из текущей позиции графического курсора в точку (X, Y) и его перемещение в эту точку
		// Обратите внимание, что мы действуем в мировых координатах
		// При отрисовке линии могут быть использованы WinApi функции
		// ::MoveToEx(dc, Xs, Ys, nullptr) и ::LineTo(dc, Xs, Ys)
		::MoveToEx(dc, WorldToScreenX(posX), WorldToScreenY(posY), nullptr);
		::LineTo(dc, WorldToScreenX(X), WorldToScreenY(Y));
		MoveTo(X, Y);
	}
	// масштабирование графика по колесику мыши
	void scale(int X, int Y, bool inc)
	{
		double
			k = inc ? 0.1 : -0.1,
			XW = ScreenToWorldX(X),
			YW = ScreenToWorldY(Y);
		X0 -= k * px*XW;
		Y0 += k * py*YW;
		px = (k+1) * px;
		py = (k+1) * py;

	}

	void StartDragging(int X, int Y)
	{
		prevX0 = X;
		prevY0 = Y;
		isDragging = true;
	}

	void StopDragging()
	{
		isDragging = false;
	}

	void drag(int X, int Y)
	{
		X0 += X - prevX0;
		Y0 += Y - prevY0;
		prevX0 = X;
		prevY0 = Y;
	}
	void Axes(HDC dc)
	{
		// Отрисовка координатных осей
		MoveTo(L(), 0);
		LineTo(dc, R(), 0);

		MoveTo(0, T());
		LineTo(dc, 0, B());
	}
	// Отрисовка полярной оси
	void polarAxes(HDC dc)
	{
		
		::MoveToEx(dc, X0, Y0, nullptr);
		::LineTo(dc, W, Y0);
		
	}
};

#endif CAMERA_2D_H
