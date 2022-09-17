#include<iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#define widthConSoLe 120
#define heightConSoLe 35

struct CauTrucBang
{
	short SDong = 0;
	short SCot = 0;
	short SSoBom = 0;// số lượng bom
	short SSoODaMo = 0;// số lượng ô đã mở
	short SSoCo = 0;// số lượng cờ
};

struct CauTrucO
{
	bool BCoBom = 0;// có bom chưa?
	bool BDaMo = 0;
	bool BCamCo = 0;
	short SBomLanCan = 0;
};

// Trang, vị trí đang chọn, Tổng mục
extern short STrang, SViTriChon, STongMuc;