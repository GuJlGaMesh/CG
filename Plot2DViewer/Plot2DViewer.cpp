#include <windows.h>
#include <windowsx.h>
#include "Data.h"
#include "Scene2D.h"
#include <cmath>
#define SCALE 0.2  

LRESULT _stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);						// �������� ������� ���������
int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)		// �������� ���������
{
	// ������ ������������ ����� �������� ��������� - �������� ����: ������� ����������� ������� ����� wc, ����� �������� ���� hWnd
	WNDCLASS wc;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;						// ��� ������� ���������, ������������ �� ������ �������
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;						// ������������� ����������, ���������� ����� ������ ���������� ��� ������� ������
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(6);
	wc.lpszMenuName = 0;							// ���� � ������� ������ �����������
	wc.lpszClassName = (LPCSTR)"MainWindowClass";	// ��� �������� ������, ������������ ��� �������� ����������� ����
	RegisterClass(&wc);								// ����������� ������ wc

	HWND hWnd = CreateWindow(						// hWnd - ����������, ���������������� ����; ������� �������� ���� ��������� ���������� hWnd ��������� ���������
		(LPCSTR)"MainWindowClass",					// ��� �������� ������
		(LPCSTR)"Plot2D Viewer",					// ��������� ����
		WS_OVERLAPPEDWINDOW,						// ����� ����
		200,200,400,400,							// ���������� �� ������ ������ �������� ���� ����, ��� ������ � ������
		nullptr,nullptr,hInstance,nullptr);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ������ ������������ ����� �������� ��������� - �������� ���� ��������� ��������� ���������, ������� ������� ��������� � ��������� �� ��������������� �����
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))				// ������� GetMessage �������� �� ������� ��������� � ������� ��� � ��������� msg
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);						// ������� DispatchMessage ��������� ������� � ������������� ������ ������� ���������
	}

	return 0;
}
Scene2D scene(X0, Y0, px, py);

// � �������� ������ ����������� ������ ���� ���������� ���������� - �������� ������ ������ Scene2D
// ��� ���������� �������� �������������� ����������� ��������� � �������, ������������� � ���� ������


bool type = true;

LRESULT _stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)		// ������� ��������� ��������� � ������������ ��� ���������, ������������ ����
{
	switch (msg)
	{
	case WM_CREATE:
	{
		scene.newModel("vet.txt", "edges.txt");
	}
	case WM_PAINT:
	{
		HDC dc = GetDC(hWnd);
		scene.Clear(dc);
		//scene.newModel("edges.txt", "vet.txt");// ����� �������������� � ������ Camera2D ������, ����������� �� ������� ������� ������� ���� hWnd
		//		// ����� �������������� � ������ Scene2D ������, ����������� �� ��������� ������� ���������

		if (type)
		{
			scene.Render(dc);
		}

		ReleaseDC(hWnd, dc);
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	case WM_SIZE:
	{
		HDC dc = GetDC(hWnd);
		scene.SetResolution(dc);
		ReleaseDC(hWnd, dc);
		InvalidateRect(hWnd, nullptr, false);
		return 0;
	}

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_UP:
			scene.model->Apply(Translation(0, 1));
			break;

		case VK_DOWN:
			scene.model->Apply(Translation(0, -1));
			break;


		case 0x52:
		{
			scene.model->Apply(Rotation(-M_PI / 2));
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case 0x20:
		{
		
		}
		case 0x10:
		{
			double x1 = scene.model->GetVerticesX(1);
			double x2 = scene.model->GetVerticesX(12);
			double y1 = scene.model->GetVerticesY(1);
			double y2 = scene.model->GetVerticesY(12);
			scene.model->Apply(Scaling((x1 + x2) / 2, (y1 + y2) / 2, 1, 0.9, x2-x1, y2-y1));
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case 0x11:
		{
			double x1 = scene.model->GetVerticesX(1);
			double x2 = scene.model->GetVerticesX(12);
			double y1 = scene.model->GetVerticesY(1);
			double y2 = scene.model->GetVerticesY(12);
			scene.model->Apply(Scaling((x1+x2)/2,(y1+y2)/2, 1, 1.1, x2,y2));
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case 0x44:
		{
			scene.model->Apply(Rotation(-M_PI / 2));
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case 0x41:
		{
			scene.model->Apply(Rotation(M_PI / 2));
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case VK_LEFT:
		{
			scene.model->Apply(MappingX());
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case VK_RIGHT:
		{
			scene.model->Apply(MappingY());
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case VK_OEM_PLUS: // ��������� ������� ������
			scene.model->Apply(Scaling(1 + SCALE, 1 + SCALE));
			break;

		case VK_OEM_MINUS: // ��������� ������� ������
			scene.model->Apply(Scaling(1 - SCALE, 1 - SCALE));
			break;

		}

		InvalidateRect(hWnd, nullptr, false);
		return 0;
	}

	case WM_LBUTTONDOWN:
	{
		scene.StartDragging(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	}
	case WM_MOUSEWHEEL:
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);

		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
			scene.scale(pt.x, pt.y, true);
		else
			scene.scale(pt.x, pt.y, false);

		InvalidateRect(hWnd, nullptr, false);
		return 0;
	}

	case WM_LBUTTONUP:
	{
		scene.StopDragging();
	}

	/*case WM_MOUSEMOVE:
	{
		if (scene.isDragging)
		{
			scene.Drag(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			InvalidateRect(hWnd, nullptr, false);
		}
		break;

	}*/

	default:
	{
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	}
	return 0;
}
