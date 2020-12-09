#ifndef MODEL_2D_H
#define MODEL_2D_H
#include <string>
#include "Matrix.h"
#include <fstream>
#include "AffineTransform.h"

class Model2D
{
private:
	Matrix<> Vertices;
	Matrix<> Edges;
	Matrix <> CumulativeAT;
	Matrix <> InitialVertices;
	int size;
	int size2;

public:
	Model2D() : Vertices(), Edges() {
		CumulativeAT = Identity(); InitialVertices = Identity();
	}
	Model2D(const Matrix<> Vertices, const Matrix<> Edges) :
		Vertices(Vertices), Edges(Edges) {
		CumulativeAT = Identity(); InitialVertices = Vertices;
	}
	Matrix<> GetVertices() { return Vertices; }
	Matrix<> GetEdges() { return Edges; }
	Model2D(string Ages, string Vert)
	{
		CumulativeAT = Identity();
		fstream fileA(Ages, ios::in);

		fstream fileV(Vert);

		double *temp;
		double *temp2;
		fileA >> size;
		temp = new double[size * 3];

		for (int j = 0; j < 3 * size; j++)
		{
			fileA >> temp[j];

		}
		fileA.close();
		Matrix<>A(3, size, temp);
		InitialVertices = Vertices = A;
		fileV >> size2;
		temp2 = new double[size2 * size2];
		for (int j = 0; j < size2 * size2; j++)
		{
			fileV >> temp2[j];

		}
		Matrix<>B(size2, size2, temp2);
		Edges = B;

		//cout << DA;
	}
	double getPosX() { return Vertices(1, Vertices.getCols()); }
	double getPosY() { return Vertices(2, Vertices.getCols()); }
	double GetXvect()
	{
		return ((GetVerticesX(10) - GetVerticesX(11)) / 10);
	}
	double GetYvect()
	{
		return ((GetVerticesY(10) - GetVerticesY(11)) / 10);
	}
	double GetXZS(int m)
	{
		return (GetVerticesX(m));
	}
	double GetYZS(int m)
	{
		return GetVerticesY(m);
	}

	double GetVerticesX(int m)
	{
		return Vertices(1, m);
	}
	double GetVerticesY(int m)
	{
		return Vertices(2, m);
	}
	void Apply(Matrix<> M)
	{
		CumulativeAT = M * CumulativeAT;
		Vertices = CumulativeAT * InitialVertices;
	}
	int GetSize()
	{
		return size;
	}
	int GetSize2()
	{
		return size2;
	}
	int Edge(int i, int j)
	{
		return Edges(i, j);
	}

};
#endif MODEL_2D_H
