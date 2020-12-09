#ifndef SCENE_2D_H
#define SCENE_2D_H

#include "Camera2D.h"
#include "Model2D.h"
#include "Matrix.h"

class Scene2D : public Camera2D
{
private:
	typedef double(*Func)(double);

public:
	Model2D *model;
	Scene2D(double X0, double Y0, double px, double py) : Camera2D(X0, Y0, px, py)
	{
		model = new Model2D();
	}

	void newModel(Model2D newmod)
	{
		model = new Model2D(newmod.GetVertices(), newmod.GetEdges());
	}
	void newModel(string V, string A)
	{
		model = new Model2D(V, A);
	}

	void Plot(HDC dc, Func f, bool axes = true)
	{
		HPEN pen = (HPEN)SelectObject(dc, CreatePen(PS_SOLID, 1, RGB(255, 0, 1)));

		if (axes)
			Axes(dc);

		MoveTo(L(), f(L()));
		for (int i = 0; i < W; i++)
		{
			double x = ScreenToWorldX(i + 1);
			LineTo(dc, x, f(x));
			//MoveTo(i, f(i));
		}

		// Построение графика функции f
		// Здесь передаваемая в качестве параметра функция f вызывается как обычная функция:
		// f(x);
	}
	void Render(HDC dc)
	{
		int kar = model->GetSize();
		int kap = model->GetSize2();
		Axes(dc);
		for (int i = 1; i <= model->GetSize(); i++)
		{
			double x1, y1;
			x1 = model->GetVerticesX(i);
			y1 = model->GetVerticesY(i);
			for (int j = i + 1; j <= model->GetSize2(); j++)
			{	
				if (model->Edge(i, j) == 1)
				{
					MoveTo(x1, y1);
					double x2, y2;
					x2 = model->GetVerticesX(j);
					y2 = model->GetVerticesY(j);

					LineTo(dc, x2, y2);

				}
			}
		}
	}


};

#endif SCENE_2D_H