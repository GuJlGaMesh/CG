#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

using namespace std;


template <typename Cell = double>
class Matrix
{
	int rows, cols;
private:
	int size_x, size_y;
	Cell **cells;
	void AllocateCells(int, int);
	void FreeCells();
public:
	Matrix() : size_x(0), size_y(0), cells(nullptr) {}	// Конструктор по умолчанию
	Matrix(const Matrix&);					// Конструктор копирования
	Matrix(int, int);							// Конструктор нулевой матрицы
	Matrix(int, int, Cell*);						// Конструктор матрицы из списка
	~Matrix();	
	int getCols() const;// Деструктор

	Cell &operator()(int i, int j) { return cells[i - 1][j - 1]; }

	Matrix& operator = (const Matrix&);		// Перегрузка оператора присваивания
	Matrix  operator + (const Matrix&);		// Сложение матриц
	Matrix  operator - (const Matrix&);		// Вычитание матриц
	Matrix  operator * (const Matrix&);		// Умножение матриц

	friend istream& operator >> <> (istream&, Matrix&);			// Перегрузка оператора >> для ввода матрицы
	friend ostream& operator << <> (ostream&, const Matrix&);	// Перегрузка оператора << для вывода матрицы
};

template <typename Cell>
Matrix<Cell>::Matrix(const Matrix<Cell>& M)
{
	AllocateCells(M.size_x, M.size_y);
	for (int i = 0; i < size_x; i++)
		for (int j = 0; j < size_y; j++)
			cells[i][j] = M.cells[i][j];
}

template <typename Cell>
Matrix<Cell>::Matrix(int Size_x, int Size_y)
{
	AllocateCells(Size_x, Size_y);
	for (int i = 0; i < size_x; i++)
		for (int j = 0; j < size_y; j++)
			cells[i][j] = 0;
}

template <typename Cell>
Matrix<Cell>::Matrix(int Size_x, int Size_y, Cell* list)
{
	/* ... */
	AllocateCells(Size_x, Size_y);
	//size = Size;
	int index = 0;
	for (int i = 0; i < size_x; i++)
		for (int j = 0; j < size_y; j++)
		{
			//cells[i][j] = list[i*size_x + j];
			cells[i][j] = list[index];
			index++;
		}
}
template<typename Cell>
int Matrix<Cell>::getCols() const {
	return cols;
}


template <typename Cell>
Matrix<Cell>::~Matrix()
{
	FreeCells();
}

template <typename Cell>
Matrix<Cell>& Matrix<Cell>::operator=(const Matrix& M)
{
	//if ( size != M.size )
	if (size_x != M.size_x && size_y != M.size_y)
	{
		FreeCells();
		AllocateCells(M.size_x, M.size_y);
	}
	for (int i = 0; i < size_x; i++)
		for (int j = 0; j < size_y; j++)
			cells[i][j] = M.cells[i][j];
	return *this;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator+(const Matrix& M)
{
	Matrix<Cell> res(*this);
	if (size_x == M.size_x && size_y == M.size_y)
	{
		for (int i = 0; i < size_x; i++)
			for (int j = 0; j < size_y; j++)
				res.cells[i][j] += M.cells[i][j];
	}
	return res;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator-(const Matrix& M)
{
	/* ... */
	Matrix<Cell> res(*this);
	if (size_x == M.size_x && size_y == M.size_y)
	{
		for (int i = 0; i < size_x; i++)
			for (int j = 0; j < size_y; j++)
				res.cells[i][j] -= M.cells[i][j];
	}
	return res;
	//return Matrix();
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator*(const Matrix& M)
{
	/* ... */
	//Matrix<Cell> res(*this);
	Matrix<Cell> res(size_x, M.size_y);
	//Matrix<Cell> res;
	/*
	int min, max;
	if (size_x < size_y)
	{
		min = size_x;
		max = size_y;
	}
	else
	{
		min = size_y;
		max = size_x;
	}
	*/
	if (size_y == M.size_x)
	{
		//AllocateCells(size);
		for (int i = 0; i < size_x; i++)
		{
			for (int j = 0; j < M.size_y; j++)
			{
				res.cells[i][j] = 0;
				for (int k = 0; k < size_y; k++)
				{
					res.cells[i][j] += cells[i][k] * M.cells[k][j];
				}
			}
		}
	}
	return res;
	//return Matrix();
}

template <typename Cell>
void Matrix<Cell>::AllocateCells(int Size_x, int Size_y)
{
	cells = new Cell*[Size_x];
	for (int i = 0; i < Size_x; i++)
		cells[i] = new Cell[Size_y];
	size_x = Size_x;
	size_y = Size_y;
}

template <typename Cell>
void Matrix<Cell>::FreeCells()
{
	for (int i = 0; i < size_x; i++)
		delete cells[i];
	delete cells;
	size_x = 0;
	size_y = 0;
}

template <typename Cell>
istream& operator >> (istream& fi, Matrix<Cell>& M)
{
	for (int i = 0; i < M.size_x; i++)
		for (int j = 0; j < M.size_y; j++)
			fi >> M.cells[i][j];
	return fi;
}

template <typename Cell>
ostream& operator << (ostream& fo, const Matrix<Cell>& M)
{
	for (int i = 0; i < M.size_x; i++)
	{
		fo << "  ";
		for (int j = 0; j < M.size_y; j++)
			fo << M.cells[i][j] << " \t";
		fo << endl;
	}
	return fo;
}

#endif MATRIX_H
