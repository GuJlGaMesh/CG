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
	Model2D() : Vertices(), Edges(), InitialVertices(), CumulativeAT(Identity()){}

	Model2D(const Matrix<> Vertices, const Matrix<> Edges) :
		Vertices(Vertices), Edges(Edges) {
		CumulativeAT = Identity(); InitialVertices = Vertices;
	}

	Model2D(string Ages, string Vert)
	{
		CumulativeAT = Identity();
		fstream fileA(Ages, ios::in);
		fileA >> size;
		double *temp = new double[size * 3];

		for (int j = 0; j < 3 * size; j++)
		{
			fileA >> temp[j];

		}
		fileA.close();
		Matrix<>A(3, size, temp);
		InitialVertices = Vertices = A;

		fstream fileV(Vert);
		fileV >> size2;
		double* temp2 = new double[size2 * size2];
		for (int j = 0; j < size2 * size2; j++)
		{
			fileV >> temp2[j];

		}
		Matrix<>B(size2, size2, temp2);
		Edges = B;
	}
	//double getPosX() { return Vertices(1, Vertices.getCols()); }
	//double getPosY() { return Vertices(2, Vertices.getCols()); }
	Matrix<> GetVertices() { return Vertices; }
	Matrix<> GetEdges() { return Edges; }

	
	double GetVerticesX(int m)
	{
		return Vertices(1, m);
	}
	double GetVerticesY(int m)
	{
		return Vertices(2, m);
	}
	void Apply(Matrix<> currentAT)
	{
		CumulativeAT = currentAT * CumulativeAT;
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
