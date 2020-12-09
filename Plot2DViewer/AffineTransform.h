#include"Matrix.h"
#ifndef AFFINE_TRANSFORM_H
#define AFFINE_TRANSFORM_H

Matrix<> Translation(double x, double y)
{
	double T[9] = {
		1, 0, x,
		0, 1, y,
		0, 0, 1 };
	return Matrix<>(3, 3, T);
}

Matrix<> Identity()
{
	double T[9] = {
		1, 0, 0,
		0, 1, 0,
		0, 0, 1 };
	return Matrix<>(3, 3, T);
}

Matrix<> Rotation(double t)
{
	double T[9] = {
		cos(t), -sin(t), 0,
		sin(t), cos(t), 0,
		0, 0, 1 };
	return Matrix<>(3, 3, T);
}
Matrix<> Rotation(double angle, double x0, double y0)
{
	return Translation(x0, y0) * Rotation(angle) * Translation(-x0, -y0);
}

Matrix<> Scaling(double kx, double ky)
{
	double T[9] = {
		kx, 0, 0,
		0, ky, 0,
		0, 0, 1 };
	return Matrix<>(3, 3, T);
}

Matrix<> MappingX()
{
	double T[9] = {
		1, 0, 0,
		0, -1, 0,
		0, 0, 1 };
	return Matrix<>(3, 3, T);
}
Matrix<> MappingY()
{
	double T[9] = {
		-1, 0, 0,
		0, 1, 0,
		0, 0, 1 };
	return Matrix<>(3, 3, T);
}

Matrix<> Rotation(double c, double s)
{
	double k = 1.0 / sqrt(c*c + s * s);

	double T[9] = {
		(c*k) , (-s * k), 0,
		(s*k), (k*c), 0,00000000000000000000
		0, 0,1 };
	return Matrix<>(3, 3, T);
}

Matrix<> Scaling(double x, double y, double kx, double ky, double xRight, double yRight)
{
	return Translation(x, y) * Rotation(xRight, yRight) * Scaling(kx, ky) * Rotation(xRight, -yRight) * Translation(-x, -y);
}

// ����� ��������� ����������� �������, ������������ ������� ������� ��:
// Identity() - ������������� ��;
// Rotation(t) - ������� �� ���� t;
// Rotation(c, s) - ������� �� ����, ������� � ����� �������� ��������������� ��������� c � s;
// Scaling(kx, ky) - ���������������;
// Mapping (��������� ���� ���������) - �� �������, ��� �������� ������ ��������� ����� ������������ ������� Scaling.

// � ���������� ������� ������������ ����������� ������� �� ������.
// �������������� ���� � ������ �������� �������� ������.
// ��������, ����� �������, ��������� ��������� �������,
// � ����������� ���������������� ��������� � �������������.

#endif AFFINE_TRANSFORM_H
