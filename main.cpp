#include"functions.h"
#include"Console.h"
#include"main.h"

short STrang, SViTriChon, STongMuc;

int main()
{
	resizeConsole(widthConSoLe,heightConSoLe);// Thay đổi kích thước màn hình console
	SetConsoleTitle(TEXT("GAME DO MIN - HUYNH CANH"));// Thay đổi tiêu đề

	veTieuDeGame();
	Cursor(false);// ẩn con trỏ
	//khoiTao(9, 9, 10);
	veMenuChinh(0);
	STrang = 1;
	//veMenuCapDo(2);
	xuLySuKien();
	system("pause");
}

