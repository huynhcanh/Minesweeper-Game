#include"main.h"
#include"functions.h"
#include"Console.h"

CauTrucBang CTBang;
CauTrucO **CTO;

// Vị trí hiện tại của con trỏ hiện tại
COORD CViTriConTro;// x là cột , y là dòng

// Sủ dụng phím
bool BSuDungPhim = false;

// Tọa độ bảng
short SToaDoX;
short SToaDoY;

bool BTrangThaiChoiGame = false;



void taoMang2ChieuDong()
{
	CTO = new CauTrucO*[CTBang.SDong];
	for (int i = 0; i < CTBang.SCot; ++i)
	{
		CTO[i] = new CauTrucO[CTBang.SCot];
	}
}
void xoaMang2ChieuDong()
{
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		delete[] CTO[i];
	}
	delete[] CTO;
}
void luuToaDoBang()
{
	SToaDoX = widthConSoLe / 2 - CTBang.SCot / 2 - 12;
	SToaDoY = (((heightConSoLe-6) - CTBang.SCot) / 2) + 7;
}
void khoiTao(short SDong, short SCot, short SSoBom)
{
	CTBang.SDong = SDong;
	CTBang.SCot = SCot;
	CTBang.SSoBom = SSoBom;
	CTBang.SSoODaMo = 0;
	CTBang.SSoCo = 0;

	taoMang2ChieuDong();
	taoBomNgauNhien();
	luuToaDoBang();
	CViTriConTro = { 0, 0 };
	BTrangThaiChoiGame = true;
	veBang();
	veTrangThaiChoiGame(1,0,0);
}
short toaDoX(short SX)
{
	return 2 * SX + SToaDoX;
}
short toaDoY(short SY)
{
	return SY + SToaDoY;
}
void veO(short SX, short SY, short SKieu)
{
	switch (SKieu)
	{
	case 0:// Rỗng nền màu xanh lá
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 10, "  "); break;
		// Số 1-8 nền trắng
	case 1: // Số 1 chữ xanh dương
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 9, 15, "1 "); break;
	case 2: // Số 2 chữ xanh lá
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 2, 15, "2 "); break;
	case 3: // Số 3 chữ đỏ
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 15, "3 "); break;
	case 4: // Số 4 chữ xanh dương đậm
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 1, 15, "4 "); break;
	case 5: // Số 5 chữ đỏ đậm
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 4, 15, "5 "); break;
	case 6: // Số 6 chữ CYAN đậm
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 3, 15, "6 "); break;
	case 7: // Số 7 chữ đen
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 15, "7 "); break;
	case 8: // Số 8 chữ hồng
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 13, 15, "8 "); break;
	case 9: // Bom
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 12, "B "); break;
	case 10: // Ô chẵn
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 8, "  "); break;
	case 11: // Ô lẻ
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 7, "  "); break;
	case 12: // Theo dõi con trỏ
		//setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 13, "  "); break;
		setColorBGTextXY(toaDoX(SX)+1, toaDoY(SY), 0, 13, " "); break;
	case 13: // Cấm cờ
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 14, "P "); break;
	case 14: // Cấm chỗ không có bom => Cấm sai
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 15, 6, "Px"); break;
	case 15: // Cấm chỗ có bom => Cấm đúng
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 14, "B "); break;
	}
}
void veBang()
{
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		for (int j = 0; j < CTBang.SCot; ++j)
		{
			if (CTO[i][j].BCamCo)// ô cấm cờ
			{
				veO(j, i, 13);
			}
			else if (CTO[i][j].SBomLanCan)
			{
				veO(j, i, CTO[i][j].SBomLanCan);
			} 
			else if (CTO[i][j].BDaMo)
			{
				veO(j, i, 0);
			}
			else if ((i + j) % 2)// ô lẻ
			{
				veO(j, i, 11);
			}
			else// ô chẵn
			{
				veO(j, i, 10);
			}
			if (BSuDungPhim)
			{
				veO(CViTriConTro.X, CViTriConTro.Y, 12);
			}
		}
	}
}
void taoBomNgauNhien()
{
	short SSoBom = CTBang.SSoBom;
	short SI;// số dòng ngẫu nhiên
	short SJ;// số cột ngẫu nhiên
	srand(time(0));
	while (SSoBom)
	{
		SI = rand() % CTBang.SDong;
		SJ = rand() % CTBang.SCot;
		if (CTO[SI][SJ].BCoBom == true)
		{
			continue;
		}
		CTO[SI][SJ].BCoBom = true;
		--SSoBom;
	}
}
void lickPhai(short SX, short SY)// cấm cờ
{
	if (!CTO[SX][SY].BDaMo)// đã mở hay chưa
	{
		if (CTO[SX][SY].BCamCo)// đã cấm cờ
		{
			CTO[SX][SY].BCamCo = false;
			CTBang.SSoCo--;
		}
		else
		{
			CTO[SX][SY].BCamCo = true;
			CTBang.SSoCo++;
		}
	}
	veBang();

	deleteRow(4, 1);
	veTrangThaiChoiGame(1, 0, 0);
}
short demBomLanCan(short SX, short SY)
{
	short SDem = 0;
	for (int i = SX - 1; i <= SX + 1; ++i)
	{
		for (int j = SY - 1; j <= SY + 1; ++j)
		{
			if (i<0 || i>= CTBang.SDong || j <0 ||j>=CTBang.SCot || (i == SX && j == SY))
			{
				continue;
			}
			if (CTO[i][j].BCoBom)
			{
				++SDem;
			}
		}
	}
	return SDem;
}
void moO(short SX, short SY)
{
	if (!CTO[SX][SY].BDaMo && !CTO[SX][SY].BCamCo)
	{
		CTO[SX][SY].BDaMo = true;
		if (CTO[SX][SY].BCoBom)// Có bom
		{
			thua();// Thoát khỏi chương trình
		}
		else// Không có bom
		{
			CTBang.SSoODaMo++;
			short SSoBomLanCan = demBomLanCan(SX, SY);
			if (SSoBomLanCan)// nếu số bom lân cận > 0
			{
				CTO[SX][SY].SBomLanCan = SSoBomLanCan;
			}
			else// Ô Rỗng
			{
				// Duyệt các ô lân cận
				for (int i = SX - 1; i <= SX + 1; ++i)
				{
					for (int j = SY - 1; j <= SY + 1; ++j)
					{
						if (i<0 || i >= CTBang.SDong || j <0 || j >= CTBang.SCot || (i == SX && j == SY))
						{
							continue;
						}
						moO(i, j);
					}
				}
			}
		}
	}
}
bool thongKeCo()
{
	if (CTBang.SSoBom + CTBang.SSoODaMo == CTBang.SDong * CTBang.SCot)
	{
		return 1;
	}
	return 0;
}
void lickTrai(short SX, short SY)
{
	if (!CTO[SX][SY].BDaMo && !CTO[SX][SY].BCamCo)
	{
		moO(SX,SY);
		if (BTrangThaiChoiGame)
		{
			veBang();
			if (thongKeCo())
			{
				thang();
			}
		}
	}
}
void thang()
{
	BTrangThaiChoiGame = false;
	xoaMang2ChieuDong();
	STrang = 5;
	deleteRow(4, 1);// xóa dòng 4 đi 1 dòng
	veTrangThaiChoiGame(2, 2, 0);
}
void thua()
{
	// Hiện bom ẩn và kiểm tra cấm cờ
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		for (int j = 0; j < CTBang.SCot; ++j)
		{
			if (CTO[i][j].BCamCo)// có cấm cờ
			{
				if (CTO[i][j].BCoBom)
				{
					veO(j, i, 15);// cấm cờ đúng
				}
				else
				{
					veO(j, i, 14);// cấm cờ sai
				}
			}
			else// Không có cấm cờ
			{
				if (CTO[i][j].BCoBom)
				{
					veO(j, i, 9);// Hiện bom ẩn
				}
			}
		}
	}
	BTrangThaiChoiGame = false;
	xoaMang2ChieuDong();
	STrang = 4;
	deleteRow(4, 1);
	veTrangThaiChoiGame(3, 3, 0);// Trạng thái thua
}
void xuLyPhim(KEY_EVENT_RECORD key)
{
	if (key.bKeyDown)// nếu có nhấn phím
	{
		switch (key.wVirtualKeyCode)
		{
		case VK_UP:// Phím lên
			//cout << "\nMui ten di len";
			switch (STrang)
			{
			case 1: // Menu Chinh
				if (STongMuc == 4)
				{
					if (SViTriChon == 0)
					{
						SViTriChon = STongMuc - 1;
					}
					else
					{
						SViTriChon -= 1;
					}
					veMenuChinh(SViTriChon);
				}
				break;
			case 2: // Menu cấp độ
				if (STongMuc == 4)
				{
					if (SViTriChon == 0)
					{
						SViTriChon = STongMuc - 1;
					}
					else
					{
						SViTriChon -= 1;
					}
					veMenuCapDo(SViTriChon);
				}
				break;
			case 3: // Menu chơi game
				if (BTrangThaiChoiGame)
				{
					BSuDungPhim = true;
					CViTriConTro.Y = ((CViTriConTro.Y == 0) ? CTBang.SDong - 1 : CViTriConTro.Y - 1);
					veBang();
				}
				break;
			case 4: // Trang thua
				veTrangThaiChoiGame(3, 3, (SViTriChon== 0)? 1 : 0);
				break;
			case 5: // Trang thang
				veTrangThaiChoiGame(2, 2, (SViTriChon == 0) ? 1 : 0);
				break;
			}
			break;
		case VK_DOWN:// Phím xuống
			//cout << "\nMui ten di xuong";
			switch (STrang)
			{
			case 1: // Menu Chinh
				if (STongMuc == 4)
				{
					if (SViTriChon == STongMuc - 1)
					{
						SViTriChon = 0;
					}
					else
					{
						SViTriChon += 1;
					}
					veMenuChinh(SViTriChon);
				}
				break;
			case 2: // Menu cấp độ
				if (STongMuc == 4)
				{
					if (SViTriChon == STongMuc - 1)
					{
						SViTriChon = 0;
					}
					else
					{
						SViTriChon += 1;
					}
					veMenuCapDo(SViTriChon);
				}
				break;
			case 3: // Menu chơi game
				if (BTrangThaiChoiGame)
				{
					BSuDungPhim = true;
					CViTriConTro.Y = ((CViTriConTro.Y == CTBang.SDong - 1) ? 0: CViTriConTro.Y + 1);
					veBang();
				}
				break;
			case 4: // Trang thua
				veTrangThaiChoiGame(3, 3, (SViTriChon== 0)? 1:0);
				break;
			case 5: // Trang thang
				veTrangThaiChoiGame(2, 2, (SViTriChon == 0) ? 1 : 0);
				break;
			}
			break;
		case VK_LEFT:// Phím trái
			//cout << "\nMui ten qua trai";
			if (BTrangThaiChoiGame)
			{
				BSuDungPhim = true;
				CViTriConTro.X = ((CViTriConTro.X == 0) ? CTBang.SCot - 1 : CViTriConTro.X - 1);
				veBang();
			}
			break;
		case VK_RIGHT:// Phím phải
			//cout << "\nMui ten qua phai";
			if (BTrangThaiChoiGame)
			{
				BSuDungPhim = true;
				CViTriConTro.X = ((CViTriConTro.X == CTBang.SCot - 1) ? 0 : CViTriConTro.X + 1);
				veBang();
			}
			break;
		case VK_RETURN:// Phím enter
			//cout << "\nEnter";
			switch (STrang)
			{
			case 1: // Menu Chinh
				if (SViTriChon == 0)
				{
					STrang = 2;
					deleteRow(4, 5);
					veMenuCapDo(0);
				}
				else if (SViTriChon == 1)// Trang bảng điểm
				{

				}
				else if (SViTriChon == 2)// Trang thông tin
				{

				}
				else if (SViTriChon == 3)// Thoát
				{
					exit(0);// thoát chương trình	
				}
				break;
			case 2: // Menu cấp độ
				if (SViTriChon == 0)// mức dễ
				{
					STrang = 3;// trang chơi game
					deleteRow(4, 10);
					khoiTao(9, 9, 10);
				}
				else if (SViTriChon == 1)// mức trung bình
				{
					STrang = 3;// trang chơi game
					deleteRow(4, 10);
					khoiTao(16, 16, 40);
				}
				else if (SViTriChon == 2)// Mức khó
				{
					STrang = 3;// trang chơi game
					deleteRow(4, 10);
					khoiTao(24, 24, 99);
				}
				else if (SViTriChon == 3)// Thoát
				{
					STrang = 1; // cập nhật lại menu chính
					deleteRow(4, 10);
					veMenuChinh(0);
				}
				break;
			case 4: // Trang thua
				if (SViTriChon)
				{
					STrang = 1;// trở về menu chính
					deleteRow(3, heightConSoLe - 3);
					veMenuChinh(0);
				}
				else
				{
					STrang = 3;// Trang chơi game
					deleteRow(3, heightConSoLe - 3);
					khoiTao(CTBang.SDong, CTBang.SCot, CTBang.SSoBom);
				}
				break;
			case 5: // Trang thang
				break;
			case 6:// Trang luu game
				if (SViTriChon)
				{
					STrang = 1;// trở về menu chính
					deleteRow(3, heightConSoLe - 3);
					veMenuChinh(0);
				}
				else
				{
					// Lưu game -> Xử lý file
				}
				break;
			}
			break;
		case VK_ESCAPE:// phím Esc
			//cout << "\nThoat";
			switch (STrang)
			{
			case 1: // Menu Chinh
					exit(0);// thoát chương trình	
					break;
			case 2: // Menu cấp độ
					STrang = 1; // cập nhật lại menu chính
					deleteRow(4, 10);
					veMenuChinh(0);
					break;
			case 3:
				STrang = 6;
				veTrangThaiChoiGame(1, 1, 0);
				break;
			case 4: // Trang thua
			case 5: // Trang thang
				STrang = 2;
				deleteRow(3, heightConSoLe - 3);
				veMenuCapDo(0);
				break;
			}
			break;
		case 0x5A:// phím Z- Lick trái-Mở ô
			//cout << "\nLick trai";
			lickTrai(CViTriConTro.Y, CViTriConTro.X);
			break;
		case 0x58:// phím X- Lick phải- cấm cờ
			//cout << "\nLick phai";
			lickPhai(CViTriConTro.Y, CViTriConTro.X);
			break;
		}
	}
}
void xuLySuKien()
{
	while (1)
	{
		// typedef unsigned long DWORD;
		DWORD DWNumberOfEvents = 0; // Lưu lại sự kiện hiện tại
		DWORD DWNumberOfEventsRead = 0;// Lưu lại số lượng sự kiện đã được lọc

		// typedef PVOID HANDLE;
		// typedef void *PVOID;
		HANDLE HConsoleInput = GetStdHandle(STD_INPUT_HANDLE);// Thiết bị đầu vào
		// typedef DWORD *LPDWORD;
		GetNumberOfConsoleInputEvents(HConsoleInput, &DWNumberOfEvents);// Đặt sự kiện đầu vào của giao diện cho biến DWNumberOfEvents

		if (DWNumberOfEvents)// Nếu như có sự kiện
		{
			INPUT_RECORD *IREventbuffer = new INPUT_RECORD[DWNumberOfEvents];
			ReadConsoleInput(HConsoleInput, IREventbuffer, DWNumberOfEvents, &DWNumberOfEventsRead);// Thì đặt các sự kiện được lưu vào con trỏ IREventbuffer

			// Chạy vòng lặp để đọc sự kiện
			for (DWORD i = 0; i < DWNumberOfEvents; ++i)
			{
				if (IREventbuffer[i].EventType == KEY_EVENT)// Nếu là sử lý sự kiện phím
				{
					xuLyPhim(IREventbuffer[i].Event.KeyEvent);
				}
				//else if (IREventbuffer[i].EventType == MOUSE_EVENT)// Nếu là sử lý sự kiện chuột
				//{

				//}
			}
		}
	}
}

void veTieuDeGame()
{
	short i;
	for (i = 0; i < widthConSoLe; i++)
	{
		cout << "-";
	}

	setColorBGTextXY(widthConSoLe / 2 - 7, 1, 2, 0, "GAME DO MIN\n");

	setColor(7);

	for (i = 0; i < widthConSoLe; i++)
	{
		cout << "-";
	}
}
void veTrangThaiChoiGame(short STrangThai, short SCheDo, short SInDex)//
{
	SViTriChon = SInDex;
	STongMuc = 2;

	setColorBGTextXY(1, 3, 15, 0, "BAN DO: ");
	cout << CTBang.SDong << "x" << CTBang.SCot;
	setColorBGTextXY(1, 4, 15, 0, "SO BOM: ");
	cout << CTBang.SSoBom - CTBang.SSoCo;

	// vẽ menu thắng thua
	LPSTR STRTextMenuCheDo;
	if (SCheDo == 1)
	{
		STRTextMenuCheDo = "  LUU LAI  ";
		setColorBGTextXY((widthConSoLe / 2) - (strlen(STRTextMenuCheDo) / 2), 3, 15, (SInDex == 0) ? 2 : 0, STRTextMenuCheDo);
	}
	
	if (SCheDo == 2)
	{
		STRTextMenuCheDo = "  LUU TEN  ";
		setColorBGTextXY((widthConSoLe / 2) - (strlen(STRTextMenuCheDo) / 2), 3, 15, (SInDex == 0) ? 2 : 0, STRTextMenuCheDo);
	}
	
	if (SCheDo == 3)
	{
		STRTextMenuCheDo = "  CHOI LAI  ";
		setColorBGTextXY((widthConSoLe / 2) - (strlen(STRTextMenuCheDo) / 2), 3, 15, (SInDex == 0) ? 2 : 0, STRTextMenuCheDo);
	}

	if (SCheDo >= 1)
	{
		STRTextMenuCheDo = "  THOAT  ";
		setColorBGTextXY((widthConSoLe / 2) - (strlen(STRTextMenuCheDo) / 2), 4, 15, (SInDex == 1) ? 2 : 0, STRTextMenuCheDo);
	}



	if (STrangThai == 1)// Đang chơi game
	{
		setColorBGTextXY(widthConSoLe - 22, 4, 15, 0, "TRANG THAI: DANG CHOI");
	}
	if (STrangThai == 2)// Thắng
	{
		setColorBGTextXY(widthConSoLe - 22, 4, 14, 0, "TRANG THAI: THANG");
	}
	if (STrangThai == 3)// Thua
	{
		setColorBGTextXY(widthConSoLe - 22, 4, 12, 0, "TRANG THAI: THUA");
	}

	cout << endl;

	setColor(7);
	short i;
	for (i = 0; i < widthConSoLe; i++)
	{
		cout << "-";
	}

}
void veMenuChinh(short SInDex)// vị trí đang chọn
{
	// cập nhật lại vị trí đang chọn và tổng mục của menu
	SViTriChon = SInDex;
	STongMuc = 4;

	// vẽ menu
	LPSTR STRTextMenuChinh = "  GAME MOI  ";
	setColorBGTextXY((widthConSoLe / 2) - (strlen(STRTextMenuChinh) / 2), 7, 15, (SInDex == 0) ? 2 : 0, STRTextMenuChinh);
	
	STRTextMenuChinh = "  BANG DIEM  ";
	setColorBGTextXY((widthConSoLe / 2) - (strlen(STRTextMenuChinh) / 2), 8, 15, (SInDex == 1) ? 2 : 0, STRTextMenuChinh);
	
	STRTextMenuChinh = "  THONG TIN  ";
	setColorBGTextXY((widthConSoLe / 2) - (strlen(STRTextMenuChinh) / 2), 9, 15, (SInDex == 2) ? 2 : 0, STRTextMenuChinh);

	STRTextMenuChinh = "  THOAT  ";
	setColorBGTextXY((widthConSoLe / 2) - (strlen(STRTextMenuChinh) / 2), 10, 15, (SInDex == 3) ? 2 : 0, STRTextMenuChinh);
}
void veMenuCapDo(short SInDex)// vị trí đang chọn
{
	// cập nhật lại vị trí đang chọn và tổng mục của menu
	SViTriChon = SInDex;
	STongMuc = 4;

	LPSTR STRTextMenuChinh = "CHON CAP DO";
	setColorBGTextXY((widthConSoLe / 2) - (strlen(STRTextMenuChinh) / 2), 4, 15, 0, "CHON CAP DO");


	// vẽ menu
	STRTextMenuChinh = "  DE (9 * 9 VA 10 BOM)  ";
	setColorBGTextXY((widthConSoLe / 2) - (strlen(STRTextMenuChinh) / 2), 7, 15, (SInDex == 0) ? 2 : 0, STRTextMenuChinh);

	STRTextMenuChinh = "  TRUNG BINH (16 * 16 VA 40 BOM)  ";
	setColorBGTextXY((widthConSoLe / 2) - (strlen(STRTextMenuChinh) / 2), 8, 15, (SInDex == 1) ? 2 : 0, STRTextMenuChinh);

	STRTextMenuChinh = "  KHO (24 * 24 VA 99 BOM)  ";
	setColorBGTextXY((widthConSoLe / 2) - (strlen(STRTextMenuChinh) / 2), 9, 15, (SInDex == 2) ? 2 : 0, STRTextMenuChinh);

	STRTextMenuChinh = "  QUAY LAI  ";
	setColorBGTextXY((widthConSoLe / 2) - (strlen(STRTextMenuChinh) / 2), 10, 15, (SInDex == 3) ? 2 : 0, STRTextMenuChinh);
}