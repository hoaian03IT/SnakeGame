#include <iostream>
#include "mylib.h"
using namespace std;
int sl = 4;
int x = 15, y = 1; // tọa độ tường chắn
int length = 88, width = 35; // chiều dài, chiều rộng tường chắn

void ve_tuong_doc(int x, int y, int width);
void ve_tuong_ngang(int x, int y, int length);
void ve_tuong(int x, int y, int length, int width);
void ve_ran(int tdx[], int tdy[]);
void khoi_tao_ran(int tdx[], int tdy[]);
void xu_li_ran(int tdx[], int tdy[], int x, int y);
void them(int a[], int x);
void xoa(int a[], int vt);
void xoa_du_lieu_cu(int tdx[], int tdy[]);
bool game_over(int xr, int yr, int tdx[], int tdy[]);
void tao_moi(int &xqua, int &yqua);
void an_moi(int &xqua, int &yqua, int &diem, int tdx[], int tdy[]);

int main()
{
	int luachon = 1;
	while (luachon == 1)
	{
		system("cls");
		int dokho;
		int thg;
		gotoXY(45, 4);
		cout << "GAME RAN SAN MOI";
		do
		{
			gotoXY(40, 5);
			cout << "Chon do kho (1, 2, 3, 4) : ";
			cin >> dokho;
		} while (dokho > 4 || dokho < 1);
		if (dokho == 1)
			thg = 300;
		else if (dokho == 2)
			thg = 100;
		else if (dokho == 3)
			thg = 50;
		else
			thg = 25;
		system("cls");
		
		srand(time(NULL));
		int xmoi, ymoi;
		// tao moi
		tao_moi(xmoi, ymoi);
		ShowCur(0);
		int tdx[100];
		int tdy[100];
		ve_tuong(x, y, length, width);
		khoi_tao_ran(tdx, tdy);

		int xr = 50, yr = 13;
		int check = 2;
		int diem = 0;
		while (true)
		{
			gotoXY(45, 0);
			cout << "Dung phim mui ten de di chuyen";
			xoa_du_lieu_cu(tdx, tdy);
			// 0: đi xuống
			// 1: đi lên
			// 2: qua phải
			// 3: qua trái

			//--------- dieu khien ----------
			if (_kbhit())
			{
				char kitu = _getch();
				if (kitu == -32)
				{
					kitu = _getch();
					if (kitu == 72 && check != 0) // phim len
					{
						check = 1;
					}
					else if (kitu == 80 && check != 1) // phim xuong
					{
						check = 0;
					}
					else if (kitu == 77 && check != 3) // phim sang phai
					{
						check = 2;
					}
					else if (kitu == 75 && check != 2) // phim sang trai
					{
						check = 3;
					}
				}
			}
			//--------- thuc hien di chuyen ----------
			if (check == 0)
			{
				yr++;
			}
			else if (check == 1)
			{
				yr--;
			}
			else if (check == 2)
			{
				xr++;
			}
			else if (check == 3)
			{
				xr--;
			}
			//---------- dieu kien GAME OVER ------------
			if (game_over(xr, yr, tdx, tdy))
			{
				system("cls");
				gotoXY(50, 11);
				cout << "NGU QUA!!! :))\n";
				gotoXY(50, 12);
				cout << "Diem dat duoc: " << diem;
				gotoXY(35, 13);
				cout << "Ban co muon tiep tuc (1. Tiep tuc, 0. Dung lai) : ";
				cin >> luachon;
				break;
			}
			an_moi(xmoi, ymoi, diem, tdx, tdy);
			xu_li_ran(tdx, tdy, xr, yr);
			gotoXY(x - 10, y);
			cout << "Diem: " << diem;
			Sleep(thg);
		}
	}
	_getch();
	return 0;
}

void an_moi(int &xqua, int &yqua, int &diem, int tdx[], int tdy[])
{
	if (tdx[0] == xqua && tdy[0] == yqua)
	{
		sl++;
		tao_moi(xqua, yqua);
		diem += 10;
	}
}

void tao_moi(int &xqua, int &yqua)
{
	textcolor(14);
	xqua = rand() % ((x + length - 1) - (x + 1) + 1) + x + 1;
	yqua = rand() % ((y + width - 1) - (y + 1) + 1) + y + 1;
	gotoXY(xqua, yqua);
	cout << "O";
}

bool game_over(int xr, int yr, int tdx[], int tdy[])
{
	// chạm tường
	if (yr == y || yr == y + width || xr == x || xr == x + length)
	{
		return true;
	}
	// ăn thân rắn
	for (int i = 1; i < sl; i++)
	{
		if (tdx[0] == tdx[i] && tdy[0] == tdy[i])
			return true;
	}
	return false;
}

void xoa_du_lieu_cu(int tdx[], int tdy[])
{
	for (int i = 0; i < sl; i++)
	{
		gotoXY(tdx[i], tdy[i]);
		cout << " ";
	}
}

void ve_tuong_doc(int x, int y, int width)
{
	int i = y;
	while (i <= y + width)
	{
		gotoXY(x, i);
		cout << (char)179;
		i++;
	}
}

void ve_tuong_ngang(int x, int y, int length)
{
	int i = x;
	while (i <= x + length)
	{
		gotoXY(i, y);
		cout << (char)196;
		i++;
	}
}

void ve_tuong(int x, int y, int length, int width)
{
	//vẽ tường trên - dưới
	SetColor(11);
	ve_tuong_ngang(x, y, length); // trên
	ve_tuong_ngang(x, y + width, length); // dưới

	// vẽ tường hai bên
	ve_tuong_doc(x, y, width); // Phải
	ve_tuong_doc(x + length, y, width);
	// Khép góc
	gotoXY(x, y); cout << (char)218;
	gotoXY(x + length, y); cout << (char)191;
	gotoXY(x, y + width); cout << (char)192;
	gotoXY(x + length, y + width); cout << (char)217;
}

void khoi_tao_ran(int tdx[], int tdy[])
{
	int x = 50, y = 13;
	for (int i = 0; i < sl; i++)
	{
		tdx[i] = x;
		tdy[i] = y;
		x--;
	}
	ve_ran(tdx, tdy);
}

void ve_ran(int tdx[], int tdy[])
{
	SetColor(5);
	for (int i = 0; i < sl; i++)
	{
		gotoXY(tdx[i], tdy[i]);
		if (i == 0)
			cout << (char)2;
		else
			cout << "o";
	}
	SetColor(7);
}

void xu_li_ran(int tdx[], int tdy[], int x, int y)
{
	// thêm tọa độ mới vào đầu mảng
	them(tdx, x);
	them(tdy, y);
	// xóa tọa độ cuối mảng
	xoa(tdx, sl - 1);
	xoa(tdy, sl - 1);
	ve_ran(tdx, tdy);
}

void them(int a[], int x)
{
	for (int i = sl; i > 0; i--)
	{
		a[i] = a[i - 1];
	}
	a[0] = x;
	sl++;
}
void xoa(int a[], int vt)
{
	for (int i = vt; i < sl ; i++)
	{
		a[i] = a[i + 1];
	}
	sl--;
}