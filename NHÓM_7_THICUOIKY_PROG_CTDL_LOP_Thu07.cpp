#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct GiaiThuong
{
	char tenGT[40];
	int namGT;
};
struct DauSach
{
	char maSSach[7];
	char tenSach[40];
	char tacGia[30];
	int namXB;
	int soLuongSach;
	int soLuongGT;
	GiaiThuong *gt = NULL;
};

struct BST
{
	DauSach data;
	BST *left;
	BST *right;
	BST *parent;
};


void ThemDauSachVaoBST(BST** T, DauSach data);
void XuatDanhSach2(DauSach ds[], int soLuong);
void Init(BST *&T);
void Menu();
void SapXepDanhSachTheoNam(DauSach ds[], int n);
void DanhSachDauSachCungTen(BST *x, char k[], DauSach ds[], int &n);
void TongSoSach(BST *T, int &tong);
void ThemSachCoThuong(BST *&T, char mss[], int luaChonCon);
void NhapThongTinGT(GiaiThuong &gt);
void XuatThongTinGiaiThuong(BST *T, char mss[]);
BST* TimDauSachTheoMaSSach(BST *T, char mss[]);
void XoaDauSachTheoMaSSach(BST *&T, char mss[]);
BST *NutMin(BST *x);
BST *SuccessorCuaMotNut(BST *x);
BST *XoaMotNut(BST **T, BST *z);
void XuatDanhSach7(DauSach ds[], int soLuong);
void DanhSachDauSachCungNamvaTenTacGia(BST *x,int nam, char tenTG[], int &n, DauSach ds[]);
void GhiBST(BST *T, FILE *fptr);
void DocBST(BST *&T, FILE *fptr);
void RutGonChuoi(char s[]);
bool KiemTraTrong(BST *T);
void NhapDauSach(DauSach &p);
bool KiemTraTrung(BST *T, DauSach x);
void GiaiPhongBST(BST *&T, BST *p);
void GiaiPhongGiaiThuong(DauSach *&p);
void DemSoLuongDauSach(BST* T, int& count);

int main()
{
	Menu();	
	return 0;
}
void Menu()
{
	DauSach ds[100], p;
	char duongDan[1000];
	int i, n, tongSach, nam,current;
	int luaChon, luaChonCon;
	char s[30], mss[7], tenTG[30];
	FILE *fptr, *f;
	BST *T;
	Init(T);
	
	while(1)
	{		
		system("cls");
	
		printf("\t\t\t ======================================QUAN LY THU VIEN======================================\n");
		printf("\t\t\t | 1. Them cac dau sach.                                                                    |\n");
		printf("\t\t\t | 2. Tim kiem theo ten sach va in thong tin ma so sach, tac gia, nam xuat ban, so luong.   |\n");
		printf("\t\t\t | 3. Tong so sach co trong thu vien.                                                       |\n");
		printf("\t\t\t | 4. Them thong tin giai thuong cho mot dau sach.                                          |\n");
		printf("\t\t\t | 5. In thong tin cac giai thuong cua mot dau sach.                                        |\n");
		printf("\t\t\t | 6. Xoa mot dau sach.                                                                     |\n");
		printf("\t\t\t | 7. Tim kiem theo nam xuat ban, ten tac gia va in thong tin ma sach ten sach.             |\n");
		printf("\t\t\t | 8. Luu danh sach.                                                                        |\n");
		printf("\t\t\t | 9. Mo file da co.                                                                        |\n");
		printf("\t\t\t | 0. Thoat chuong trinh.                                                                   |\n");
		printf("\t\t\t ============================================================================================\n\n");
		printf("	Moi ban nhap lua chon: ");
		scanf("%d", &luaChon);
		printf("\n");
		fflush(stdin);
		
		switch(luaChon)
		{
			case 1:
				n = 0,current = 0;
				printf("Nhap so luong sach can them: ");
				scanf("%d", &n);
				DemSoLuongDauSach(T,current);
				if(n + current > 100)
				{
					printf("\n\tTHONG BAO LOI: Thu vien chi chua duoc toi da 100 dau sach!!!. Dang con trong %d dau sach\n", 100 - current);
					break;
				}
				for(i=0; i<n; i++)
				{
					printf("\n\t=======Nhap thong tin dau sach=======\n");
					NhapDauSach(p);
					ThemDauSachVaoBST(&T, p);
					printf("\n");
				}
				break;
			case 2:
				if(KiemTraTrong(T) == true)
				{
					printf("\n\tTHONG BAO: Danh sach trong\n");
					break;
				}
				n = 0;				
				printf("\nNhap ten sach can tim: ");
				gets(s);
				
				DanhSachDauSachCungTen(T, s, ds, n);
				if(n==0)
				{
					printf("\n\tTHONG BAO: Khong tim thay ten sach ban da nhap\n");
					break;
				}
				SapXepDanhSachTheoNam(ds, n);
				XuatDanhSach2(ds, n);
				
				break;
			case 3:
				tongSach = 0;
				TongSoSach(T, tongSach);
				printf("THONG BAO: So sach co trong thu vien la: %d\n", tongSach);
				break;
			case 4:
				if(KiemTraTrong(T) == true)
				{
					printf("\n\tTHONG BAO: Danh sach trong\n");
					break;
				}
				printf("\n\tThem moi nhan phim 1, them noi tiep nhan phim 0. Moi ban nhap: ");
				scanf("%d", &luaChonCon);
				
				printf("\nNhap ma sach co thuong: ");
				fflush(stdin);
				gets(mss);				
				
				ThemSachCoThuong(T, mss, luaChonCon);
				break;
			case 5:
				if(KiemTraTrong(T) == true)
				{
					printf("\n\tTHONG BAO: Danh sach trong\n");
					break;
				}
				printf("Nhap ma so sach: ");
				fflush(stdin);
				gets(mss);
				XuatThongTinGiaiThuong(T, mss);
				break;
			case 6:
				if(KiemTraTrong(T) == true)
				{
					printf("\n\tTHONG BAO: Danh sach trong\n");
					break;
				}
				printf("Nhap ma so sach can xoa: ");
				fflush(stdin);
				gets(mss);
				XoaDauSachTheoMaSSach(T, mss);
				break;
			case 7:
				if(KiemTraTrong(T) == true)
				{
					printf("\n\tTHONG BAO: Danh sach trong\n");
					break;
				}
				n = 0;
				
				printf("Nhap nam: ");
				scanf("%d", &nam);
				
				printf("Nhap ten tac gia: ");
				fflush(stdin);
				gets(tenTG);
				
				DanhSachDauSachCungNamvaTenTacGia(T, nam, tenTG, n, ds);
				if(n!=0)
					XuatDanhSach7(ds, n);
				else
					printf("\n\tTHONG BAO: Khong tim thay dau sach co nam va ten tac gia ma ban vua nhap\n");
				break;
			case 8:
				luaChonCon = -1;
				printf("Nhap duong dan de luu file: ");
				fflush(stdin);
				gets(duongDan);
				strcat(duongDan, ".dat");
				
				f = fopen(duongDan,"r");
				if(f!=NULL)
				{
					printf("\n\tTHONG BAO: File da ton tai. Ghi moi nhan phim 1, huy ghi nhan phim 0. Moi ban nhap lua chon: ");
					scanf("%d", &luaChonCon);
				}
				fclose(f);
				
				if(luaChonCon==0)
				{
					printf("\n\tTHONG BAO: Ban da huy ghi file\n");
					break;
				}
				else
				{
					fptr = fopen(duongDan,"w");
					if(fptr == NULL)
					{
						printf("\n\tTHONG BAO LOI: Loi mo file.\n");
						break;
					}			
					GhiBST(T,fptr);
					printf("\n\tTHONG BAO: Ghi thanh cong\n");
					fclose(fptr);
					break;					
				}
				break;
			case 9:
				printf("\tThem moi nhan phim 1, them tiep nhan phim 0. Moi ban nhap lua chon: ");
				scanf("%d", &luaChonCon);
				
				printf("\nNhap duong dan de mo file: ");
				fflush(stdin);
				gets(duongDan);
				strcat(duongDan, ".dat");
				
				fptr = fopen(duongDan,"r");
				if(fptr == NULL)
				{
					printf("\n\tTHONG BAO LOI: Loi mo file\n");
					break;
				}
				if(luaChonCon == 0)
					DocBST(T,fptr);
				else
				{
					GiaiPhongBST(T, T);
					DocBST(T, fptr);
				}
				fclose(fptr);
				break;
			case 0:
				printf("\n\tTam biet ban. Chuc ban mot ngay tot lanh.\n");
				return;
		}
		
		system("pause");
	}
}
void Init(BST *&T)
{
	T = NULL;
}

void DemSoLuongDauSach(BST* T, int& count)
{
	BST* p;
	p = T;
	if (p != NULL)
	{
		DemSoLuongDauSach(p->left, count);
			count++;
		DemSoLuongDauSach(p->right, count);
	}
}

void NhapDauSach(DauSach &p)
{
	printf("\tNhap ma so sach: ");
	fflush(stdin);	// xoa bo nho dem
	gets(p.maSSach); // doc cho toi khi gap dau cach
	
	printf("\tNhap ten sach: ");
	fflush(stdin);
	gets(p.tenSach);
	
	printf("\tNhap ten tac gia: ");
	fflush(stdin);
	gets(p.tacGia);
	
	printf("\tNhap nam xuat ban: ");
	scanf("%d", &p.namXB);
	
	printf("\tNhap so luong sach: ");
	scanf("%d", &p.soLuongSach);
}

bool KiemTraTrung(BST *T, DauSach x)
{
	while (T != NULL && strcmp(T->data.maSSach, x.maSSach) != 0)
	{
		if (strcmp(x.maSSach, T->data.maSSach) < 0)
			T = T->left;
		else
			T = T->right;
	}
	if(T!=NULL)
		return true;
	return false;
}

void ThemDauSachVaoBST(BST** T, DauSach data)
{
	BST* x, * y, * z;
	if(KiemTraTrung(*T, data) == true)
	{
		printf("\n\tTHONG BAO LOI: Them that bai. gia tri ma sach bi trung !!!\n");
		return;
	}
	
	z = (BST*)malloc(sizeof(BST));
	if(z==NULL)
	{
		printf("\n\tTHONG BAO LOI: Them dau sach that bai. Khong du bo nho !!!\n");
		return;
	}
	z->data = data; z->left = NULL; z->right = NULL;
	y = NULL;
	x = *T;
	while (x != NULL)
	{
		y = x;
		if (strcmp(z->data.maSSach, x->data.maSSach) < 0)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if (y == NULL) // Tree is empty
		*T = z;
	else if (strcmp(z->data.maSSach, y->data.maSSach) < 0)
		y->left = z;
	else
		y->right = z;
	printf("\n\tTHONG BAO: %s them thanh cong\n", data.maSSach);
}

bool KiemTraTrong(BST *T)
{
	if(T==NULL)
		return true;
	return false;
}

void DanhSachDauSachCungTen(BST *x,char k[], DauSach ds[], int &n)
{
	if (x != NULL) 
	{
		DanhSachDauSachCungTen(x->left,k, ds, n);
		if(strcmp(x->data.tenSach, k)==0)
		{
			ds[n]=x->data;
			n++;
		}
		DanhSachDauSachCungTen(x->right, k, ds, n);
	}
}

void SapXepDanhSachTheoNam(DauSach ds[], int n)
{
	int i, j;
	DauSach t;
	for (i = 1 ; i < n ; i++ )
	{
		j = i; 
		t = ds[j];
		while ( j > 0 && t.namXB < ds[j-1].namXB ) 
		{
			ds[j] = ds[j-1];
			j--;
		}
		ds[j] = t;
	}
} 

void XuatDanhSach2(DauSach ds[], int soLuong)
{
	int i;
	printf("\n\tKET QUA: tim thay %d dau sach\n", soLuong);
	printf("\n%-10s", "Ma sach");	printf("%-35s", "Tac gia"); printf("%-20s", "Nam xuat ban"); printf("%-10s\n", "So luong");
	for(i=0; i<soLuong; i++)
	{
		printf("%-10s", ds[i].maSSach);
		printf("%-35s", ds[i].tacGia);
		printf("%-20d", ds[i].namXB);
		printf("%-10d\n", ds[i].soLuongSach);
	}
	printf("\n");
}

void TongSoSach(BST *T, int &tong)
{
	if (T != NULL) 
	{
		TongSoSach(T->left, tong);
		tong += T->data.soLuongSach;
		TongSoSach(T->right, tong);
	}
}

BST* TimDauSachTheoMaSSach(BST *T, char mss[])
{
	BST *p = NULL;
	while (T != NULL && strcmp(T->data.maSSach, mss) != 0)
	{
		if (strcmp(mss, T->data.maSSach) < 0)
			T = T->left;
		else
			T = T->right;
	}
	p = T;
	return p;
}

void NhapThongTinGT(GiaiThuong &gt)
{
	printf("\n\t=========== Nhap thong tin giai thuong ===========\n");
	printf("\tNhap ten giai thuong: ");
	fflush(stdin);
	gets(gt.tenGT);
		
	printf("\tNhap nam nhan giai thuong: ");
	scanf("%d", &gt.namGT);
	printf("\n");
}

void ThemSachCoThuong(BST *&T, char mss[], int luaChonCon)
{
	BST *p;
	GiaiThuong *x;	
	int i, n;
	
	p = TimDauSachTheoMaSSach(T, mss);
	if(p==NULL)
	{
		printf("\n\tTHONG BAO: Khong tim thay ma so sach ban da nhap\n");
		return;
	}
	
	printf("Nhap so giai thuong: ");
	scanf("%d", &n);
	
	if(p->data.soLuongGT != 0 && luaChonCon == 0) //0 noi tiep, 1 lam moi
	{
		x = p->data.gt;
		
		p->data.soLuongGT = p->data.soLuongGT + n;
		
		p->data.gt = (GiaiThuong*)malloc(p->data.soLuongGT*sizeof(GiaiThuong));
		for(i=0; i<p->data.soLuongGT - n; i++)
		{
			strcpy(p->data.gt[i].tenGT, x[i].tenGT);
			p->data.gt[i].namGT = x[i].namGT; //them [i]
		}
		for(i=i; i< p->data.soLuongGT; i++)
			NhapThongTinGT(p->data.gt[i]);
		
	}
	else
	{
		p->data.soLuongGT = n;
		p->data.gt = (GiaiThuong*)malloc(n*sizeof(GiaiThuong));
		for(i = 0; i<n; i++)
			NhapThongTinGT(p->data.gt[i]);
	}
	
	printf("\n\tTHONG BAO: Them thong tin giai thuong thanh cong\n");
}

void XuatThongTinGiaiThuong(BST *T, char mss[])
{
	int i;
	BST *p = TimDauSachTheoMaSSach(T, mss);
	if(p==NULL)
	{
		printf("\n\tTHONG BAO: Khong tim thay ma so sach ban da nhap\n");
		return;
	}
	if(p->data.soLuongGT>0)
	{
		printf("\n\tKET QUA: %s co %d giai thuong\n", p->data.maSSach, p->data.soLuongGT);
		printf("\n%-45s", "Ten giai thuong"); printf("%-10s\n", "Nam nhan giai");
		for(i = 0; i<p->data.soLuongGT; i++)
		{
			printf("%-45s", p->data.gt[i].tenGT);
			printf("%-10d\n", p->data.gt[i].namGT);
		}
	}
	else
		printf("\n\tTHONG BAO: Khong co giai thuong\n");
}

BST *NutMin(BST *x)
{
	while (x->left != NULL) 
		x = x->left;
	return x;
}
BST *SuccessorCuaMotNut(BST *x)
{ 
	BST *y;
	if (x->right != NULL) 
		return NutMin(x->right);
	y = x->parent;
	while ((y != NULL) && (x == y->right))
	{
		x = y; 
		y = y->parent;
	}
	return y;
}
BST *XoaMotNut(BST **T, BST *z)
{ 
	BST *x, *y;
	if ((z->left== NULL) || (z->right == NULL))  // TH node khong co con
		y = z;
	else 										// TH co con
		y = SuccessorCuaMotNut(z);  				// nut ke tiep nut can xoa
		
	if (y->left != NULL) 					
		x = y->left ;
	else 
		x = y->right ;
		
	if (x != NULL) 
		x->parent = y->parent;
		
	if (y->parent == NULL) 
		*T = x;
	else
		if (y == (y->parent)->left) 
			(y->parent)->left = x;
		else (y->parent)->right = x;
			if (y != z) 
				z->data = y->data; 
	
	return y;
}
void XoaDauSachTheoMaSSach(BST *&T, char mss[])
{
	BST *p = TimDauSachTheoMaSSach(T, mss);
	if(p==NULL)
	{
		printf("\n\tTHONG BAO: Khong tim thay ma so sach ban da nhap\n");
		return;
	}
	free(XoaMotNut(&T, p));
	printf("\n\tTHONG BAO: Xoa thanh cong !!!\n");
}

void DanhSachDauSachCungNamvaTenTacGia(BST *x, int nam, char tenTG[], int &n, DauSach ds[])
{
	if (x != NULL) 
	{
		DanhSachDauSachCungNamvaTenTacGia(x->left,nam, tenTG, n,ds);
		if(strcmp(x->data.tacGia, tenTG)==0 && x->data.namXB == nam)
		{
			ds[n]=x->data;
			n++;
		}
		DanhSachDauSachCungNamvaTenTacGia(x->right,nam, tenTG, n,ds);
	}
}

void XuatDanhSach7(DauSach ds[], int soLuong)
{
	int i;
	printf("\n\tKET QUA: co %d dau sach\n", soLuong);
	printf("\n%-10s", "Ma sach"); printf("%-45s\n", "Ten sach");
	for(i=0; i<soLuong; i++)
	{
		printf("%-10s", ds[i].maSSach);
		printf("%-45s\n", ds[i].tenSach);
	}
	printf("\n");
}

void RutGonChuoi(char s[])
{
	int i, j = 0;
	int vtriCuoi= strlen(s) - 1;
	
	while(s[vtriCuoi] == ' ')
		vtriCuoi--;
	s[vtriCuoi+1] = '\0';
	while(s[i] == ' ')
		i++;
	for(i=i; i<= vtriCuoi+1; i++)
		s[j++] = s[i];
}
void GhiBST(BST *T, FILE *fptr)
{
	int i = 0;
	if(T != NULL)
	{
		GhiBST(T->left, fptr);
		fprintf(fptr,"%-10s", T->data.maSSach);
		fprintf(fptr,"%-45s", T->data.tenSach);
		fprintf(fptr,"%-35s", T->data.tacGia);
		fprintf(fptr,"%-10d", T->data.namXB);
		fprintf(fptr,"%-10d", T->data.soLuongSach);
		fprintf(fptr,"%-10d", T->data.soLuongGT);
		while(i<T->data.soLuongGT)
		{										
			fprintf(fptr,"%-45s", T->data.gt[i].tenGT);
			fprintf(fptr,"%-10d", T->data.gt[i].namGT);
			i++;
		}
		fprintf(fptr, "\n");
		GhiBST(T->right, fptr);
	}
}

void GiaiPhongGiaiThuong(DauSach *&p)
{
	if(p->gt != NULL)
	{
		free(p->gt);
		p->soLuongGT = 0;
	}
}
void GiaiPhongBST(BST *&T, BST *p)
{
	if (p != NULL) 
	{
		GiaiPhongBST(T, p->left);
		GiaiPhongBST(T, p->right);
		free(XoaMotNut(&T, p));
	}
}

void DocBST(BST *&T, FILE *fptr)
{
	char du[20];
	DauSach p;
	int i, viTriDauDong;
	fseek(fptr, 0, SEEK_END);		// di chuyen con tro den cuoi file
	int vtriCuoiFile = ftell(fptr); // lay vi tri cuoi file
	rewind(fptr);					// di chuyen con tro ve dau file

	while(ftell(fptr) < vtriCuoiFile) 
	{
		i = 0;
		viTriDauDong = ftell(fptr);
		
		fgets(p.maSSach, 7, fptr); 
		RutGonChuoi(p.maSSach);
		fseek(fptr, 4, SEEK_CUR);  
		
		fgets(p.tenSach, 40, fptr);	
		RutGonChuoi(p.tenSach);	
		fseek(fptr, 6, SEEK_CUR);
		
		fgets(p.tacGia, 30, fptr);
		RutGonChuoi(p.tacGia);
		fseek(fptr, 6, SEEK_CUR);
		
		fscanf(fptr, "%d", &p.namXB);
				
		fscanf(fptr, "%d", &p.soLuongSach);
		
		fscanf(fptr, "%d", &p.soLuongGT);		
		
		if(p.soLuongGT>0)
		{
			p.gt = (GiaiThuong*)malloc(p.soLuongGT*sizeof(GiaiThuong));
			fseek(fptr, viTriDauDong + 120, SEEK_SET);  // di chuyen con tro den vi tri giai thuong dau tien
		}
		
		while(i<p.soLuongGT)
		{
			fgets(p.gt[i].tenGT, 40, fptr);
			RutGonChuoi(p.gt[i].tenGT);
			
			fscanf(fptr, "%d", &p.gt[i].namGT);
			fseek(fptr, viTriDauDong + 120 + 55*(i+1), SEEK_SET);
	
			i++;
		}
	
		fgets(du, 20, fptr);  //doc den khi chuoi chua ky tu '\n'
	
		ThemDauSachVaoBST(&T, p);
	}
}
