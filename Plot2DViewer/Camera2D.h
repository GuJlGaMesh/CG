#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include <windows.h>

class Camera2D
{
public:
	bool isDragging;
protected:
	double X0, Y0;						// �������� ���������� ������ ������� ������� ���������
	double px, py;		// ������� �������� ������� ������� ���������, ���������� � ��������
	int W, H;							// ���������� ������� ������� ����
	double prevX0, prevY0;

	int WorldToScreenX(double X)		// ������� �� ������� ��������� � �������� (��� ��������)
	{
		return int(X0 + px * X);
	}
	int WorldToScreenY(double Y)		// ������� �� ������� ��������� � �������� (��� ��������)
	{
		return int(Y0 - py * Y);
	}
	double ScreenToWorldX(int X)		// ������� �� �������� ��������� � ������� (��� ��������)
	{
		return (((double)X - X0 + 0.5)/px);
	}
	double ScreenToWorldY(int Y)		// ������� �� �������� ��������� � ������� (��� ��������)
	{
		return (-((double)Y - Y0 + 0.5)/py);
	}
	double L()							// �������� ����� ������� ������� ������� ���� (� ������� �����������)
	{
		return -(X0 / px);
	}
	double R()							// �������� ������ ������� ������� ������� ���� (� ������� �����������)
	{
		return (W - X0) / px;
	}
	double T()							// �������� ����� ������� ������� ������� ���� (� ������� �����������)
	{
		return Y0/ py;
	}
	double B()							// �������� ����� ������� ������� ������� ���� (� ������� �����������)
	{
		return (Y0 - H) / py;
	}
private:
	double posX, posY;					// ������� ������������ ������� � ������� ����������� (��� ������� MoveTo � LineTo)
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
		// ������ ��������� ���������� ��� ��������� �������� ����
		// � ��� �������� �������� ������� W, H, � ����� ������������� �������� ���������� X0, Y0, px, py ����� �������, ����� ���������� ���������� �������� �� ������������ ����
		RECT r;
		GetClientRect(WindowFromDC(dc), &r);
		W = r.right + 1;
		H = r.bottom + 1;
		
	}
	void MoveTo(double X, double Y)
	{
		posX = X;
		posY = Y;
		// ����������� ������������ ������� (posX, posY)
		// �������� ��������, ��� �� ��������� � ������� �����������
	}
	void LineTo(HDC dc, double X, double Y)
	{
		// ��������� ����� �� ������� ������� ������������ ������� � ����� (X, Y) � ��� ����������� � ��� �����
		// �������� ��������, ��� �� ��������� � ������� �����������
		// ��� ��������� ����� ����� ���� ������������ WinApi �������
		// ::MoveToEx(dc, Xs, Ys, nullptr) � ::LineTo(dc, Xs, Ys)
		::MoveToEx(dc, WorldToScreenX(posX), WorldToScreenY(posY), nullptr);
		::LineTo(dc, WorldToScreenX(X), WorldToScreenY(Y));
		MoveTo(X, Y);
	}
	// ��������������� ������� �� �������� ����
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
		// ��������� ������������ ����
		MoveTo(L(), 0);
		LineTo(dc, R(), 0);

		MoveTo(0, T());
		LineTo(dc, 0, B());
	}
	// ��������� �������� ���
	void polarAxes(HDC dc)
	{
		
		::MoveToEx(dc, X0, Y0, nullptr);
		::LineTo(dc, W, Y0);
		
	}
};

#endif CAMERA_2D_H
